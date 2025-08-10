package org.mdholloway.listentowikipedia.repository

import app.cash.turbine.test
import com.google.common.truth.Truth.assertThat
import io.mockk.every
import io.mockk.mockk
import kotlinx.coroutines.flow.emptyFlow
import kotlinx.coroutines.flow.flowOf
import kotlinx.coroutines.test.runTest
import org.junit.Test
import org.mdholloway.listentowikipedia.model.Length
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.network.SseManager

class RecentChangesRepositoryTest {
    private val mockSseManager = mockk<SseManager>()
    private val repository = RecentChangesRepository(mockSseManager)

    @Test
    fun `listenToRecentChanges returns empty flow when SseManager returns empty`() =
        runTest {
            every { mockSseManager.recentChangeEvents } returns emptyFlow()

            repository.listenToRecentChanges().test {
                awaitComplete()
            }
        }

    @Test
    fun `listenToRecentChanges forwards events from SseManager`() =
        runTest {
            val testEvent =
                RecentChangeEvent(
                    type = "edit",
                    namespace = 0,
                    title = "Test Article",
                    comment = "Test edit",
                    timestamp = System.currentTimeMillis(),
                    user = "TestUser",
                    bot = false,
                    length = Length(old = 100, new = 150),
                    wiki = "enwiki",
                )

            every { mockSseManager.recentChangeEvents } returns flowOf(testEvent)

            repository.listenToRecentChanges().test {
                val receivedEvent = awaitItem()
                assertThat(receivedEvent).isEqualTo(testEvent)
                awaitComplete()
            }
        }

    @Test
    fun `listenToRecentChanges forwards multiple events`() =
        runTest {
            val event1 = createTestEvent("Article1")
            val event2 = createTestEvent("Article2")
            val event3 = createTestEvent("Article3")

            every { mockSseManager.recentChangeEvents } returns flowOf(event1, event2, event3)

            repository.listenToRecentChanges().test {
                assertThat(awaitItem()).isEqualTo(event1)
                assertThat(awaitItem()).isEqualTo(event2)
                assertThat(awaitItem()).isEqualTo(event3)
                awaitComplete()
            }
        }

    @Test
    fun `listenToRecentChanges handles empty flow from SseManager`() =
        runTest {
            every { mockSseManager.recentChangeEvents } returns emptyFlow()

            repository.listenToRecentChanges().test {
                awaitComplete()
            }
        }

    private fun createTestEvent(title: String = "Test Article") =
        RecentChangeEvent(
            type = "edit",
            namespace = 0,
            title = title,
            comment = "Test comment",
            timestamp = System.currentTimeMillis(),
            user = "TestUser",
            bot = false,
            length = Length(old = 100, new = 150),
            wiki = "enwiki",
        )
}
