package org.mdholloway.listentowikipedia.repository

import kotlinx.coroutines.flow.Flow
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.network.RecentChangesSseService
import javax.inject.Inject
import javax.inject.Singleton

@Singleton
class RecentChangesRepository
    @Inject
    constructor(
        private val sseService: RecentChangesSseService,
    ) {
        fun listenToRecentChanges(): Flow<RecentChangeEvent> = sseService.listenToRecentChanges()

        fun close() {
            sseService.close()
        }
    }
