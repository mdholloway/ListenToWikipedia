package org.mdholloway.listentowikipedia.di

import com.DspFaust.DspFaust
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.components.ActivityComponent
import dagger.hilt.android.scopes.ActivityScoped

@Module
@InstallIn(ActivityComponent::class)
object AudioModule {
    @Provides
    @ActivityScoped
    fun provideDspFaust(): DspFaust = DspFaust()
}
