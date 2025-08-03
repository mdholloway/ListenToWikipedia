package org.mdholloway.listentowikipedia.viewmodel

import android.app.Application
import android.util.Log
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.viewModelScope
import com.DspFaust.DspFaust
import kotlinx.coroutines.Job
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.launch
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.network.RecentChangesSseService
import kotlin.math.abs
import kotlin.math.exp
import kotlin.math.ln

class RecentChangesViewModel(application: Application) : AndroidViewModel(application) {

    companion object {
        private const val TAG = "RecentChangesViewModel"
        private const val MAX_DISPLAY_MESSAGES = 3
    }

    private val _latestRecentChangeEvent = MutableLiveData<RecentChangeEvent?>(null)
    val latestRecentChangeEvent: LiveData<RecentChangeEvent?> = _latestRecentChangeEvent

    private val _recentChangeTextList = MutableLiveData<List<String>>(emptyList())
    val recentChangeTextList: LiveData<List<String>> = _recentChangeTextList

    private val sseService = RecentChangesSseService(application.applicationContext)
    private var recentChangesJob: Job? = null
    private val dsp = DspFaust()

    fun startListeningToRecentChanges() {
        if (recentChangesJob?.isActive == true) {
            Log.d(TAG, "Already listening to recent changes, skipping start.")
            return
        }

        // Attempt to start the DspFaust audio engine
        val started = dsp.start()
        if (!started) {
            Log.e(TAG, "DspFaust failed to start audio engine! Check RECORD_AUDIO permission and device state.")
            // Do not proceed if the audio engine couldn't start
            return
        }
        Log.i(TAG, "DspFaust audio engine started successfully.")

        // Set global parameters (these apply to all voices, unless overridden per voice)
        /* dsp.setParamValue("/Polyphonic/Voices/marimba/gain", 1.0f)
        dsp.setParamValue("/Polyphonic/Voices/marimba/exPos", 0.5f)
        dsp.setParamValue("/Polyphonic/Voices/marimba/exPos2", 1.0f)
        dsp.setParamValue("/Polyphonic/Voices/marimba/sharpness", 0.5f) */

        // --- TEMPORARY TEST: Play a fixed tone to confirm audio output ---
        //viewModelScope.launch {
            //Log.d(TAG, "Attempting to play a test tone for 1 second")
            //val testVoiceAddress = dsp.newVoice()
            //if (testVoiceAddress != 0L) {
                //dsp.setVoiceParamValue("/marimba/freq", testVoiceAddress, 440.0f) // A4 note
                //dsp.setVoiceParamValue("/marimba/gain", testVoiceAddress, 0.8f) // High gain for testing
                //dsp.setParamValue("/synth/gate", 1.0f) // Gate ON
                //dsp.keyOn(69, 100)
                //Log.d(TAG, "Test tone triggered")
                //delay(1000) // Play for 1 second
                //dsp.setParamValue("/synth/gate", 0.0f) // Gate OFF
                //dsp.keyOff(69)
                //Log.d(TAG, "Test tone released")
                //dsp.deleteVoice(testVoiceAddress) // Delete the voice
                // Log.d(TAG, "Test tone finished")
            //} else {
            //    Log.e(TAG, "Failed to allocate test voice.")
            //}
        //}
        // --- END TEMPORARY TEST ---

        recentChangesJob = sseService.listenToRecentChanges()
            .onEach { event ->
                if (event.wiki == "enwiki" && event.namespace == 0 && event.type == "edit") {
                    _latestRecentChangeEvent.postValue(event)
                    addEventToTextList(event)

                    // Calculate MIDI note based on byte difference
                    val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
                    val midiNote = calculateMidiNoteFromBytes(diff)

                    Log.d(TAG, "Playing MIDI note $midiNote for ${abs(diff)} byte difference in ${event.title}")
                    val voiceAddress = dsp.keyOn(midiNote, 100)
                    if (voiceAddress != 0L) { // Check if a voice was successfully allocated
                        Log.d(TAG, "New Faust voice allocated: $voiceAddress for event: ${event.title}")

                        // 5. Set parameters for the *individual voice*
                        //dsp.setVoiceParamValue("/marimba/freq", voiceAddress, freq)
                        //dsp.setVoiceParamValue("/marimba/gain", voiceAddress, 1.0f) // Set voice-specific gain
                        //dsp.setVoiceParamValue("/marimba/gate", voiceAddress, 1.0f) // Trigger the sound (gate ON)

                        //Log.d(TAG, "Triggering sound for ${event.title} with freq: $freq Hz, gate ON.")

                        // 2. CRITICAL: Turn the gate OFF after a short delay
                        // This allows the Faust instrument's internal envelope to play out
                        // and makes the voice available for reuse.
                        //viewModelScope.launch {
                            //delay(500) // Play sound for 0.5 seconds. Adjust this duration as needed.
                            //dsp.setVoiceParamValue("/marimba/gate", voiceAddress, 0.0f) // Gate OFF
                            //Log.d(TAG, "Released gate for voice: $voiceAddress")

                            // Optionally, delete the voice if you want to explicitly manage voice pool.
                            // If your Faust DSP handles voice recycling well with gate 0, you might not need to delete.
                            // If you run out of voices, uncomment and try.
                            // dsp.deleteVoice(voiceAddress)
                            // Log.d(TAG, "Deleted voice: $voiceAddress")}
                        //}
                    } else {
                        Log.e(TAG, "Failed to allocate new Faust voice. Is the DSP compiled with -nvoices and not out of voices?")
                    }
                }
            }
            .catch { e ->
                Log.e(TAG, "Error collecting recent changes", e)
            }
            .launchIn(viewModelScope)
    }

    private fun addEventToTextList(event: RecentChangeEvent) {
        val currentList = _recentChangeTextList.value.orEmpty().toMutableList()
        val formattedMessage = formatRecentChangeEventForDisplay(event)
        currentList.add(0, formattedMessage) // Add to the beginning
        if (currentList.size > MAX_DISPLAY_MESSAGES) {
            currentList.removeAt(currentList.size - 1) // Remove the oldest if over limit
        }
        _recentChangeTextList.postValue(currentList)
    }

    private fun formatRecentChangeEventForDisplay(event: RecentChangeEvent): String {
        val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
        val bytes = abs(diff)
        if (diff >= 0) {
            return "${event.user} added $bytes bytes to ${event.title}"
        } else {
            return "${event.user} removed $bytes bytes from ${event.title}"
        }
    }


    // Helper function to map byte differences to a MIDI note number
    private fun calculateMidiNoteFromBytes(byteDiff: Int): Int {
        val absDiff = abs(byteDiff)

        // Define your desired byte difference range and MIDI note range
        val minBytes = 1 // Smallest diff you want to map
        val maxBytes = 50000 // Largest diff you expect
        val minMidiNote = 36 // C2 (low but audible)
        val maxMidiNote = 96 // C7 (high and clear)

        // Clamp the byteDiff to stay within a reasonable range for mapping
        val clampedDiff = absDiff.coerceIn(minBytes, maxBytes)

        // Use logarithmic scaling for pitch perception
        // Map clampedDiff (log scale) to normalized 0-1 range
        val normalizedValue = (ln(clampedDiff.toFloat()) - ln(minBytes.toFloat())) / 
                             (ln(maxBytes.toFloat()) - ln(minBytes.toFloat()))

        // Map normalized 0-1 range to MIDI note range
        val midiNote = minMidiNote + (normalizedValue * (maxMidiNote - minMidiNote)).toInt()

        return midiNote.coerceIn(0, 127) // Ensure valid MIDI range
    }

    fun stopListeningToRecentChanges() {
        Log.i(TAG, "Stopping listening to recent changes and cancelling job.")
        recentChangesJob?.cancel()
        recentChangesJob = null
    }

    override fun onCleared() {
        super.onCleared()
        Log.i(TAG, "ViewModel onCleared. Ensuring audio engine and SSE service are stopped.")
        stopListeningToRecentChanges()
        dsp.stop()
        sseService.close()
    }
    
    // Helper function to check if a string is an IP address
    private fun isIpAddress(input: String): Boolean {
        val ipv4Pattern = "^([0-9]{1,3}\\.)+\\d{1,3}$".toRegex()
        val ipv6Pattern = "^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$".toRegex()
        return input.matches(ipv4Pattern) || input.matches(ipv6Pattern)
    }
}