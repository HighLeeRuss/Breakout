////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_TYPES_HEADER
#define KF_TYPES_HEADER

#include "kf/kf.h"

namespace kf
{
	static_assert(sizeof(long long) == 8, "long long isn't 8 bytes");
	static_assert(sizeof(int) == 4, "int isn't 4 bytes");
	static_assert(sizeof(short) == 2, "short isn't 2 bytes");
	static_assert(sizeof(char) == 1, "char isn't 1 byte");

	typedef unsigned long long	u64;
	typedef signed long long	s64;
	typedef unsigned int		u32;
	typedef signed int			s32;
	typedef unsigned short		u16;
	typedef signed short		s16;
	typedef unsigned char		u8;
	typedef signed char			s8;

	inline u8 nibbleToHex(u8 value)
	{
		const char *digits = "0123456789ABCDEF";
		return digits[(int) (value) & 15];

	}

	inline u16 byteToHex(u8 value)
	{
		const char *digits = "0123456789ABCDEF";
		return (digits[value >> 4] << 8) | (digits[value & 0x0f]);
	}

	template<typename T>
	inline T endianSwap(T value)
	{
		T temp;
		u8 *p = &value;
		for (int i = 0; i < sizeof(T); ++i)
		{
			&temp[sizeof(T) - i - 1] = p[i];
		}
		return temp;
	}
}

#endif
