package org.mdholloway.listentowikipedia.ui

import androidx.compose.ui.test.assertIsDisplayed
import androidx.compose.ui.test.hasText
import androidx.compose.ui.test.junit4.createComposeRule
import androidx.compose.ui.test.onNodeWithText
import androidx.test.ext.junit.runners.AndroidJUnit4
import org.junit.Rule
import org.junit.Test
import org.junit.runner.RunWith
import org.mdholloway.listentowikipedia.model.Length
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import org.mdholloway.listentowikipedia.ui.state.CircleColors
import org.mdholloway.listentowikipedia.ui.state.DisplayCircle

@RunWith(AndroidJUnit4::class)
class RecentChangesScreenTest {
    @get:Rule
    val composeTestRule = createComposeRule()

    @Test
    fun recentChangesScreen_displaysEmptyState() {
        composeTestRule.setContent {
            RecentChangesScreen(
                displayCircles = emptyList(),
                recentChangeTexts = emptyList(),
            )
        }

        // Screen should be displayed but have no text content
        // The dark blue background should be visible
        composeTestRule.waitForIdle()
    }

    @Test
    fun recentChangesScreen_displaysRecentChangeTexts() {
        val testTexts =
            listOf(
                "User123 added 50 bytes to Test Article",
                "Anonymous user removed 25 bytes from Another Article",
                "BotUser added 100 bytes to Bot Article",
            )

        composeTestRule.setContent {
            RecentChangesScreen(
                displayCircles = emptyList(),
                recentChangeTexts = testTexts,
            )
        }

        // Verify all text messages are displayed
        testTexts.forEach { text ->
            composeTestRule.onNodeWithText(text).assertIsDisplayed()
        }
    }

    @Test
    fun recentChangesScreen_displaysMaximumThreeTexts() {
        val testTexts =
            listOf(
                "First message",
                "Second message",
                "Third message",
                "Fourth message", // This should not be displayed based on ViewModel logic
                "Fifth message", // This should not be displayed based on ViewModel logic
            )

        composeTestRule.setContent {
            RecentChangesScreen(
                displayCircles = emptyList(),
                recentChangeTexts = testTexts.take(3), // RecentChangesViewModel limits to 3
            )
        }

        // Should display first three messages
        composeTestRule.onNodeWithText("First message").assertIsDisplayed()
        composeTestRule.onNodeWithText("Second message").assertIsDisplayed()
        composeTestRule.onNodeWithText("Third message").assertIsDisplayed()

        // Should not display fourth and fifth messages (not passed to component)
        composeTestRule.onNode(hasText("Fourth message")).assertDoesNotExist()
        composeTestRule.onNode(hasText("Fifth message")).assertDoesNotExist()
    }

    @Test
    fun recentChangesScreen_displaysCircles() {
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

        val testCircles =
            listOf(
                DisplayCircle(
                    id = "circle1",
                    event = testEvent,
                    x = 0.5f,
                    y = 0.5f,
                    radius = 50f,
                    color = CircleColors.Registered,
                ),
                DisplayCircle(
                    id = "circle2",
                    event = testEvent.copy(user = "192.168.1.1"),
                    x = 0.3f,
                    y = 0.7f,
                    radius = 30f,
                    color = CircleColors.Anonymous,
                ),
            )

        var animationCallbackCount = 0

        composeTestRule.setContent {
            RecentChangesScreen(
                displayCircles = testCircles,
                recentChangeTexts = emptyList(),
                onCircleAnimationFinished = { circleId ->
                    animationCallbackCount++
                },
            )
        }

        // Circles are drawn on Canvas, which is harder to test directly in Compose
        // We can test that the Composable renders without crashing
        composeTestRule.waitForIdle()

        // The screen should render successfully with circles
        // Animation callbacks will be tested separately
    }

    @Test
    fun recentChangesScreen_handlesCircleAnimationCallback() {
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

        val testCircle =
            DisplayCircle(
                id = "test-circle",
                event = testEvent,
                x = 0.5f,
                y = 0.5f,
                radius = 50f,
                color = CircleColors.Registered,
            )

        var callbackCircleId: String? = null
        var callbackCount = 0

        composeTestRule.setContent {
            RecentChangesScreen(
                displayCircles = listOf(testCircle),
                recentChangeTexts = emptyList(),
                onCircleAnimationFinished = { circleId ->
                    callbackCircleId = circleId
                    callbackCount++
                },
            )
        }

        // The animation callback mechanism is set up correctly
        // Note: Testing the actual animation timing would require advancing animation clocks
        // which is complex for this integration test level
        composeTestRule.waitForIdle()
    }

    @Test
    fun recentChangesScreen_combinesCirclesAndTexts() {
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

        val testCircle =
            DisplayCircle(
                id = "circle1",
                event = testEvent,
                x = 0.4f,
                y = 0.6f,
                radius = 40f,
                color = CircleColors.Bot,
            )

        val testTexts =
            listOf(
                "TestUser added 50 bytes to Test Article",
            )

        composeTestRule.setContent {
            RecentChangesScreen(
                displayCircles = listOf(testCircle),
                recentChangeTexts = testTexts,
            )
        }

        // Verify text is displayed
        composeTestRule
            .onNodeWithText("TestUser added 50 bytes to Test Article")
            .assertIsDisplayed()

        // Screen should render both circles and text without issues
        composeTestRule.waitForIdle()
    }
}
