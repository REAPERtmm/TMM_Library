#pragma once

// REQUIRED internal inclusion
#include <TMM_Setup.h>

// REQUIRED external inclusion
#include <float.h>
#include <cmath>

namespace TMM
{
	template<unsigned char DIM, typename T, typename Derived>
	struct Vec {
		virtual __forceinline float Dot(const Derived& other) const = 0;
		virtual float MagnitudeSQ() const = 0;
		virtual float Magnitude() const = 0;

		virtual Derived Normalized() const = 0;
		virtual Derived Rescaled(float length) const = 0;
		virtual __forceinline Derived operator + (const Derived& other) const = 0;
		virtual __forceinline Derived operator - (const Derived& other) const = 0;
		virtual __forceinline Derived operator * (float other) const = 0;
		virtual __forceinline Derived operator / (float other) const = 0;

		virtual void Normalize() = 0;
		virtual void Rescale(float length) = 0;
		virtual __forceinline Derived& operator += (const Derived& other) = 0;
		virtual __forceinline Derived& operator -= (const Derived& other) = 0;
		virtual __forceinline Derived& operator *= (float other) = 0;
		virtual __forceinline Derived& operator /= (float other) = 0;

		virtual __forceinline bool operator == (const Derived& other) = 0;
		virtual __forceinline bool operator != (const Derived& other) = 0;
		virtual __forceinline bool operator < (const Derived& other) = 0;
		virtual __forceinline bool operator > (const Derived& other) = 0;
		virtual __forceinline bool operator >= (const Derived& other) = 0;
		virtual __forceinline bool operator <= (const Derived& other) = 0;

		virtual __forceinline operator const T* () = 0;
		virtual __forceinline operator T* () = 0;
	};
	


	template<typename T> requires Countable<T>
	struct Vec2 : public Vec<2, T, Vec2<T>>
	{
		union
		{
			struct { T x, y; };
			struct { T u, v; };
		};

		Vec2() : x(0), y(0) {};
		Vec2(T _x, T _y) : x(_x), y(_y) {};

		// ===  Vec  === 

		__forceinline float Dot(const Vec2& other) const override 
		{ 
			return x * other.x + y * other.y; 
		}

		float MagnitudeSQ() const override 
		{ 
			return static_cast<float>(x * x + y * y); 
		}

		float Magnitude() const override 
		{ 
			return sqrtf(static_cast<float>(x * x + y * y)); 
		}


		Vec2 Normalized() const override 
		{ 
			float r_Magnitude = 1 / Magnitude(); 
			return { x * r_Magnitude, y * r_Magnitude }; 
		}

		Vec2 Rescaled(float length) const override 
		{ 
			float factor = length / Magnitude(); 
			return { x * factor, y * factor };
		}

		__forceinline Vec2 operator + (const Vec2& other) const override 
		{ 
			return { x + other.x, y + other.y }; 
		}

		__forceinline Vec2 operator - (const Vec2& other) const override 
		{ 
			return { x - other.x, y - other.y };
		}

		__forceinline Vec2 operator * (float other) const override 
		{ 
			return { x * other, y * other }; 
		}

		__forceinline Vec2 operator / (float other) const override 
		{ 
			return { x / other, y / other }; 
		}


		void Normalize() override 
		{ 
			float r_Magnitude = 1 / Magnitude();
			x *= r_Magnitude; 
			y *= r_Magnitude; 
		}

		void Rescale(float length) override 
		{ 
			float factor = length / Magnitude();
			x *= factor;
			y *= factor;
		}

		__forceinline Vec2& operator += (const Vec2& other) override 
		{ 
			x += other.x; 
			y += other.y;
			return *this;
		}

		__forceinline Vec2& operator -= (const Vec2& other) override 
		{ 
			x -= other.x; 
			y -= other.y;
			return *this;
		}

		__forceinline Vec2& operator *= (float other) override 
		{ 
			x *= other; 
			y *= other;
			return *this;
		}

		__forceinline Vec2& operator /= (float other) override 
		{ 
			x /= other;
			y /= other;
			return *this;
		}


		__forceinline bool operator == (const Vec2& other) override
		{
			if constexpr (TMM::is_same<T, float>::value) {
				float dx = fabs(x - other.x);
				float dy = fabs(y - other.y);
				return dx < FLT_EPSILON && dy < FLT_EPSILON;
			}
			if constexpr (TMM::is_same<T, double>::value) {
				float dx = abs(x - other.x);
				float dy = abs(y - other.y);
				return dx < DBL_EPSILON && dy < DBL_EPSILON;
			}
			else {
				return x == other.x && y == other.y;
			}
		}

		__forceinline bool operator != (const Vec2& other) override
		{
			return !operator==(other);
		}

		__forceinline bool operator < (const Vec2& other) override
		{
			return MagnitudeSQ() < other.MagnitudeSQ();
		}

		__forceinline bool operator > (const Vec2& other) override
		{
			return MagnitudeSQ() > other.MagnitudeSQ();
		}

		__forceinline bool operator >= (const Vec2& other) override
		{
			return operator >(other) || operator==(other);
		}

		__forceinline bool operator <= (const Vec2& other) override
		{
			return operator <(other) || operator==(other);
		}


		__forceinline operator const T* () override { return &x; }
		__forceinline operator T* () override { return &x; }

		// ===  Additional Functionalities  === 

		Vec2<T> Rotated(float rad) const 
		{ 
			float _cos = cosf(rad); 
			float _sin = sinf(rad); 
			return { x * _cos - y * _sin, x * _sin + y * _cos }; 
		}

		void Rotate(float rad) 
		{ 
			float _cos = cosf(rad); 
			float _sin = sinf(rad); 
			float temp = x * _cos - y * _sin; 
			y = x * _sin + y * _cos; 
			x = temp; 
		};

	};

	template<Countable T>
	__forceinline Vec2<T> operator * (float lhs, const Vec2<T>& rhs) 
	{
		return { rhs.x * lhs, rhs.y * lhs };
	}

	template<Countable T>
	__forceinline float Dot(const Vec2<T>& v1, const Vec2<T>& v2) 
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	// ===  Vec3  ===

	template<typename T> requires Countable<T>
	struct Vec3 : public Vec<3, T, Vec3<T>>
	{
		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		Vec3() : x(0), y(0), z(0) {};
		Vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {};

		// ===  Vec  === 

		__forceinline float Dot(const Vec3& other) const override 
		{ 
			return x * other.x + y * other.y + z * other.z;
		}

		float MagnitudeSQ() const override 
		{ 
			return static_cast<float>(x * x + y * y + z * z); 
		}

		float Magnitude() const override 
		{ 
			return sqrtf(static_cast<float>(x * x + y * y + z * z)); 
		}


		Vec3 Normalized() const override { 
			float r_Magnitude = 1 / Magnitude(); 
			return { x * r_Magnitude, y * r_Magnitude, z * r_Magnitude }; 
		}

		Vec3 Rescaled(float length) const override 
		{ 
			float factor = length / Magnitude();
			return { x * factor, y * factor, z * factor };
		}

		__forceinline Vec3 operator + (const Vec3& other) const override 
		{ 
			return { x + other.x, y + other.y, z + other.z }; 
		}

		__forceinline Vec3 operator - (const Vec3& other) const override 
		{ 
			return { x - other.x, y - other.y, z - other.z }; 
		}

		__forceinline Vec3 operator * (float other) const override 
		{ 
			return { x * other, y * other, z * other }; 
		}

		__forceinline Vec3 operator / (float other) const override 
		{ 
			return { x / other, y / other, z / other }; 
		}


		void Normalize() override 
		{ 
			float r_Magnitude = 1 / Magnitude(); 
			x *= r_Magnitude; 
			y *= r_Magnitude; 
			z *= r_Magnitude; 
		}

		void Rescale(float length) override 
		{ 
			float factor = length / Magnitude(); 
			x *= factor; 
			y *= factor; 
			z *= factor; 
		}

		__forceinline Vec3& operator += (const Vec3& other) override 
		{ 
			x += other.x; 
			y += other.y; 
			z += other.z; 
			return *this;
		}

		__forceinline Vec3& operator -= (const Vec3& other) override 
		{ 
			x -= other.x; 
			y -= other.y; 
			z -= other.z;
			return *this;
		}

		__forceinline Vec3& operator *= (float other) override 
		{ 
			x *= other; 
			y *= other; 
			z *= other;
			return *this;
		}

		__forceinline Vec3& operator /= (float other) override 
		{ 
			x /= other; 
			y /= other; 
			z /= other;
			return *this;
		}


		__forceinline bool operator == (const Vec3& other) override
		{
			if constexpr (TMM::is_same<T, float>::value) {
				float dx = fabs(x - other.x);
				float dy = fabs(y - other.y);
				float dz = fabs(z - other.z);
				return dx < FLT_EPSILON && dy < FLT_EPSILON && dz < FLT_EPSILON;
			}
			if constexpr (TMM::is_same<T, double>::value) {
				float dx = abs(x - other.x);
				float dy = abs(y - other.y);
				float dz = abs(z - other.z);
				return dx < DBL_EPSILON && dy < DBL_EPSILON && dz < DBL_EPSILON;
			}
			else {
				return x == other.x && y == other.y && z == other.z;
			}
		}

		__forceinline bool operator != (const Vec3& other) override
		{
			return !operator==(other);
		}

		__forceinline bool operator < (const Vec3& other) override
		{
			return MagnitudeSQ() < other.MagnitudeSQ();
		}

		__forceinline bool operator > (const Vec3& other) override
		{
			return MagnitudeSQ() > other.MagnitudeSQ();
		}

		__forceinline bool operator >= (const Vec3& other) override
		{
			return operator >(other) || operator==(other);
		}

		__forceinline bool operator <= (const Vec3& other) override
		{
			return operator <(other) || operator==(other);
		}


		__forceinline operator const T* () override { return &x; }
		__forceinline operator T* () override { return &x; }

		// ===  Additional Functionalities  === 

	};

	template<Countable T>
	__forceinline Vec3<T> operator * (float lhs, const Vec3<T>& rhs) {
		return { rhs.x * lhs, rhs.y * lhs, rhs.z * lhs };
	}

	template<Countable T>
	__forceinline float Dot(const Vec3<T>& v1, const Vec3<T>& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	// ===  Vec4  ===

	template<typename T> requires Countable<T>
	struct Vec4 : public Vec<4, T, Vec4<T>>
	{
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};

		Vec4() : x(0), y(0), z(0), w(0) {};
		Vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {};

		// ===  Vec  === 

		__forceinline float Dot(const Vec4& other) const override
		{
			return x * other.x + y * other.y + z * other.z + w * other.w;
		}

		float MagnitudeSQ() const override
		{
			return static_cast<float>(x * x + y * y + z * z + w * w);
		}

		float Magnitude() const override
		{
			return sqrtf(static_cast<float>(x * x + y * y + z * z + w * w));
		}

		Vec4 Normalized() const override {
			float r_Magnitude = 1 / Magnitude();
			return { x * r_Magnitude, y * r_Magnitude, z * r_Magnitude, w * r_Magnitude };
		}

		Vec4 Rescaled(float length) const override
		{
			float factor = length / Magnitude();
			return { x * factor, y * factor, z * factor, w * factor };
		}

		__forceinline Vec4 operator + (const Vec4& other) const override
		{
			return { x + other.x, y + other.y, z + other.z, w + other.w };
		}

		__forceinline Vec4 operator - (const Vec4& other) const override
		{
			return { x - other.x, y - other.y, z - other.z, w - other.w };
		}

		__forceinline Vec4 operator * (float other) const override
		{
			return { x * other, y * other, z * other, w * other };
		}

		__forceinline Vec4 operator / (float other) const override
		{
			return { x / other, y / other, z / other, w / other };
		}

		void Normalize() override
		{
			float r_Magnitude = 1 / Magnitude();
			x *= r_Magnitude;
			y *= r_Magnitude;
			z *= r_Magnitude;
			w *= r_Magnitude;
		}

		void Rescale(float length) override
		{
			float factor = length / Magnitude();
			x *= factor;
			y *= factor;
			z *= factor;
			w *= factor;
		}

		__forceinline Vec4& operator += (const Vec4& other) override
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		__forceinline Vec4& operator -= (const Vec4& other) override
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		__forceinline Vec4& operator *= (float other) override
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;
			return *this;
		}

		__forceinline Vec4& operator /= (float other) override
		{
			x /= other;
			y /= other;
			z /= other;
			w /= other;
			return *this;
		}

		__forceinline bool operator == (const Vec4& other) override
		{
			if constexpr (TMM::is_same<T, float>::value) {
				float dx = fabs(x - other.x);
				float dy = fabs(y - other.y);
				float dz = fabs(z - other.z);
				float dw = fabs(w - other.w);
				return dx < FLT_EPSILON && dy < FLT_EPSILON && dz < FLT_EPSILON && dw < FLT_EPSILON;
			}
			if constexpr (TMM::is_same<T, double>::value) {
				float dx = abs(x - other.x);
				float dy = abs(y - other.y);
				float dz = abs(z - other.z);
				float dw = abs(w - other.w);
				return dx < DBL_EPSILON && dy < DBL_EPSILON && dz < DBL_EPSILON && dw < DBL_EPSILON;
			}
			else {
				return x == other.x && y == other.y && z == other.z && w == other.w;
			}
		}

		__forceinline bool operator != (const Vec4& other) override
		{
			return !operator==(other);
		}

		__forceinline bool operator < (const Vec4& other) override
		{
			return MagnitudeSQ() < other.MagnitudeSQ();
		}

		__forceinline bool operator > (const Vec4& other) override
		{
			return MagnitudeSQ() > other.MagnitudeSQ();
		}

		__forceinline bool operator >= (const Vec4& other) override
		{
			return operator >(other) || operator==(other);
		}

		__forceinline bool operator <= (const Vec4& other) override
		{
			return operator <(other) || operator==(other);
		}

		__forceinline operator const T* () override { return &x; }
		__forceinline operator T* () override { return &x; }

		// ===  Additional Functionalities  === 

	};

	template<Countable T>
	__forceinline Vec4<T> operator * (float lhs, const Vec4<T>& rhs) {
		return { rhs.x * lhs, rhs.y * lhs, rhs.z * lhs };
	}

	template<Countable T>
	__forceinline float Dot(const Vec4<T>& v1, const Vec4<T>& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	// ===  using  ===

	using Vec2f = Vec2<float>;
	using Vec2d = Vec2<double>;
	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned int>;

	using Vec3f = Vec3<float>;
	using Vec3d = Vec3<double>;
	using Vec3i = Vec3<int>;
	using Vec3u = Vec3<unsigned int>;
	using ColorRGB255 = Vec3<unsigned char>;

	using Vec4f = Vec4<float>;
	using Vec4d = Vec4<double>;
	using Vec4i = Vec4<int>;
	using Vec4u = Vec4<unsigned int>;
	using ColorRGBA255 = Vec4<unsigned char>;
}
