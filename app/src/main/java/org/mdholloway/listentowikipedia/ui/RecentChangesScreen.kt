package org.mdholloway.listentowikipedia.ui.main

import androidx.compose.animation.core.EaseInOut
import androidx.compose.animation.core.FastOutLinearInEasing
import androidx.compose.animation.core.LinearEasing
import androidx.compose.animation.core.animateFloatAsState
import androidx.compose.animation.core.tween
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import java.util.UUID
import kotlin.random.Random
import kotlinx.coroutines.delay
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material3.MaterialTheme
import androidx.compose.ui.util.fastCoerceIn
import org.mdholloway.listentowikipedia.util.isIpAddress

// Data class to hold the information for a circle to be displayed
data class DisplayCircle(
    val id: String,
    val event: RecentChangeEvent,
    val x: Float,
    val y: Float,
    val radius: Float,
    val color: Color,
    val createdAt: Long = System.currentTimeMillis()
)

@Composable
fun RecentChangesScreen(recentChange: RecentChangeEvent?, recentChangeTexts: List<String>) {
    val circles = remember { mutableStateListOf<DisplayCircle>() }

    // Duration for which a circle stays on screen (in milliseconds)
    val DISPLAY_DURATION_MILLIS = 30000L

    // Observe incoming events and add them to the list
    LaunchedEffect(recentChange) {
        recentChange?.let { event ->
            val id = UUID.randomUUID().toString()

            val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
            val radius = diff.fastCoerceIn(10, 240).dp.value // Scale diff to radius

            val color = when {
                event.bot -> Color(0xFF8A2BE2) // Purple for bots
                isIpAddress(event.user) -> Color(0xFF00FF00) // Green for unregistered users (IPs)
                else -> Color(0xFF808080) // Gray for registered users
            }

            // Generate random position within screen bounds (relative to size)
            val randomX = Random.nextFloat()
            val randomY = Random.nextFloat()

            circles.add(
                DisplayCircle(
                    id = id,
                    event = event,
                    x = randomX,
                    y = randomY,
                    radius = radius,
                    color = color
                )
            )
        }
    }

    // Periodically clean up old circles
    LaunchedEffect(Unit) {
        while (true) {
            val currentTime = System.currentTimeMillis()
            circles.removeAll { currentTime - it.createdAt > DISPLAY_DURATION_MILLIS }
            delay(1000) // Check every second
        }
    }

    Box(
        modifier = Modifier
            .fillMaxSize()
            .background(Color(0xFF0D1B2A)) // Dark blue background
    ) {
        circles.forEach { displayCircle ->
            AnimatedCircle(displayCircle, DISPLAY_DURATION_MILLIS)
        }

        // Text overlay at the bottom
        Box(
            modifier = Modifier
                .fillMaxWidth()
                .align(Alignment.BottomCenter)
                .padding(bottom = 16.dp) // Adjust padding as needed
        ) {
            LazyColumn(
                modifier = Modifier
                    .fillMaxWidth()
                    .align(Alignment.BottomCenter)
            ) {
                itemsIndexed(recentChangeTexts) { index, text ->
                    val textAlpha = when (index) {
                        0 -> 0.5f // Most recent
                        1 -> 0.3f  // Second most recent
                        2 -> 0.1f // Third most recent
                        else -> 0.0f // Should not happen with MAX_DISPLAY_MESSAGES = 3
                    }
                    Text(
                        text = text,
                        color = Color.White.copy(alpha = textAlpha),
                        style = MaterialTheme.typography.labelSmall,
                        textAlign = TextAlign.Center,
                        modifier = Modifier
                            .fillMaxWidth()
                            .padding(vertical = 2.dp)
                    )
                }
            }
        }
    }
}

@Composable
private fun AnimatedCircle(
    displayCircle: DisplayCircle,
    displayDurationMillis: Long
) {
    val targetAlpha = remember { mutableStateOf(0.55f) }
    
    LaunchedEffect(displayCircle.id) {
        targetAlpha.value = 0f
    }
    
    val animatedAlpha by animateFloatAsState(
        targetValue = targetAlpha.value,
        animationSpec = tween(durationMillis = displayDurationMillis.toInt(), easing = LinearEasing), label = "alphaAnimation"
    )

    // Draw Circle
    Canvas(modifier = Modifier.fillMaxSize()) {
        // Ensure circle stays within bounds by accounting for radius
        val centerX = (displayCircle.radius + (size.width - 2 * displayCircle.radius) * displayCircle.x).coerceIn(
            displayCircle.radius, 
            size.width - displayCircle.radius
        )
        val centerY = (displayCircle.radius + (size.height - 2 * displayCircle.radius) * displayCircle.y).coerceIn(
            displayCircle.radius, 
            size.height - displayCircle.radius
        )
        
        drawCircle(
            color = displayCircle.color,
            center = Offset(centerX, centerY),
            radius = displayCircle.radius,
            alpha = animatedAlpha
        )
    }
}