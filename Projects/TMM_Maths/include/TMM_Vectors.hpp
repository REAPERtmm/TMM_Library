#include "TMM_Vectors.h"

namespace TMM
{
	//				=== Vec2 ===

	template<typename T> requires Countable<T>
	inline float Vec2<T>::Dot(const Vec2<T>& other) const
	{
		return x * other.x + y * other.y;
	}


	template<typename T> requires Countable<T>
	inline float Vec2<T>::MagnitudeSQ() const
	{
		return x * x + y * y;
	}

	template<typename T> requires Countable<T>
	inline float Vec2<T>::Magnitude() const
	{
		return sqrtf(MagnitudeSQ());
	}

	template<typename T> requires Countable<T>
	inline Vec2<T> Vec2<T>::operator+(const Vec2<T>& other) const
	{
		return { x + other.x, y + other.y };
	}

	template<typename T> requires Countable<T>
	inline Vec2<T> Vec2<T>::operator-(const Vec2<T>& other) const
	{
		return { x - other.x, y - other.y };
	}

	template<typename T> requires Countable<T>
	inline Vec2<T> Vec2<T>::operator*(float other) const
	{
		return { x * other, y * other };
	}

	template<typename T> requires Countable<T>
	inline Vec2<T> Vec2<T>::operator/(float other) const
	{
		return { x / other, y / other };
	}

	template<typename T> requires Countable<T>
	inline Vec2<T> Vec2<T>::Normalized() const
	{
		float Inv_magnitude = 1 / Magnitude();
		return { x * Inv_magnitude, y * Inv_magnitude };
	}

	template<typename T> requires Countable<T>
	inline Vec2<T> Vec2<T>::Rescaled(float length) const
	{
		float factor = length / Magnitude();
		return { factor * x, factor * y };
	}

	template<typename T> requires Countable<T>
	inline Vec2<T> Vec2<T>::Rotated(float rad) const
	{
		float _cos = cosf(rad);
		float _sin = sinf(rad);
		return { _cos * x - _sin * y, _sin * x + _cos * y };
	}

	template<typename T> requires Countable<T>
	inline Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	template<typename T> requires Countable<T>
	inline Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template<typename T> requires Countable<T>
	inline Vec2<T>& Vec2<T>::operator*=(float other)
	{
		x *= other;
		y *= other;
		return *this;
	}

	template<typename T> requires Countable<T>
	inline Vec2<T>& Vec2<T>::operator/=(float other)
	{
		x /= other;
		y /= other;
		return *this;
	}


	template<typename T> requires Countable<T>
	inline void Vec2<T>::Normalize()
	{
		float Inv_magnitude = 1 / Magnitude();
		x *= Inv_magnitude;
		y *= Inv_magnitude;
	}

	template<typename T> requires Countable<T>
	inline void Vec2<T>::Rescale(float length)
	{
		float factor = length / Magnitude();
		x *= factor;
		y *= factor;
	}

	template<typename T> requires Countable<T>
	inline void Vec2<T>::Rotate(float rad)
	{
		float _cos = cosf(rad);
		float _sin = sinf(rad);

		float temp = x * _cos - y * _sin;
		y = x * _sin + y * _cos;
		x = temp;
	}

	template<Countable T>
	Vec2<T> operator*(float lhs, const Vec2<T>& rhs)
	{
		return { rhs.x * lhs, rhs.y * lhs };
	}

	template<Countable T>
	float Dot(const Vec2<T>& v1, const Vec2<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	//				=== Vec4 ===

	template<typename T> requires Countable<T>
	inline float Vec4<T>::Dot(const Vec4<T>& other) const
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}

	template<typename T> requires Countable<T>
	inline float Vec4<T>::MagnitudeSQ() const
	{
		return x * x + y * y + z * z + w * w;
	}

	template<typename T> requires Countable<T>
	inline float Vec4<T>::Magnitude() const
	{
		return sqrtf(MagnitudeSQ());
	}

	template<typename T> requires Countable<T>
	inline Vec4<T> Vec4<T>::operator+(const Vec4<T>& other) const
	{
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}

	template<typename T> requires Countable<T>
	inline Vec4<T> Vec4<T>::operator-(const Vec4<T>& other) const
	{
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}


	template<typename T> requires Countable<T>
	inline Vec4<T> Vec4<T>::operator*(float other) const
	{
		return { x * other, y * other, z * other, w * other };
	}

	template<typename T> requires Countable<T>
	inline Vec4<T> Vec4<T>::operator/(float other) const
	{
		return { x / other, y / other, z / other, w / other };
	}

	template<typename T> requires Countable<T>
	inline Vec4<T> Vec4<T>::Normalized() const
	{
		float Inv_magnitude = 1 / Magnitude();
		return { x * Inv_magnitude, y * Inv_magnitude, z * Inv_magnitude, w * Inv_magnitude };
	}

	template<typename T> requires Countable<T>
	inline Vec4<T> Vec4<T>::Rescaled(float length) const
	{
		float factor = length / Magnitude();
		return { factor * x, factor * y, factor * z, factor * w };
	}

	template<typename T> requires Countable<T>
	inline Vec4<T>& Vec4<T>::operator+=(const Vec4<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	template<typename T> requires Countable<T>
	inline Vec4<T>& Vec4<T>::operator-=(const Vec4<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	template<typename T> requires Countable<T>
	inline Vec4<T>& Vec4<T>::operator*=(float other)
	{
		x *= other;
		y *= other;
		z *= other;
		w *= other;
		return *this;
	}

	template<typename T> requires Countable<T>
	inline Vec4<T>& Vec4<T>::operator/=(float other)
	{
		x /= other;
		y /= other;
		z /= other;
		w /= other;
		return *this;
	}


	template<typename T> requires Countable<T>
	inline void Vec4<T>::Normalize()
	{
		float Inv_magnitude = 1 / Magnitude();
		x *= Inv_magnitude;
		y *= Inv_magnitude;
		z *= Inv_magnitude;
		w *= Inv_magnitude;
	}

	template<typename T> requires Countable<T>
	inline void Vec4<T>::Rescale(float length)
	{
		float factor = length / Magnitude();
		x *= factor;
		y *= factor;
		z *= factor;
		w *= factor;
	}

	template<typename T> requires Countable<T>
	inline Vec4<T>::operator Vec4<float>()
	{
		return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w) };
	}

	template<Countable T>
	Vec4<T> operator*(float lhs, const Vec4<T>& rhs)
	{
		return { rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs };
	}

	template<Countable T>
	float Dot(const Vec4<T>& v1, const Vec4<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}
}