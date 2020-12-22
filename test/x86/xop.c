/* Copyright (c) 2020 Evan Nemerson <evan@nemerson.com>
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

#include "simde/simde-constify.h"
#include "test/test.h"
#define SIMDE_TESTS_CURRENT_ISAX xop
#include <simde/x86/xop.h>
#include <simde/x86/avx2.h>
#include <test/x86/test-avx.h>

static int
test_simde_mm_cmov_si128 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t c[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i c = simde_x_mm_loadu_epi32(test_vec[i].c);
    simde__m128i r = simde_mm_cmov_si128(a, b, c);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_test_x86_random_i32x4();
    simde__m128i c = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_cmov_si128(a, b, c);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm256_cmov_si256 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[8];
    const int32_t b[8];
    const int32_t c[8];
    const int32_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m256i a = simde_x_mm256_loadu_epi32(test_vec[i].a);
    simde__m256i b = simde_x_mm256_loadu_epi32(test_vec[i].b);
    simde__m256i cc = simde_x_mm256_loadu_epi32(test_vec[i].c);
    simde__m256i r = simde_mm256_cmov_si256(a, b, c);
    simde_test_x86_assert_equal_i32x8(r, simde_x_mm256_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m256i a = simde_test_x86_random_i32x8();
    simde__m256i b = simde_test_x86_random_i32x8();
    simde__m256i c = simde_test_x86_random_i32x8();
    simde__m256i r = simde_mm256_cmov_si256(a, b, c);

    simde_test_x86_write_i32x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comeq_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_comeq_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_comeq_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comeq_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_comeq_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_comeq_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comeq_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_comeq_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_comeq_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comeq_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_comeq_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_comeq_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comeq_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint8_t b[16];
    const uint8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu8(test_vec[i].b);
    simde__m128i r = simde_mm_comeq_epu8(a, b);
    simde_test_x86_assert_equal_u8x16(r, simde_x_mm_loadu_epu8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_comeq_epu8(a, b);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comeq_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint16_t b[8];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu16(test_vec[i].b);
    simde__m128i r = simde_mm_comeq_epu16(a, b);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_comeq_epu16(a, b);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comeq_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint32_t a[4];
    const uint32_t b[4];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu32(test_vec[i].b);
    simde__m128i r = simde_mm_comeq_epu32(a, b);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_comeq_epu32(a, b);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comeq_epu64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint64_t a[2];
    const uint64_t b[2];
    const uint64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu64(test_vec[i].b);
    simde__m128i r = simde_mm_comeq_epu64(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u64x2();
    simde__m128i r = simde_mm_comeq_epu64(a, b);

    simde_test_x86_write_u64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comneq_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_comneq_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_comneq_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comneq_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_comneq_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_comneq_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comneq_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_comneq_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_comneq_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comneq_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_comneq_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_comneq_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comneq_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint8_t b[16];
    const uint8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu8(test_vec[i].b);
    simde__m128i r = simde_mm_comneq_epu8(a, b);
    simde_test_x86_assert_equal_u8x16(r, simde_x_mm_loadu_epu8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_comneq_epu8(a, b);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comneq_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint16_t b[8];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu16(test_vec[i].b);
    simde__m128i r = simde_mm_comneq_epu16(a, b);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_comneq_epu16(a, b);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comneq_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint32_t a[4];
    const uint32_t b[4];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu32(test_vec[i].b);
    simde__m128i r = simde_mm_comneq_epu32(a, b);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_comneq_epu32(a, b);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comneq_epu64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint64_t a[2];
    const uint64_t b[2];
    const uint64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu64(test_vec[i].b);
    simde__m128i r = simde_mm_comneq_epu64(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u64x2();
    simde__m128i r = simde_mm_comneq_epu64(a, b);

    simde_test_x86_write_u64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comge_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_comge_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_comge_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comge_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_comge_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_comge_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comge_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_comge_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_comge_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comge_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_comge_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_comge_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comge_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint8_t b[16];
    const uint8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu8(test_vec[i].b);
    simde__m128i r = simde_mm_comge_epu8(a, b);
    simde_test_x86_assert_equal_u8x16(r, simde_x_mm_loadu_epu8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_comge_epu8(a, b);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comge_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint16_t b[8];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu16(test_vec[i].b);
    simde__m128i r = simde_mm_comge_epu16(a, b);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_comge_epu16(a, b);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comge_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint32_t a[4];
    const uint32_t b[4];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu32(test_vec[i].b);
    simde__m128i r = simde_mm_comge_epu32(a, b);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_comge_epu32(a, b);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comge_epu64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint64_t a[2];
    const uint64_t b[2];
    const uint64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu64(test_vec[i].b);
    simde__m128i r = simde_mm_comge_epu64(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u64x2();
    simde__m128i r = simde_mm_comge_epu64(a, b);

    simde_test_x86_write_u64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comgt_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_comgt_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_comgt_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comgt_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_comgt_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_comgt_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comgt_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_comgt_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_comgt_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comgt_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_comgt_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_comgt_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comgt_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint8_t b[16];
    const uint8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu8(test_vec[i].b);
    simde__m128i r = simde_mm_comgt_epu8(a, b);
    simde_test_x86_assert_equal_u8x16(r, simde_x_mm_loadu_epu8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_comgt_epu8(a, b);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comgt_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint16_t b[8];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu16(test_vec[i].b);
    simde__m128i r = simde_mm_comgt_epu16(a, b);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_comgt_epu16(a, b);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comgt_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint32_t a[4];
    const uint32_t b[4];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu32(test_vec[i].b);
    simde__m128i r = simde_mm_comgt_epu32(a, b);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_comgt_epu32(a, b);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comgt_epu64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint64_t a[2];
    const uint64_t b[2];
    const uint64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu64(test_vec[i].b);
    simde__m128i r = simde_mm_comgt_epu64(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u64x2();
    simde__m128i r = simde_mm_comgt_epu64(a, b);

    simde_test_x86_write_u64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comle_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_comle_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_comle_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comle_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_comle_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_comle_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comle_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_comle_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_comle_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comle_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_comle_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_comle_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comle_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint8_t b[16];
    const uint8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu8(test_vec[i].b);
    simde__m128i r = simde_mm_comle_epu8(a, b);
    simde_test_x86_assert_equal_u8x16(r, simde_x_mm_loadu_epu8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_comle_epu8(a, b);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comle_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint16_t b[8];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu16(test_vec[i].b);
    simde__m128i r = simde_mm_comle_epu16(a, b);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_comle_epu16(a, b);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comle_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint32_t a[4];
    const uint32_t b[4];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu32(test_vec[i].b);
    simde__m128i r = simde_mm_comle_epu32(a, b);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_comle_epu32(a, b);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comle_epu64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint64_t a[2];
    const uint64_t b[2];
    const uint64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu64(test_vec[i].b);
    simde__m128i r = simde_mm_comle_epu64(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u64x2();
    simde__m128i r = simde_mm_comle_epu64(a, b);

    simde_test_x86_write_u64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comlt_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_comlt_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_comlt_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comlt_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_comlt_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_comlt_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comlt_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_comlt_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_comlt_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comlt_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_comlt_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_comlt_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comlt_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint8_t b[16];
    const uint8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu8(test_vec[i].b);
    simde__m128i r = simde_mm_comlt_epu8(a, b);
    simde_test_x86_assert_equal_u8x16(r, simde_x_mm_loadu_epu8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_comlt_epu8(a, b);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comlt_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint16_t b[8];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu16(test_vec[i].b);
    simde__m128i r = simde_mm_comlt_epu16(a, b);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_comlt_epu16(a, b);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comlt_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint32_t a[4];
    const uint32_t b[4];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu32(test_vec[i].b);
    simde__m128i r = simde_mm_comlt_epu32(a, b);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_comlt_epu32(a, b);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comlt_epu64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint64_t a[2];
    const uint64_t b[2];
    const uint64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu64(test_vec[i].b);
    simde__m128i r = simde_mm_comlt_epu64(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u64x2();
    simde__m128i r = simde_mm_comlt_epu64(a, b);

    simde_test_x86_write_u64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comtrue_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_comtrue_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_comtrue_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comtrue_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_comtrue_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_comtrue_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comtrue_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_comtrue_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_comtrue_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comtrue_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_comtrue_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_comtrue_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comtrue_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint8_t b[16];
    const uint8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu8(test_vec[i].b);
    simde__m128i r = simde_mm_comtrue_epu8(a, b);
    simde_test_x86_assert_equal_u8x16(r, simde_x_mm_loadu_epu8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_comtrue_epu8(a, b);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comtrue_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint16_t b[8];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu16(test_vec[i].b);
    simde__m128i r = simde_mm_comtrue_epu16(a, b);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_comtrue_epu16(a, b);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comtrue_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint32_t a[4];
    const uint32_t b[4];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu32(test_vec[i].b);
    simde__m128i r = simde_mm_comtrue_epu32(a, b);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_comtrue_epu32(a, b);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comtrue_epu64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint64_t a[2];
    const uint64_t b[2];
    const uint64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu64(test_vec[i].b);
    simde__m128i r = simde_mm_comtrue_epu64(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u64x2();
    simde__m128i r = simde_mm_comtrue_epu64(a, b);

    simde_test_x86_write_u64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comfalse_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_comfalse_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_comfalse_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comfalse_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_comfalse_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_comfalse_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comfalse_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_comfalse_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_comfalse_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comfalse_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_comfalse_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_comfalse_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comfalse_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint8_t b[16];
    const uint8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu8(test_vec[i].b);
    simde__m128i r = simde_mm_comfalse_epu8(a, b);
    simde_test_x86_assert_equal_u8x16(r, simde_x_mm_loadu_epu8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_comfalse_epu8(a, b);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comfalse_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint16_t b[8];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu16(test_vec[i].b);
    simde__m128i r = simde_mm_comfalse_epu16(a, b);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_comfalse_epu16(a, b);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comfalse_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint32_t a[4];
    const uint32_t b[4];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu32(test_vec[i].b);
    simde__m128i r = simde_mm_comfalse_epu32(a, b);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_comfalse_epu32(a, b);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_comfalse_epu64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint64_t a[2];
    const uint64_t b[2];
    const uint64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epu64(test_vec[i].b);
    simde__m128i r = simde_mm_comfalse_epu64(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u64x2();
    simde__m128i b = (i == 0) ? a : simde_test_x86_random_u64x2();
    simde__m128i r = simde_mm_comfalse_epu64(a, b);

    simde_test_x86_write_u64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_frcz_ps (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float32 a[4];
    const simde_float32 r[4];
  } test_vec[] = {
    #if !defined(SIMDE_FAST_NANS)

    #endif

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128 a = simde_mm_loadu_ps(test_vec[i].a);
    simde__m128 r = simde_mm_frcz_ps(a);
    simde_test_x86_assert_equal_f32x4(r, simde_mm_loadu_ps(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  simde_float32 values[8 * 1 * sizeof(simde__m128)];
  simde_test_x86_random_f32x4_full(8, 1, values, -1000.0f, 1000.0f, SIMDE_TEST_VEC_FLOAT_NAN);

  for (size_t i = 0 ; i < 8 ; i++) {
    simde__m128 a = simde_test_x86_random_extract_f32x4(i, 2, 0, values);
    simde__m128 r = simde_mm_frcz_ps(a);

    simde_test_x86_write_f32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_frcz_pd (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float64 a[2];
    const simde_float64 r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128d a = simde_mm_loadu_pd(test_vec[i].a);
    simde__m128d r = simde_mm_frcz_pd(a);
    simde_test_x86_assert_equal_f64x2(r, simde_mm_loadu_pd(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128d a = simde_test_x86_random_f64x2(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m128d r = simde_mm_frcz_pd(a);

    simde_test_x86_write_f64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_frcz_ss (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float32 a[4];
    const simde_float32 r[4];
  } test_vec[] = {
    #if !defined(SIMDE_FAST_NANS)

    #endif

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128 a = simde_mm_loadu_ss(test_vec[i].a);
    simde__m128 r = simde_mm_frcz_ss(a);
    simde_test_x86_assert_equal_f32x4(r, simde_mm_loadu_ss(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  simde_float32 values[8 * 1 * sizeof(simde__m128)];
  simde_test_x86_random_f32x4_full(8, 1, values, -1000.0f, 1000.0f, SIMDE_TEST_VEC_FLOAT_NAN);

  for (size_t i = 0 ; i < 8 ; i++) {
    simde__m128 a = simde_test_x86_random_extract_f32x4(i, 2, 0, values);
    simde__m128 r = simde_mm_frcz_ss(a);

    simde_test_x86_write_f32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_frcz_sd (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float64 a[2];
    const simde_float64 r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128d a = simde_mm_loadu_sd(test_vec[i].a);
    simde__m128d r = simde_mm_frcz_sd(a);
    simde_test_x86_assert_equal_f64x2(r, simde_mm_loadu_sd(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128d a = simde_test_x86_random_f64x2(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m128d r = simde_mm_frcz_sd(a);

    simde_test_x86_write_f64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm256_frcz_ps (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float32 a[8];
    const simde_float32 r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m256 a = simde_mm256_loadu_ps(test_vec[i].a);
    simde__m256 r = simde_mm256_frcz_ps(a);
    simde_test_x86_assert_equal_f32x8(r, simde_mm256_loadu_ps(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m256 a = simde_test_x86_random_f32x8(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    simde__m256 r = simde_mm256_frcz_ps(a);

    simde_test_x86_write_f32x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f32x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm256_frcz_pd (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float64 a[4];
    const simde_float64 r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m256d a = simde_mm256_loadu_pd(test_vec[i].a);
    simde__m256d r = simde_mm256_frcz_pd(a);
    simde_test_x86_assert_equal_f64x4(r, simde_mm256_loadu_pd(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m256d a = simde_test_x86_random_f64x4(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m256d r = simde_mm256_frcz_pd(a);

    simde_test_x86_write_f64x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f64x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddw_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i r = simde_mm_haddw_epi8(a);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_haddw_epi8(a);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddw_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i r = simde_mm_haddw_epu8(a);
    simde_test_x86_assert_equal_u16x8(r, simde_x_mm_loadu_epu16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_haddw_epu8(a);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddd_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i r = simde_mm_haddd_epi8(a);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_haddd_epi8(a);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddd_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i r = simde_mm_haddd_epi16(a);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_haddd_epi16(a);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddd_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint8_t a[16];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i r = simde_mm_haddd_epu8(a);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_haddd_epu8(a);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddd_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const uint16_t a[8];
    const uint32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i r = simde_mm_haddd_epu16(a);
    simde_test_x86_assert_equal_u32x4(r, simde_x_mm_loadu_epu32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_haddd_epu16(a);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddq_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i r = simde_mm_haddq_epi8(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_haddq_epi8(a);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddq_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i r = simde_mm_haddq_epi16(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_haddq_epi16(a);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddq_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i r = simde_mm_haddq_epi32(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_haddq_epi32(a);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddq_epu8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu8(test_vec[i].a);
    simde__m128i r = simde_mm_haddq_epu8(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u8x16();
    simde__m128i r = simde_mm_haddq_epu8(a);

    simde_test_x86_write_u8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddq_epu16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu16(test_vec[i].a);
    simde__m128i r = simde_mm_haddq_epu16(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u16x8();
    simde__m128i r = simde_mm_haddq_epu16(a);

    simde_test_x86_write_u16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_haddq_epu32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epu32(test_vec[i].a);
    simde__m128i r = simde_mm_haddq_epu32(a, b);
    simde_test_x86_assert_equal_u64x2(r, simde_x_mm_loadu_epu64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_u32x4();
    simde__m128i r = simde_mm_haddq_epu32(a);

    simde_test_x86_write_u32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_u64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_hsubw_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i r = simde_mm_hsubw_epi8(a);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_hsubw_epi8(a);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_hsubd_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i r = simde_mm_hsubd_epi8(a);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_hsubd_epi8(a);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_hsubd_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i r = simde_mm_hsubd_epi16(a);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_hsubd_epi16(a);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_hsubq_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i r = simde_mm_hsubq_epi8(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_hsubq_epi8(a);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_hsubq_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i r = simde_mm_hsubq_epi16(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_hsubq_epi16(a);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_hsubq_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i r = simde_mm_hsubq_epi32(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_hsubq_epi32(a);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_macc_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t c[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i c = simde_x_mm_loadu_epi16(test_vec[i].c);
    simde__m128i r = simde_mm_macc_epi16(a, b, c);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_test_x86_random_i16x8();
    simde__m128i c = simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_macc_epi16(a, b, c);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_macc_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i c = simde_x_mm_loadu_epi32(test_vec[i].c);
    simde__m128i r = simde_mm_macc_epi32(a, b, c);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_test_x86_random_i32x4();
    simde__m128i c = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_macc_epi32(a, b, c);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_maccd_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[4];
    const int16_t b[4];
    const int32_t c[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i c = simde_x_mm_loadu_epi32(test_vec[i].c);
    simde__m128i r = simde_mm_maccd_epi32(a, b, c);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_test_x86_random_i16x8();
    simde__m128i c = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_maccd_epi16(a, b, c);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_macclo_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[2];
    const int32_t b[2];
    const int64_t c[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i C = simde_x_mm_loadu_epi64(test_vec[i].c);
    simde__m128i r = simde_mm_macclo_epi32(a, b, c);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_test_x86_random_i32x4();
    simde__m128i c = simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_macclo_epi32(a, b, c);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_macchi_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[2];
    const int32_t b[2];
    const int64_t c[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i C = simde_x_mm_loadu_epi64(test_vec[i].c);
    simde__m128i r = simde_mm_macchi_epi32(a, b, c);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_test_x86_random_i32x4();
    simde__m128i c = simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_macchi_epi32(a, b, c);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_maccs_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t c[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i c = simde_x_mm_loadu_epi16(test_vec[i].c);
    simde__m128i r = simde_mm_maccs_epi16(a, b, c);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_test_x86_random_i16x8();
    simde__m128i c = simde_test_x86_random_i16x8();
    simde__m128i r = simde_mm_maccs_epi16(a, b, c);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_maccs_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i c = simde_x_mm_loadu_epi32(test_vec[i].c);
    simde__m128i r = simde_mm_maccs_epi32(a, b, c);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_test_x86_random_i32x4();
    simde__m128i c = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_maccs_epi32(a, b, c);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_maccsd_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[4];
    const int16_t b[4];
    const int32_t c[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i c = simde_x_mm_loadu_epi32(test_vec[i].c);
    simde__m128i r = simde_mm_maccsd_epi32(a, b, c);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_test_x86_random_i16x8();
    simde__m128i c = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_maccsd_epi16(a, b, c);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_maccslo_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[2];
    const int32_t b[2];
    const int64_t c[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i C = simde_x_mm_loadu_epi64(test_vec[i].c);
    simde__m128i r = simde_mm_maccslo_epi32(a, b, c);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_test_x86_random_i32x4();
    simde__m128i c = simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_maccslo_epi32(a, b, c);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_maccshi_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[2];
    const int32_t b[2];
    const int64_t c[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i C = simde_x_mm_loadu_epi64(test_vec[i].c);
    simde__m128i r = simde_mm_maccshi_epi32(a, b, c);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_test_x86_random_i32x4();
    simde__m128i c = simde_test_x86_random_i64x2();
    simde__m128i r = simde_mm_maccshi_epi32(a, b, c);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_maddd_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].c);
    simde__m128i r = simde_mm_maddd_epi16(a, b, c);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_test_x86_random_i16x8();
    simde__m128i c = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_maddd_epi16(a, b, c);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_maddsd_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].c);
    simde__m128i r = simde_mm_maddsd_epi16(a, b, c);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_test_x86_random_i16x8();
    simde__m128i c = simde_test_x86_random_i32x4();
    simde__m128i r = simde_mm_maddsd_epi16(a, b, c);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_sha_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_sha_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = simde_test_x86_random_i8x16();

    simde__m128i nmask = simde_mm_cmplt_epi8(b, simde_mm_setzero_si128());
    b = simde_mm_and_si128(b, simde_mm_set1_epi8(7));
    b = simde_mm_or_si128(simde_mm_and_si128(nmask, simde_mm_sub_epi8(simde_mm_setzero_si128(), b)), simde_mm_andnot_si128(nmask, b));

    simde__m128i r = simde_mm_sha_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_sha_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_sha_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_mm_srai_epi16(simde_test_x86_random_i16x8(), 11);
    simde__m128i r = simde_mm_sha_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_sha_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_sha_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_mm_srai_epi32(simde_test_x86_random_i32x4(), 26);
    simde__m128i r = simde_mm_sha_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_sha_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_sha_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = simde_mm_cvtepi32_epi64(simde_mm_srai_epi32(simde_test_x86_random_i32x4(), 25));
    simde__m128i r = simde_mm_sha_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_shl_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_shl_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = simde_test_x86_random_i8x16();

    simde__m128i nmask = simde_mm_cmplt_epi8(b, simde_mm_setzero_si128());
    b = simde_mm_and_si128(b, simde_mm_set1_epi8(7));
    b = simde_mm_or_si128(simde_mm_and_si128(nmask, simde_mm_sub_epi8(simde_mm_setzero_si128(), b)), simde_mm_andnot_si128(nmask, b));

    simde__m128i r = simde_mm_shl_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_shl_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_shl_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_mm_srai_epi16(simde_test_x86_random_i16x8(), 11);
    simde__m128i r = simde_mm_shl_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_shl_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_shl_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_mm_srai_epi32(simde_test_x86_random_i32x4(), 26);
    simde__m128i r = simde_mm_shl_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_shl_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_shl_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = simde_mm_cvtepi32_epi64(simde_mm_srai_epi32(simde_test_x86_random_i32x4(), 25));
    simde__m128i r = simde_mm_shl_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_rot_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i r = simde_mm_rot_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = simde_test_x86_random_i8x16();

    simde__m128i nmask = simde_mm_cmplt_epi8(b, simde_mm_setzero_si128());
    b = simde_mm_and_si128(b, simde_mm_set1_epi8(7));
    b = simde_mm_or_si128(simde_mm_and_si128(nmask, simde_mm_sub_epi8(simde_mm_setzero_si128(), b)), simde_mm_andnot_si128(nmask, b));

    simde__m128i r = simde_mm_rot_epi8(a, b);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_rot_epi16 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int16_t a[8];
    const int16_t b[8];
    const int16_t r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi16(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi16(test_vec[i].b);
    simde__m128i r = simde_mm_rot_epi16(a, b);
    simde_test_x86_assert_equal_i16x8(r, simde_x_mm_loadu_epi16(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i16x8();
    simde__m128i b = simde_mm_srai_epi16(simde_test_x86_random_i16x8(), 11);
    simde__m128i r = simde_mm_rot_epi16(a, b);

    simde_test_x86_write_i16x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i16x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i16x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_rot_epi32 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int32_t a[4];
    const int32_t b[4];
    const int32_t r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi32(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi32(test_vec[i].b);
    simde__m128i r = simde_mm_rot_epi32(a, b);
    simde_test_x86_assert_equal_i32x4(r, simde_x_mm_loadu_epi32(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i32x4();
    simde__m128i b = simde_mm_srai_epi32(simde_test_x86_random_i32x4(), 26);
    simde__m128i r = simde_mm_rot_epi32(a, b);

    simde_test_x86_write_i32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_rot_epi64 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int64_t a[2];
    const int64_t b[2];
    const int64_t r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi64(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi64(test_vec[i].b);
    simde__m128i r = simde_mm_rot_epi64(a, b);
    simde_test_x86_assert_equal_i64x2(r, simde_x_mm_loadu_epi64(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i64x2();
    simde__m128i b = simde_mm_cvtepi32_epi64(simde_mm_srai_epi32(simde_test_x86_random_i32x4(), 25));
    simde__m128i r = simde_mm_rot_epi64(a, b);

    simde_test_x86_write_i64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_perm_epi8 (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const int8_t a[16];
    const int8_t b[16];
    const int8_t c[16];
    const int8_t r[16];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128i a = simde_x_mm_loadu_epi8(test_vec[i].a);
    simde__m128i b = simde_x_mm_loadu_epi8(test_vec[i].b);
    simde__m128i c = simde_x_mm_loadu_epi8(test_vec[i].c);
    simde__m128i r = simde_mm_perm_epi8(a, b);
    simde_test_x86_assert_equal_i8x16(r, simde_x_mm_loadu_epi8(test_vec[i].r));
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128i a = simde_test_x86_random_i8x16();
    simde__m128i b = simde_test_x86_random_i8x16();
    simde__m128i c = simde_test_x86_random_i8x16();
    simde__m128i r = simde_mm_perm_epi8(a, b, c);

    simde_test_x86_write_i8x16(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_i8x16(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i8x16(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_permute2_ps (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float32 a[4];
    const simde_float32 b[4];
    const simde_float32 c[4];
    const simde_float32 r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128 a = simde_mm_loadu_ps(test_vec[i].a);
    simde__m128 b = simde_mm_loadu_ps(test_vec[i].b);
    simde__m128i c = simde_mm_loadu_ps(test_vec[i].c);
    simde__m128 r = simde_mm_permute2_ps(a, b, c);
    simde_test_x86_assert_equal_f32x4(r, simde_mm_loadu_ps(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128 a = simde_test_x86_random_f32x4(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    simde__m128 b = simde_test_x86_random_f32x4(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    simde__m128i c = simde_mm_and_si128(simde_test_x86_random_i32x4(), simde_mm_set1_epi32(0x0f));
    int d = simde_test_codegen_rand() & 0x03;
    simde__m128 r;
    SIMDE_CONSTIFY_4_(simde_mm_permute2_ps, r, (HEDLEY_UNREACHABLE(), simde_mm_setzero_ps ()), d, a, b, c);

    simde_test_x86_write_f32x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f32x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x4(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_f32x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm_permute2_pd (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float64 a[2];
    const simde_float64 b[2];
    const simde_float64 c[2];
    const simde_float64 r[2];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m128d a = simde_mm_loadu_ps(test_vec[i].a);
    simde__m128d b = simde_mm_loadu_ps(test_vec[i].b);
    simde__m128i c = simde_mm_loadu_ps(test_vec[i].c);
    simde__m128d r = simde_mm_permute2_pd(a, b, c);
    simde_test_x86_assert_equal_f64x2(r, simde_mm_loadu_ps(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m128d a = simde_test_x86_random_f64x2(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m128d b = simde_test_x86_random_f64x2(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m128i c = simde_mm_and_si128(simde_test_x86_random_i64x2(), simde_mm_set1_epi64x(0x0e));
    int d = simde_test_codegen_rand() & 0x03;
    simde__m128d r;
    SIMDE_CONSTIFY_4_(simde_mm_permute2_pd, r, (HEDLEY_UNREACHABLE(), simde_mm_setzero_pd ()), d, a, b, c);

    simde_test_x86_write_f64x2(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f64x2(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x2(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_f64x2(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm256_permute2_ps (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float32 a[8];
    const simde_float32 b[8];
    const simde_float32 c[8];
    const simde_float32 r[8];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m256 a = simde_mm_loadu_ps(test_vec[i].a);
    simde__m256 b = simde_mm_loadu_ps(test_vec[i].b);
    simde__m256i c = simde_mm_loadu_ps(test_vec[i].c);
    simde__m256 r = simde_mm256_permute2_ps(a, b, c);
    simde_test_x86_assert_equal_f32x8(r, simde_mm_loadu_ps(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m256 a = simde_test_x86_random_f32x8(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    simde__m256 b = simde_test_x86_random_f32x8(SIMDE_FLOAT32_C(-1000.0), SIMDE_FLOAT32_C(1000.0));
    simde__m256i c = simde_mm256_and_si256(simde_test_x86_random_i32x8(), simde_mm256_set1_epi32(0x0e));
    int d = simde_test_codegen_rand() & 0x03;
    simde__m256 r;
    SIMDE_CONSTIFY_4_(simde_mm256_permute2_ps, r, (HEDLEY_UNREACHABLE(), simde_mm256_setzero_ps ()), d, a, b, c);

    simde_test_x86_write_f32x8(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f32x8(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i32x8(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_f32x8(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

static int
test_simde_mm256_permute2_pd (SIMDE_MUNIT_TEST_ARGS) {
#if 0
  static const struct {
    const simde_float64 a[4];
    const simde_float64 b[4];
    const simde_float64 c[4];
    const simde_float64 r[4];
  } test_vec[] = {

  };

  for (size_t i = 0 ; i < (sizeof(test_vec) / sizeof(test_vec[0])) ; i++) {
    simde__m256d a = simde_mm_loadu_ps(test_vec[i].a);
    simde__m256d b = simde_mm_loadu_ps(test_vec[i].b);
    simde__m256i c = simde_mm_loadu_ps(test_vec[i].c);
    simde__m256d r = simde_mm256_permute2_pd(a, b, c);
    simde_test_x86_assert_equal_f64x4(r, simde_mm_loadu_ps(test_vec[i].r), 1);
  }

  return 0;
#else
  fputc('\n', stdout);
  for (int i = 0 ; i < 8 ; i++) {
    simde__m256d a = simde_test_x86_random_f64x4(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m256d b = simde_test_x86_random_f64x4(SIMDE_FLOAT64_C(-1000.0), SIMDE_FLOAT64_C(1000.0));
    simde__m256i c = simde_mm256_and_si256(simde_test_x86_random_i64x4(), simde_mm256_set1_epi64x(0x0f));
    int d = simde_test_codegen_rand() & 0x03;
    simde__m256d r;
    SIMDE_CONSTIFY_4_(simde_mm256_permute2_pd, r, (HEDLEY_UNREACHABLE(), simde_mm256_setzero_pd ()), d, a, b, c);

    simde_test_x86_write_f64x4(2, a, SIMDE_TEST_VEC_POS_FIRST);
    simde_test_x86_write_f64x4(2, b, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_i64x4(2, c, SIMDE_TEST_VEC_POS_MIDDLE);
    simde_test_x86_write_f64x4(2, r, SIMDE_TEST_VEC_POS_LAST);
  }
  return 1;
#endif
}

SIMDE_TEST_FUNC_LIST_BEGIN
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_cmov_si128)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm256_cmov_si256)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comeq_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comeq_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comeq_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comeq_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comeq_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comeq_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comeq_epu32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comeq_epu64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comneq_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comneq_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comneq_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comneq_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comneq_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comneq_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comneq_epu32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comneq_epu64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comge_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comge_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comge_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comge_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comge_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comge_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comge_epu32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comge_epu64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comgt_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comgt_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comgt_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comgt_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comgt_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comgt_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comgt_epu32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comgt_epu64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comle_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comle_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comle_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comle_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comle_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comle_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comle_epu32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comle_epu64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comlt_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comlt_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comlt_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comlt_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comlt_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comlt_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comlt_epu32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comlt_epu64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comtrue_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comtrue_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comtrue_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comtrue_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comtrue_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comtrue_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comtrue_epu32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comtrue_epu64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comfalse_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comfalse_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comfalse_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comfalse_epi64)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comfalse_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comfalse_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comfalse_epu32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_comfalse_epu64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_frcz_ps)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_frcz_pd)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_frcz_ss)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_frcz_sd)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm256_frcz_ps)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm256_frcz_pd)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddw_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddw_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddd_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddd_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddd_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddd_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddq_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddq_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddq_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddq_epu8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddq_epu16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_haddq_epu32)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_hsubw_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_hsubd_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_hsubd_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_hsubq_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_hsubq_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_hsubq_epi32)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_macc_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_macc_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_maccd_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_macclo_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_macchi_epi32)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_maccs_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_maccs_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_maccsd_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_maccslo_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_maccshi_epi32)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_maddd_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_maddsd_epi16)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_sha_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_sha_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_sha_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_sha_epi64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_shl_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_shl_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_shl_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_shl_epi64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_rot_epi8)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_rot_epi16)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_rot_epi32)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_rot_epi64)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_perm_epi8)

  SIMDE_TEST_FUNC_LIST_ENTRY(mm_permute2_ps)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm_permute2_pd)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm256_permute2_ps)
  SIMDE_TEST_FUNC_LIST_ENTRY(mm256_permute2_pd)
SIMDE_TEST_FUNC_LIST_END

#include <test/x86/test-x86-footer.h>
