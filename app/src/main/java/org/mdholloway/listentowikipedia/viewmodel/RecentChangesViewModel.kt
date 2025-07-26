package org.mdholloway.listentowikipedia.viewmodel

import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.Job
import kotlinx.coroutines.flow.catch
import kotlinx.coroutines.flow.launchIn
import kotlinx.coroutines.flow.onEach
import org.mdholloway.listentowikipedia.network.RecentChangesSseService
import org.mdholloway.listentowikipedia.model.RecentChangeEvent

class RecentChangesViewModel : ViewModel() {

    companion object {
        private const val TAG = "RecentChangesViewModel"
        private const val MAX_DISPLAY_MESSAGES = 3
    }

    private val _latestRecentChangeEvent = MutableLiveData<RecentChangeEvent?>(null)
    val latestRecentChangeEvent: LiveData<RecentChangeEvent?> = _latestRecentChangeEvent

    private val _recentChangeTextList = MutableLiveData<List<String>>(emptyList())
    val recentChangeTextList: LiveData<List<String>> = _recentChangeTextList

    private val sseService = RecentChangesSseService()
    private var recentChangesJob: Job? = null

    fun startListeningToRecentChanges() {
        if (recentChangesJob?.isActive == true) return

        recentChangesJob = sseService.listenToRecentChanges()
            .onEach { event ->
                if (event.wiki == "enwiki" && event.namespace == 0 && event.type == "edit") {
                    _latestRecentChangeEvent.postValue(event)
                    addEventToTextList(event)
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
        val action = if (diff >= 0) "added" else "removed"
        val bytes = Math.abs(diff)
        return "${event.user} $action $bytes bytes to ${event.title}"
    }

    fun stopListeningToRecentChanges() {
        recentChangesJob?.cancel()
        recentChangesJob = null
    }

    override fun onCleared() {
        super.onCleared()
        stopListeningToRecentChanges()
        sseService.close()
    }
}