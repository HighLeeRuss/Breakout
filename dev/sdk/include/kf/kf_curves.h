////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_CURVES_HEADER
#define KF_CURVES_HEADER

#include <ostream>
#include "kf/kf_types.h"
#include "kf/kf_math.h"

namespace kf
{
	template<typename T>
	inline T cubic(const T &v0, const T &v1, const T &v2, const T &v3, float t)
	{
		return (v3 - v2 - v0 + v1) * t * t * t + (2.0f * v0 - 2.0f * v1 + v2 - v3) * t * t + (v2 - v0) * t + v1;
	}

	template<typename T>
	inline T hermite(const T &v0, const T &v1, const T &v2, const T &v3, float bias, float tension, float t)
	{
		T m0, m1;
		float a0, a1, a2, a3;
		m0 = (v1 - v0) * (1.0f + bias) * (1.0f - tension) / 2.0f;
		m0 += (v2 - v1) * (1.0f - bias) * (1.0f - tension) / 2.0f;
		m1 = (v2 - v1) * (1.0f + bias) * (1.0f - tension) / 2.0f;
		m1 += (v3 - v2) * (1.0f - bias) * (1.0f - tension) / 2.0f;
		a0 = 2.0f * t * t * t - 3.0f * t * t + 1.0f;
		a1 = t * t * t - 2.0f * t * t + t;
		a2 = t * t * t - t * t;
		a3 = -2.0f * t * t * t + 3.0f * t * t;
		return a0 * v1 + a1 * m0 + a2 * m1 + a3 * v2;
	}

	template<typename T>
	inline T hermite(const T &v0, const T &v1, const T &v2, const T &v3, float tension, float t)
	{
		T m0, m1;
		float a0, a1, a2, a3;
		float tt = t * t;
		m0 = ((v1 - v0) + (v2 - v1)) * (1.0f - tension) * 0.5f;
		m1 = ((v2 - v1) + (v3 - v2)) * (1.0f - tension) * 0.5f;
		a0 = (2.0f * t - 3.0f) * tt + 1.0f;
		a1 = (t - 2.0f) * tt + t;
		a2 = tt * t - tt;
		a3 = (-2.0f * t + 3.0f) * tt;
		return a0 * v1 + a1 * m0 + a2 * m1 + a3 * v2;
	}

	template<typename T>
	inline T bezier(const std::vector<T> &controlPoints, float t)
	{
		std::vector<T> temp = controlPoints;
		for (int j = controlPoints.size() - 1; j > 0; --j)
		{
			for (int i = 0; i < j; ++i)
			{
				temp[i] = kf::lerp(temp[i],temp[i + 1], t);
			}
		}
		return temp[0];
	}

	template<typename T>
	inline T cubicPath(const std::vector<T> &controlPoints, float t)
	{
		int count = controlPoints.size();
		if (t >= 1.0)
			return controlPoints.back();
		int index = t*(count -1);
		int i0 = index - 1;
		int i1 = index;
		int i2 = index + 1;
		int i3 = index + 2;
		if (i3 > count - 1)
			i3 = count - 1;
		if (i0 < 0)
			i0 = 0;
		return kf::cubic(controlPoints[i0], controlPoints[i1], controlPoints[i2], controlPoints[i3], fmod(t*(count - 1), 1.0f));
	}

	template<typename T>
	inline T hermitePath(const std::vector<T> &controlPoints, float t)
	{
		int count = controlPoints.size();
		if (t >= 1.0)
			return controlPoints.back();
		int index = t*(count - 1);
		int i0 = index - 1;
		int i1 = index;
		int i2 = index + 1;
		int i3 = index + 2;
		if (i3 > count - 1)
			i3 = count - 1;
		if (i0 < 0)
			i0 = 0;
		return kf::hermite(controlPoints[i0], controlPoints[i1], controlPoints[i2], controlPoints[i3], 0.3, fmod(t*(count - 1), 1.0f));
	}

	template<typename T>
	inline std::vector<T> bezierToHermite(const std::vector<T> &controlPoints, int points)
	{
		std::vector<T> temp;
		for (int i = 0;i < points;++i)
		{
			temp.push_back(bezier(controlPoints, (1.0f / (points - 1))*i));
		}
		return temp;
	}

	template<typename T>
	inline float hermiteLength(const std::vector<T> &controlPoints, int points)
	{
		float length = 0;

		T lp = controlPoints[0];
		for (int i = 1;i < points;++i)
		{
			T p = hermitePath(controlPoints, (1.0f / (points - 1))*i);
			length += (p - lp).length();
		}
		return length;
	}

	//template<typename T>
	//inline std::vector<T> hermiteResample(const std::vector<T> &controlPoints, int points float step)
	//{
	//	std::vector<T> temp;
	//	float length = hermiteLength(controlPoints , controlPoints.size()*10);

	//	T lp = controlPoints[0];
	//	
	//	for (int i = 0; i < points; ++i)
	//	{
	//		T p = cubicPath(controlPoints, (1.0f / (points - 1))*i);
	//		length += (p - lp).length();
	//	}
	//	return length;
	//}

}
#endif
