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
    fun `playNote calls AudioEngine keyOn when engine is running`() {
        every { mockAudioEngine.start() } returns true
        audioManager.start()

        audioManager.playNote(60, 100)

        verify { mockAudioEngine.keyOn(60, 100) }
    }

    @Test
    fun `playNote does not call AudioEngine keyOn when engine is not running`() {
        // Engine not started
        audioManager.playNote(60, 100)

        verify(exactly = 0) { mockAudioEngine.keyOn(any(), any()) }
    }

    @Test
    fun `playNote handles valid MIDI range`() {
        every { mockAudioEngine.start() } returns true
        audioManager.start()

        // Test boundary values
        audioManager.playNote(0, 0) // Min values
        audioManager.playNote(127, 127) // Max values
        audioManager.playNote(60, 64) // Middle C, medium velocity

        verify { mockAudioEngine.keyOn(0, 0) }
        verify { mockAudioEngine.keyOn(127, 127) }
        verify { mockAudioEngine.keyOn(60, 64) }
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
