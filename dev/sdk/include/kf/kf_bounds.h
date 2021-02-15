////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_BOUNDS_HEADER
#define KF_BOUNDS_HEADER

//#include "kf/kf_bounds1.h"
//#include "kf/kf_bounds2.h"
//#include "kf/kf_bounds3.h"
#include "kf/kf_vector.h"

namespace kf
{
	template<typename TT, int DIM>
	class AABB
	{
	public:
		using TYPE = typename TT;

		Vec<TT, DIM> minCorner;
		Vec<TT, DIM> maxCorner;
		bool infinite;

		inline AABB() :minCorner(std::numeric_limits<TT>::max()), maxCorner(std::numeric_limits<TT>::min()), infinite(false)
		{
		}

		explicit inline AABB(const Vec<TT, DIM>& v) : minCorner(v), maxCorner(v), infinite(false)
		{
		}

		explicit inline AABB(const Vec<TT, DIM>& v1, const Vec<TT, DIM>& v2) : infinite(false)
		{
			kf::reorder(v1, v2, minCorner, maxCorner);
		}

		explicit inline AABB(bool inf) : minCorner(std::numeric_limits<TT>::max()), maxCorner(std::numeric_limits<TT>::min()), infinite(inf)
		{
		}

		//inline AABB(TT x1, TT y1, TT z1, TT x2, TT y2, TT z2) : infinite(false)
		//{
		//	kf::reorder(Vec
		//	if (x1 <= x2)
		//	{
		//		minCorner.x = x1;
		//		maxCorner.x = x2;
		//	}
		//	else
		//	{
		//		minCorner.x = x2;
		//		maxCorner.x = x1;
		//	}
		//	if (y1 <= y2)
		//	{
		//		minCorner.y = y1;
		//		maxCorner.y = y2;
		//	}
		//	else
		//	{
		//		minCorner.y = y2;
		//		maxCorner.y = y1;
		//	}
		//	if (z1 <= z2)
		//	{
		//		minCorner.z = z1;
		//		maxCorner.z = z2;
		//	}
		//	else
		//	{
		//		minCorner.z = z2;
		//		maxCorner.z = z1;
		//	}
		//}

		inline AABB& operator=(const Vec<TT, DIM>& v)
		{
			minCorner = v;
			maxCorner = v;
			infinite = false;
			return *this;
		}

		inline AABB& set(const Vec<TT, DIM>& v)
		{
			minCorner = v;
			maxCorner = v;
			infinite = false;
			return *this;
		}

		inline AABB& set(const Vec<TT, DIM>& v1, const Vec<TT, DIM>& v2)
		{
			if (v1.x <= v2.x)
			{
				minCorner.x = v1.x;
				maxCorner.x = v2.x;
			}
			else
			{
				minCorner.x = v2.x;
				maxCorner.x = v1.x;
			}
			if constexpr (DIM >= 2)
			{
				if (v1.y <= v2.y)
				{
					minCorner.y = v1.y;
					maxCorner.y = v2.y;
				}
				else
				{
					minCorner.y = v2.y;
					maxCorner.y = v1.y;
				}
			}
			if constexpr (DIM >= 3)
			{
				if (v1.z <= v2.z)
				{
					minCorner.z = v1.z;
					maxCorner.z = v2.z;
				}
				else
				{
					minCorner.z = v2.z;
					maxCorner.z = v1.z;
				}
			}
			if constexpr (DIM >= 4)
			{
				if (v1.w <= v2.w)
				{
					minCorner.w = v1.w;
					maxCorner.w = v2.w;
				}
				else
				{
					minCorner.w = v2.w;
					maxCorner.w = v1.w;
				}
			}
			infinite = false;
			return *this;
		}

		inline AABB& set(const TT& x1, const TT& y1, const TT& x2, const TT& y2)
		{
			if (x1 <= x2)
			{
				minCorner.x = x1;
				maxCorner.x = x2;
			}
			else
			{
				minCorner.x = x2;
				maxCorner.x = x1;
			}
			if constexpr (DIM >= 2)
			{
				if (y1 <= y2)
				{
					minCorner.y = y1;
					maxCorner.y = y2;
				}
				else
				{
					minCorner.y = y2;
					maxCorner.y = y1;
				}
			}
		
			infinite = false;
			return *this;
		}
		inline AABB& set(const TT& x1, const TT& y1, const TT& z1, const TT& x2, const TT& y2, const TT& z2)
		{
			if (x1 <= x2)
			{
				minCorner.x = x1;
				maxCorner.x = x2;
			}
			else
			{
				minCorner.x = x2;
				maxCorner.x = x1;
			}
			if constexpr (DIM >= 2)
			{
				if (y1 <= y2)
				{
					minCorner.y = y1;
					maxCorner.y = y2;
				}
				else
				{
					minCorner.y = y2;
					maxCorner.y = y1;
				}
			}
			if constexpr (DIM >= 3)
			{
				if (z1 <= z2)
				{
					minCorner.z = z1;
					maxCorner.z = z2;
				}
				else
				{
					minCorner.z = z2;
					maxCorner.z = z1;
				}
			}
			
			infinite = false;
			return *this;
		}
		inline AABB& set(const TT& x1, const TT& y1, const TT& z1, const TT& w1, const TT& x2, const TT& y2, const TT& z2, const TT& w2)
		{
			if (x1 <= x2)
			{
				minCorner.x = x1;
				maxCorner.x = x2;
			}
			else
			{
				minCorner.x = x2;
				maxCorner.x = x1;
			}
			if constexpr (DIM >= 2)
			{
				if (y1 <= y2)
				{
					minCorner.y = y1;
					maxCorner.y = y2;
				}
				else
				{
					minCorner.y = y2;
					maxCorner.y = y1;
				}
			}
			if constexpr (DIM >= 3)
			{
				if (z1 <= z2)
				{
					minCorner.z = z1;
					maxCorner.z = z2;
				}
				else
				{
					minCorner.z = z2;
					maxCorner.z = z1;
				}
			}
			if constexpr (DIM >= 4)
			{
				if (w1 <= w2)
				{
					minCorner.w = w1;
					maxCorner.w = w2;
				}
				else
				{
					minCorner.w = w2;
					maxCorner.w = w1;
				}
			}

			infinite = false;
			return *this;
		}

		inline bool operator==(const AABB& aabb)
		{
			return (infinite == aabb.infinite) && (minCorner == aabb.minCorner) && (maxCorner == aabb.maxCorner);
		}

		inline bool operator<(const AABB& aabb)
		{
			return minCorner < aabb.minCorner;
		}

		inline AABB& merge(const Vec<TT, DIM>& v)
		{
			if (!infinite)
			{
				minCorner = minimum(minCorner,v);
				maxCorner = maximum(maxCorner,v);
			}
			return *this;
		}

		inline AABB& merge(const AABB& aabb)
		{
			if (!infinite)
			{
				if (!aabb.infinite)
				{
					minCorner = minimum(minCorner, aabb.minCorner);
					maxCorner = maximum(maxCorner, aabb.maxCorner);
				}
				else
				{
					infinite = true;
				}
			}
			return *this;
		}

		inline TT width() const
		{
			if (!infinite)
			{
				return (maxCorner.x - minCorner.x);
			}
			else
			{
				return 0;
			}
		}

		inline TT height() const
		{
			if (!infinite)
			{
				return (maxCorner.y - minCorner.y);
			}
			else
			{
				return 0;
			}
		}

		inline TT depth() const
		{
			if (!infinite)
			{
				return (maxCorner.z - minCorner.z);
			}
			else
			{
				return 0;
			}
		}

		inline Vec<TT, DIM> size() const
		{
			if (!infinite)
			{
				return (maxCorner - minCorner);
			}
			else
			{
				return kf::Vec<TT, DIM>::zero();
			}
		}

		inline Vec<TT, DIM> centre() const
		{
			if (!infinite)
			{
				return (maxCorner + minCorner) * 0.5;
			}
			else
			{
				return kf::Vec<TT, DIM>::zero();
			}
		}

		inline static AABB zero()
		{
			return AABB(0, 0, 0, 0, 0, 0);
		}

		//inline static AABB Infinite()
		//{
		//	AABB aabb;
		//	aabb.infinite = true;
		//	return aabb;
		//}

		inline operator std::string() const
		{
			std::stringstream ss;
			ss << "[" << minCorner << "," << maxCorner << "]";
			return ss.str();
		}


	};

	template <typename TT, int DIM>
	inline std::ostream& operator<<(std::ostream& o, const AABB<TT, DIM>& aabb)
	{
		o << "[" << aabb.minCorner << ", " << aabb.maxCorner<<"]";
		return o;
	}

	typedef AABB<float, 2>  AABB2f;
	typedef AABB<int, 2>    AABB2i;
	typedef AABB<double, 2> AABB2d;
	typedef AABB<float, 2>  AABB2;

	typedef AABB<float, 3>  AABB3f;
	typedef AABB<int, 3>    AABB3i;
	typedef AABB<double, 3> AABB3d;
	typedef AABB<float, 3>  AABB3;

	typedef AABB<float, 4>  AABB4f;
	typedef AABB<int, 4>    AABB4i;
	typedef AABB<double, 4> AABB4d;
	typedef AABB<float, 4>  AABB4;
}

#endif

