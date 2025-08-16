package org.mdholloway.listentowikipedia.viewmodel

import androidx.arch.core.executor.testing.InstantTaskExecutorRule
import com.google.common.truth.Truth.assertThat
import io.mockk.every
import io.mockk.mockk
import io.mockk.verify
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.ExperimentalCoroutinesApi
import kotlinx.coroutines.flow.flowOf
import kotlinx.coroutines.test.StandardTestDispatcher
import kotlinx.coroutines.test.advanceUntilIdle
import kotlinx.coroutines.test.resetMain
import kotlinx.coroutines.test.runTest
import kotlinx.coroutines.test.setMain
import org.junit.After
import org.junit.Before
import org.junit.Rule
import org.junit.Test
import org.mdholloway.listentowikipedia.audio.AudioManager
import org.mdholloway.listentowikipedia.model.Length
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.network.SseManager
import org.mdholloway.listentowikipedia.repository.RecentChangesRepository
import org.mdholloway.listentowikipedia.testutil.AndroidLogRule
import org.mdholloway.listentowikipedia.ui.state.CircleColors

@OptIn(ExperimentalCoroutinesApi::class)
class RecentChangesViewModelTest {
    @get:Rule
    val instantExecutorRule = InstantTaskExecutorRule()

    @get:Rule
    val androidLogRule = AndroidLogRule()

    private val testDispatcher = StandardTestDispatcher()
    private val mockRepository = mockk<RecentChangesRepository>()
    private val mockAudioManager = mockk<AudioManager>(relaxed = true)
    private val mockSseManager = mockk<SseManager>(relaxed = true)

    private lateinit var viewModel: RecentChangesViewModel

    @Before
    fun setUp() {
        Dispatchers.setMain(testDispatcher)
        viewModel = RecentChangesViewModel(mockRepository, mockAudioManager, mockSseManager)
    }

    @After
    fun tearDown() {
        Dispatchers.resetMain()
    }

    @Test
    fun `initial state is empty`() {
        val initialState = viewModel.uiState.value
        assertThat(initialState.displayCircles).isEmpty()
        assertThat(initialState.recentChangeTexts).isEmpty()
    }

    @Test
    fun `startListeningToRecentChanges processes valid events`() =
        runTest {
            val testEvent =
                createTestEvent(
                    wiki = "enwiki",
                    namespace = 0,
                    type = "edit",
                    user = "TestUser",
                    length = Length(old = 100, new = 150),
                )

            every { mockRepository.listenToRecentChanges() } returns flowOf(testEvent)

            viewModel.startListeningToRecentChanges()
            advanceUntilIdle()

            val updatedState = viewModel.uiState.value

            // Verify circle was added
            assertThat(updatedState.displayCircles).hasSize(1)
            val circle = updatedState.displayCircles[0]
            assertThat(circle.event).isEqualTo(testEvent)
            assertThat(circle.radius).isEqualTo(50f) // abs(150 - 100)
            assertThat(circle.color).isEqualTo(CircleColors.Registered)

            // Verify text was added
            assertThat(updatedState.recentChangeTexts).hasSize(1)
            assertThat(updatedState.recentChangeTexts[0]).contains("TestUser added 50 bytes")

            // Verify audio was played with correct parameters (50 bytes addition)
            verify { mockAudioManager.playWikipediaEdit(50, true) }
        }

    @Test
    fun `startListeningToRecentChanges handles bot user correctly`() =
        runTest {
            val botEvent = createTestEvent(bot = true, user = "BotUser")

            every { mockRepository.listenToRecentChanges() } returns flowOf(botEvent)

            viewModel.startListeningToRecentChanges()
            advanceUntilIdle()

            val updatedState = viewModel.uiState.value
            val circle = updatedState.displayCircles[0]
            assertThat(circle.color).isEqualTo(CircleColors.Bot)
        }

    @Test
    fun `startListeningToRecentChanges handles anonymous user correctly`() =
        runTest {
            val anonymousEvent = createTestEvent(user = "192.168.1.1")

            every { mockRepository.listenToRecentChanges() } returns flowOf(anonymousEvent)

            viewModel.startListeningToRecentChanges()
            advanceUntilIdle()

            val updatedState = viewModel.uiState.value
            val circle = updatedState.displayCircles[0]
            assertThat(circle.color).isEqualTo(CircleColors.Anonymous)
            assertThat(updatedState.recentChangeTexts[0]).contains("An anonymous user")
        }

    @Test
    fun `startListeningToRecentChanges ignores invalid events`() =
        runTest {
            val invalidEvents =
                listOf(
                    createTestEvent(wiki = "dewiki"), // Wrong wiki
                    createTestEvent(namespace = 1), // Wrong namespace
                    createTestEvent(type = "new"), // Wrong type
                )

            every { mockRepository.listenToRecentChanges() } returns flowOf(*invalidEvents.toTypedArray())

            val initialState = viewModel.uiState.value

            viewModel.startListeningToRecentChanges()
            advanceUntilIdle()

            // State should remain unchanged
            assertThat(viewModel.uiState.value).isEqualTo(initialState)
        }

    @Test
    fun `removeCircle removes correct circle from state`() =
        runTest {
            val testEvent = createTestEvent(user = "TestUser")

            every { mockRepository.listenToRecentChanges() } returns flowOf(testEvent)

            viewModel.startListeningToRecentChanges()
            advanceUntilIdle()

            val stateWithCircle = viewModel.uiState.value
            assertThat(stateWithCircle.displayCircles).hasSize(1)

            val circleId = stateWithCircle.displayCircles[0].id
            viewModel.removeCircle(circleId)

            val stateAfterRemoval = viewModel.uiState.value
            assertThat(stateAfterRemoval.displayCircles).isEmpty()
        }

    @Test
    fun `radius calculation clamps values correctly`() =
        runTest {
            val largeEditEvent = createTestEvent(length = Length(old = 100, new = 10000)) // +9900 bytes
            val smallEditEvent = createTestEvent(length = Length(old = 100, new = 105)) // +5 bytes

            every { mockRepository.listenToRecentChanges() } returns flowOf(largeEditEvent, smallEditEvent)

            viewModel.startListeningToRecentChanges()
            advanceUntilIdle()

            val finalState = viewModel.uiState.value
            assertThat(finalState.displayCircles).hasSize(2)

            // Check the clamped values
            val circles = finalState.displayCircles
            assertThat(circles[0].radius).isEqualTo(240f) // Max radius for large edit
            assertThat(circles[1].radius).isEqualTo(10f) // Min radius for small edit
        }

    @Test
    fun `text list maintains maximum size`() =
        runTest {
            val events =
                (1..5).map { i ->
                    createTestEvent(title = "Article$i", length = Length(old = 100, new = 100 + i))
                }

            every { mockRepository.listenToRecentChanges() } returns flowOf(*events.toTypedArray())

            viewModel.startListeningToRecentChanges()
            advanceUntilIdle()

            val finalState = viewModel.uiState.value

            // Should only keep the latest 3 messages
            assertThat(finalState.recentChangeTexts).hasSize(3)
            // Most recent should be first (Article5, Article4, Article3)
            assertThat(finalState.recentChangeTexts[0]).contains("Article5")
            assertThat(finalState.recentChangeTexts[1]).contains("Article4")
            assertThat(finalState.recentChangeTexts[2]).contains("Article3")
        }

    private fun createTestEvent(
        type: String = "edit",
        namespace: Int = 0,
        title: String = "Test Article",
        user: String = "TestUser",
        bot: Boolean = false,
        length: Length? = Length(old = 100, new = 150),
        wiki: String = "enwiki",
    ) = RecentChangeEvent(
        type = type,
        namespace = namespace,
        title = title,
        comment = "Test comment",
        timestamp = System.currentTimeMillis(),
        user = user,
        bot = bot,
        length = length,
        wiki = wiki,
    )
}
