////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_RANDOM_HEADER
#define KF_RANDOM_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector.h"
// hashRJ32 - http://www.concentric.net/~Ttwang/tech/inthash.htm
// Xor128 - http://en.wikipedia.org/wiki/Xorshift
// SplitMix64 - http://vigna.di.unimi.it/xorshift/splitmix64.c

namespace kf
{

	class SplitMix64
	{
	public:
		kf::u64 state;
		SplitMix64(kf::u64 s = 0)
		{
			state = s;
		}
		void seed(kf::u64 s)
		{
			state = s;
		}
		kf::u64 operator()() 
		{
			kf::u64 z = (state += 0x9e3779b97f4a7c15);
			z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
			z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
			return z ^ (z >> 31);
		}
		kf::u64 operator()(kf::u64 upper)
		{
			return (*this)() % upper;
		}
		kf::u64 operator()(kf::u64 lower, kf::u64 upper)
		{
			kf::u64 r = (*this)();
			return lower + r % (upper - lower);
		}
		double norm()
		{
			return double((*this)()) / double(0xffffffffffffffffULL);
		}
	};

	inline kf::u32 hashRJ32( kf::u32 a)
	{
		a = (a+0x7ed55d16) + (a<<12);
		a = (a^0xc761c23c) ^ (a>>19);
		a = (a+0x165667b1) + (a<<5);
		a = (a+0xd3a2646c) ^ (a<<9);
		a = (a+0xfd7046c5) + (a<<3);
		a = (a^0xb55a4f09) ^ (a>>16);
		return a;
	}

	class Xor128
	{
	public:
		Xor128():m_x(123456789),m_y(362436069),m_z(521288629),m_w(88675123)
		{
		}
		Xor128(kf::u32 s)
		{
			seed(s);
		}
		void seed(kf::u32 seed)
		{
			SplitMix64 sm(seed);
			kf::u64 a = sm();
			kf::u64 b = sm();
			m_x = a & 0xffffffff;
			m_y = a >> 32;
			m_z = b & 0xffffffff;
			m_w = b >> 32;
		}
		kf::u32 operator()()
		{
			kf::u32 t;
			t = m_x ^ (m_x << 11);
			m_x = m_y; m_y = m_z; m_z = m_w;
			return m_w = m_w ^ (m_w >> 19) ^ (t ^ (t >> 8));
		}
		kf::u64 operator()(kf::u32 upper)
		{
			return (*this)() % upper;
		}
		kf::u32 operator()(kf::u32 lower, kf::u32 upper)
		{
			kf::u32 r = (*this)();
			return lower + r % (upper - lower);
		}		
		double norm()
		{
			return double((*this)())/double(0xffffffff);
		}
	protected:
		kf::u32 m_x;
		kf::u32 m_y;
		kf::u32 m_z;
		kf::u32 m_w;
	};


}

#endif
