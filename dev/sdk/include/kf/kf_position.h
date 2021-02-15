////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_POSITION_HEADER
#define KF_POSITION_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include "kf/kf_vector.h"
#include "kf/kf_fixed.h"

#pragma warning( disable : 4201)

namespace kf
{
	template<typename T, int fracBits>
	class PositionT
	{
	public:
		enum
		{
			size = 3
		};
		enum Elements
		{
			X = 0,
			Y = 1,
			Z = 2
		};
		union
		{
			kf::FixedT<T, fracBits> e[3];
			struct
			{
				kf::FixedT<T, fracBits> x;
				kf::FixedT<T, fracBits> y;
				kf::FixedT<T, fracBits> z;
			};
		};

		PositionT() : x(0), y(0), z(0)
		{
		}

		inline PositionT operator+(const kf::Vec3 &v)
		{
			PositionT p(*this);
			p.x += v.x;
			p.y += v.y;
			p.z += v.z;
			return p;
		}

		inline PositionT operator-(const kf::Vec3 &v)
		{
			PositionT p(*this);
			p.x -= v.x;
			p.y -= v.y;
			p.z -= v.z;
			return p;
		}

		//inline kf::Vector3 operator-(const kf::Position &p)
		//{
		//	return kf::Vector3(
		//}
		//
	};
	typedef PositionT<long long, 16>  Position48_16;
	typedef PositionT<long long, 16>  Position;

}

#endif

