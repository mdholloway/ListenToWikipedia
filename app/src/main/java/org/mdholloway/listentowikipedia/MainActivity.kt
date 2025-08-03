package org.mdholloway.listentowikipedia

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.result.contract.ActivityResultContracts
import androidx.activity.viewModels
import androidx.compose.runtime.livedata.observeAsState
import androidx.core.content.ContextCompat
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat
import org.mdholloway.listentowikipedia.ui.main.RecentChangesScreen
import org.mdholloway.listentowikipedia.viewmodel.RecentChangesViewModel

class MainActivity : ComponentActivity() {


    private val recentChangesViewModel: RecentChangesViewModel by viewModels()

    private val requestPermissionLauncher = registerForActivityResult(
        ActivityResultContracts.RequestPermission()
    ) { isGranted: Boolean ->
        if (isGranted) {
            Log.i("MainActivity", "RECORD_AUDIO permission granted. Starting audio service.")
            // Permission granted, now it's safe to start listening
            recentChangesViewModel.startListeningToRecentChanges()
        } else {
            Log.w("MainActivity", "RECORD_AUDIO permission denied. Audio features may not work.")
            // Permission denied. You might want to show a message to the user.
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        
        // Hide navigation bar
        val windowInsetsController = WindowCompat.getInsetsController(window, window.decorView)
        windowInsetsController.apply {
            hide(WindowInsetsCompat.Type.navigationBars())
            systemBarsBehavior = WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE
        }

        // 2. Check and request permission on activity creation
        when {
            ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) == PackageManager.PERMISSION_GRANTED -> {
                // Permission already granted, start immediately
                Log.i("MainActivity", "RECORD_AUDIO permission already granted. Starting audio service.")
                recentChangesViewModel.startListeningToRecentChanges()
            }
            shouldShowRequestPermissionRationale(Manifest.permission.RECORD_AUDIO) -> {
                // Explain to the user why the permission is needed (optional, good practice)
                Log.d("MainActivity", "Displaying rationale for RECORD_AUDIO permission.")
                // You could show a dialog here before launching the request
                requestPermissionLauncher.launch(Manifest.permission.RECORD_AUDIO)
            }
            else -> {
                // Directly request the permission
                Log.d("MainActivity", "Requesting RECORD_AUDIO permission for the first time.")
                requestPermissionLauncher.launch(Manifest.permission.RECORD_AUDIO)
            }
        }

        setContent {
            val latestRecentChangeEvent =
                recentChangesViewModel.latestRecentChangeEvent.observeAsState().value
            val recentChangeTextList =
                recentChangesViewModel.recentChangeTextList.observeAsState(initial = emptyList()).value
            RecentChangesScreen(
                recentChange = latestRecentChangeEvent,
                recentChangeTexts = recentChangeTextList
            )
        }
    }

    override fun onStop() {
        super.onStop()
        recentChangesViewModel.stopListeningToRecentChanges()
    }
}