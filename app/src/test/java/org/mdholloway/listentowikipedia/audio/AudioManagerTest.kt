package org.mdholloway.listentowikipedia.audio

import com.google.common.truth.Truth.assertThat
import io.mockk.every
import io.mockk.mockk
import io.mockk.verify
import org.junit.Before
import org.junit.Rule
import org.junit.Test
import org.mdholloway.listentowikipedia.testutil.AndroidLogRule

class AudioManagerTest {
    @get:Rule
    val androidLogRule = AndroidLogRule()

    private val mockAudioEngine = mockk<AudioEngine>(relaxed = true)
    private lateinit var audioManager: AudioManager

    @Before
    fun setUp() {
        audioManager = AudioManager(mockAudioEngine)
    }

    @Test
    fun `start returns true when AudioEngine starts successfully`() {
        every { mockAudioEngine.start() } returns true

        val result = audioManager.start()

        assertThat(result).isTrue()
        assertThat(audioManager.isRunning()).isTrue()
        verify { mockAudioEngine.start() }
    }

    @Test
    fun `start returns false when AudioEngine fails to start`() {
        every { mockAudioEngine.start() } returns false

        val result = audioManager.start()

        assertThat(result).isFalse()
        assertThat(audioManager.isRunning()).isFalse()
        verify { mockAudioEngine.start() }
    }

    @Test
    fun `start is idempotent - multiple calls don't restart engine`() {
        every { mockAudioEngine.start() } returns true

        // First call should start
        audioManager.start()
        assertThat(audioManager.isRunning()).isTrue()

        // Second call should not call start again
        audioManager.start()

        verify(exactly = 1) { mockAudioEngine.start() }
    }

    @Test
    fun `stop calls AudioEngine stop when engine is running`() {
        every { mockAudioEngine.start() } returns true
        audioManager.start()

        audioManager.stop()

        assertThat(audioManager.isRunning()).isFalse()
        verify { mockAudioEngine.stop() }
    }

    @Test
    fun `stop is idempotent - multiple calls don't call AudioEngine stop multiple times`() {
        every { mockAudioEngine.start() } returns true
        audioManager.start()

        audioManager.stop()
        audioManager.stop() // Second call

        verify(exactly = 1) { mockAudioEngine.stop() }
    }

    @Test
    fun `playWikipediaEdit calls AudioEngine playWikipediaEdit when engine is running`() {
        every { mockAudioEngine.start() } returns true
        audioManager.start()

        audioManager.playWikipediaEdit(100, true, 0.5f)

        verify { mockAudioEngine.playWikipediaEdit(100, true, 0.5f) }
    }

    @Test
    fun `playWikipediaEdit does not call AudioEngine when engine is not running`() {
        // Engine not started
        audioManager.playWikipediaEdit(100, true, 0.5f)

        verify(exactly = 0) { mockAudioEngine.playWikipediaEdit(any(), any(), any()) }
    }

    @Test
    fun `playWikipediaEdit handles different edit types and sizes`() {
        every { mockAudioEngine.start() } returns true
        audioManager.start()

        // Test different scenarios
        audioManager.playWikipediaEdit(50, true) // Small addition
        audioManager.playWikipediaEdit(1000, false, 0.8f) // Large deletion
        audioManager.playWikipediaEdit(5000, true, 1.0f) // Very large addition

        verify { mockAudioEngine.playWikipediaEdit(50, true, 1.0f) } // Default volume
        verify { mockAudioEngine.playWikipediaEdit(1000, false, 0.8f) }
        verify { mockAudioEngine.playWikipediaEdit(5000, true, 1.0f) }
    }

    @Test
    fun `isRunning returns correct state throughout lifecycle`() {
        // Initially not running
        assertThat(audioManager.isRunning()).isFalse()

        // After successful start
        every { mockAudioEngine.start() } returns true
        audioManager.start()
        assertThat(audioManager.isRunning()).isTrue()

        // After stop
        audioManager.stop()
        assertThat(audioManager.isRunning()).isFalse()
    }

    @Test
    fun `isRunning returns false when start fails`() {
        every { mockAudioEngine.start() } returns false

        audioManager.start()

        assertThat(audioManager.isRunning()).isFalse()
    }

    @Test
    fun `engine state is maintained correctly after multiple operations`() {
        every { mockAudioEngine.start() } returns true

        // Start -> Stop -> Start cycle
        audioManager.start()
        assertThat(audioManager.isRunning()).isTrue()

        audioManager.stop()
        assertThat(audioManager.isRunning()).isFalse()

        audioManager.start()
        assertThat(audioManager.isRunning()).isTrue()

        // Should have called start twice and stop once
        verify(exactly = 2) { mockAudioEngine.start() }
        verify(exactly = 1) { mockAudioEngine.stop() }
    }
}
