package org.mdholloway.listentowikipedia.di

import android.content.Context
import com.DspFaust.DspFaust
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import org.mdholloway.listentowikipedia.audio.AudioEngine
import org.mdholloway.listentowikipedia.audio.DspFaustEngine
import org.mdholloway.listentowikipedia.network.SseManager
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object SingletonModule {
    @Provides
    @Singleton
    fun provideDspFaust(): DspFaust = DspFaust()

    @Provides
    @Singleton
    fun provideAudioEngine(dspFaust: DspFaust): AudioEngine = DspFaustEngine(dspFaust)
}

@Module
@InstallIn(SingletonComponent::class)
object ApplicationModule {
    @Provides
    @Singleton
    fun provideSseManager(
        @ApplicationContext context: Context,
    ): SseManager = SseManager(context)
}
