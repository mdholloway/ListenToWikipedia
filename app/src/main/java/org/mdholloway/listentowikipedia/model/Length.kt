package org.mdholloway.listentowikipedia.model

import kotlinx.serialization.Serializable

@Serializable
data class Length(
    val old: Int? = null,
    val new: Int,
)
