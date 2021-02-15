////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_FIXED_HEADER
#define KF_FIXED_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include <ostream>
#include <intrin.h>

namespace kf
{
	template<typename T, int FRACBITS>
	class FixedT
	{
	public:
		typedef T type;
		enum
		{
			intBits = sizeof(T) * 8 - FRACBITS,
			fracBits = FRACBITS
			//multiplier = 1<<fracBits
		};
		const T multiplier = 1LL << fracBits;
		T raw;

		FixedT():raw(0)
		{
		}

		template <typename TT>
		FixedT(TT v):raw(v*multiplier)
		{
		}

		inline FixedT(const FixedT& a)
		{
			raw = a.raw;
		}

		inline FixedT& operator=(const FixedT& a)
		{
			raw = a.raw;
			return *this;
		}

		inline FixedT operator+(const FixedT &v) const
		{
			FixedT t;
			t.raw = raw + v.raw;
			return t;
		}

		inline FixedT operator-(const FixedT &v) const
		{
			FixedT t;
			t.raw = raw - v.raw;
			return t;
		}

		inline FixedT operator*(const FixedT &v) const
		{
			FixedT t;
			t.raw = rawMulDiv(raw, v.raw, multiplier);
			//if constexpr (sizeof(T) > 4)
			//{
			//	long long high;
			//	t.raw = _mul128(raw, v.raw, &high);
			//}
			//else
			//{
			//	t.raw = ((long long)raw * (long long)v.raw) / (long long)multiplier;
			//}
			
			return t;
		}

		inline FixedT operator/(const FixedT &v) const
		{
			FixedT t;
			t.raw = rawMulDiv(raw, multiplier, v.raw);
			//t.raw = ((long long)raw * (long long)multiplier) / (long long)v.raw;
			return t;
		}

		inline FixedT operator-() const
		{
			FixedT t;
			t.raw = -raw;
			return t;
		}

		inline T integer() const
		{
			return raw >= 0 ? raw >> fracBits : (raw >> fracBits) + 1;
		}

		inline double frac() const
		{
			double d = double(raw & (multiplier - 1)) / double(multiplier);
			return raw >= 0 ? d : 1.0 - d;
		}

		explicit inline operator float() const
		{
			return float(raw) / multiplier;
		}

		inline operator double() const
		{
			return double(raw) / multiplier;
		}

		inline T rawMul(const T& a, const T& b) const
		{
			if constexpr (sizeof(T) > 4)
			{
				long long high;
				return _mul128(a, b, &high);
			}
			else
			{
				return (long long)a * (long long)b;
			}
		}
		inline T rawMulDiv(const T& a, const T& b, const T& c) const
		{
			if constexpr (sizeof(T) > 4)
			{
				long long high;
				long long low;
				long long remainder;
				low = _mul128(a, b, &high);
				return _div128(high, low, c, &remainder);
			}
			else
			{
				return ((long long)a * (long long)b) / (long long)c;
			}
		}
	};

	template<typename T, int FRACBITS>
	FixedT<T, FRACBITS> sqrt(const FixedT<T, FRACBITS>& f)
	{
		FixedT<T, FRACBITS> t;
		if constexpr (sizeof(T) > 4)
		{
			t.raw = std::sqrt((long long)f.raw) * (long long)sqrt(f.multiplier);
		}
		else
		{
			t.raw = std::sqrt((long long)f.raw * (long long)f.multiplier);
		}
		return t;
	}

#pragma region IO
	template<typename T, int FRACBITS>
	inline std::ostream& operator<<(std::ostream& o, const FixedT<T,FRACBITS>& f)
	{
		o << (double)f;
		return o;
	}
#pragma endregion


	typedef FixedT<short, 8>  Fixed8_8;
	typedef FixedT<int, 8>  Fixed24_8;
	typedef FixedT<int, 16>  Fixed16_16;
	typedef FixedT<long long, 16>  Fixed48_16;
	typedef FixedT<long long, 32>  Fixed32_32;

}

#endif

