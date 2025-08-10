package org.mdholloway.listentowikipedia.repository

import kotlinx.coroutines.flow.Flow
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.network.SseManager
import javax.inject.Inject
import javax.inject.Singleton

@Singleton
class RecentChangesRepository
    @Inject
    constructor(
        private val sseManager: SseManager,
    ) {
        fun listenToRecentChanges(): Flow<RecentChangeEvent> = sseManager.recentChangeEvents
    }
