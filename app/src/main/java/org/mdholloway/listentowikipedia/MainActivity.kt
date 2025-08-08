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
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.core.content.ContextCompat
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat
import dagger.hilt.android.AndroidEntryPoint
import org.mdholloway.listentowikipedia.audio.AudioManager
import org.mdholloway.listentowikipedia.ui.RecentChangesScreen
import org.mdholloway.listentowikipedia.viewmodel.RecentChangesViewModel
import javax.inject.Inject

@AndroidEntryPoint
class MainActivity : ComponentActivity() {
    private val recentChangesViewModel: RecentChangesViewModel by viewModels()

    @Inject
    lateinit var audioManager: AudioManager

    private val requestPermissionLauncher =
        registerForActivityResult(
            ActivityResultContracts.RequestPermission(),
        ) { isGranted: Boolean ->
            if (isGranted) {
                Log.i("MainActivity", "RECORD_AUDIO permission granted.")
                startAudioAndListening()
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

        // Set the AudioManager in the ViewModel
        recentChangesViewModel.setAudioManager(audioManager)

        // Check and request permission on activity creation
        checkAndRequestPermission()

        setContent {
            val latestRecentChangeEvent by recentChangesViewModel.latestRecentChangeEvent.collectAsState()
            val recentChangeTextList by recentChangesViewModel.recentChangeTextList.collectAsState()
            RecentChangesScreen(
                recentChange = latestRecentChangeEvent,
                recentChangeTexts = recentChangeTextList,
            )
        }
    }

    override fun onResume() {
        super.onResume()
        // Start audio and listening when app becomes active
        if (hasAudioPermission()) {
            startAudioAndListening()
        }
    }

    override fun onPause() {
        super.onPause()
        // Stop audio and listening when app goes to background
        stopAudioAndListening()
    }

    private fun hasAudioPermission(): Boolean =
        ContextCompat.checkSelfPermission(
            this,
            Manifest.permission.RECORD_AUDIO,
        ) == PackageManager.PERMISSION_GRANTED

    private fun checkAndRequestPermission() {
        when {
            hasAudioPermission() -> {
                Log.i("MainActivity", "RECORD_AUDIO permission already granted.")
                startAudioAndListening()
            }
            shouldShowRequestPermissionRationale(Manifest.permission.RECORD_AUDIO) -> {
                Log.d("MainActivity", "Displaying rationale for RECORD_AUDIO permission.")
                requestPermissionLauncher.launch(Manifest.permission.RECORD_AUDIO)
            }
            else -> {
                Log.d("MainActivity", "Requesting RECORD_AUDIO permission for the first time.")
                requestPermissionLauncher.launch(Manifest.permission.RECORD_AUDIO)
            }
        }
    }

    private fun startAudioAndListening() {
        Log.i("MainActivity", "Starting audio engine and listening to changes")
        if (audioManager.start()) {
            recentChangesViewModel.startListeningToRecentChanges()
        } else {
            Log.e("MainActivity", "Failed to start audio engine")
        }
    }

    private fun stopAudioAndListening() {
        Log.i("MainActivity", "Stopping audio engine and listening to changes")
        recentChangesViewModel.stopListeningToRecentChanges()
        audioManager.stop()
    }
}
