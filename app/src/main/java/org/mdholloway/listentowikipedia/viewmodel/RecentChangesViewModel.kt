package org.mdholloway.listentowikipedia.viewmodel

import android.util.Log
import androidx.compose.ui.graphics.Color
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Job
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.launch
import org.mdholloway.listentowikipedia.audio.AudioManager
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.repository.RecentChangesRepository
import org.mdholloway.listentowikipedia.ui.state.CircleColors
import org.mdholloway.listentowikipedia.ui.state.DisplayCircle
import org.mdholloway.listentowikipedia.ui.state.RecentChangesUiState
import org.mdholloway.listentowikipedia.util.isIpAddress
import java.util.UUID
import javax.inject.Inject
import kotlin.math.abs
import kotlin.math.ln
import kotlin.random.Random

@HiltViewModel
class RecentChangesViewModel
    @Inject
    constructor(
        val repository: RecentChangesRepository,
    ) : ViewModel() {
        companion object {
            private const val TAG = "RecentChangesViewModel"
            private const val MAX_DISPLAY_MESSAGES = 3
            private const val CIRCLE_DISPLAY_DURATION_MS = 30000L
            private const val CLEANUP_INTERVAL_MS = 1000L
        }

        // Single source of truth for UI state
        private val _uiState = MutableStateFlow(RecentChangesUiState())
        val uiState: StateFlow<RecentChangesUiState> = _uiState.asStateFlow()

        private var recentChangesJob: Job? = null
        private var circleCleanupJob: Job? = null
        private var audioManager: AudioManager? = null

        init {
            startCircleCleanup()
        }

        private fun startCircleCleanup() {
            circleCleanupJob =
                viewModelScope.launch {
                    while (true) {
                        delay(CLEANUP_INTERVAL_MS)
                        cleanupOldCircles()
                    }
                }
        }

        private fun cleanupOldCircles() {
            val currentTime = System.currentTimeMillis()
            val currentState = _uiState.value
            val filteredCircles =
                currentState.displayCircles.filter {
                    currentTime - it.createdAt <= CIRCLE_DISPLAY_DURATION_MS
                }

            if (filteredCircles.size != currentState.displayCircles.size) {
                _uiState.value = currentState.copy(displayCircles = filteredCircles)
            }
        }

        private fun addCircleForEvent(event: RecentChangeEvent) {
            val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
            val radius = abs(diff).coerceIn(10, 240).toFloat()

            val color =
                when {
                    event.bot -> CircleColors.Bot
                    isIpAddress(event.user) -> CircleColors.Anonymous
                    else -> CircleColors.Registered
                }

            val randomX = Random.nextFloat()
            val randomY = Random.nextFloat()

            val newCircle =
                DisplayCircle(
                    id = UUID.randomUUID().toString(),
                    event = event,
                    x = randomX,
                    y = randomY,
                    radius = radius,
                    color = color,
                )

            val currentState = _uiState.value
            _uiState.value =
                currentState.copy(
                    displayCircles = currentState.displayCircles + newCircle,
                )
        }

        fun setAudioManager(audioManager: AudioManager) {
            this.audioManager = audioManager
        }

        fun startListeningToRecentChanges() {
            if (recentChangesJob?.isActive == true) {
                Log.i(TAG, "Already listening to recent changes, skipping start.")
                return
            }

            Log.i(TAG, "Starting to listen to recent changes")

            recentChangesJob =
                repository
                    .listenToRecentChanges()
                    .onEach { event ->
                        if (event.wiki == "enwiki" && event.namespace == 0 && event.type == "edit") {
                            // Calculate MIDI note based on byte difference
                            val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
                            val midiNote = calculateMidiNoteFromBytes(diff)
                            audioManager?.playNote(midiNote, 100)

                            addCircleForEvent(event)
                            addEventToTextList(event)
                        }
                    }.catch { e ->
                        Log.e(TAG, "Error collecting recent changes", e)
                    }.launchIn(viewModelScope)
        }

        private fun addEventToTextList(event: RecentChangeEvent) {
            val formattedMessage = formatRecentChangeEventForDisplay(event)
            val currentState = _uiState.value
            val currentList = currentState.recentChangeTexts.toMutableList()

            currentList.add(0, formattedMessage) // Add to the beginning
            if (currentList.size > MAX_DISPLAY_MESSAGES) {
                currentList.removeAt(currentList.size - 1) // Remove the oldest if over limit
            }

            _uiState.value = currentState.copy(recentChangeTexts = currentList)
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
            Log.i(TAG, "ViewModel onCleared.")
            stopListeningToRecentChanges()
            circleCleanupJob?.cancel()
        }
    }
