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

class RecentChangesViewModel : ViewModel() {

    companion object {
        private const val TAG = "RecentChangesViewModel"
    }

    private val _recentChangesList = MutableLiveData<List<String>>(emptyList())
    val recentChangesList: LiveData<List<String>> = _recentChangesList

    private val sseService = RecentChangesSseService()
    private var recentChangesJob: Job? = null

    fun startListeningToRecentChanges() {
        if (recentChangesJob?.isActive == true) return

        recentChangesJob = sseService.listenToRecentChanges()
            .onEach { event ->
                if (event.wiki == "enwiki" && event.namespace == 0 && event.type == "edit") {
                    val diff = (event.length?.new ?: 0) - (event.length?.old ?: 0)
                    val description = when {
                        diff > 0 -> "${event.user} added $diff bytes to ${event.title}"
                        diff < 0 -> "${event.user} removed ${-diff} bytes from ${event.title}"
                        else -> "${event.user} edited ${event.title} (no size change)"
                    }
                    val currentList = _recentChangesList.value ?: emptyList()
                    _recentChangesList.postValue(listOf(description) + currentList.take(19))
                }
            }
            .catch { e ->
                Log.e(TAG, "Error collecting recent changes", e)
            }
            .launchIn(viewModelScope)
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