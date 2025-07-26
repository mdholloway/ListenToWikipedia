package org.mdholloway.listentowikipedia.model

import kotlinx.serialization.Serializable

@Serializable
data class RecentChangeEvent(
    val type: String,
    val namespace: Int,
    val title: String,
    val comment: String,
    val timestamp: Long,
    val user: String,
    val bot: Boolean,
    val minor: Boolean? = null,
    val length: Length? = null,
    val wiki: String,
)