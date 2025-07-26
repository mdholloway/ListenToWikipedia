package org.mdholloway.listentowikipedia.ui.main

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.compose.ui.platform.ComposeView
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.compose.runtime.livedata.observeAsState
import org.mdholloway.listentowikipedia.viewmodel.RecentChangesViewModel

class RecentChangesFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        return ComposeView(requireContext()).apply {
            setContent {
                val viewModel = ViewModelProvider(this@RecentChangesFragment).get(RecentChangesViewModel::class.java)
                val latestRecentChangeEvent = viewModel.latestRecentChangeEvent.observeAsState().value
                RecentChangesScreen(recentChange = latestRecentChangeEvent)
                viewModel.startListeningToRecentChanges()
            }
        }
    }
}