package org.mdholloway.listentowikipedia.viewmodel

import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.DspFaust.DspFaust
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.repository.RecentChangesRepository
import org.mdholloway.listentowikipedia.util.isIpAddress
import javax.inject.Inject
import kotlin.math.abs
import kotlin.math.ln

@HiltViewModel
class RecentChangesViewModel
    @Inject
    constructor(
        private val repository: RecentChangesRepository,
    ) : ViewModel() {
        companion object {
            private const val TAG = "RecentChangesViewModel"
            private const val MAX_DISPLAY_MESSAGES = 3
        }

        private val _latestRecentChangeEvent = MutableLiveData<RecentChangeEvent?>(null)
        val latestRecentChangeEvent: LiveData<RecentChangeEvent?> = _latestRecentChangeEvent

        private val _recentChangeTextList = MutableLiveData<List<String>>(emptyList())
        val recentChangeTextList: LiveData<List<String>> = _recentChangeTextList

        private var recentChangesJob: Job? = null
        private val dsp = DspFaust()

        fun startListeningToRecentChanges() {
            if (recentChangesJob?.isActive == true) {
                Log.i(TAG, "Already listening to recent changes, skipping start.")
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

            recentChangesJob =
                repository
                    .listenToRecentChanges()
                    .onEach { event ->
                        if (event.wiki == "enwiki" && event.namespace == 0 && event.type == "edit") {
                            // Calculate MIDI note based on byte difference
                            val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
                            val midiNote = calculateMidiNoteFromBytes(diff)
                            dsp.keyOn(midiNote, 100)

                            _latestRecentChangeEvent.postValue(event)
                            addEventToTextList(event)
                        }
                    }.catch { e ->
                        Log.e(TAG, "Error collecting recent changes", e)
                    }.launchIn(viewModelScope)
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
            val user = if (isIpAddress(event.user)) "An anonymous user" else event.user
            if (diff >= 0) {
                return "$user added $bytes bytes to ${event.title}"
            } else {
                return "$user removed $bytes bytes from ${event.title}"
            }
        }

        // Helper function to map byte differences to a MIDI note number
        private fun calculateMidiNoteFromBytes(byteDiff: Int): Int {
            val absDiff = abs(byteDiff)

            // Define your desired byte difference range and MIDI note range
            val minBytes = 1 // Smallest diff you want to map
            val maxBytes = 5000 // Largest diff you expect
            val minMidiNote = 36 // C2 (low but audible)
            val maxMidiNote = 96 // C7 (high and clear)

            // Clamp the byteDiff to stay within a reasonable range for mapping
            val clampedDiff = absDiff.coerceIn(minBytes, maxBytes)

            // Use logarithmic scaling for pitch perception
            // Map clampedDiff (log scale) to normalized 0-1 range
            val normalizedValue =
                (ln(clampedDiff.toFloat()) - ln(minBytes.toFloat())) /
                    (ln(maxBytes.toFloat()) - ln(minBytes.toFloat()))

            // Map normalized 0-1 range to MIDI note range (inverted: larger edits = lower notes)
            val midiNote = maxMidiNote - (normalizedValue * (maxMidiNote - minMidiNote)).toInt()

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
            repository.close()
        }
    }
