package org.mdholloway.listentowikipedia.di

import android.content.Context
import com.DspFaust.DspFaust
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.components.ActivityComponent
import dagger.hilt.android.qualifiers.ActivityContext
import dagger.hilt.android.scopes.ActivityScoped
import org.mdholloway.listentowikipedia.network.SseManager

@Module
@InstallIn(ActivityComponent::class)
object ActivityScopedModule {
    @Provides
    @ActivityScoped
    fun provideDspFaust(): DspFaust = DspFaust()

    @Provides
    @ActivityScoped
    fun provideSseManager(
        @ActivityContext context: Context,
    ): SseManager = SseManager(context)
}
