package org.mdholloway.listentowikipedia.testutil

import android.util.Log
import io.mockk.every
import io.mockk.mockk
import io.mockk.mockkStatic
import io.mockk.unmockkStatic
import org.junit.rules.TestRule
import org.junit.runner.Description
import org.junit.runners.model.Statement

class AndroidLogRule : TestRule {
    override fun apply(
        base: Statement,
        description: Description,
    ): Statement =
        object : Statement() {
            override fun evaluate() {
                mockkStatic(Log::class)
                every { Log.v(any(), any()) } returns 0
                every { Log.d(any(), any()) } returns 0
                every { Log.i(any(), any()) } returns 0
                every { Log.w(any(), any<String>()) } returns 0
                every { Log.e(any(), any<String>()) } returns 0
                every { Log.e(any(), any(), any()) } returns 0

                try {
                    base.evaluate()
                } finally {
                    unmockkStatic(Log::class)
                }
            }
        }
}
