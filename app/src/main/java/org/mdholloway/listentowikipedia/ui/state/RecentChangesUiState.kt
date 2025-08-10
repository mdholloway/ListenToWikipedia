package org.mdholloway.listentowikipedia.ui.state

import androidx.compose.ui.graphics.Color
import org.mdholloway.listentowikipedia.model.RecentChangeEvent

/**
 * Connection state for real-time data streams
 */
sealed class ConnectionState {
    object Connected : ConnectionState()

    object Connecting : ConnectionState()

    data class Error(
        val message: String,
        val canRetry: Boolean = true,
        val lastSuccessfulConnection: Long? = null,
    ) : ConnectionState()

    object Disconnected : ConnectionState()
}

/**
 * UI state for the Recent Changes screen
 */
data class RecentChangesUiState(
    val displayCircles: List<DisplayCircle> = emptyList(),
    val recentChangeTexts: List<String> = emptyList(),
    val connectionState: ConnectionState = ConnectionState.Disconnected,
    val isRetrying: Boolean = false,
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
