#ifndef FSQRT_HPP
#define FSQRT_HPP
#if defined( __AVX2__) || defined(__SSE__) || defined(__SSE2__) || defined(__SSE3__) || defined(__SSE4_1__) || defined( __AVX__) || defined( __AVX2__)
#include <xmmintrin.h>
#define SSE_SUPPORTED
#define _mm_fsqrt(x) _mm_mul_ss(x, _mm_rsqrt_ss(x))

struct SSE_FLOAT {
	__m128 mm;
	float f[4];
	void toMM() {
		// mm = _mm_set_ps(f[0], f[1], f[2], f[3]);
		mm = _mm_load_ps(f);
	}
	void toF()
	{
		_mm_store_ps(f,mm);
	}
};

#endif

#endif // FSQRT_HPP
