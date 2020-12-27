/* SPDX-License-Identifier: MIT
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
 *
 * Copyright:
 *   2020      Evan Nemerson <evan@nemerson.com>
 */

#if !defined(SIMDE_X86_XOP_H)
#define SIMDE_X86_XOP_H

#include "avx.h"

#if !defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_ENABLE_NATIVE_ALIASES)
#  define SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES
#endif

HEDLEY_DIAGNOSTIC_PUSH
SIMDE_DISABLE_UNWANTED_DIAGNOSTICS
SIMDE_BEGIN_DECLS_

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_cmov_si128 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_cmov_si128(a, b, c);
  #elif defined(SIMDE_X86_AVX512VL_NATIVE)
    return _mm_ternarylogic_epi32(a, b, c, 0xca);
  #elif defined(SIMDE_X86_SSE2_NATIVE)
    return _mm_or_si128(_mm_and_si128(c, a), _mm_andnot_si128(c, b));
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    #if defined(SIMDE_ARM_NEON_A32V7_NATIVE)
      r_.neon_i8 = vbslq_s8(c_.neon_u8, a_.neon_i8, b_.neon_i8);
    #elif defined(SIMDE_WASM_SIMD128_NATIVE)
      r_.wasm_v128 = wasm_v128_bitselect(a_.wasm_v128, b_.wasm_v128, c_.wasm_v128);
    #elif defined(SIMDE_POWER_ALTIVEC_P7_NATIVE)
      r_.altivec_i32 = vec_sel(b_.altivec_i32, a_.altivec_i32, c_.altivec_u32);
    #elif defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i32f = (c_.i32f & a_.i32f) | (~c_.i32f & b_.i32f);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i32f) / sizeof(r_.i32f[0])) ; i++) {
        r_.i32f[i] = (c_.i32f[i] & a_.i32f[i]) | (~c_.i32f[i] & b_.i32f[i]);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_cmov_si128(a, b, c) simde_mm_cmov_si128((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m256i
simde_mm256_cmov_si256 (simde__m256i a, simde__m256i b, simde__m256i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm256_cmov_si256(a, b, c);
  #elif defined(SIMDE_X86_AVX512VL_NATIVE)
    return _mm256_ternarylogic_epi32(a, b, c, 0xca);
  #else
    simde__m256i_private
      r_,
      a_ = simde__m256i_to_private(a),
      b_ = simde__m256i_to_private(b),
      c_ = simde__m256i_to_private(c);

    #if SIMDE_NATURAL_VECTOR_SIZE_LE(128)
      for (size_t i = 0 ; i < (sizeof(r_.m128i) / sizeof(r_.m128i[0])) ; i++) {
        r_.m128i[i] = simde_mm_cmov_si128(a_.m128i[i], b_.m128i[i], c_.m128i[i]);
      }
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i32f) / sizeof(r_.i32f[0])) ; i++) {
        r_.i32f[i] = (c_.i32f[i] & a_.i32f[i]) | (~c_.i32f[i] & b_.i32f[i]);
      }
    #endif

    return simde__m256i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm256_cmov_si256(a, b, c) simde_mm256_cmov_si256((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comeq_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_EQ)
    return _mm_com_epi8(a, b, _MM_PCOMCTRL_EQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comeq_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i8), a_.i8 == b_.i8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i8) / sizeof(r_.i8[0])) ; i++) {
        r_.i8[i] = (a_.i8[i] == b_.i8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comeq_epi8(a, b) simde_mm_comeq_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comeq_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_EQ)
    return _mm_com_epi16(a, b, _MM_PCOMCTRL_EQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comeq_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i16), a_.i16 == b_.i16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
        r_.i16[i] = (a_.i16[i] == b_.i16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comeq_epi16(a, b) simde_mm_comeq_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comeq_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_EQ)
    return _mm_com_epi32(a, b, _MM_PCOMCTRL_EQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comeq_epi32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i32), a_.i32 == b_.i32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
        r_.i32[i] = (a_.i32[i] == b_.i32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comeq_epi32(a, b) simde_mm_comeq_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comeq_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_EQ)
    return _mm_com_epi64(a, b, _MM_PCOMCTRL_EQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comeq_epi64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i64), a_.i64 == b_.i64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
        r_.i64[i] = (a_.i64[i] == b_.i64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comeq_epi64(a, b) simde_mm_comeq_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comeq_epu8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_EQ)
    return _mm_com_epu8(a, b, _MM_PCOMCTRL_EQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comeq_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u8), a_.u8 == b_.u8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
        r_.u8[i] = (a_.u8[i] == b_.u8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comeq_epu8(a, b) simde_mm_comeq_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comeq_epu16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_EQ)
    return _mm_com_epu16(a, b, _MM_PCOMCTRL_EQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comeq_epu16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u16), a_.u16 == b_.u16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
        r_.u16[i] = (a_.u16[i] == b_.u16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comeq_epu16(a, b) simde_mm_comeq_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comeq_epu32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_EQ)
    return _mm_com_epu32(a, b, _MM_PCOMCTRL_EQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comeq_epu32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u32), a_.u32 == b_.u32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
        r_.u32[i] = (a_.u32[i] == b_.u32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comeq_epu32(a, b) simde_mm_comeq_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comeq_epu64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_EQ)
    return _mm_com_epu64(a, b, _MM_PCOMCTRL_EQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comeq_epu64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u64), a_.u64 == b_.u64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
        r_.u64[i] = (a_.u64[i] == b_.u64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comeq_epu64(a, b) simde_mm_comeq_epu64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comge_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GE)
    return _mm_com_epi8(a, b, _MM_PCOMCTRL_GE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comge_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i8), a_.i8 >= b_.i8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i8) / sizeof(r_.i8[0])) ; i++) {
        r_.i8[i] = (a_.i8[i] >= b_.i8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comge_epi8(a, b) simde_mm_comge_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comge_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GE)
    return _mm_com_epi16(a, b, _MM_PCOMCTRL_GE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comge_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i16), a_.i16 >= b_.i16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
        r_.i16[i] = (a_.i16[i] >= b_.i16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comge_epi16(a, b) simde_mm_comge_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comge_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GE)
    return _mm_com_epi32(a, b, _MM_PCOMCTRL_GE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comge_epi32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i32), a_.i32 >= b_.i32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
        r_.i32[i] = (a_.i32[i] >= b_.i32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comge_epi32(a, b) simde_mm_comge_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comge_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GE)
    return _mm_com_epi64(a, b, _MM_PCOMCTRL_GE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comge_epi64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i64), a_.i64 >= b_.i64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
        r_.i64[i] = (a_.i64[i] >= b_.i64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comge_epi64(a, b) simde_mm_comge_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comge_epu8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GE)
    return _mm_com_epu8(a, b, _MM_PCOMCTRL_GE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comge_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u8), a_.u8 >= b_.u8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
        r_.u8[i] = (a_.u8[i] >= b_.u8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comge_epu8(a, b) simde_mm_comge_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comge_epu16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GE)
    return _mm_com_epu16(a, b, _MM_PCOMCTRL_GE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comge_epu16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u16), a_.u16 >= b_.u16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
        r_.u16[i] = (a_.u16[i] >= b_.u16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comge_epu16(a, b) simde_mm_comge_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comge_epu32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GE)
    return _mm_com_epu32(a, b, _MM_PCOMCTRL_GE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comge_epu32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u32), a_.u32 >= b_.u32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
        r_.u32[i] = (a_.u32[i] >= b_.u32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comge_epu32(a, b) simde_mm_comge_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comge_epu64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GE)
    return _mm_com_epu64(a, b, _MM_PCOMCTRL_GE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comge_epu64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u64), a_.u64 >= b_.u64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
        r_.u64[i] = (a_.u64[i] >= b_.u64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comge_epu64(a, b) simde_mm_comge_epu64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comgt_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GT)
    return _mm_com_epi8(a, b, _MM_PCOMCTRL_GT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comgt_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i8), a_.i8 > b_.i8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i8) / sizeof(r_.i8[0])) ; i++) {
        r_.i8[i] = (a_.i8[i] > b_.i8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comgt_epi8(a, b) simde_mm_comgt_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comgt_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GT)
    return _mm_com_epi16(a, b, _MM_PCOMCTRL_GT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comgt_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i16), a_.i16 > b_.i16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
        r_.i16[i] = (a_.i16[i] > b_.i16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comgt_epi16(a, b) simde_mm_comgt_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comgt_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GT)
    return _mm_com_epi32(a, b, _MM_PCOMCTRL_GT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comgt_epi32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i32), a_.i32 > b_.i32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
        r_.i32[i] = (a_.i32[i] > b_.i32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comgt_epi32(a, b) simde_mm_comgt_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comgt_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GT)
    return _mm_com_epi64(a, b, _MM_PCOMCTRL_GT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comgt_epi64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i64), a_.i64 > b_.i64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
        r_.i64[i] = (a_.i64[i] > b_.i64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comgt_epi64(a, b) simde_mm_comgt_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comgt_epu8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GT)
    return _mm_com_epu8(a, b, _MM_PCOMCTRL_GT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comgt_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u8), a_.u8 > b_.u8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
        r_.u8[i] = (a_.u8[i] > b_.u8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comgt_epu8(a, b) simde_mm_comgt_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comgt_epu16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GT)
    return _mm_com_epu16(a, b, _MM_PCOMCTRL_GT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comgt_epu16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u16), a_.u16 > b_.u16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
        r_.u16[i] = (a_.u16[i] > b_.u16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comgt_epu16(a, b) simde_mm_comgt_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comgt_epu32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GT)
    return _mm_com_epu32(a, b, _MM_PCOMCTRL_GT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comgt_epu32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u32), a_.u32 > b_.u32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
        r_.u32[i] = (a_.u32[i] > b_.u32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comgt_epu32(a, b) simde_mm_comgt_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comgt_epu64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_GT)
    return _mm_com_epu64(a, b, _MM_PCOMCTRL_GT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comgt_epu64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u64), a_.u64 > b_.u64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
        r_.u64[i] = (a_.u64[i] > b_.u64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comgt_epu64(a, b) simde_mm_comgt_epu64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comle_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LE)
    return _mm_com_epi8(a, b, _MM_PCOMCTRL_LE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comle_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i8), a_.i8 <= b_.i8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i8) / sizeof(r_.i8[0])) ; i++) {
        r_.i8[i] = (a_.i8[i] <= b_.i8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comle_epi8(a, b) simde_mm_comle_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comle_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LE)
    return _mm_com_epi16(a, b, _MM_PCOMCTRL_LE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comle_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i16), a_.i16 <= b_.i16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
        r_.i16[i] = (a_.i16[i] <= b_.i16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comle_epi16(a, b) simde_mm_comle_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comle_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LE)
    return _mm_com_epi32(a, b, _MM_PCOMCTRL_LE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comle_epi32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i32), a_.i32 <= b_.i32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
        r_.i32[i] = (a_.i32[i] <= b_.i32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comle_epi32(a, b) simde_mm_comle_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comle_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LE)
    return _mm_com_epi64(a, b, _MM_PCOMCTRL_LE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comle_epi64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i64), a_.i64 <= b_.i64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
        r_.i64[i] = (a_.i64[i] <= b_.i64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comle_epi64(a, b) simde_mm_comle_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comle_epu8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LE)
    return _mm_com_epu8(a, b, _MM_PCOMCTRL_LE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comle_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u8), a_.u8 <= b_.u8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
        r_.u8[i] = (a_.u8[i] <= b_.u8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comle_epu8(a, b) simde_mm_comle_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comle_epu16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LE)
    return _mm_com_epu16(a, b, _MM_PCOMCTRL_LE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comle_epu16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u16), a_.u16 <= b_.u16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
        r_.u16[i] = (a_.u16[i] <= b_.u16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comle_epu16(a, b) simde_mm_comle_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comle_epu32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LE)
    return _mm_com_epu32(a, b, _MM_PCOMCTRL_LE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comle_epu32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u32), a_.u32 <= b_.u32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
        r_.u32[i] = (a_.u32[i] <= b_.u32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comle_epu32(a, b) simde_mm_comle_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comle_epu64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LE)
    return _mm_com_epu64(a, b, _MM_PCOMCTRL_LE);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comle_epu64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u64), a_.u64 <= b_.u64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
        r_.u64[i] = (a_.u64[i] <= b_.u64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comle_epu64(a, b) simde_mm_comle_epu64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comlt_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
    return _mm_com_epi8(a, b, _MM_PCOMCTRL_LT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comlt_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i8), a_.i8 < b_.i8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i8) / sizeof(r_.i8[0])) ; i++) {
        r_.i8[i] = (a_.i8[i] < b_.i8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comlt_epi8(a, b) simde_mm_comlt_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comlt_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
    return _mm_com_epi16(a, b, _MM_PCOMCTRL_LT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comlt_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i16), a_.i16 < b_.i16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
        r_.i16[i] = (a_.i16[i] < b_.i16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comlt_epi16(a, b) simde_mm_comlt_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comlt_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
    return _mm_com_epi32(a, b, _MM_PCOMCTRL_LT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comlt_epi32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i32), a_.i32 < b_.i32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
        r_.i32[i] = (a_.i32[i] < b_.i32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comlt_epi32(a, b) simde_mm_comlt_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comlt_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
    return _mm_com_epi64(a, b, _MM_PCOMCTRL_LT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comlt_epi64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i64), a_.i64 < b_.i64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
        r_.i64[i] = (a_.i64[i] < b_.i64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comlt_epi64(a, b) simde_mm_comlt_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comlt_epu8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
    return _mm_com_epu8(a, b, _MM_PCOMCTRL_LT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comlt_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u8), a_.u8 < b_.u8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
        r_.u8[i] = (a_.u8[i] < b_.u8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comlt_epu8(a, b) simde_mm_comlt_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comlt_epu16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
    return _mm_com_epu16(a, b, _MM_PCOMCTRL_LT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comlt_epu16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u16), a_.u16 < b_.u16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
        r_.u16[i] = (a_.u16[i] < b_.u16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comlt_epu16(a, b) simde_mm_comlt_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comlt_epu32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
    return _mm_com_epu32(a, b, _MM_PCOMCTRL_LT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comlt_epu32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u32), a_.u32 < b_.u32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
        r_.u32[i] = (a_.u32[i] < b_.u32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comlt_epu32(a, b) simde_mm_comlt_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comlt_epu64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
    return _mm_com_epu64(a, b, _MM_PCOMCTRL_LT);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comlt_epu64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u64), a_.u64 < b_.u64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
        r_.u64[i] = (a_.u64[i] < b_.u64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comlt_epu64(a, b) simde_mm_comlt_epu64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comneq_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_NEQ)
    return _mm_com_epi8(a, b, _MM_PCOMCTRL_NEQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comneq_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i8), a_.i8 != b_.i8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i8) / sizeof(r_.i8[0])) ; i++) {
        r_.i8[i] = (a_.i8[i] != b_.i8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comneq_epi8(a, b) simde_mm_comneq_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comneq_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_NEQ)
    return _mm_com_epi16(a, b, _MM_PCOMCTRL_NEQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comneq_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i16), a_.i16 != b_.i16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
        r_.i16[i] = (a_.i16[i] != b_.i16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comneq_epi16(a, b) simde_mm_comneq_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comneq_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_NEQ)
    return _mm_com_epi32(a, b, _MM_PCOMCTRL_NEQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comneq_epi32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i32), a_.i32 != b_.i32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
        r_.i32[i] = (a_.i32[i] != b_.i32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comneq_epi32(a, b) simde_mm_comneq_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comneq_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_NEQ)
    return _mm_com_epi64(a, b, _MM_PCOMCTRL_NEQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comneq_epi64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.i64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.i64), a_.i64 != b_.i64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
        r_.i64[i] = (a_.i64[i] != b_.i64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comneq_epi64(a, b) simde_mm_comneq_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comneq_epu8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_NEQ)
    return _mm_com_epu8(a, b, _MM_PCOMCTRL_NEQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comneq_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u8 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u8), a_.u8 != b_.u8);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
        r_.u8[i] = (a_.u8[i] != b_.u8[i]) ? ~INT8_C(0) : INT8_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comneq_epu8(a, b) simde_mm_comneq_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comneq_epu16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_NEQ)
    return _mm_com_epu16(a, b, _MM_PCOMCTRL_NEQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comneq_epu16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u16 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u16), a_.u16 != b_.u16);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
        r_.u16[i] = (a_.u16[i] != b_.u16[i]) ? ~INT16_C(0) : INT16_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comneq_epu16(a, b) simde_mm_comneq_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comneq_epu32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_NEQ)
    return _mm_com_epu32(a, b, _MM_PCOMCTRL_NEQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comneq_epu32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u32 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u32), a_.u32 != b_.u32);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
        r_.u32[i] = (a_.u32[i] != b_.u32[i]) ? ~INT32_C(0) : INT32_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comneq_epu32(a, b) simde_mm_comneq_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comneq_epu64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_NEQ)
    return _mm_com_epu64(a, b, _MM_PCOMCTRL_NEQ);
  #elif defined(SIMDE_X86_XOP_NATIVE)
    return _mm_comneq_epu64(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    #if defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
      r_.u64 = HEDLEY_REINTERPRET_CAST(__typeof__(r_.u64), a_.u64 != b_.u64);
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
        r_.u64[i] = (a_.u64[i] != b_.u64[i]) ? ~INT64_C(0) : INT64_C(0);
      }
    #endif

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comneq_epu64(a, b) simde_mm_comneq_epu64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comfalse_epi8 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_mm_setzero_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comfalse_epi8(a, b) simde_mm_comfalse_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comfalse_epi16 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_mm_setzero_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comfalse_epi16(a, b) simde_mm_comfalse_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comfalse_epi32 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_mm_setzero_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comfalse_epi32(a, b) simde_mm_comfalse_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comfalse_epi64 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_mm_setzero_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comfalse_epi64(a, b) simde_mm_comfalse_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comfalse_epu8 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_mm_setzero_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comfalse_epu8(a, b) simde_mm_comfalse_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comfalse_epu16 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_mm_setzero_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comfalse_epu16(a, b) simde_mm_comfalse_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comfalse_epu32 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_mm_setzero_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comfalse_epu32(a, b) simde_mm_comfalse_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comfalse_epu64 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_mm_setzero_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comfalse_epu64(a, b) simde_mm_comfalse_epu64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comtrue_epi8 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_x_mm_setone_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comtrue_epi8(a, b) simde_mm_comtrue_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comtrue_epi16 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_x_mm_setone_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comtrue_epi16(a, b) simde_mm_comtrue_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comtrue_epi32 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_x_mm_setone_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comtrue_epi32(a, b) simde_mm_comtrue_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comtrue_epi64 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_x_mm_setone_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comtrue_epi64(a, b) simde_mm_comtrue_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comtrue_epu8 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_x_mm_setone_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comtrue_epu8(a, b) simde_mm_comtrue_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comtrue_epu16 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_x_mm_setone_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comtrue_epu16(a, b) simde_mm_comtrue_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comtrue_epu32 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_x_mm_setone_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comtrue_epu32(a, b) simde_mm_comtrue_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_comtrue_epu64 (simde__m128i a, simde__m128i b) {
  (void) a;
  (void) b;
  return simde_x_mm_setone_si128();
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_comtrue_epu64(a, b) simde_mm_comtrue_epu64((a), (b))
#endif

#if defined(SIMDE_X86_XOP_NATIVE) && defined(_MM_PCOMCTRL_LT)
  #define SIMDE_X86_XOP_HAVE_COM_ 1
  #define SIMDE_MM_PCOMCTRL_LT    _MM_PCOMCTRL_LT
  #define SIMDE_MM_PCOMCTRL_LE    _MM_PCOMCTRL_LE
  #define SIMDE_MM_PCOMCTRL_GT    _MM_PCOMCTRL_GT
  #define SIMDE_MM_PCOMCTRL_GE    _MM_PCOMCTRL_GE
  #define SIMDE_MM_PCOMCTRL_EQ    _MM_PCOMCTRL_EQ
  #define SIMDE_MM_PCOMCTRL_NEQ   _MM_PCOMCTRL_NEQ
  #define SIMDE_MM_PCOMCTRL_FALSE _MM_PCOMCTRL_FALSE
  #define SIMDE_MM_PCOMCTRL_TRUE  _MM_PCOMCTRL_TRUE
#else
  #define SIMDE_MM_PCOMCTRL_LT    0
  #define SIMDE_MM_PCOMCTRL_LE    1
  #define SIMDE_MM_PCOMCTRL_GT    2
  #define SIMDE_MM_PCOMCTRL_GE    3
  #define SIMDE_MM_PCOMCTRL_EQ    4
  #define SIMDE_MM_PCOMCTRL_NEQ   5
  #define SIMDE_MM_PCOMCTRL_FALSE 6
  #define SIMDE_MM_PCOMCTRL_TRUE  7

  #if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
    #define _MM_PCOMCTRL_LT    SIMDE_MM_PCOMCTRL_LT
    #define _MM_PCOMCTRL_LE    SIMDE_MM_PCOMCTRL_LE
    #define _MM_PCOMCTRL_GT    SIMDE_MM_PCOMCTRL_GT
    #define _MM_PCOMCTRL_GE    SIMDE_MM_PCOMCTRL_GE
    #define _MM_PCOMCTRL_EQ    SIMDE_MM_PCOMCTRL_EQ
    #define _MM_PCOMCTRL_NEQ   SIMDE_MM_PCOMCTRL_NEQ
    #define _MM_PCOMCTRL_FALSE SIMDE_MM_PCOMCTRL_FALSE
    #define _MM_PCOMCTRL_TRUE  SIMDE_MM_PCOMCTRL_TRUE
  #endif
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_com_epi8 (simde__m128i a, simde__m128i b, const int imm8)
    SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 7) {
  switch (imm8) {
    case SIMDE_MM_PCOMCTRL_LT:
      return simde_mm_comlt_epi8(a, b);
    case SIMDE_MM_PCOMCTRL_LE:
      return simde_mm_comle_epi8(a, b);
    case SIMDE_MM_PCOMCTRL_GT:
      return simde_mm_comgt_epi8(a, b);
    case SIMDE_MM_PCOMCTRL_GE:
      return simde_mm_comge_epi8(a, b);
    case SIMDE_MM_PCOMCTRL_EQ:
      return simde_mm_comeq_epi8(a, b);
    case SIMDE_MM_PCOMCTRL_NEQ:
      return simde_mm_comneq_epi8(a, b);
    case SIMDE_MM_PCOMCTRL_FALSE:
      return simde_mm_comfalse_epi8(a, b);
    case SIMDE_MM_PCOMCTRL_TRUE:
      return simde_mm_comtrue_epi8(a, b);
    default:
      HEDLEY_UNREACHABLE_RETURN(simde_mm_setzero_si128());
  }
}
#if defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_X86_XOP_HAVE_COM_)
  #define simde_mm_com_epi8(a, b, imm8) _mm_com_epi8((a), (b), (imm8))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_com_epi8(a, b, imm8) simde_mm_com_epi8((a), (b), (imm8))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_com_epi16 (simde__m128i a, simde__m128i b, const int imm8)
    SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 7) {
  switch (imm8) {
    case SIMDE_MM_PCOMCTRL_LT:
      return simde_mm_comlt_epi16(a, b);
    case SIMDE_MM_PCOMCTRL_LE:
      return simde_mm_comle_epi16(a, b);
    case SIMDE_MM_PCOMCTRL_GT:
      return simde_mm_comgt_epi16(a, b);
    case SIMDE_MM_PCOMCTRL_GE:
      return simde_mm_comge_epi16(a, b);
    case SIMDE_MM_PCOMCTRL_EQ:
      return simde_mm_comeq_epi16(a, b);
    case SIMDE_MM_PCOMCTRL_NEQ:
      return simde_mm_comneq_epi16(a, b);
    case SIMDE_MM_PCOMCTRL_FALSE:
      return simde_mm_comfalse_epi16(a, b);
    case SIMDE_MM_PCOMCTRL_TRUE:
      return simde_mm_comtrue_epi16(a, b);
    default:
      HEDLEY_UNREACHABLE_RETURN(simde_mm_setzero_si128());
  }
}
#if defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_X86_XOP_HAVE_COM_)
  #define simde_mm_com_epi16(a, b, imm8) _mm_com_epi16((a), (b), (imm8))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_com_epi16(a, b, imm8) simde_mm_com_epi16((a), (b), (imm8))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_com_epi32 (simde__m128i a, simde__m128i b, const int imm8)
    SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 7) {
  switch (imm8) {
    case SIMDE_MM_PCOMCTRL_LT:
      return simde_mm_comlt_epi32(a, b);
    case SIMDE_MM_PCOMCTRL_LE:
      return simde_mm_comle_epi32(a, b);
    case SIMDE_MM_PCOMCTRL_GT:
      return simde_mm_comgt_epi32(a, b);
    case SIMDE_MM_PCOMCTRL_GE:
      return simde_mm_comge_epi32(a, b);
    case SIMDE_MM_PCOMCTRL_EQ:
      return simde_mm_comeq_epi32(a, b);
    case SIMDE_MM_PCOMCTRL_NEQ:
      return simde_mm_comneq_epi32(a, b);
    case SIMDE_MM_PCOMCTRL_FALSE:
      return simde_mm_comfalse_epi32(a, b);
    case SIMDE_MM_PCOMCTRL_TRUE:
      return simde_mm_comtrue_epi32(a, b);
    default:
      HEDLEY_UNREACHABLE_RETURN(simde_mm_setzero_si128());
  }
}
#if defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_X86_XOP_HAVE_COM_)
  #define simde_mm_com_epi32(a, b, imm8) _mm_com_epi32((a), (b), (imm8))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_com_epi32(a, b, imm8) simde_mm_com_epi32((a), (b), (imm8))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_com_epi64 (simde__m128i a, simde__m128i b, const int imm8)
    SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 7) {
  switch (imm8) {
    case SIMDE_MM_PCOMCTRL_LT:
      return simde_mm_comlt_epi64(a, b);
    case SIMDE_MM_PCOMCTRL_LE:
      return simde_mm_comle_epi64(a, b);
    case SIMDE_MM_PCOMCTRL_GT:
      return simde_mm_comgt_epi64(a, b);
    case SIMDE_MM_PCOMCTRL_GE:
      return simde_mm_comge_epi64(a, b);
    case SIMDE_MM_PCOMCTRL_EQ:
      return simde_mm_comeq_epi64(a, b);
    case SIMDE_MM_PCOMCTRL_NEQ:
      return simde_mm_comneq_epi64(a, b);
    case SIMDE_MM_PCOMCTRL_FALSE:
      return simde_mm_comfalse_epi64(a, b);
    case SIMDE_MM_PCOMCTRL_TRUE:
      return simde_mm_comtrue_epi64(a, b);
    default:
      HEDLEY_UNREACHABLE_RETURN(simde_mm_setzero_si128());
  }
}
#if defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_X86_XOP_HAVE_COM_)
  #define simde_mm_com_epi64(a, b, imm8) _mm_com_epi64((a), (b), (imm8))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_com_epi64(a, b, imm8) simde_mm_com_epi64((a), (b), (imm8))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_com_epu8 (simde__m128i a, simde__m128i b, const int imm8)
    SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 7) {
  switch (imm8) {
    case SIMDE_MM_PCOMCTRL_LT:
      return simde_mm_comlt_epu8(a, b);
    case SIMDE_MM_PCOMCTRL_LE:
      return simde_mm_comle_epu8(a, b);
    case SIMDE_MM_PCOMCTRL_GT:
      return simde_mm_comgt_epu8(a, b);
    case SIMDE_MM_PCOMCTRL_GE:
      return simde_mm_comge_epu8(a, b);
    case SIMDE_MM_PCOMCTRL_EQ:
      return simde_mm_comeq_epu8(a, b);
    case SIMDE_MM_PCOMCTRL_NEQ:
      return simde_mm_comneq_epu8(a, b);
    case SIMDE_MM_PCOMCTRL_FALSE:
      return simde_mm_comfalse_epu8(a, b);
    case SIMDE_MM_PCOMCTRL_TRUE:
      return simde_mm_comtrue_epu8(a, b);
    default:
      HEDLEY_UNREACHABLE_RETURN(simde_mm_setzero_si128());
  }
}
#if defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_X86_XOP_HAVE_COM_)
  #define simde_mm_com_epu8(a, b, imm8) _mm_com_epu8((a), (b), (imm8))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_com_epu8(a, b, imm8) simde_mm_com_epu8((a), (b), (imm8))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_com_epu16 (simde__m128i a, simde__m128i b, const int imm8)
    SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 7) {
  switch (imm8) {
    case SIMDE_MM_PCOMCTRL_LT:
      return simde_mm_comlt_epu16(a, b);
    case SIMDE_MM_PCOMCTRL_LE:
      return simde_mm_comle_epu16(a, b);
    case SIMDE_MM_PCOMCTRL_GT:
      return simde_mm_comgt_epu16(a, b);
    case SIMDE_MM_PCOMCTRL_GE:
      return simde_mm_comge_epu16(a, b);
    case SIMDE_MM_PCOMCTRL_EQ:
      return simde_mm_comeq_epu16(a, b);
    case SIMDE_MM_PCOMCTRL_NEQ:
      return simde_mm_comneq_epu16(a, b);
    case SIMDE_MM_PCOMCTRL_FALSE:
      return simde_mm_comfalse_epu16(a, b);
    case SIMDE_MM_PCOMCTRL_TRUE:
      return simde_mm_comtrue_epu16(a, b);
    default:
      HEDLEY_UNREACHABLE_RETURN(simde_mm_setzero_si128());
  }
}
#if defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_X86_XOP_HAVE_COM_)
  #define simde_mm_com_epu16(a, b, imm8) _mm_com_epu16((a), (b), (imm8))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_com_epu16(a, b, imm8) simde_mm_com_epu16((a), (b), (imm8))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_com_epu32 (simde__m128i a, simde__m128i b, const int imm8)
    SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 7) {
  switch (imm8) {
    case SIMDE_MM_PCOMCTRL_LT:
      return simde_mm_comlt_epu32(a, b);
    case SIMDE_MM_PCOMCTRL_LE:
      return simde_mm_comle_epu32(a, b);
    case SIMDE_MM_PCOMCTRL_GT:
      return simde_mm_comgt_epu32(a, b);
    case SIMDE_MM_PCOMCTRL_GE:
      return simde_mm_comge_epu32(a, b);
    case SIMDE_MM_PCOMCTRL_EQ:
      return simde_mm_comeq_epu32(a, b);
    case SIMDE_MM_PCOMCTRL_NEQ:
      return simde_mm_comneq_epu32(a, b);
    case SIMDE_MM_PCOMCTRL_FALSE:
      return simde_mm_comfalse_epu32(a, b);
    case SIMDE_MM_PCOMCTRL_TRUE:
      return simde_mm_comtrue_epu32(a, b);
    default:
      HEDLEY_UNREACHABLE_RETURN(simde_mm_setzero_si128());
  }
}
#if defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_X86_XOP_HAVE_COM_)
  #define simde_mm_com_epu32(a, b, imm8) _mm_com_epu32((a), (b), (imm8))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_com_epu32(a, b, imm8) simde_mm_com_epu32((a), (b), (imm8))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_com_epu64 (simde__m128i a, simde__m128i b, const int imm8)
    SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 7) {
  switch (imm8) {
    case SIMDE_MM_PCOMCTRL_LT:
      return simde_mm_comlt_epu64(a, b);
    case SIMDE_MM_PCOMCTRL_LE:
      return simde_mm_comle_epu64(a, b);
    case SIMDE_MM_PCOMCTRL_GT:
      return simde_mm_comgt_epu64(a, b);
    case SIMDE_MM_PCOMCTRL_GE:
      return simde_mm_comge_epu64(a, b);
    case SIMDE_MM_PCOMCTRL_EQ:
      return simde_mm_comeq_epu64(a, b);
    case SIMDE_MM_PCOMCTRL_NEQ:
      return simde_mm_comneq_epu64(a, b);
    case SIMDE_MM_PCOMCTRL_FALSE:
      return simde_mm_comfalse_epu64(a, b);
    case SIMDE_MM_PCOMCTRL_TRUE:
      return simde_mm_comtrue_epu64(a, b);
    default:
      HEDLEY_UNREACHABLE_RETURN(simde_mm_setzero_si128());
  }
}
#if defined(SIMDE_X86_XOP_NATIVE) && defined(SIMDE_X86_XOP_HAVE_COM_)
  #define simde_mm_com_epu64(a, b, imm8) _mm_com_epu64((a), (b), (imm8))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_com_epu64(a, b, imm8) simde_mm_com_epu64((a), (b), (imm8))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128
simde_mm_frcz_ps (simde__m128 a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_frcz_ps(a);
  #else
    simde__m128_private
      r_,
      a_ = simde__m128_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.f32) / sizeof(r_.f32[0])) ; i++) {
      #if defined(simde_math_modff)
        simde_float32 integral;
        r_.f32[i] = simde_math_modff(a_.f32[i], &integral);
      #else
        r_.f32[i] = (a_.f32[i] / 1.0f);
      #endif
    }

    return simde__m128_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_frcz_ps(a, b, c) simde_mm_frcz_ps((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128d
simde_mm_frcz_pd (simde__m128d a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_frcz_pd(a);
  #else
    simde__m128d_private
      r_,
      a_ = simde__m128d_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.f64) / sizeof(r_.f64[0])) ; i++) {
      #if defined(simde_math_modf)
        simde_float64 integral;
        r_.f64[i] = simde_math_modf(a_.f64[i], &integral);
      #else
        r_.f64[i] = (a_.f64[i] / 1.0f);
      #endif
    }

    return simde__m128d_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_frcz_ps(a, b, c) simde_mm_frcz_ps((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128
simde_mm_frcz_ss (simde__m128 a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_frcz_ss(a);
  #else
    simde__m128_private a_ = simde__m128_to_private(a);

    #if defined(simde_math_modff)
      simde_float32 integral;
      a_.f32[0] = simde_math_modff(a_.f32[0], &integral);
    #else
      a_.f32[0] = (a_.f32[0] / 1.0f);
    #endif

    return simde__m128_from_private(a_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_frcz_ss(a, b, c) simde_mm_frcz_ss((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128d
simde_mm_frcz_sd (simde__m128d a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_frcz_sd(a);
  #else
    simde__m128d_private a_ = simde__m128d_to_private(a);

    #if defined(simde_math_modf)
      simde_float64 integral;
      a_.f64[0] = simde_math_modf(a_.f64[0], &integral);
    #else
      a_.f64[0] = (a_.f64[0] / 1.0f);
    #endif

    return simde__m128d_from_private(a_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_frcz_ps(a, b, c) simde_mm_frcz_ps((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m256
simde_mm256_frcz_ps (simde__m256 a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm256_frcz_ps(a);
  #else
    simde__m256_private
      r_,
      a_ = simde__m256_to_private(a);

    #if SIMDE_NATURAL_VECTOR_SIZE_LE(128)
      for (size_t i = 0 ; i < (sizeof(r_.m128) / sizeof(r_.m128[0])) ; i++) {
        r_.m128[i] = simde_mm_frcz_ps(a_.m128[i]);
      }
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.f32) / sizeof(r_.f32[0])) ; i++) {
        #if defined(simde_math_modff)
          simde_float32 integral;
          r_.f32[i] = simde_math_modff(a_.f32[i], &integral);
        #else
          r_.f32[i] = (a_.f32[i] / 1.0f);
        #endif
      }
    #endif

    return simde__m256_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm256_frcz_ps(a, b, c) simde_mm256_frcz_ps((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m256d
simde_mm256_frcz_pd (simde__m256d a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm256_frcz_pd(a);
  #else
    simde__m256d_private
      r_,
      a_ = simde__m256d_to_private(a);

    #if SIMDE_NATURAL_VECTOR_SIZE_LE(128)
      for (size_t i = 0 ; i < (sizeof(r_.m128d) / sizeof(r_.m128d[0])) ; i++) {
        r_.m128d[i] = simde_mm_frcz_pd(a_.m128d[i]);
      }
    #else
      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.f64) / sizeof(r_.f64[0])) ; i++) {
        #if defined(simde_math_modf)
          simde_float64 integral;
          r_.f64[i] = simde_math_modf(a_.f64[i], &integral);
        #else
          r_.f64[i] = (a_.f64[i] / 1.0f);
        #endif
      }
    #endif

    return simde__m256d_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm256_frcz_ps(a, b, c) simde_mm256_frcz_ps((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddw_epi8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddw_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
      r_.i16[i] = HEDLEY_STATIC_CAST(int16_t, a_.i8[i * 2]) + HEDLEY_STATIC_CAST(int16_t, a_.i8[(i * 2) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddw_epi8(a, b) simde_mm_haddw_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddw_epu8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddw_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
      r_.u16[i] = HEDLEY_STATIC_CAST(uint16_t, a_.u8[i * 2]) + HEDLEY_STATIC_CAST(uint16_t, a_.u8[(i * 2) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddw_epu8(a, b) simde_mm_haddw_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddd_epi8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddd_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      r_.i32[i] =
        HEDLEY_STATIC_CAST(int32_t, a_.i8[(i * 4)    ]) + HEDLEY_STATIC_CAST(int32_t, a_.i8[(i * 4) + 1]) +
        HEDLEY_STATIC_CAST(int32_t, a_.i8[(i * 4) + 2]) + HEDLEY_STATIC_CAST(int32_t, a_.i8[(i * 4) + 3]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddd_epi8(a, b) simde_mm_haddd_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddd_epi16 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddd_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      r_.i32[i] =
        HEDLEY_STATIC_CAST(int32_t, a_.i16[(i * 2)    ]) + HEDLEY_STATIC_CAST(int32_t, a_.i16[(i * 2) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddd_epi8(a, b) simde_mm_haddd_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddd_epu8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddd_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
      r_.u32[i] =
        HEDLEY_STATIC_CAST(uint32_t, a_.u8[(i * 4)    ]) + HEDLEY_STATIC_CAST(uint32_t, a_.u8[(i * 4) + 1]) +
        HEDLEY_STATIC_CAST(uint32_t, a_.u8[(i * 4) + 2]) + HEDLEY_STATIC_CAST(uint32_t, a_.u8[(i * 4) + 3]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddd_epu8(a, b) simde_mm_haddd_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddd_epu16 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddd_epu16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
      r_.u32[i] =
        HEDLEY_STATIC_CAST(uint32_t, a_.u16[(i * 2)    ]) + HEDLEY_STATIC_CAST(uint32_t, a_.u16[(i * 2) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddd_epu8(a, b) simde_mm_haddd_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddq_epi8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddq_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.i64[i] =
        HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8)    ]) + HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 1]) +
        HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 2]) + HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 3]) +
        HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 4]) + HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 5]) +
        HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 6]) + HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 7]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddq_epi8(a, b) simde_mm_haddq_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddq_epi16 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddq_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.i64[i] =
        HEDLEY_STATIC_CAST(int64_t, a_.i16[(i * 8)    ]) + HEDLEY_STATIC_CAST(int64_t, a_.i16[(i * 8) + 1]) +
        HEDLEY_STATIC_CAST(int64_t, a_.i16[(i * 8) + 2]) + HEDLEY_STATIC_CAST(int64_t, a_.i16[(i * 8) + 3]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddq_epi16(a, b) simde_mm_haddq_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddq_epi32 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddq_epi32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.i64[i] = HEDLEY_STATIC_CAST(int64_t, a_.i32[(i * 8)    ]) + HEDLEY_STATIC_CAST(int64_t, a_.i32[(i * 8) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddq_epi32(a, b) simde_mm_haddq_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddq_epu8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddq_epu8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.u64[i] =
        HEDLEY_STATIC_CAST(uint64_t, a_.u8[(i * 8)    ]) + HEDLEY_STATIC_CAST(uint64_t, a_.u8[(i * 8) + 1]) +
        HEDLEY_STATIC_CAST(uint64_t, a_.u8[(i * 8) + 2]) + HEDLEY_STATIC_CAST(uint64_t, a_.u8[(i * 8) + 3]) +
        HEDLEY_STATIC_CAST(uint64_t, a_.u8[(i * 8) + 4]) + HEDLEY_STATIC_CAST(uint64_t, a_.u8[(i * 8) + 5]) +
        HEDLEY_STATIC_CAST(uint64_t, a_.u8[(i * 8) + 6]) + HEDLEY_STATIC_CAST(uint64_t, a_.u8[(i * 8) + 7]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddq_epu8(a, b) simde_mm_haddq_epu8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddq_epu16 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddq_epu16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.u64[i] =
        HEDLEY_STATIC_CAST(uint64_t, a_.u16[(i * 8)    ]) + HEDLEY_STATIC_CAST(uint64_t, a_.u16[(i * 8) + 1]) +
        HEDLEY_STATIC_CAST(uint64_t, a_.u16[(i * 8) + 2]) + HEDLEY_STATIC_CAST(uint64_t, a_.u16[(i * 8) + 3]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddq_epu16(a, b) simde_mm_haddq_epu16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_haddq_epu32 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_haddq_epu32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.u64[i] = HEDLEY_STATIC_CAST(uint64_t, a_.u32[(i * 8)    ]) + HEDLEY_STATIC_CAST(uint64_t, a_.u32[(i * 8) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_haddq_epu32(a, b) simde_mm_haddq_epu32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_hsubw_epi8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_hsubw_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
      r_.i16[i] = HEDLEY_STATIC_CAST(int16_t, a_.i8[i * 2]) - HEDLEY_STATIC_CAST(int16_t, a_.i8[(i * 2) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_hsubw_epi8(a, b) simde_mm_hsubw_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_hsubd_epi8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_hsubd_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      r_.i32[i] =
        HEDLEY_STATIC_CAST(int32_t, a_.i8[(i * 4)    ]) - HEDLEY_STATIC_CAST(int32_t, a_.i8[(i * 4) + 1]) +
        HEDLEY_STATIC_CAST(int32_t, a_.i8[(i * 4) + 2]) - HEDLEY_STATIC_CAST(int32_t, a_.i8[(i * 4) + 3]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_hsubd_epi8(a, b) simde_mm_hsubd_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_hsubd_epi16 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_hsubd_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      r_.i32[i] =
        HEDLEY_STATIC_CAST(int32_t, a_.i16[(i * 2)    ]) - HEDLEY_STATIC_CAST(int32_t, a_.i16[(i * 2) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_hsubd_epi8(a, b) simde_mm_hsubd_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_hsubq_epi8 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_hsubq_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.i64[i] =
        HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8)    ]) - HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 1]) +
        HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 2]) - HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 3]) +
        HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 4]) - HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 5]) +
        HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 6]) - HEDLEY_STATIC_CAST(int64_t, a_.i8[(i * 8) + 7]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_hsubq_epi8(a, b) simde_mm_hsubq_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_hsubq_epi16 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_hsubq_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.i64[i] =
        HEDLEY_STATIC_CAST(int64_t, a_.i16[(i * 8)    ]) - HEDLEY_STATIC_CAST(int64_t, a_.i16[(i * 8) + 1]) +
        HEDLEY_STATIC_CAST(int64_t, a_.i16[(i * 8) + 2]) - HEDLEY_STATIC_CAST(int64_t, a_.i16[(i * 8) + 3]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_hsubq_epi16(a, b) simde_mm_hsubq_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_hsubq_epi32 (simde__m128i a) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_hsubq_epi32(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.i64[i] = HEDLEY_STATIC_CAST(int64_t, a_.i32[(i * 8)    ]) - HEDLEY_STATIC_CAST(int64_t, a_.i32[(i * 8) + 1]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_hsubq_epi32(a, b) simde_mm_hsubq_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_macc_epi16 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_macc_epi16(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
      r_.i16[i] = (a_.i16[i] * b_.i16[i]) + c_.i16[i];
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_macc_epi16(a, b, c) simde_mm_macc_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_macc_epi32 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_macc_epi32(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      r_.i32[i] = (a_.i32[i] * b_.i32[i]) + c_.i32[i];
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_macc_epi32(a, b, c) simde_mm_macc_epi32((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_maccd_epi16 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_maccd_epi16(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      r_.i32[i] = (HEDLEY_STATIC_CAST(int32_t, a_.i16[i * 2]) * HEDLEY_STATIC_CAST(int32_t, b_.i16[i * 2])) + c_.i32[i];
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_maccd_epi16(a, b, c) simde_mm_maccd_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_macclo_epi32 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_macclo_epi32(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.i64[i] = (HEDLEY_STATIC_CAST(int64_t, a_.i32[(i * 2) + 0]) * HEDLEY_STATIC_CAST(int64_t, b_.i32[(i * 2) + 0])) + c_.i64[i];
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_macclo_epi16(a, b, c) simde_mm_macclo_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_macchi_epi32 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_macchi_epi32(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      r_.i64[i] = (HEDLEY_STATIC_CAST(int64_t, a_.i32[(i * 2) + 1]) * HEDLEY_STATIC_CAST(int64_t, b_.i32[(i * 2) + 1])) + c_.i64[i];
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_macchi_epi16(a, b, c) simde_mm_macchi_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_maccs_epi16 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_maccs_epi16(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
      int32_t tmp = HEDLEY_STATIC_CAST(int32_t, a_.i16[i]) * HEDLEY_STATIC_CAST(int32_t, b_.i16[i]);
      tmp += c_.i16[i];
      if (tmp > INT16_MAX)
        r_.i16[i] = INT16_MAX;
      else if (tmp < INT16_MIN)
        r_.i16[i] = INT16_MIN;
      else
        r_.i16[i] = HEDLEY_STATIC_CAST(int16_t, tmp);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_maccs_epi16(a, b, c) simde_mm_maccs_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_maccs_epi32 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_maccs_epi32(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      int64_t tmp = HEDLEY_STATIC_CAST(int64_t, a_.i32[i]) * HEDLEY_STATIC_CAST(int64_t, b_.i32[i]);
      tmp += HEDLEY_STATIC_CAST(int64_t, c_.i32[i]);
      if (tmp > INT32_MAX)
        r_.i32[i] = INT32_MAX;
      else if (tmp < INT32_MIN)
        r_.i32[i] = INT32_MIN;
      else
        r_.i32[i] = HEDLEY_STATIC_CAST(int32_t, tmp);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_maccs_epi32(a, b, c) simde_mm_maccs_epi32((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_maccsd_epi16 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_maccsd_epi16(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      int32_t tmp = HEDLEY_STATIC_CAST(int32_t, a_.i16[i * 2]) * HEDLEY_STATIC_CAST(int32_t, b_.i16[i * 2]);
      tmp += c_.i32[i];
      if (tmp > INT16_MAX)
        r_.i16[i] = INT16_MAX;
      else if (tmp < INT16_MIN)
        r_.i16[i] = INT16_MIN;
      else
        r_.i16[i] = HEDLEY_STATIC_CAST(int16_t, tmp);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_maccsd_epi16(a, b, c) simde_mm_maccsd_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_maccslo_epi32 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_maccslo_epi32(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      int64_t tmp = HEDLEY_STATIC_CAST(int64_t, a_.i32[(i * 2) + 0]) * HEDLEY_STATIC_CAST(int64_t, b_.i32[(i * 2) + 0]);
      tmp += c_.i64[i];
      if (tmp > INT32_MAX)
        r_.i64[i] = INT32_MAX;
      else if (tmp < INT32_MIN)
        r_.i64[i] = INT32_MIN;
      else
        r_.i64[i] = HEDLEY_STATIC_CAST(int64_t, tmp);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_maccslo_epi16(a, b, c) simde_mm_maccslo_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_maccshi_epi32 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_maccshi_epi32(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      int64_t tmp = HEDLEY_STATIC_CAST(int64_t, a_.i32[(i * 2) + 1]) * HEDLEY_STATIC_CAST(int64_t, b_.i32[(i * 2) + 1]);
      tmp += c_.i64[i];
      if (tmp > INT32_MAX)
        r_.i64[i] = INT32_MAX;
      else if (tmp < INT32_MIN)
        r_.i64[i] = INT32_MIN;
      else
        r_.i64[i] = HEDLEY_STATIC_CAST(int64_t, tmp);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_maccshi_epi16(a, b, c) simde_mm_maccshi_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_maddd_epi16 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_maddd_epi32(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      r_.i32[i] =
        (a_.i16[(i * 2) + 0] * b_.i16[(i * 2) + 0]) +
        (a_.i16[(i * 2) + 1] * b_.i16[(i * 2) + 1]);
      r_.i32[i] += c_.i32[i];
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_maddd_epi16(a, b, c) simde_mm_maddd_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_maddsd_epi16 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_maddsd_epi32(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      /* The AMD64 Architecture Programmer's Manual says that "the"
       * addition is saturated; I'm not sure whether that means
       * the pairwise addition or the accumulate, or both. */
      r_.i32[i] =
        (a_.i16[(i * 2) + 0] * b_.i16[(i * 2) + 0]) +
        (a_.i16[(i * 2) + 1] * b_.i16[(i * 2) + 1]);
      r_.i32[i] = simde_math_adds_i32(r_.i32[i], c_.i32[i]);
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_maddsd_epi16(a, b, c) simde_mm_maddsd_epi16((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_sha_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_sha_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i8) / sizeof(r_.i8[0])) ; i++) {
      if (b_.i8[i] < 0) {
        r_.i8[i] = HEDLEY_STATIC_CAST(int8_t, a_.i8[i] >> -b_.i8[i]);
      } else {
        r_.i8[i] = HEDLEY_STATIC_CAST(int8_t, a_.i8[i] <<  b_.i8[i]);
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_sha_epi8(a, b) simde_mm_sha_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_sha_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_sha_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i16) / sizeof(r_.i16[0])) ; i++) {
      if (b_.i16[i] < 0) {
        r_.i16[i] = HEDLEY_STATIC_CAST(int16_t, a_.i16[i] >> -b_.i16[i]);
      } else {
        r_.i16[i] = HEDLEY_STATIC_CAST(int16_t, a_.i16[i] <<  b_.i16[i]);
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_sha_ep16(a, b) simde_mm_sha_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_sha_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_sha_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i32) / sizeof(r_.i32[0])) ; i++) {
      if (b_.i32[i] < 0) {
        r_.i32[i] = HEDLEY_STATIC_CAST(int32_t, a_.i32[i] >> -b_.i32[i]);
      } else {
        r_.i32[i] = HEDLEY_STATIC_CAST(int32_t, a_.i32[i] <<  b_.i32[i]);
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_sha_ep32(a, b) simde_mm_sha_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_sha_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_sha_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i64) / sizeof(r_.i64[0])) ; i++) {
      if (b_.i64[i] < 0) {
        r_.i64[i] = HEDLEY_STATIC_CAST(int64_t, a_.i64[i] >> -b_.i64[i]);
      } else {
        r_.i64[i] = HEDLEY_STATIC_CAST(int64_t, a_.i64[i] <<  b_.i64[i]);
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_sha_ep64(a, b) simde_mm_sha_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_shl_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_shl_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
      if (b_.i8[i] < 0) {
        r_.u8[i] = HEDLEY_STATIC_CAST(uint8_t, a_.u8[i] >> -b_.i8[i]);
      } else {
        r_.u8[i] = HEDLEY_STATIC_CAST(uint8_t, a_.u8[i] <<  b_.i8[i]);
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_shl_epi8(a, b) simde_mm_shl_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_shl_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_shl_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
      if (b_.i16[i] < 0) {
        r_.u16[i] = HEDLEY_STATIC_CAST(uint16_t, a_.u16[i] >> -b_.i16[i]);
      } else {
        r_.u16[i] = HEDLEY_STATIC_CAST(uint16_t, a_.u16[i] <<  b_.i16[i]);
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_shl_ep16(a, b) simde_mm_shl_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_shl_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_shl_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
      if (b_.i32[i] < 0) {
        r_.u32[i] = HEDLEY_STATIC_CAST(uint32_t, a_.u32[i] >> -b_.i32[i]);
      } else {
        r_.u32[i] = HEDLEY_STATIC_CAST(uint32_t, a_.u32[i] <<  b_.i32[i]);
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_shl_ep32(a, b) simde_mm_shl_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_shl_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_shl_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
      if (b_.i64[i] < 0) {
        r_.u64[i] = HEDLEY_STATIC_CAST(uint64_t, a_.u64[i] >> -b_.i64[i]);
      } else {
        r_.u64[i] = HEDLEY_STATIC_CAST(uint64_t, a_.u64[i] <<  b_.i64[i]);
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_shl_ep64(a, b) simde_mm_shl_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_rot_epi8 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_rot_epi8(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
      r_.u8[i] = (b_.i8[i] < 0) ?
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u8[i] >> -b_.i8[i]) | (a_.u8[i] >> ( b_.i8[i] & 7)))) :
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u8[i] <<  b_.i8[i]) | (a_.u8[i] >> (-b_.i8[i] & 7))));
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_rot_epi8(a, b) simde_mm_rot_epi8((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_rot_epi16 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_rot_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
      r_.u16[i] = (b_.i16[i] < 0) ?
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u16[i] >> -b_.i16[i]) | (a_.u16[i] >> ( b_.i16[i] & 15)))) :
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u16[i] <<  b_.i16[i]) | (a_.u16[i] >> (-b_.i16[i] & 15))));
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_rot_ep16(a, b) simde_mm_rot_epi16((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_rot_epi32 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_rot_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
      r_.u32[i] = (b_.i32[i] < 0) ?
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u32[i] >> -b_.i32[i]) | (a_.u32[i] >> ( b_.i32[i] & 31)))) :
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u32[i] <<  b_.i32[i]) | (a_.u32[i] >> (-b_.i32[i] & 31))));
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_rot_ep32(a, b) simde_mm_rot_epi32((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_rot_epi64 (simde__m128i a, simde__m128i b) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_rot_epi16(a, b);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
      r_.u64[i] = (b_.i64[i] < 0) ?
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u64[i] >> -b_.i64[i]) | (a_.u64[i] >> ( b_.i64[i] & 63)))) :
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u64[i] <<  b_.i64[i]) | (a_.u64[i] >> (-b_.i64[i] & 63))));
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_rot_ep64(a, b) simde_mm_rot_epi64((a), (b))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_roti_epi8 (simde__m128i a, const int count) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_perm_epi8(a, count);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u8) / sizeof(r_.u8[0])) ; i++) {
      r_.u8[i] = (count < 0) ?
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u8[i] >> -count) | (a_.u8[i] >> ( count & 7)))) :
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u8[i] <<  count) | (a_.u8[i] >> (-count & 7))));
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_NATIVE)
  #define simde_mm_roti_epi8(a, count) _mm_roti_epi8((a), (count))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_roti_epi8(a, b) simde_mm_roti_epi8((a), (count))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_roti_epi16 (simde__m128i a, const int count) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_perm_epi16(a, count);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u16) / sizeof(r_.u16[0])) ; i++) {
      r_.u16[i] = (count < 0) ?
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u16[i] >> -count) | (a_.u16[i] >> ( count & 15)))) :
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u16[i] <<  count) | (a_.u16[i] >> (-count & 15))));
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_NATIVE)
  #define simde_mm_roti_epi16(a, count) _mm_roti_epi16((a), (count))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_roti_ep16(a, count) simde_mm_roti_epi16((a), (count))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_roti_epi32 (simde__m128i a, const int count) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_perm_epi32(a, count);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
      r_.u32[i] = (count < 0) ?
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u32[i] >> -count) | (a_.u32[i] >> ( count & 31)))) :
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u32[i] <<  count) | (a_.u32[i] >> (-count & 31))));
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_NATIVE)
  #define simde_mm_roti_epi32(a, count) _mm_roti_epi32((a), (count))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_roti_ep32(a, count) simde_mm_roti_epi32((a), (count))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_roti_epi64 (simde__m128i a, const int count) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_perm_epi64(a, count);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
      r_.u64[i] = (count < 0) ?
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u64[i] >> -count) | (a_.u64[i] >> ( count & 63)))) :
        HEDLEY_STATIC_CAST(uint8_t, ((a_.u64[i] <<  count) | (a_.u64[i] >> (-count & 63))));
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_NATIVE)
  #define simde_mm_roti_epi64(a, count) _mm_roti_epi64((a), (count))
#endif
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_roti_ep64(a, count) simde_mm_roti_epi64((a), (count))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_perm_epi8 (simde__m128i a, simde__m128i b, simde__m128i c) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_perm_epi8(a, b, c);
  #else
    simde__m128i_private
      r_,
      a_ = simde__m128i_to_private(a),
      b_ = simde__m128i_to_private(b),
      c_ = simde__m128i_to_private(c);

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.i8) / sizeof(r_.i8[0])) ; i++) {
      int8_t src = (c_.u8[i] < 16) ? a_.i8[i] : b_.i8[i];
      if (c_.u8[i] & 0x20)
        src = ~src;

      switch ((c_.u8[i] & 0xc0) >> 5) {
        case 0:
          r_.i8[i] = src;
          break;
        case 2:
          #if HEDLEY_HAS_BUILTIN(__builtin_bitreverse8) && !defined(HEDLEY_IBM_VERSION)
            r_.i8[i] = HEDLEY_STATIC_CAST(int8_t, __builtin_bitreverse8(HEDLEY_STATIC_CAST(uint8_t, src)));
          #else
            r_.i8[i] = HEDLEY_STATIC_CAST(int8_t, (( src * UINT32_C(0x80200802)) & UINT32_C(0x0884422110)) * UINT32_C(0x0101010101) >> 32);
          #endif
          break;
        case 4:
          r_.i8[i] = 0;
          break;
        case 6:
          r_.i8[i] =  src >> 7;
          break;
      }
    }

    return simde__m128i_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_perm_epi8(a, b, c) simde_mm_perm_epi8((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128
simde_mm_permute2_ps (simde__m128 a, simde__m128 b, simde__m128i c, const int imm8) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_permute2_ps(a, b, c, imm8);
  #else
    simde__m128_private
      r_,
      a_ = simde__m128_to_private(a),
      b_ = simde__m128_to_private(b);
    simde__m128i_private c_ = simde__m128i_to_private(c);

    const int m2z = imm8 & 0x03;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.f32) / sizeof(r_.f32[0])) ; i++) {
      const int sel = c_.i32[i] & 0x07;
      const int   m = c_.i32[i] & 0x08;

      switch (m | m2z) {
        case 0xa:
        case 0x3:
          r_.i32[i] = 0;
          break;
        default:
          r_.i32[i] = (sel > 3) ? b_.i32[sel >> 2] : a_.i32[sel];
          break;
      }
    }

    return simde__m128_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_permute2_ps(a, b, c) simde_mm_permute2_ps((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m128d
simde_mm_permute2_pd (simde__m128d a, simde__m128d b, simde__m128i c, const int imm8) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm_permute2_pd(a, b, c, imm8);
  #else
    simde__m128d_private
      r_,
      a_ = simde__m128d_to_private(a),
      b_ = simde__m128d_to_private(b);
    simde__m128i_private c_ = simde__m128i_to_private(c);

    const int m2z = imm8 & 0x03;

    SIMDE_VECTORIZE
    for (size_t i = 0 ; i < (sizeof(r_.f64) / sizeof(r_.f64[0])) ; i++) {
      const int sel = (c_.i64[i] & 0x06) >> 1;
      const int   m = c_.i64[i] & 0x08;

      switch (m | m2z) {
        case 0x0a:
        case 0x03:
          r_.i64[i] = 0;
          break;
        default:
          r_.i64[i] = (sel > 1) ? b_.i64[sel >> 1] : a_.i64[sel];
          break;
      }
    }

    return simde__m128d_from_private(r_);
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm_permute2_pd(a, b, c) simde_mm_permute2_pd((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m256
simde_mm256_permute2_ps (simde__m256 a, simde__m256 b, simde__m256i c, const int imm8) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm256_permute2_ps(a, b, c, imm8);
  #else
    simde__m256_private
      r_,
      a_ = simde__m256_to_private(a),
      b_ = simde__m256_to_private(b);
    simde__m256i_private c_ = simde__m256i_to_private(c);

    #if SIMDE_NATURAL_VECTOR_SIZE_LE(128)
      for (size_t i = 0 ; i < (sizeof(r_.f32) / sizeof(r_.f32[0])) ; i++) {
        r_.m128[i] = simde_mm_permute2_ps(a_.m128[i], b_.m128[i], c_.m128i[i], imm8);
      }
    #else
      const int m2z = imm8 & 0x03;

      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.f32) / sizeof(r_.f32[0])) ; i++) {
        const int sel = c_.i32[i] & 0x07;
        const int   m = c_.i32[i] & 0x08;

        switch (m | m2z) {
          case 0xa:
          case 0x3:
            r_.i32[i] = 0;
            break;
          default:
            r_.i32[i] = (sel > 3) ? b_.i32[sel >> 2] : a_.i32[sel];
            break;
        }
      }

      return simde__m256_from_private(r_);
    #endif
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm256_permute2_ps(a, b, c) simde_mm256_permute2_ps((a), (b), (c))
#endif

SIMDE_FUNCTION_ATTRIBUTES
simde__m256d
simde_mm256_permute2_pd (simde__m256d a, simde__m256d b, simde__m256i c, const int imm8) {
  #if defined(SIMDE_X86_XOP_NATIVE)
    return _mm256_permute2_pd(a, b, c, imm8);
  #else
    simde__m256d_private
      r_,
      a_ = simde__m256d_to_private(a),
      b_ = simde__m256d_to_private(b);
    simde__m256i_private c_ = simde__m256i_to_private(c);

    #if SIMDE_NATURAL_VECTOR_SIZE_LE(128)
      for (size_t i = 0 ; i < (sizeof(r_.f32) / sizeof(r_.f32[0])) ; i++) {
        r_.m128d[i] = simde_mm_permute2_pd(a_.m128d[i], b_.m128d[i], c_.m128i[i], imm8);
      }
    #else
      const int m2z = imm8 & 0x03;

      SIMDE_VECTORIZE
      for (size_t i = 0 ; i < (sizeof(r_.f64) / sizeof(r_.f64[0])) ; i++) {
        const int sel = (c_.i64[i] & 0x06) >> 1;
        const int   m = c_.i64[i] & 0x08;

        switch (m | m2z) {
          case 0x0a:
          case 0x03:
            r_.i64[i] = 0;
            break;
          default:
            r_.i64[i] = (sel > 1) ? b_.i64[sel >> 1] : a_.i64[sel];
            break;
        }
      }

      return simde__m256d_from_private(r_);
    #endif
  #endif
}
#if defined(SIMDE_X86_XOP_ENABLE_NATIVE_ALIASES)
  #define _mm256_permute2_pd(a, b, c) simde_mm256_permute2_pd((a), (b), (c))
#endif

HEDLEY_DIAGNOSTIC_POP

#endif /* !defined(SIMDE_X86_XOP_H) */
