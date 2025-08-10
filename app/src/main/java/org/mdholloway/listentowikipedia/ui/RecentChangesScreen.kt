package org.mdholloway.listentowikipedia.ui

import androidx.compose.animation.AnimatedVisibility
import androidx.compose.animation.core.LinearEasing
import androidx.compose.animation.core.tween
import androidx.compose.animation.fadeIn
import androidx.compose.animation.fadeOut
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.layout.width
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.itemsIndexed
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CircularProgressIndicator
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
import androidx.compose.ui.semantics.LiveRegionMode
import androidx.compose.ui.semantics.contentDescription
import androidx.compose.ui.semantics.liveRegion
import androidx.compose.ui.semantics.role
import androidx.compose.ui.semantics.semantics
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import kotlinx.coroutines.delay
import org.mdholloway.listentowikipedia.ui.state.ConnectionState
import org.mdholloway.listentowikipedia.ui.state.DisplayCircle
import org.mdholloway.listentowikipedia.ui.state.RecentChangesUiState

@Composable
fun RecentChangesScreen(
    uiState: RecentChangesUiState,
    onCircleAnimationFinished: (String) -> Unit = {},
    onRetryConnection: () -> Unit = {},
) {
    Box(
        modifier =
            Modifier
                .fillMaxSize()
                .background(Color(0xFF0D1B2A)) // Dark blue background
                .semantics {
                    contentDescription =
                        "Wikipedia recent changes visualization. Circles represent page edits with size based on change amount."
                    role = androidx.compose.ui.semantics.Role.Image
                },
    ) {
        // Connection status banner at the top
        ConnectionStatusBanner(
            connectionState = uiState.connectionState,
            isRetrying = uiState.isRetrying,
            onRetryClick = onRetryConnection,
            modifier =
                Modifier
                    .fillMaxWidth()
                    .align(Alignment.TopCenter),
        )

        uiState.displayCircles.forEach { displayCircle ->
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
                    .padding(bottom = 16.dp) // Adjust padding as needed
                    .semantics {
                        contentDescription = "Recent Wikipedia page edits list"
                        liveRegion = LiveRegionMode.Polite
                    },
        ) {
            LazyColumn(
                modifier =
                    Modifier
                        .fillMaxWidth()
                        .align(Alignment.BottomCenter),
            ) {
                itemsIndexed(uiState.recentChangeTexts) { index, text ->
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
                                .padding(vertical = 2.dp)
                                .semantics {
                                    contentDescription =
                                        when (index) {
                                            0 -> "Most recent edit: $text"
                                            1 -> "Second most recent edit: $text"
                                            2 -> "Third most recent edit: $text"
                                            else -> "Edit: $text"
                                        }
                                },
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
        Canvas(
            modifier =
                Modifier
                    .fillMaxSize()
                    .semantics {
                        val changeType = if (displayCircle.event.bot) "bot edit" else "user edit"
                        val userType =
                            when {
                                displayCircle.event.bot -> "by a bot"
                                displayCircle.event.user.contains('.') -> "by an anonymous user"
                                else -> "by user ${displayCircle.event.user}"
                            }
                        val changeSize =
                            when {
                                displayCircle.radius < 50 -> "small"
                                displayCircle.radius < 100 -> "medium"
                                else -> "large"
                            }
                        contentDescription = "$changeSize $changeType on ${displayCircle.event.title} $userType"
                        role = androidx.compose.ui.semantics.Role.Image
                    },
        ) {
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

@Composable
private fun ConnectionStatusBanner(
    connectionState: ConnectionState,
    isRetrying: Boolean,
    onRetryClick: () -> Unit,
    modifier: Modifier = Modifier,
) {
    when (connectionState) {
        is ConnectionState.Connecting -> {
            ConnectingBanner(modifier = modifier)
        }
        is ConnectionState.Error -> {
            ErrorBanner(
                message = connectionState.message,
                canRetry = connectionState.canRetry && !isRetrying,
                isRetrying = isRetrying,
                onRetryClick = onRetryClick,
                modifier = modifier,
            )
        }
        ConnectionState.Connected,
        ConnectionState.Disconnected,
        -> {
            // No banner needed for these states
        }
    }
}

@Composable
private fun ConnectingBanner(modifier: Modifier = Modifier) {
    Box(
        modifier =
            modifier
                .background(Color(0xFF1976D2)) // Blue connecting color
                .padding(16.dp)
                .semantics {
                    contentDescription = "Connecting to Wikipedia live changes"
                    liveRegion = LiveRegionMode.Polite
                },
        contentAlignment = Alignment.Center,
    ) {
        Row(
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.Center,
        ) {
            CircularProgressIndicator(
                modifier = Modifier.size(16.dp),
                color = Color.White,
                strokeWidth = 2.dp,
            )
            Spacer(modifier = Modifier.width(8.dp))
            Text(
                text = "Connecting...",
                color = Color.White,
                style = MaterialTheme.typography.bodyMedium,
            )
        }
    }
}

@Composable
private fun ErrorBanner(
    message: String,
    canRetry: Boolean,
    isRetrying: Boolean,
    onRetryClick: () -> Unit,
    modifier: Modifier = Modifier,
) {
    Box(
        modifier =
            modifier
                .background(Color(0xFFD32F2F)) // Red error color
                .padding(16.dp)
                .semantics {
                    contentDescription = "Connection error: $message"
                    liveRegion = LiveRegionMode.Assertive
                },
    ) {
        Row(
            modifier = Modifier.fillMaxWidth(),
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.SpaceBetween,
        ) {
            Text(
                text = message,
                color = Color.White,
                style = MaterialTheme.typography.bodyMedium,
                modifier = Modifier.weight(1f),
            )

            if (canRetry) {
                if (isRetrying) {
                    CircularProgressIndicator(
                        modifier = Modifier.size(20.dp),
                        color = Color.White,
                        strokeWidth = 2.dp,
                    )
                } else {
                    Button(
                        onClick = onRetryClick,
                        colors =
                            ButtonDefaults.buttonColors(
                                containerColor = Color.White,
                                contentColor = Color(0xFFD32F2F),
                            ),
                        modifier =
                            Modifier.semantics {
                                contentDescription = "Retry connection to Wikipedia live changes"
                            },
                    ) {
                        Text("Retry", style = MaterialTheme.typography.labelMedium)
                    }
                }
            }
        }
    }
}
