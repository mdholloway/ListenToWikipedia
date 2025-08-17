package org.mdholloway.listentowikipedia.viewmodel

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import kotlinx.coroutines.launch
import org.mdholloway.listentowikipedia.audio.AudioManager
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.network.SseManager
import org.mdholloway.listentowikipedia.repository.RecentChangesRepository
import org.mdholloway.listentowikipedia.ui.state.CircleColors
import org.mdholloway.listentowikipedia.ui.state.ConnectionState
import org.mdholloway.listentowikipedia.ui.state.DisplayCircle
import org.mdholloway.listentowikipedia.ui.state.RecentChangesUiState
import org.mdholloway.listentowikipedia.util.isIpAddress
import java.util.UUID
import javax.inject.Inject
import kotlin.math.abs
import kotlin.random.Random

@HiltViewModel
class RecentChangesViewModel
    @Inject
    constructor(
        val repository: RecentChangesRepository,
        private val audioManager: AudioManager,
        private val sseManager: SseManager,
    ) : ViewModel() {
        companion object {
            private const val TAG = "RecentChangesViewModel"
            private const val MAX_DISPLAY_MESSAGES = 3
        }

        // Single source of truth for UI state
        private val _uiState = MutableStateFlow(RecentChangesUiState())
        val uiState: StateFlow<RecentChangesUiState> = _uiState.asStateFlow()

        private var recentChangesJob: Job? = null
        private var connectionStateJob: Job? = null

        fun removeCircle(circleId: String) {
            val currentState = _uiState.value
            val filteredCircles = currentState.displayCircles.filterNot { it.id == circleId }
            _uiState.value = currentState.copy(displayCircles = filteredCircles)
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

        fun startListeningToRecentChanges() {
            if (recentChangesJob?.isActive == true) {
                Log.i(TAG, "Already listening to recent changes, skipping start.")
                return
            }

            Log.i(TAG, "Starting to listen to recent changes")

            // Start listening to connection state changes
            connectionStateJob =
                sseManager.connectionState
                    .onEach { connectionState ->
                        _uiState.value = _uiState.value.copy(connectionState = connectionState)
                    }.launchIn(viewModelScope)

            recentChangesJob =
                repository
                    .listenToRecentChanges()
                    .onEach { event ->
                        if (event.wiki == "enwiki" && event.namespace == 0 && event.type == "edit") {
                            // Play sound based on edit size using Wikipedia's original algorithm
                            val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
                            val sizeBytes = abs(diff)
                            val isAddition = diff >= 0
                            audioManager.playWikipediaEdit(sizeBytes, isAddition)

                            addCircleForEvent(event)
                            addEventToTextList(event)
                        }
                    }.catch { e ->
                        Log.e(TAG, "Error collecting recent changes", e)
                        _uiState.value =
                            _uiState.value.copy(
                                connectionState =
                                    ConnectionState.Error(
                                        message = "Error processing events: ${e.message}",
                                        canRetry = true,
                                    ),
                            )
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

        fun stopListeningToRecentChanges() {
            Log.i(TAG, "Stopping listening to recent changes and cancelling job.")
            recentChangesJob?.cancel()
            recentChangesJob = null
            connectionStateJob?.cancel()
            connectionStateJob = null
        }

        fun retryConnection() {
            Log.i(TAG, "User requested connection retry")
            _uiState.value = _uiState.value.copy(isRetrying = true)
            sseManager.retryConnection(viewModelScope)
            // Reset retrying flag after a short delay
            viewModelScope.launch {
                kotlinx.coroutines.delay(1000)
                _uiState.value = _uiState.value.copy(isRetrying = false)
            }
        }

        override fun onCleared() {
            super.onCleared()
            Log.i(TAG, "ViewModel onCleared.")
            stopListeningToRecentChanges()
        }
    }
