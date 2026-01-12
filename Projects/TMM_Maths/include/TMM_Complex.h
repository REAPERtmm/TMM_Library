#pragma once

// REQUIRED internal inclusion
#include <TMM_Setup.h>
#include "TMM_MathUnits.h"

// REQUIRED external inclusion
#include <cmath>
#include <float.h>

namespace TMM
{

	struct Complex
	{
		R_SET RealPart = 0;
		R_SET ImaginaryPart = 0;

		__forceinline const R_SET& Re() const { return RealPart; };
		__forceinline const R_SET& Im() const { return ImaginaryPart; };

		static inline Complex ImaginaryPure(R_SET im) { return Complex{ 0, im }; }
		static inline Complex RealPure(R_SET re) { return Complex{ re, 0 }; }

		static inline Complex Polar(R_SET r, Radians phi) { return Complex{ r * cos(phi), r * sin(phi) }; }
		Complex(R_SET re = 0, R_SET im = 0) : RealPart(re), ImaginaryPart(im) {};

		__forceinline Complex Conjugate() const
		{
			return Complex{
				Re(),
				-Im()
			};
		}

		__forceinline Radians Argument() const
		{
			return atan2f(Im(), Re());
		}

		__forceinline R_SET Module() const
		{
			return sqrtf(InternalSumSquare());
		}

		__forceinline R_SET Abs() const
		{
			return Module();
		}

		__forceinline bool IsZero() const {
			return 
				-FLT_EPSILON < Re() && Re() < FLT_EPSILON &&
				-FLT_EPSILON < Im() && Im() < FLT_EPSILON;
		}

		__forceinline Complex Reverse() const
		{
			R_SET InverseSumSquare = 1 / InternalSumSquare();
			return Complex{
				Re() * InverseSumSquare,
				-Im() * InverseSumSquare
			};
		}

		inline Complex operator + (const Complex& other) const
		{
			return Complex{
				Re() + other.Re(),
				Im() + other.Im()
			};
		}

		inline Complex operator - (const Complex& other) const
		{
			return Complex{
				Re() - other.Re(),
				Im() - other.Im()
			};
		}

		inline Complex operator * (const Complex& other) const
		{
			return Complex{
				Re() * other.Re() - Im() * other.Im(),
				Im() * other.Re() + Re() * other.Im()
			};
		}

		inline Complex operator / (const Complex& other) const
		{
			return operator * (other.Reverse());
		}

		inline bool operator == (const Complex& other) const {
			return operator -(other).IsZero();
		};

		inline operator R_SET() const { return Re(); }

	private:

		inline R_SET InternalSumSquare() const
		{
			return Re() * Re() + Im() * Im();
		}

	};

}