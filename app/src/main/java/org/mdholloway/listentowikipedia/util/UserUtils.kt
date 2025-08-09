package org.mdholloway.listentowikipedia.util

/**
 * Helper function to check if a string is an IP address
 */
fun isIpAddress(input: String): Boolean {
    if (input.isEmpty()) return false

    // IPv4 pattern - exactly 4 groups of 1-3 digits, each group 0-255
    val ipv4Pattern =
        "^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$"
            .toRegex()

    // IPv6 pattern - exactly 8 groups of 1-4 hex digits
    val ipv6Pattern = "^([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$".toRegex()

    return input.matches(ipv4Pattern) || input.matches(ipv6Pattern)
}
