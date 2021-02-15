////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_SSE_HEADER
#define KF_SSE_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include <limits>
#include <intrin.h>

namespace kf
{
	namespace sse
	{
		float minimum(float a, float b)
		{
			// Branchless SSE min.
			_mm_store_ss(&a, _mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
			return a;
		}

		float maximum(float a, float b)
		{
			// Branchless SSE max.
			_mm_store_ss(&a, _mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
			return a;
		}
	}
}

#endif

