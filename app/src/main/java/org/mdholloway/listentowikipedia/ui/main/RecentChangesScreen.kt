package org.mdholloway.listentowikipedia.ui.main

import androidx.compose.animation.core.animateFloatAsState
import androidx.compose.animation.core.tween
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.offset
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateListOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import org.mdholloway.listentowikipedia.model.RecentChangeEvent
import java.util.UUID
import kotlin.random.Random
import kotlinx.coroutines.delay

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

// Helper function to check if a string is an IP address
fun isIpAddress(input: String): Boolean {
    val ipv4Pattern = "^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$".toRegex()
    val ipv6Pattern = "^(?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$".toRegex()
    return input.matches(ipv4Pattern) || input.matches(ipv6Pattern)
}

@Composable
fun RecentChangesScreen(recentChange: RecentChangeEvent?) {
    val circles = remember { mutableStateListOf<DisplayCircle>() }

    // Duration for which a circle stays on screen (in milliseconds)
    val DISPLAY_DURATION_MILLIS = 15000L // 15 seconds

    // Observe incoming events and add them to the list
    LaunchedEffect(recentChange) {
        recentChange?.let { event ->
            val id = UUID.randomUUID().toString()

            val diff = event.length?.let { it.new - (it.old ?: 0) } ?: 0
            val radius = (10.dp + (diff / 10).coerceAtMost(100).dp).value // Scale diff to radius

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
        // Draw circles
        Canvas(modifier = Modifier.fillMaxSize()) {
            circles.forEach { displayCircle ->
                val animatedAlpha by animateFloatAsState(
                    targetValue = if (System.currentTimeMillis() - displayCircle.createdAt < DISPLAY_DURATION_MILLIS) 1f else 0f,
                    animationSpec = tween(durationMillis = 1000), label = "alphaAnimation"
                )

                drawCircle(
                    color = displayCircle.color,
                    center = Offset(size.width * displayCircle.x, size.height * displayCircle.y),
                    radius = displayCircle.radius,
                    alpha = animatedAlpha
                )
            }
        }

        // Overlay text (titles)
        circles.forEach { displayCircle ->
            val animatedAlpha by animateFloatAsState(
                targetValue = if (System.currentTimeMillis() - displayCircle.createdAt < DISPLAY_DURATION_MILLIS) 1f else 0f,
                animationSpec = tween(durationMillis = 1000), label = "textAlphaAnimation"
            )

            // Position text relative to the circle
            Box(
                modifier = Modifier
                    .fillMaxSize()
                    .offset(
                        x = (displayCircle.x * this.density - displayCircle.radius).dp,
                        y = (displayCircle.y * this.density - displayCircle.radius).dp
                    ),
                contentAlignment = Alignment.Center
            ) {
                Text(
                    text = displayCircle.event.title,
                    color = Color.White.copy(alpha = animatedAlpha),
                    fontSize = (displayCircle.radius / 3).sp, // Adjust font size based on circle size
                    textAlign = TextAlign.Center,
                    modifier = Modifier.offset(
                        x = (displayCircle.x * this.density).dp, // Adjust text position based on circle center
                        y = (displayCircle.y * this.density).dp
                    )
                )
            }
        }
    }
}