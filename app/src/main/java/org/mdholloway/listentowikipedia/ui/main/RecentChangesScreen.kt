package org.mdholloway.listentowikipedia.ui.main

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import org.mdholloway.listentowikipedia.model.RecentChangeEvent

@Composable
fun RecentChangesScreen(recentChanges: List<RecentChangeEvent>) {
    Column(modifier = Modifier.fillMaxSize()) {
        if (recentChanges.isEmpty()) {
            Text(
                text = "No recent changes yet...",
                modifier = Modifier.padding(16.dp)
            )
        } else {
            recentChanges.forEach { change ->
                // This will be replaced by the animated circle drawing logic
                Text(text = change.title, modifier = Modifier.padding(8.dp))
            }
        }
    }
}