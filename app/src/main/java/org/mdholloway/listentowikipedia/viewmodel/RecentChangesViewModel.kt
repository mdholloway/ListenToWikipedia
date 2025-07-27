package org.mdholloway.listentowikipedia.viewmodel

import android.app.Application
import android.util.Log
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import org.mdholloway.listentowikipedia.network.RecentChangesSseService
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.audio.OboeAudioPlayer
import kotlin.math.abs

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
    private val oboeAudioPlayer = OboeAudioPlayer()

    fun startListeningToRecentChanges() {
        if (recentChangesJob?.isActive == true) return

        recentChangesJob = sseService.listenToRecentChanges()
            .onEach { event ->
                if (event.wiki == "enwiki" && event.namespace == 0 && event.type == "edit") {
                    _latestRecentChangeEvent.postValue(event)
                    addEventToTextList(event)
                    
                    // Play sound
                    val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
                    oboeAudioPlayer.playEventSound(
                        diff = diff,
                        isBot = event.bot,
                        isIpAddress = isIpAddress(event.user)
                    )
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

    fun stopListeningToRecentChanges() {
        recentChangesJob?.cancel()
        recentChangesJob = null
    }

    override fun onCleared() {
        super.onCleared()
        stopListeningToRecentChanges()
        sseService.close()
        oboeAudioPlayer.release()
    }
    
    // Helper function to check if a string is an IP address
    private fun isIpAddress(input: String): Boolean {
        val ipv4Pattern = "^([0-9]{1,3}\\.)+\\d{1,3}$".toRegex()
        val ipv6Pattern = "^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$".toRegex()
        return input.matches(ipv4Pattern) || input.matches(ipv6Pattern)
    }
}