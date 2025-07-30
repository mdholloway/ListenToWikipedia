package org.mdholloway.listentowikipedia

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.viewModels
import androidx.compose.runtime.livedata.observeAsState
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import org.mdholloway.listentowikipedia.ui.main.RecentChangesScreen
import org.mdholloway.listentowikipedia.viewmodel.RecentChangesViewModel

class MainActivity : ComponentActivity() {

    private val recentChangesViewModel: RecentChangesViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        if (ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO)
            != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                arrayOf(Manifest.permission.RECORD_AUDIO),
                999);
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
            recentChangesViewModel.startListeningToRecentChanges()
        }
    }

    @Deprecated("TODO: Use the Activity Result API")
    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(
            requestCode,
            permissions,
            grantResults
        ) // Crucial for fragments
        when (requestCode) {
            999 -> {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.isNotEmpty()
                    && grantResults[0] == PackageManager.PERMISSION_GRANTED
                ) {
                    // Permission was granted, yay!
                    // You can now proceed with audio recording logic
                } else {
                    // Permission denied, boo! Disable the functionality that depends on this permission.
                    // You might want to show a message to the user explaining why the permission is needed.
                }
                return
            }
        }
    }
}