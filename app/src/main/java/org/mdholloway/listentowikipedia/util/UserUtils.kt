package org.mdholloway.listentowikipedia.util

/**
 * Helper function to check if a string is an IP address
 */
fun isIpAddress(input: String): Boolean {
    val ipv4Pattern = "^([0-9]{1,3}\\.)+\\d{1,3}$".toRegex()
    val ipv6Pattern = "^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$".toRegex()
    return input.matches(ipv4Pattern) || input.matches(ipv6Pattern)
}
