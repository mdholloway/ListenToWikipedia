package org.mdholloway.listentowikipedia.util

import com.google.common.truth.Truth.assertThat
import org.junit.Test

class UserUtilsTest {
    @Test
    fun `isIpAddress returns true for valid IPv4 addresses`() {
        assertThat(isIpAddress("192.168.1.1")).isTrue()
        assertThat(isIpAddress("10.0.0.1")).isTrue()
        assertThat(isIpAddress("127.0.0.1")).isTrue()
        assertThat(isIpAddress("255.255.255.255")).isTrue()
    }

    @Test
    fun `isIpAddress returns true for valid IPv6 addresses`() {
        assertThat(isIpAddress("2001:0db8:85a3:0000:0000:8a2e:0370:7334")).isTrue()
        assertThat(isIpAddress("2001:db8:85a3:0:0:8a2e:370:7334")).isTrue()
    }

    @Test
    fun `isIpAddress returns false for invalid addresses`() {
        assertThat(isIpAddress("300.300.300.300")).isFalse()
        assertThat(isIpAddress("192.168.1")).isFalse()
        assertThat(isIpAddress("not.an.ip.address")).isFalse()
        assertThat(isIpAddress("")).isFalse()
    }

    @Test
    fun `isIpAddress returns false for usernames`() {
        assertThat(isIpAddress("User123")).isFalse()
        assertThat(isIpAddress("WikipediaEditor")).isFalse()
        assertThat(isIpAddress("Admin")).isFalse()
    }

    @Test
    fun `isIpAddress handles edge cases`() {
        assertThat(isIpAddress("0.0.0.0")).isTrue()
        assertThat(isIpAddress("192.168.1.1.1")).isFalse()
        assertThat(isIpAddress("192.168.01.1")).isFalse() // Leading zeros
    }
}
