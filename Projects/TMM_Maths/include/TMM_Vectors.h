#pragma once
#include <TMM_Setup.h>

#include <cmath>

namespace TMM
{

	template<typename T> requires Countable<T>
	struct Vec4;
	
	// ===  Vec2  ===

	template<typename T> requires Countable<T>
	struct Vec2 {
		T x;
		T y;

		Vec2() : x(0), y(0) {}
		Vec2(T _x, T _y) : x(_x), y(_y) {}
		Vec2(const Vec4<T>& v) : x(v.x), y(v.y) {}

		float Dot(const Vec2<T>& other) const;
		float MagnitudeSQ() const;
		float Magnitude() const;
		Vec2<T> operator + (const Vec2<T>& other) const;
		Vec2<T> operator - (const Vec2<T>& other) const;
		Vec2<T> operator * (float other) const;
		Vec2<T> operator / (float other) const;
		Vec2<T> Normalized() const;
		Vec2<T> Rescaled(float length) const;
		Vec2<T> Rotated(float rad) const;

		Vec2<T>& operator += (const Vec2<T>& other);
		Vec2<T>& operator -= (const Vec2<T>& other);
		Vec2<T>& operator *= (float other);
		Vec2<T>& operator /= (float other);
		void Normalize();
		void Rescale(float length);
		void Rotate(float rad);

		operator const T* () { return &x; }
		operator T* () { return &x; }
	};

	template<Countable T>
	Vec2<T> operator * (float lhs, const Vec2<T>& rhs);

	template<Countable T>
	float Dot(const Vec2<T>& v1, const Vec2<T>& v2);

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned int>;

	// ===  Vec3  ===
	// TODO : Vec3

	// ===  Vec4  ===

	template<typename T> requires Countable<T>
	struct Vec4 {
		T x;
		T y;
		T z;
		T w;

		Vec4() : x(0), y(0) {}
		Vec4(T _x, T _y, T _z, T _w = 0) : x(_x), y(_y), z(_z), w(_w) {}
		Vec4(const Vec2<T>& v) : x(v.x), y(v.y), z(0), w(0) {}

		float Dot(const Vec4<T>& other) const;
		float MagnitudeSQ() const;
		float Magnitude() const;
		Vec4<T> operator + (const Vec4<T>& other) const;
		Vec4<T> operator - (const Vec4<T>& other) const;
		Vec4<T> operator * (float other) const;
		Vec4<T> operator / (float other) const;
		Vec4<T> Normalized() const;
		Vec4<T> Rescaled(float length) const;

		Vec4<T>& operator += (const Vec4<T>& other);
		Vec4<T>& operator -= (const Vec4<T>& other);
		Vec4<T>& operator *= (float other);
		Vec4<T>& operator /= (float other);
		void Normalize();
		void Rescale(float length);

		operator const T* () { return &x; }
		operator T* () { return &x; }

		operator Vec4<float>();
	};

	template<Countable T>
	Vec4<T> operator * (float lhs, const Vec4<T>& rhs);

	template<Countable T>
	float Dot(const Vec4<T>& v1, const Vec4<T>& v2);

	using Vec4f = ALIGN16 Vec4<float>;
	using Vec4d = Vec4<double>;
	using Vec4i = ALIGN16 Vec4<int>;
	using Vec4u = ALIGN16 Vec4<unsigned int>;
}

#include "TMM_Vectors.hpp"