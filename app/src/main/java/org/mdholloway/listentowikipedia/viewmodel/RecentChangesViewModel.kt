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
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.network.RecentChangesSseService

class RecentChangesViewModel : ViewModel() {

    companion object {
        private const val TAG = "RecentChangesViewModel"
    }

    // LiveData to hold a list of changes for a RecyclerView
    private val _recentChangesList = MutableLiveData<List<RecentChangeEvent>>(emptyList())
    val recentChangesList: LiveData<List<RecentChangeEvent>> = _recentChangesList

    private val sseService = RecentChangesSseService()
    private var recentChangesJob: Job? = null

    fun startListeningToRecentChanges() {
        if (recentChangesJob?.isActive == true) return

        recentChangesJob = sseService.listenToRecentChanges()
            .onEach { rc ->
                if (rc.wiki == "enwiki" && rc.namespace == 0 && rc.type == "edit") {
                    val diff = rc.length!!.new - (rc.length.old ?: 0)
                    if (diff > 0) {
                        Log.d(TAG, "${rc.user} added $diff bytes to ${rc.title}")
                        // _latestChange.postValue("${rc.user} added $diff bytes to ${rc.title}")
                    } else if (diff < 0) {
                        Log.d(TAG, "${rc.user} removed ${-diff} bytes from ${rc.title}")
                        // _latestChange.postValue("${rc.user} removed $diff bytes from ${rc.title}")
                    }
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