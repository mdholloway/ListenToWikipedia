package org.mdholloway.listentowikipedia

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.runtime.livedata.observeAsState
import org.mdholloway.listentowikipedia.ui.main.RecentChangesScreen
import org.mdholloway.listentowikipedia.viewmodel.RecentChangesViewModel

class MainActivity : ComponentActivity() {

    private val recentChangesViewModel: RecentChangesViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContent {
            val latestRecentChangeEvent =
                recentChangesViewModel.latestRecentChangeEvent.observeAsState().value
            val recentChangeTextList =
                recentChangesViewModel.recentChangeTextList.observeAsState(initial = emptyList()).value
            RecentChangesScreen(
                recentChange = latestRecentChangeEvent,
                recentChangeTexts = recentChangeTextList
            )
            recentChangesViewModel.startListeningToRecentChanges()
        }
    }
}