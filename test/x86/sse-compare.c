/* Copyright (c) 2017, 2019 Evan Nemerson <evan@nemerson.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define SIMDE_TESTS_CURRENT_ISAX sse
#include <simde/x86/sse2.h>
#include <test/x86/test-sse2.h>

#if defined(__SSE__)
#include <xmmintrin.h>

#if !defined(SIMDE_TESTS_COMPARE_ITERATIONS)
  #define SIMDE_TESTS_COMPARE_ITERATIONS (1 << 10)
#endif

static int
test_simde_mm_add_ps (SIMDE_MUNIT_TEST_ARGS) {
  for (size_t i = 0 ; i < SIMDE_TESTS_COMPARE_ITERATIONS ; i++) {
    simde__m128 a = simde_test_x86_random_f32x4(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    simde__m128 b = simde_test_x86_random_f32x4(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));

    simde__m128 r = simde_mm_add_ps(a, b);
    simde__m128 e = _mm_add_ps(a, b);

    simde_test_x86_assert_equal_f32x4(r, e, 1);
  }

  return 0;
}
#endif

SIMDE_TEST_FUNC_LIST_BEGIN
  #if defined(__SSE__)
    SIMDE_TEST_FUNC_LIST_ENTRY(mm_add_ps)
  #endif
SIMDE_TEST_FUNC_LIST_END

#include <test/x86/test-x86-footer.h>
