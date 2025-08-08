package org.mdholloway.listentowikipedia.repository

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.emptyFlow
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.network.SseManager
import javax.inject.Inject
import javax.inject.Singleton

@Singleton
class RecentChangesRepository
    @Inject
    constructor() {
        private var sseManager: SseManager? = null

        fun setSseManager(sseManager: SseManager) {
            this.sseManager = sseManager
        }

        fun listenToRecentChanges(): Flow<RecentChangeEvent> = sseManager?.recentChangeEvents ?: emptyFlow()
    }
