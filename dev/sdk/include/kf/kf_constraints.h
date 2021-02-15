////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_CONSTRAINTS_HEADER
#define KF_CONSTRAINTS_HEADER

#include <ostream>
#include "kf/kf_types.h"
#include "kf/kf_math.h"

namespace kf
{
	template<typename T=float, typename T2>
	void constrainDistFixed(T2 &pos1, T2 &pos2, float desiredDist, float compensate1 = 0.5, float compensate2 = 0.5)
	{
		T2 delta = pos2 - pos1;
		T deltalength = kf::length(delta);
		if (deltalength > 0)
		{
			T diff = (deltalength - desiredDist) / deltalength;
			pos1 += delta * compensate1 * diff;
			pos2 -= delta * compensate2 * diff;
		}
	}

	template<typename T = float, typename T2>
	void constrainDistMin(T2 &pos1, T2 &pos2, float minDist, float compensate1 = 0.5, float compensate2 = 0.5)
	{
		T2 delta = pos2 - pos1;
		T deltalength = kf::length(delta);
		if (deltalength > 0 && deltalength < minDist)
		{
			T diff = (deltalength - minDist) / deltalength;
			pos1 += delta * compensate1 * diff;
			pos2 -= delta * compensate2 * diff;
		}
	}

	template<typename T = float, typename T2>
	void constrainDistMax(T2 &pos1, T2 &pos2, float maxDist, float compensate1 = 0.5, float compensate2 = 0.5)
	{
		T2 delta = pos2 - pos1;
		T deltalength = kf::length(delta);
		if (deltalength > 0 && deltalength > maxDist)
		{
			T diff = (deltalength - maxDist) / deltalength;
			pos1 += delta * compensate1 * diff;
			pos2 -= delta * compensate2 * diff;
		}
	}

	template<typename T = float, typename T2>
	void constrainDistRange(T2 &pos1, T2 &pos2, float minDist, float maxDist, float compensate1 = 0.5, float compensate2 = 0.5)
	{
		T2 delta = pos2 - pos1;
		T deltalength = kf::length(delta);
		if (deltalength > 0 && (deltalength > maxDist || deltalength < minDist))
		{
			T diff = (deltalength - maxDist) / deltalength;
			pos1 += delta * compensate1 * diff;
			pos2 -= delta * compensate2 * diff;
		}
	}

	template<typename T = float, typename T2>
	void constrainBox(T2& pos, const T2& minCorner, const T2& maxCorner)
	{
		pos = kf::minimum(kf::maximum(pos, minCorner), maxCorner);
	}
}
#endif
