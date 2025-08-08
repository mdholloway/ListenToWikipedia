package org.mdholloway.listentowikipedia.di

import android.content.Context
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.android.qualifiers.ApplicationContext
import dagger.hilt.components.SingletonComponent
import org.mdholloway.listentowikipedia.network.RecentChangesSseService
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object NetworkModule {
    @Provides
    @Singleton
    fun provideRecentChangesSseService(
        @ApplicationContext context: Context,
    ): RecentChangesSseService = RecentChangesSseService(context)
}
