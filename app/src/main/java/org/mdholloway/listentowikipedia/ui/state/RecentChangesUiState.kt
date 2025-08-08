package org.mdholloway.listentowikipedia.ui.state

import androidx.compose.ui.graphics.Color
import org.mdholloway.listentowikipedia.model.RecentChangeEvent

/**
 * UI state for the Recent Changes screen
 */
data class RecentChangesUiState(
    val displayCircles: List<DisplayCircle> = emptyList(),
    val recentChangeTexts: List<String> = emptyList(),
)

/**
 * Represents a circle to be displayed on screen
 */
data class DisplayCircle(
    val id: String,
    val event: RecentChangeEvent,
    val x: Float,
    val y: Float,
    val radius: Float,
    val color: Color,
    val createdAt: Long = System.currentTimeMillis(),
)

/**
 * Colors for different types of users/edits
 */
object CircleColors {
    val Bot = Color(0xFF8A2BE2) // Purple for bots
    val Anonymous = Color(0xFF00FF00) // Green for anonymous users (IPs)
    val Registered = Color(0xFF808080) // Gray for registered users
}
