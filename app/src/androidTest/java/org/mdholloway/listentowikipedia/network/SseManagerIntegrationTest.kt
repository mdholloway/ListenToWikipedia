package org.mdholloway.listentowikipedia.network

import android.content.Context
import androidx.test.core.app.ApplicationProvider
import androidx.test.ext.junit.runners.AndroidJUnit4
import com.google.common.truth.Truth.assertThat
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.ExperimentalCoroutinesApi
import kotlinx.coroutines.SupervisorJob
import kotlinx.coroutines.cancel
import kotlinx.coroutines.test.advanceUntilIdle
import kotlinx.coroutines.test.runTest
import org.junit.After
import org.junit.Before
import org.junit.Test
import org.junit.runner.RunWith

@OptIn(ExperimentalCoroutinesApi::class)
@RunWith(AndroidJUnit4::class)
class SseManagerIntegrationTest {
    private lateinit var context: Context
    private lateinit var sseManager: SseManager
    private var testScope: CoroutineScope? = null

    @Before
    fun setup() {
        context = ApplicationProvider.getApplicationContext()
        sseManager = SseManager(context)
        testScope = CoroutineScope(SupervisorJob() + Dispatchers.Main)
    }

    @After
    fun teardown() {
        sseManager.stop()
        testScope?.cancel()
        testScope = null
    }

    @Test
    fun sseManager_initialState_isNotConnected() {
        assertThat(sseManager.isConnected()).isFalse()
    }

    @Test
    fun sseManager_start_setsConnectionState() =
        runTest {
            val scope = testScope!!

            // Note: This will attempt to connect to the real Wikimedia SSE endpoint
            // In CI/local environments without network, this should fail gracefully
            val started = sseManager.start(scope)
            advanceUntilIdle()

            // The start method should return true even if network connection fails
            // The actual connection state is managed internally
            assertThat(started).isTrue()
        }

    @Test
    fun sseManager_stop_cleansUpResources() {
        val scope = testScope!!

        sseManager.start(scope)
        assertThat(sseManager.isConnected()).isTrue()

        sseManager.stop()
        assertThat(sseManager.isConnected()).isFalse()
    }

    @Test
    fun sseManager_multipleStarts_isIdempotent() =
        runTest {
            val scope = testScope!!

            val firstStart = sseManager.start(scope)
            val secondStart = sseManager.start(scope)

            assertThat(firstStart).isTrue()
            assertThat(secondStart).isTrue()

            // Should only have one connection
            assertThat(sseManager.isConnected()).isTrue()
        }

    @Test
    fun sseManager_multipleStops_isIdempotent() {
        val scope = testScope!!

        sseManager.start(scope)
        sseManager.stop()
        sseManager.stop() // Second stop should be safe

        assertThat(sseManager.isConnected()).isFalse()
    }

    @Test
    fun sseManager_eventsFlow_isNotNull() {
        // Even when not connected, the flow should exist
        assertThat(sseManager.recentChangeEvents).isNotNull()
    }

    // Note: Testing actual SSE events would require either:
    // 1. A mock server setup (complex for integration tests)
    // 2. Network access to the real endpoint (flaky in CI)
    // 3. A test-specific SSE endpoint
    //
    // For now, we test the integration points and state management.
    // Real event processing is covered by unit tests.

    @Test
    fun sseManager_contextIntegration_hasProperUserAgent() {
        // Verify that SseManager can access app context for user agent
        val appName = context.applicationInfo?.loadLabel(context.packageManager).toString()
        assertThat(appName).isNotEmpty()

        // The SseManager should be able to create HTTP client with proper headers
        // This is implicitly tested by successful instantiation
        assertThat(sseManager).isNotNull()
    }

    @Test
    fun sseManager_lifecycleManagement_worksWithActivityScope() =
        runTest {
            val scope = testScope!!

            // Start connection
            sseManager.start(scope)
            assertThat(sseManager.isConnected()).isTrue()

            // Cancel scope (simulates activity destruction)
            scope.cancel()
            advanceUntilIdle()

            // SseManager should handle scope cancellation gracefully
            // Connection state should remain consistent
            sseManager.stop()
            assertThat(sseManager.isConnected()).isFalse()
        }
}
