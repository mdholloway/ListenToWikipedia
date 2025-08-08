package org.mdholloway.listentowikipedia.ui

import androidx.compose.animation.AnimatedVisibility
import androidx.compose.animation.core.LinearEasing
import androidx.compose.animation.core.tween
import androidx.compose.animation.fadeIn
import androidx.compose.animation.fadeOut
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import kotlinx.coroutines.delay
import org.mdholloway.listentowikipedia.ui.state.DisplayCircle

@Composable
fun RecentChangesScreen(
    displayCircles: List<DisplayCircle>,
    recentChangeTexts: List<String>,
    onCircleAnimationFinished: (String) -> Unit = {},
) {
    Box(
        modifier =
            Modifier
                .fillMaxSize()
                .background(Color(0xFF0D1B2A)), // Dark blue background
    ) {
        displayCircles.forEach { displayCircle ->
            AnimatedCircle(
                displayCircle = displayCircle,
                onAnimationFinished = { onCircleAnimationFinished(displayCircle.id) },
            )
        }

        // Text overlay at the bottom
        Box(
            modifier =
                Modifier
                    .fillMaxWidth()
                    .align(Alignment.BottomCenter)
                    .padding(bottom = 16.dp), // Adjust padding as needed
        ) {
            LazyColumn(
                modifier =
                    Modifier
                        .fillMaxWidth()
                        .align(Alignment.BottomCenter),
            ) {
                itemsIndexed(recentChangeTexts) { index, text ->
                    val textAlpha =
                        when (index) {
                            0 -> 0.5f // Most recent
                            1 -> 0.3f // Second most recent
                            2 -> 0.1f // Third most recent
                            else -> 0.0f // Should not happen with MAX_DISPLAY_MESSAGES = 3
                        }
                    Text(
                        text = text,
                        color = Color.White.copy(alpha = textAlpha),
                        style = MaterialTheme.typography.labelSmall,
                        textAlign = TextAlign.Center,
                        modifier =
                            Modifier
                                .fillMaxWidth()
                                .padding(vertical = 2.dp),
                    )
                }
            }
        }
    }
}

@Composable
private fun AnimatedCircle(
    displayCircle: DisplayCircle,
    onAnimationFinished: () -> Unit = {},
) {
    val displayDurationMillis = 30000L
    val isVisible = remember { mutableStateOf(true) }

    LaunchedEffect(displayCircle.id) {
        isVisible.value = false
    }

    AnimatedVisibility(
        visible = isVisible.value,
        enter = fadeIn(animationSpec = tween(durationMillis = 0)),
        exit = fadeOut(animationSpec = tween(durationMillis = displayDurationMillis.toInt(), easing = LinearEasing)),
    ) {
        // Monitor animation completion with a separate LaunchedEffect
        LaunchedEffect(isVisible.value) {
            if (!isVisible.value) {
                // Wait for the animation duration, then notify
                delay(displayDurationMillis.toLong())
                onAnimationFinished()
            }
        }
        Canvas(modifier = Modifier.fillMaxSize()) {
            // Ensure circle stays within bounds by accounting for radius
            val centerX =
                (displayCircle.radius + (size.width - 2 * displayCircle.radius) * displayCircle.x).coerceIn(
                    displayCircle.radius,
                    size.width - displayCircle.radius,
                )
            val centerY =
                (displayCircle.radius + (size.height - 2 * displayCircle.radius) * displayCircle.y).coerceIn(
                    displayCircle.radius,
                    size.height - displayCircle.radius,
                )

            drawCircle(
                color = displayCircle.color,
                center = Offset(centerX, centerY),
                radius = displayCircle.radius,
            )
        }
    }
}
