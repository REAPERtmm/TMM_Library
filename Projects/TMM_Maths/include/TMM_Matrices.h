#pragma once

// REQUIRED internal inclusion
#include <TMM_Setup.h>

// REQUIRED external inclusion
#include <memory.h>

namespace TMM
{
	template<unsigned char WIDTH, unsigned char HEIGHT, typename T> requires (Countable<T> && WIDTH != 0 && HEIGHT != 0)
	struct Mat {
		static constexpr size_t SIZE = WIDTH * HEIGHT;

		union
		{
			struct { T data[SIZE]; };
			struct { T m[HEIGHT][WIDTH]; };
		};

		constexpr T& operator()(unsigned char x, unsigned char y) { return m[y][x]; }
		constexpr const T& operator()(unsigned char x, unsigned char y) const { return m[y][x]; }

		template<typename... Args> requires (sizeof...(Args) == SIZE)
		constexpr Mat(Args... args) 
			: data{ static_cast<T>(args)... } 
		{ 

		}

		template<typename F>
		constexpr Mat(F&& generator)
		{
			for (unsigned char y = 0; y < HEIGHT; ++y)
				for (unsigned char x = 0; x < WIDTH; ++x)
					(*this)(x, y) = generator(x, y);
		}

		constexpr Mat()
			: Mat([](unsigned char x, unsigned char y) { return x == y ? 1 : 0; }) 
		{ 

		}

		Mat<WIDTH - 1, HEIGHT - 1, T> SubMat(unsigned char _x, unsigned char _y) const {
			return Mat<WIDTH - 1, HEIGHT - 1, T>([&](unsigned char x, unsigned char y)
				{
					return (*this)((x < _x ? x : x + 1), (y < _y ? y : y + 1));
				}
			);
		}

		Mat Transposed() const {
			static_assert(WIDTH == HEIGHT, "Cant transpose a non squared matrix");
			return Mat([&](unsigned char x, unsigned char y)
				{
					return (*this)(y, x);
				}
			);
		}

		constexpr void Transpose() {
			static_assert(WIDTH == HEIGHT, "Cant transpose a non squared matrix");
			if constexpr (Decimal<T>) {
				for (int y = 0; y < HEIGHT; ++y) {
					for (int x = y; x < WIDTH; ++x) {
						TMM_SWAP((*this)(x, y), (*this)(y, x));
					}
				}
			}
			else {
				for (int y = 0; y < HEIGHT; ++y) {
					for (int x = y; x < WIDTH; ++x) {
						TMM_SWAP_XOR((*this)(x, y), (*this)(y, x));
					}
				}
			}
		}

		__forceinline Mat operator+(const Mat& other) const
		{
			return Mat([&](unsigned char x, unsigned char y) 
				{
					return (*this)(x, y) + other(x, y);
				}
			);
		}

		__forceinline Mat operator-(const Mat& other) const
		{
			return Mat([&](unsigned char x, unsigned char y) 
				{
					return (*this)(x, y) - other(x, y);
				}
			);
		}

		__forceinline Mat operator*(float other) const
		{
			return Mat([&](unsigned char x, unsigned char y)
				{
					return (*this)(x, y) * other;
				}
			);
		}

		__forceinline Mat operator/(float other) const
		{
			return Mat([&](unsigned char x, unsigned char y)
				{
					return (*this)(x, y) / other;
				}
			);
		}

		__forceinline Mat operator*(const Mat& other) const
		{
			return Mat([&](unsigned char x, unsigned char y)
				{
					T value = 0;
					for (int i = 0; i < WIDTH; ++i) {
						value += (*this)(i, y) * other(x, i);
					}
					return value;
				}
			);
		}

		template<typename D = float> requires Decimal<D>
		constexpr double Determinant() const {
			static_assert(WIDTH == HEIGHT, "Cant find the determinant of a non squared matrix");
			if constexpr (WIDTH == 1) {
				return m[0][0];
			}
			else if constexpr (WIDTH == 2) {
				return m[0][0] * m[1][1] - m[1][0] * m[0][1];
			}
			else if constexpr (WIDTH == 3) {
				return 
					  m[0][0] * m[1][1] * m[2][2]
					+ m[0][1] * m[1][2] * m[2][0]
					+ m[0][2] * m[1][0] * m[2][1]
					- m[0][2] * m[1][1] * m[2][0]
					- m[0][1] * m[1][0] * m[2][2]
					- m[0][0] * m[1][2] * m[2][1];
			}
			else {
				D det = 0.0;
				for (unsigned char x = 0; x < WIDTH; ++x) {
					auto sub_mat = SubMat(x, 0);
					auto sign = (x % 2 == 0 ? 1 : -1);
					auto sub_det = sub_mat.Determinant<D>();
					auto cofactor = sign * sub_det;
					det += (*this)(x, 0) * cofactor;
				}
				return det;
			}
		}
	};


	using Matf4x4 = Mat<4, 4, float>;
	using Matd4x4 = Mat<4, 4, double>;
	using Mati4x4 = Mat<4, 4, int>;
	using Matu4x4 = Mat<4, 4, unsigned int>;

	using Matf3x3 = Mat<3, 3, float>;
	using Matd3x3 = Mat<3, 3, double>;
	using Mati3x3 = Mat<3, 3, int>;
	using Matu3x3 = Mat<3, 3, unsigned int>;

	using Matf2x2 = Mat<2, 2, float>;
	using Matd2x2 = Mat<2, 2, double>;
	using Mati2x2 = Mat<2, 2, int>;
	using Matu2x2 = Mat<2, 2, unsigned int>;
}
