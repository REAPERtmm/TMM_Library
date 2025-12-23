#pragma once
// REQUIRED internal inclusion
#include <TMM_Setup.h>
#include <TMM_Vectors.h>

// REQUIRED external inclusion
#include <immintrin.h>

// ===  OP Vec        ===

#define TMM_OPP_DOT_VEC(out, v) TMM::VECTOR_OPP out(TMM::OPP_SIMD::_dotVec(v.r))
#define TMM_OPP_DOT_VEC_Accumulate(out) out.r = TMM::OPP_SIMD::_dotVec(out.r)
#define TMM_OPP_NORMALIZE_VEC(out, v) TMM::VECTOR_OPP out(TMM::OPP_SIMD::_normalizeVec(v.r))
#define TMM_OPP_NORMALIZE_VEC_Accumulate(out) out.r = TMM::OPP_SIMD::_normalizeVec(out.r)

// ===  OP Vec - Vec  ===

#define TMM_OPP_ADD_VEC(out, a, b) TMM::VECTOR_OPP out(TMM::OPP_SIMD::_addVec(a.r, b.r))
#define TMM_OPP_ADD_VEC_Accumulate(out, in) out.r = TMM::OPP_SIMD::_addVec(out.r, in.r)
#define TMM_OPP_SUB_VEC(out, a, b) TMM::VECTOR_OPP out(TMM::OPP_SIMD::_subVec(a.r, b.r))
#define TMM_OPP_SUB_VEC_Accumulate(out, in) out.r = TMM::OPP_SIMD::_subVec(out.r, in.r)
#define TMM_OPP_MUL_VEC(out, a, b) TMM::VECTOR_OPP out(TMM::OPP_SIMD::_mulVec(a.r, b.r))
#define TMM_OPP_MUL_VEC_Accumulate(out, in) out.r = TMM::OPP_SIMD::_mulVec(out.r, in.r)
#define TMM_OPP_DIV_VEC(out, a, b) TMM::VECTOR_OPP out(TMM::OPP_SIMD::_divVec(a.r, b.r))
#define TMM_OPP_DIV_VEC_Accumulate(out, in) out.r = TMM::OPP_SIMD::_divVec(out.r, in.r)
#define TMM_OPP_CROSS_VEC3(out, a, b) TMM::VECTOR_OPP out(TMM::OPP_SIMD::_crossVec3(a.r, b.r))
#define TMM_OPP_CROSS_VEC3_Accumulate(out, in) out.r = TMM::OPP_SIMD::_crossVec3(out.r, in.r)
			  
// ===  OP MatP - Mat  ===
			  
#define TMM_OPP_MUL_MAT(out, a, b) TMM::MATRIX_OPP out; TMM::OPP_SIMD::_mulMat(a.r, b.r, out.r)
#define TMM_OPP_MUL_MAT_Accumulate(out, in) TMM::OPP_SIMD::_mulMat(out.r, in.r, out.r)

namespace TMM {

	struct ALIGN16 VECTOR_OPP 
	{
		__m128 r;

		__forceinline void operator=(const VECTOR_OPP& other) {
			r = other.r;
		}

		VECTOR_OPP() = default;

		explicit inline VECTOR_OPP(__m128 m128) : r(m128) { }
		__forceinline VECTOR_OPP(const Vec4f& v) : r(_mm_loadu_ps(&v.x)) { }
		__forceinline VECTOR_OPP(float s) : r(_mm_set1_ps(s)) { }
		__forceinline VECTOR_OPP(float x, float y, float z, float w) : r(_mm_set_ps(x, y, z, w)) { }

		__forceinline void Out(Vec4f& out) {
			_mm_storeu_ps(&out.x, r);
		}
	};
	struct ALIGN16 MATRIX_OPP
	{
		__m128 r[4];

		__forceinline void operator=(const MATRIX_OPP& other) {
			r[0] = other.r[0];
			r[1] = other.r[1];
			r[2] = other.r[2];
			r[3] = other.r[3];
		}

		__forceinline MATRIX_OPP() = default;

		__forceinline MATRIX_OPP(const Vec4f& row0, const Vec4f& row1, const Vec4f& row2, const Vec4f& row3)
		{
			r[0] = _mm_loadu_ps(&row0.x);
			r[1] = _mm_loadu_ps(&row1.x);
			r[2] = _mm_loadu_ps(&row2.x);
			r[3] = _mm_loadu_ps(&row3.x);
		}

		__forceinline MATRIX_OPP(const Vec4f* rows)
		{
			r[0] = _mm_loadu_ps(&rows[0].x);
			r[1] = _mm_loadu_ps(&rows[1].x);
			r[2] = _mm_loadu_ps(&rows[2].x);
			r[3] = _mm_loadu_ps(&rows[3].x);
		}


		// /!\ HEAVY LATENCY !
		__forceinline MATRIX_OPP(float s)
		{
			r[0] = _mm_set_ps(0.0f, 0.0f, 0.0f, s);
			r[1] = _mm_set_ps(0.0f, 0.0f, s, 0.0f);
			r[2] = _mm_set_ps(0.0f, s, 0.0f, 0.0f);
			r[3] = _mm_set_ps(s, 0.0f, 0.0f, 0.0f);
		}

		// /!\ HEAVY LATENCY !
		__forceinline MATRIX_OPP(
			float m00, float m10, float m20, float m30,
			float m01, float m11, float m21, float m31,
			float m02, float m12, float m22, float m32,
			float m03, float m13, float m23, float m33
		)
		{
			r[0] = _mm_set_ps(m30, m20, m10, m00);
			r[1] = _mm_set_ps(m31, m21, m11, m01);
			r[2] = _mm_set_ps(m32, m22, m12, m02);
			r[3] = _mm_set_ps(m33, m23, m13, m03);
		}

		__forceinline void Out(Vec4f& out0, Vec4f& out1, Vec4f& out2, Vec4f& out3) {
			_mm_storeu_ps(&out0.x, r[0]);
			_mm_storeu_ps(&out1.x, r[1]);
			_mm_storeu_ps(&out2.x, r[2]);
			_mm_storeu_ps(&out3.x, r[3]);
		}

		__forceinline void Out(Vec4f* outs) {
			_mm_storeu_ps(&outs[0].x, r[0]);
			_mm_storeu_ps(&outs[1].x, r[1]);
			_mm_storeu_ps(&outs[2].x, r[2]);
			_mm_storeu_ps(&outs[3].x, r[3]);
		}
	};

	struct OPP_SIMD
	{
		// ===  OP Vec        ===

		static __forceinline __m128 _dotVec(__m128 v) {
			return _mm_dp_ps(v, v, 0b11111111);
		}

		static __forceinline __m128 _normalizeVec(__m128 v) {
			return _mm_mul_ps(
				v,
				_mm_rsqrt14_ps(
					_dotVec(
						_mm_mul_ps(v, v)
					)
				)
			);
		}

		// ===  OP Vec - Vec  ===

		static __forceinline __m128 _addVec(__m128 a, __m128 b) {
			return _mm_add_ps(a, b);
		}

		static __forceinline __m128 _subVec(__m128 a, __m128 b) {
			return _mm_sub_ps(a, b);
		}

		static __forceinline __m128 _divVec(__m128 a, __m128 b) {
			return _mm_mul_ps(a, _mm_rcp14_ps(b));
		}

		static __forceinline __m128 _mulVec(__m128 a, __m128 b) {
			return _mm_mul_ps(a, b);
		}


		static __forceinline __m128 _crossVec3(__m128 a, __m128 b) {
			return _mm_sub_ps(
				_mm_mul_ps(
					_mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 0, 2, 1)),	// yzx
					_mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 1, 0, 2))),	// zxy 
				_mm_mul_ps(
					_mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 1, 0, 2)),	// zxy
					_mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 0, 2, 1))	// yzx
				)
			);
		}

		// ===  OP Mat        ===

		// ===  OP Mat - Mat  ===
		static __forceinline void _mulMat(__m128 a[4], __m128 b[4], __m128 out[4]) {
			for (int i = 0; i < 4; ++i) {
				out[i] = _mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_shuffle_ps(a[i], a[i], _MM_SHUFFLE(0, 0, 0, 0)),
							b[0]), 
						_mm_mul_ps(
							_mm_shuffle_ps(a[i], a[i], _MM_SHUFFLE(1, 1, 1, 1)),
							b[1])),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_shuffle_ps(a[i], a[i], _MM_SHUFFLE(2, 2, 2, 2)),
							b[2]),
						_mm_mul_ps(
							_mm_shuffle_ps(a[i], a[i], _MM_SHUFFLE(3, 3, 3, 3)),
							b[3]
						)
					)
				);
			}
		}

		// ===  OP Mat - Vec  ===

		// TODO
		static __forceinline __m128 _mulMatVec(__m128 a[4], __m128 b) {
			return __m128();
		}

		// TODO
		static __forceinline __m128 _mulVecMat(__m128 a, __m128 b[4]) {
			return __m128();
		}

	};
}
