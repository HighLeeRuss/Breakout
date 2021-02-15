////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_MATH_H
#define KF_MATH_H
#include <cmath>
#include <cstdlib>

namespace kf
{
	const float PI = 3.14159265f;

	template<typename T>
	inline typename T::TYPE length(const T &value)
	{
		return T::length(value);
	}

	template<typename T>
	inline T minimum(const T &value1, const T &value2)
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			return value1 < value2 ? value1 : value2;
		}
		else
		{
			return T::minimum(value1, value2);
		}
	}

	template<typename T>
	inline T maximum(const T &value1, const T &value2)
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			return value1 > value2 ? value1 : value2;
		}
		else
		{
			return T::maximum(value1, value2);
		}
	}

	template<typename T>
	inline T clamp(T v, T low, T high)
	{
		if (v < low) v = low;
		if (v > high) v = high;
		return v;
	}

	template<typename T>
	inline T sign(T v)
	{
		if (v < 0) return -1;
		if (v > 0) return 1;
		return 0;
	}

	template<typename T>
	inline T saturate(T v)
	{
		if (v < 0) v = 0;
		if (v > 1) v = 1;
		return v;
	}

	template<typename T1, typename T2>
	inline T1 lerp(const T1 &val1, const T1 &val2, T2 t)
	{
		return (val2 - val1) * t + val1;
	}

	template<typename T>
	inline T remap(const T &src_range_start, const T &src_range_end, const T &dst_range_start, const T &dst_range_end, const T &value_to_remap)
	{
		return ((dst_range_end - dst_range_start) * (value_to_remap - src_range_start)) / (src_range_end - src_range_start) + dst_range_start;
	}

	template<typename T>
	inline T s_curve(const T &val)
	{
		return val * val*(T(3.0) - T(2.0)*val);
	}

	template<typename T>
	inline T expose(const T &val)
	{
		return 1.0 - exp(-val);
	}

	template<typename T>
	inline T acos(const T &val)
	{
		if (val <= 1.0 && val >= -1.0f)
			return std::acos(val);
		return 0.0f;
	}

	template<typename T>
	inline T asin(const T &val)
	{
		if (val <= 1.0 && val >= -1.0f)
			return std::asin(val);
		return 0.0f;
	}

	template<typename T>
	inline T sqrt(const T& value)
	{
		if constexpr (std::is_arithmetic_v<T>)
		{
			return std::sqrt(value);
		}
		else
		{
			return T::sqrt(value);
		}
	}
}

#endif
