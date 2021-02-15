////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2020 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_VEC_HEADER
#define KF_VEC_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"
#include <ostream>

#if __has_include("sfml/system/vector2.hpp")
#include "sfml/system/vector2.hpp"
#endif
#if __has_include("sfml/graphics/color.hpp")
#include "sfml/graphics/color.hpp"
#endif

#if __has_include("box2d/b2_math.h")
#include "box2d/b2_math.h"
#endif

#if __has_include("imgui/imgui.h")
#include "imgui/imgui.h"
#endif

#pragma warning( disable : 4201)

namespace kf
{
#pragma region Macros
#define KFVECDIM(XX,YY,ZZ,WW) if constexpr (DIM == 1) return Vec<TT,DIM>(XX); if constexpr (DIM == 2) return Vec<TT,DIM>(XX,YY); if constexpr (DIM == 3) return Vec<TT,DIM>(XX,YY,ZZ); if constexpr (DIM == 4) return Vec<TT,DIM>(XX,YY,ZZ,WW);
#define KFVECDIMCMP(XX,YY,ZZ,WW) if constexpr (DIM == 1) return Vec<bool,DIM>(XX); if constexpr (DIM == 2) return Vec<bool,DIM>(XX,YY); if constexpr (DIM == 3) return Vec<bool,DIM>(XX,YY,ZZ); if constexpr (DIM == 4) return Vec<bool,DIM>(XX,YY,ZZ,WW);
#define KFVECDIMDIRECT(XX,YY,ZZ,WW) if constexpr (DIM >= 1) {XX;} if constexpr (DIM >= 2) {YY;} if constexpr (DIM >= 3) {ZZ;} if constexpr (DIM >= 4) {WW;}
#define KFVECDIMAGR(XX,YY,ZZ,WW,OP) if constexpr (DIM == 1) {XX;} if constexpr (DIM == 2) {XX OP YY;} if constexpr (DIM == 3) {XX OP YY OP ZZ;} if constexpr (DIM == 4) {XX OP YY OP ZZ OP WW;}
#define VTD Vec<TT,DIM>
#define VT2 Vec<TT,2>
#define VT3 Vec<TT,3>
#define VT4 Vec<TT,4>

#pragma endregion

	template<typename TT, int DIM>
	struct Vec
	{
		static_assert(sizeof(TT) == 0, "Invalid Vector dimensions. Only 2D, 3D and 4D vectors supported.");
	};

	//template<typename TT> struct VecRawXYZ { TT x, y, z; inline  operator VT3() const { return VT3(x, y, z); } };
	//template<typename TT> struct VecRawYXZ { TT y, x, z; inline  operator VT3() const { return VT3(x, y, z); } };
	//template<typename TT> struct VecRawXXX { TT x, _, __; inline  operator VT3() const { return VT3(x, x, x); } };
	////template<typename TT> struct VecRawXYZ { TT x, y, z; inline  operator VT3() const { return VT3(x, y, z); } };
	//template<typename TT> struct VecRawXY { TT x, y; inline  operator Vec<TT, 2>() const { return Vec<TT, 2>(x, y); } };
	//template<typename TT> struct VecRawYX { TT y, x; inline  operator Vec<TT, 2>() const { return Vec<TT, 2>(x, y); } };
	//template<typename TT> struct VecRawXX { TT x, _; inline  operator Vec<TT, 2>() const { return Vec<TT, 2>(x, y); } };
	//template<typename TT> struct VecRawYY { TT _, y; inline  operator Vec<TT, 2>() const { return Vec<TT, 2>(x, y); } };

#pragma region Dimension Specialisation
	template <typename TT> struct Vec<TT, 2>
	{
		union 
		{ 
			//TT c[2]; 
			struct { TT x, y; }; 
			struct { TT r, g; }; 
			struct { TT u, v; }; 
		};
		Vec() :                     x(0),    y(0)    {}
		Vec(TT a) :                 x(a),    y(a)    {}
		Vec(TT x_, TT y_) :         x(x_),   y(y_)   {}
		Vec(VT3 vec) :         x(vec.x),  y(vec.y)  {}
		Vec(VT4 vec) :         x(vec.x),  y(vec.y)  {}
		template <typename T2>
		Vec(Vec<T2,2> vec) : x(vec.x), y(vec.y) {}
		explicit Vec(const TT* p) : x(p[0]), y(p[1]) {}
		static Vec zero()  { return Vec(TT(0), TT(0)); }
		static Vec one()   { return Vec(TT(1), TT(1)); }
		static Vec unitX() { return Vec(TT(1), TT(0)); }
		static Vec unitY() { return Vec(TT(0), TT(1)); }

		//inline static const Vec one = { 1, 1 };
		enum Components
		{
			X = 0, R = 0, U = 0,
			Y = 1, G = 1, V = 1
		};
		
		// Operator[]
		inline TT& operator[](unsigned int index)
		{
			return (&x)[index];
		}

		// Operator[] const
		inline const TT& operator[](unsigned int index) const
		{
			return (&x)[index];
		}

		inline VT2& set(const TT* p)
		{
			x = p[0];
			y = p[1];
			return *this;
		}

		inline VT2& set(const TT& x_, const TT& y_)
		{
			x = x_;
			y = y_;
			return *this;
		}

		inline VT2& set(const VT2& xy_)
		{
			x = xy_.x;
			y = xy_.y;
			return *this;
		}

		inline VT2& set(const VT3& xyz_)
		{
			x = xyz_.x;
			y = xyz_.y;
			return *this;
		}

		inline VT2& set(const VT4& xyzw_)
		{
			x = xyzw_.x;
			y = xyzw_.y;
			return *this;
		}

		inline VT2& set(const TT& value)
		{
			x = value;
			return *this;
		}

		template <typename TT2>
		inline  operator VT2() const
		{
			return VT2(x, y);
		}
		
		inline operator std::string() const
		{
			std::stringstream ss;
			ss << "<" << x << "," << y << ">";
			return ss.str();
		}

		inline Vec<TT, 2>& operator=(const Vec& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}

		template <typename T2>
		inline Vec& operator=(const Vec<T2, 2>& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}

		inline Vec<TT, 2>(std::initializer_list<TT> list)
		{
			int m = list.size();
			if (m > 2)
				m = 2;
			for (int i = 0; i < m; ++i)
			{
				(&x)[i] = list.begin()[i];
			}
		}

		inline Vec<TT, 2>& operator=(std::initializer_list<TT> list)
		{
			int m = list.size();
			if (m > 2)
				m = 2;
			for (int i = 0; i < m; ++i)
			{
				(&x)[i] = list.begin()[i];
			}
			return *this;
		}
#pragma region Foreign Vectors
#ifdef SFML_VECTOR2_HPP
		inline Vec<TT, 2>(const sf::Vector2f& c) : x(c.x), y(c.y)
		{
		}

		inline Vec<TT, 2>(const sf::Vector2i& c) : x(c.x), y(c.y)
		{
		}

		inline Vec<TT, 2>(const sf::Vector2u& c) : x(c.x), y(c.y)
		{
		}

		inline operator sf::Vector2i() const
		{
			return sf::Vector2i(x, y);
		}

		inline operator sf::Vector2u() const
		{
			return sf::Vector2u(x, y);
		}

		inline operator sf::Vector2f() const
		{
			return sf::Vector2f(x, y);
		}

		inline Vec& operator=(const sf::Vector2i& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}
		inline Vec& operator=(const sf::Vector2f& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}
		inline Vec& operator=(const sf::Vector2u& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}
#endif
#ifdef B2_MATH_H
		inline Vec(const b2Vec2& c) : x(c.x), y(c.y)
		{
		}

		inline operator b2Vec2() const
		{
			return b2Vec2(x, y);
		}

		inline Vec& operator=(const b2Vec2& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}
#endif
#ifdef IMGUI_VERSION
		inline Vec(const ImVec2& c) : x(c.x), y(c.y)
		{
		}

		inline operator ImVec2() const
		{
			return ImVec2(x, y);
		}

		inline Vec& operator=(const ImVec2& vec)
		{
			x = vec.x;
			y = vec.y;
			return *this;
		}
#endif

#pragma endregion
	};

	template <typename TT> struct VT3
	{
		union 
		{ 
			//TT c[3]; 
			struct { TT x, y, z; }; 
			struct { TT r, g, b; }; 
			struct { TT u, v; }; 
			VT2 xy;
			VT2 rg;
			VT2 uv;
			struct { TT _; VT2 yz;};
			struct { TT _; VT2 gb;};
		};
		Vec() :                      x(0),     y(0),     z(0)     {}
		Vec(TT value) :                  x(value),     y(value),     z(value)     {}
		Vec(TT x_, TT y_, TT z_) :   x(x_),    y(y_),    z(z_)    {}
		Vec(VT2 xy_, TT z_) : x(xy_.x), y(xy_.y), z(z_)    {}
		Vec(TT x_, VT2 yz_) : x(x_),    y(yz_.x), z(yz_.y) {}
		Vec(VT4 vec) :          x(vec.x),   y(vec.y),   z(vec.z)   {}
		
		explicit Vec(const TT* p) :  x(p[0]),  y(p[1]),  z(p[2])  {}
		static Vec zero()  { return Vec(TT(0), TT(0), TT(0)); }
		static Vec one()   { return Vec(TT(1), TT(1), TT(1)); }
		static Vec unitX() { return Vec(TT(1), TT(0), TT(0)); }
		static Vec unitY() { return Vec(TT(0), TT(1), TT(0)); }
		static Vec unitZ() { return Vec(TT(0), TT(0), TT(1)); }

		enum Components
		{
			X = 0, R = 0, U = 0,
			Y = 1, G = 1, V = 1,
			Z = 2, B = 2
		};


		// Operator[]
		inline TT& operator[](unsigned int index)
		{
			return (&x)[index];
		}
		// Operator[]
		inline const TT& operator[](unsigned int index) const
		{
			return (&x)[index];
		}

		inline VT3& set(const TT* p)
		{
			x = p[0];
			y = p[1];
			z = p[2];
			return *this;
		}

		inline VT3& set(const TT& x_, const TT& y_, const TT& z_)
		{
			x = x_;
			y = y_;
			z = z_;
			return *this;
		}

		inline VT3& set(const TT& x_, const TT& y_)
		{
			x = x_;
			y = y_;
			return *this;
		}

		inline VT3& set(const VT2& xy_, const TT& z_)
		{
			x = xy_.x;
			y = xy_.y;
			z = z_;
			return *this;
		}

		inline VT3& set(const VT2& xy_)
		{
			x = xy_.x;
			y = xy_.y;
			return *this;
		}

		inline VT3& set(const TT& x_, const VT2& yz_)
		{
			x = x_;
			y = yz_.x;
			z = yz_.y;
			return *this;
		}

		inline VT3& set(const VT3& xyz_)
		{
			x = xyz_.x;
			y = xyz_.y;
			z = xyz_.z;
			return *this;
		}

		inline VT3& set(const VT4& xyzw_)
		{
			x = xyzw_.x;
			y = xyzw_.y;
			z = xyzw_.z;
			return *this;
		}

		inline VT3& set(const TT& value)
		{
			x = value;
			y = value;
			z = value;
			return *this;
		}
		
		template <typename TT2>
		inline  operator Vec<TT2, 3>() const
		{
			return Vec<TT2, 3>(x, y, z);
		}

		inline operator std::string() const
		{
			std::stringstream ss;
			ss << "<" << x << "," << y << "," << z << ">";
			return ss.str();
		}

		inline Vec<TT, 3>& operator=(const Vec& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			return *this;
		}

		template <typename T2>
		inline Vec<TT,3>& operator=(const Vec<T2, 3>& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			return *this;
		}

		inline Vec<TT, 3>(std::initializer_list<TT> list)
		{
			int m = list.size();
			if (m > 3)
				m = 3;
			for (int i = 0; i < m; ++i)
			{
				(&x)[i] = list.begin()[i];
			}
		}
		inline Vec<TT, 3>& operator=(std::initializer_list<TT> list)
		{
			int m = list.size();
			if (m > 3)
				m = 3;
			for (int i = 0; i < m; ++i)
			{
				(&x)[i] = list.begin()[i];
			}
			return *this;
		}
#ifdef SFML_COLOR_HPP
		inline Vec<TT,3>(const sf::Color& c) : r(c.r/255.0f), g(c.g / 255.0f), b(c.b / 255.0f)
		{
		}

		inline operator sf::Color() const
		{
			return sf::Color(kf::saturate(r) * 255, kf::saturate(g) * 255, kf::saturate(b) * 255);
		}

		inline Vec<TT, 3>& operator=(const sf::Color& vec)
		{
			r = vec.r/255.0f;
			g = vec.g/255.0f;
			b = vec.b/255.0f;
			return *this;
		}
#endif

#ifdef IMGUI_VERSION
		inline Vec<TT, 3>(const ImVec4& c) : x(c.x), y(c.y), z(c.z)
		{
		}

		inline operator ImVec4() const
		{
			return ImVec4(x, y, z, 0);
		}

		inline Vec<TT, 3>& operator=(const ImVec4& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			return *this;
		}
#endif
	};
	
	template <typename TT> struct VT4
	{
		union 
		{ 
			//TT c[4]; 
			struct { TT x, y, z, w; }; 
			struct { TT r, g, b, a; }; 
			struct { TT u, v; }; 
			VT2 xy;
			VT2 rg;
			VT2 uv;
			VT3 xyz;
			VT3 rgb;
			struct { TT _; VT2 yz; };
			struct { TT _; VT2 gb; };
			struct { TT _; TT __; VT2 zw; };
			struct { TT _; TT __; VT2 ba; };
			struct { TT _; VT3 yzw; };
			struct { TT _; VT3 gba; };
		};
		Vec() : x(0), y(0), z(0), w(0) {}
		Vec(TT value) : x(value), y(value), z(value), w(value) {}
		Vec(TT x_, TT y_, TT z_, TT w_) :     x(x_),     y(y_),     z(z_),     w(w_)     {}
		Vec(VT2 xy_, TT z_, TT w_) :   x(xy_.x),  y(xy_.y),  z(z_),     w(w_)     {}
		Vec(TT x_, VT2 yz_, TT w_) :   x(x_),     y(yz_.x),  z(yz_.y),  w(w_)     {}
		Vec(TT x_, TT y_, VT2 zw_) :   x(x_),     y(y_),     z(zw_.x),  w(zw_.y)  {}
		Vec(VT2 xy_, VT2 zw_) : x(xy_.x),  y(xy_.y),  z(zw_.x),  w(zw_.y)  {}
		Vec(VT3 xyz_, TT w_) :         x(xyz_.x), y(xyz_.y), z(xyz_.z), w(w_)     {}
		Vec(TT x_, VT3 yzw_) :         x(x_),     y(yzw_.x), z(yzw_.y), w(yzw_.z) {}
		explicit Vec(const TT* p) :           x(p[0]),   y(p[1]),   z(p[2]),   w(p[3])   {}
		static Vec zero()  { return Vec(TT(0), TT(0), TT(0), TT(0)); }
		static Vec one()   { return Vec(TT(1), TT(1), TT(1), TT(1)); }
		static Vec unitX() { return Vec(TT(1), TT(0), TT(0), TT(0)); }
		static Vec unitY() { return Vec(TT(0), TT(1), TT(0), TT(0)); }
		static Vec unitZ() { return Vec(TT(0), TT(0), TT(1), TT(0)); }
		static Vec unitW() { return Vec(TT(0), TT(0), TT(0), TT(1)); }

		enum Components
		{
			X = 0, R = 0, U = 0,
			Y = 1, G = 1, V = 1,
			Z = 2, B = 2,
			W = 3, A = 3
		};

		//VT4& operator=(const Vec& v)
		//{
		//	x = v.x;
		//	y = v.y;
		//	z = v.z;
		//	w = v.w;
		//	return *this;
		//}

		// Operator[]
		inline TT& operator[](unsigned int index)
		{
			return (&x)[index];
		}
		// Operator[]
		inline const TT& operator[](unsigned int index) const
		{
			return (&x)[index];
		}
		
		inline VT4& set(const TT* p)
		{
			x = p[0];
			y = p[1];
			z = p[2];
			w = p[3];
			return *this;
		}
		inline VT4& set(const TT& x_, const TT& y_, const TT& z_, const TT& w_)
		{
			x = x_;
			y = y_;
			z = z_;
			w = w_;
			return *this;
		}

		inline VT4& set(const TT& x_, const TT& y_, const TT& z_)
		{
			x = x_;
			y = y_;
			z = z_;
			return *this;
		}

		inline VT4& set(const TT& x_, const TT& y_)
		{
			x = x_;
			y = y_;
			return *this;
		}

		inline VT4& set(const VT2& xy_, const TT& z_, const TT& w_)
		{
			x = xy_.x;
			y = xy_.y;
			z = z_;
			w = w_;
			return *this;
		}
		inline VT4& set(const VT2& xy_, const TT& z_)
		{
			x = xy_.x;
			y = xy_.y;
			z = z_;
			return *this;
		}
		inline VT4& set(const VT2& xy_, const VT2& zw_)
		{
			x = xy_.x;
			y = xy_.y;
			z = zw_.x;
			w = zw_.y;
			return *this;
		}
		inline VT4& set(const TT& x_, const VT2& yz_, const TT& w_)
		{
			x = x_;
			y = yz_.x;
			z = yz_.y;
			w = w_;
			return *this;
		}
		inline VT4& set(const TT& x_, const VT2& yz_)
		{
			x = x_;
			y = yz_.x;
			z = yz_.y;
			return *this;
		}
		inline VT4& set(const TT& x_, const TT& y_, const VT2& zw_)
		{
			x = x_;
			y = y_;
			z = zw_.x;
			w = zw_.y;
			return *this;
		}
		inline VT4& set(const VT3& xyz_, const TT& w_)
		{
			x = xyz_.x;
			y = xyz_.y;
			z = xyz_.z;
			w = w_;
			return *this;
		}
		inline VT4& set(const VT3& xyz_)
		{
			x = xyz_.x;
			y = xyz_.y;
			z = xyz_.z;
			return *this;
		}
		inline VT4& set(const VT4& xyzw_)
		{
			x = xyzw_.x;
			y = xyzw_.y;
			z = xyzw_.z;
			w = xyzw_.w;
			return *this;
		}

		inline VT4& set(const TT& x_, const VT3& yzw_)
		{
			x = x_;
			y = yzw_.x;
			z = yzw_.y;
			w = yzw_.z;
			return *this;
		}
		inline VT4& set(const TT& value)
		{
			x = value;
			y = value;
			z = value;
			w = value;
			return *this;
		}

		template <typename TT2>
		inline  operator Vec<TT2, 4>() const
		{
			return Vec<TT2, 4>(x, y, z, w);
		}
		
		inline operator std::string() const
		{
			std::stringstream ss;
			ss << "<" << x << "," << y << "," << z << "," << w << ">";
			return ss.str();
		}
		inline Vec<TT,4>& operator=(const Vec<TT, 4>& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
			return *this;
		}
		template<typename T2>
		inline Vec<TT, 4>& operator=(const Vec<T2, 4>& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
			return *this;
		}

		inline Vec<TT, 4>(std::initializer_list<TT> list)
		{
			int m = list.size();
			if (m > 4)
				m = 4;
			for (int i = 0; i < m; ++i)
			{
				(&x)[i] = list.begin()[i];
			}
		}

		inline Vec<TT, 4>& operator=(std::initializer_list<TT> list)
		{
			int m = list.size();
			if (m > 4)
				m = 4;
			for (int i = 0; i < m; ++i)
			{
				(&x)[i] = list.begin()[i];
			}
			return *this;
		}

#ifdef SFML_COLOR_HPP
		inline Vec<TT,4>(const sf::Color& c) : r(c.r / 255.0f), g(c.g / 255.0f), b(c.b / 255.0f), a(c.a/255.0f)
		{
		}

		inline operator sf::Color() const
		{
			return sf::Color(kf::saturate(r) * 255, kf::saturate(g) * 255, kf::saturate(b) * 255, kf::saturate(a) * 255);
		}

		/*inline Vec<TT, 3>& operator=(const sf::Color& v)
		{
			r = v.r/255.0f;
			g = v.g/255.0f;
			b = v.b/255.0f;
			return *this;
		}*/
#endif
#ifdef IMGUI_VERSION
		inline Vec<TT, 4>(const ImVec4& c) : x(c.x), y(c.y), z(c.z), w(c.w)
		{
		}

		inline operator ImVec4() const
		{
			return ImVec4(x,y,z,w);
		}

		inline Vec<TT, 4>& operator=(const ImVec4& vec)
		{
			x = vec.x;
			y = vec.y;
			z = vec.z;
			w = vec.w;
			return *this;
		}

#endif
	};
#pragma endregion

	


#pragma region Arithmetic Operators
	// Operator+
	template <typename TT, int DIM>
	inline VTD operator+(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator+(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x + b, a.y + b, a.z + b, a.w + b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator+(const TT2& a, const VTD& b)
	{
		KFVECDIM(a + b.x, a + b.y, a + b.z, a + b.w);
	}

	// Operator-
	template <typename TT, int DIM>
	inline VTD operator-(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator-(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x - b, a.y - b, a.z - b, a.w - b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator-(const TT2& a, const VTD& b)
	{
		KFVECDIM(a - b.x, a - b.y, a - b.z, a - b.w);
	}

	// Operator*
	template <typename TT, int DIM>
	inline VTD operator*(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator*(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x * b, a.y * b, a.z * b, a.w * b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator*(const TT2& a, const VTD& b)
	{
		KFVECDIM(a * b.x, a * b.y, a * b.z, a * b.w);
	}

	// Operator/
	template <typename TT, int DIM>
	inline VTD operator/(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator/(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x / b, a.y / b, a.z / b, a.w / b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator/(const TT2& a, const VTD& b)
	{
		KFVECDIM(a / b.x, a / b.y, a / b.z, a / b.w);
	}

	// Operator%
	template <typename TT, int DIM>
	inline VTD operator%(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator%(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x % b, a.y % b, a.z % b, a.w % b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator%(const TT2& a, const VTD& b)
	{
		KFVECDIM(a % b.x, a % b.y, a % b.z, a % b.w);
	}

	// Operator-
	template <typename TT, int DIM>
	inline VTD operator-(const VTD& a)
	{
		KFVECDIM(-a.x, -a.y, -a.z, -a.w);
	}

#pragma endregion

#pragma region Binary Operators
	// Operator&
	template <typename TT, int DIM>
	inline VTD operator&(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x & b.x, a.y & b.y, a.z & b.z, a.w & b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator&(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x & b, a.y & b, a.z & b, a.w & b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator&(const TT2& a, const VTD& b)
	{
		KFVECDIM(a & b.x, a & b.y, a & b.z, a & b.w);
	}

	// Operator|
	template <typename TT, int DIM>
	inline VTD operator|(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x | b.x, a.y | b.y, a.z | b.z, a.w | b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator|(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x | b, a.y | b, a.z | b, a.w | b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator|(const TT2& a, const VTD& b)
	{
		KFVECDIM(a | b.x, a | b.y, a | b.z, a | b.w);
	}

	// Operator^
	template <typename TT, int DIM>
	inline VTD operator^(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x ^ b.x, a.y ^ b.y, a.z ^ b.z, a.w ^ b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator^(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x ^ b, a.y ^ b, a.z ^ b, a.w ^ b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator^(const TT2& a, const VTD& b)
	{
		KFVECDIM(a ^ b.x, a ^ b.y, a ^ b.z, a ^ b.w);
	}

	// Operator<<
	template <typename TT, int DIM>
	inline VTD operator<<(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x << b.x, a.y << b.y, a.z << b.z, a.w << b.w);
	}

	template <typename TT, int DIM>
	inline VTD operator<<(const VTD& a, int b)
	{
		KFVECDIM(a.x << b, a.y << b, a.z << b, a.w << b);
	}

	template <typename TT, int DIM>
	inline VTD operator<<(int a, const VTD& b)
	{
		KFVECDIM(a << b.x, a << b.y, a << b.z, a << b.w);
	}

	// Operator>>
	template <typename TT, int DIM>
	inline VTD operator>>(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x >> b.x, a.y >> b.y, a.z >> b.z, a.w >> b.w);
	}

	template <typename TT, int DIM>
	inline VTD operator>>(const VTD& a, int b)
	{
		KFVECDIM(a.x >> b, a.y >> b, a.z >> b, a.w >> b);
	}

	template <typename TT, int DIM>
	inline VTD operator>>(int a, const VTD& b)
	{
		KFVECDIM(a >> b.x, a >> b.y, a >> b.z, a >> b.w);
	}

	// Operator~
	template <typename TT, int DIM>
	inline Vec<bool, DIM> operator~(const VTD& a)
	{
		KFVECDIMCMP(~a.x, ~a.y, ~a.z, ~a.w);
		return a;
	}

#pragma endregion

#pragma region Logical Operators
	// Operator&&
	template <typename TT, int DIM>
	inline VTD operator&&(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x && b.x, a.y && b.y, a.z && b.z, a.w && b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator&&(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x && b, a.y && b, a.z && b, a.w && b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator&&(const TT2& a, const VTD& b)
	{
		KFVECDIM(a && b.x, a && b.y, a && b.z, a && b.w);
	}

	// Operator||
	template <typename TT, int DIM>
	inline VTD operator||(const VTD& a, const VTD& b)
	{
		KFVECDIM(a.x || b.x, a.y || b.y, a.z || b.z, a.w || b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator||(const VTD& a, const TT2& b)
	{
		KFVECDIM(a.x || b, a.y || b, a.z || b, a.w || b);
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD operator||(const TT2& a, const VTD& b)
	{
		KFVECDIM(a || b.x, a || b.y, a || b.z, a || b.w);
	}

	// Operator!
	template <typename TT, int DIM>
	inline Vec<bool, DIM> operator!(const VTD& a)
	{
		KFVECDIMCMP(!a.x, !a.y, !a.z, !a.w);
		//return a;
	}

#pragma endregion

#pragma region Comparison Operators
	// Operator<
	template <typename TT, int DIM>
	inline Vec<bool, DIM> operator<(const VTD& a, const VTD& b)
	{
		KFVECDIMCMP(a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator<(const VTD& a, const TT2& b)
	{
		KFVECDIMCMP(a.x < b, a.y < b, a.z < b, a.w < b);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator<(const TT2& a, const VTD& b)
	{
		KFVECDIMCMP(a < b.x, a < b.y, a < b.z, a < b.w);
	}

	// Operator>
	template <typename TT, int DIM>
	inline Vec<bool, DIM> operator>(const VTD& a, const VTD& b)
	{
		KFVECDIMCMP(a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator>(const VTD& a, const TT2& b)
	{
		KFVECDIMCMP(a.x > b, a.y > b, a.z > b, a.w > b);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator>(const TT2& a, const VTD& b)
	{
		KFVECDIMCMP(a > b.x, a > b.y, a > b.z, a > b.w);
	}

	// Operator==
	template <typename TT, int DIM>
	inline Vec<bool, DIM> operator==(const VTD& a, const VTD& b)
	{
		KFVECDIMCMP(a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator==(const VTD& a, const TT2& b)
	{
		KFVECDIMCMP(a.x == b, a.y == b, a.z == b, a.w == b);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator==(const TT2& a, const VTD& b)
	{
		KFVECDIMCMP(a == b.x, a == b.y, a == b.z, a == b.w);
	}

	// Operator!=
	template <typename TT, int DIM>
	inline Vec<bool, DIM> operator!=(const VTD& a, const VTD& b)
	{
		KFVECDIMCMP(a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator!=(const VTD& a, const TT2& b)
	{
		KFVECDIMCMP(a.x != b, a.y != b, a.z != b, a.w != b);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator!=(const TT2& a, const VTD& b)
	{
		KFVECDIMCMP(a != b.x, a != b.y, a != b.z, a != b.w);
	}

	// Operator<=
	template <typename TT, int DIM>
	inline Vec<bool, DIM> operator<=(const VTD& a, const VTD& b)
	{
		KFVECDIMCMP(a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator<=(const VTD& a, const TT2& b)
	{
		KFVECDIMCMP(a.x <= b, a.y <= b, a.z <= b, a.w <= b);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator<=(const TT2& a, const VTD& b)
	{
		KFVECDIMCMP(a <= b.x, a <= b.y, a <= b.z, a <= b.w);
	}

	// Operator>=
	template <typename TT, int DIM>
	inline Vec<bool, DIM> operator>=(const VTD& a, const VTD& b)
	{
		KFVECDIMCMP(a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator>=(const VTD& a, const TT2& b)
	{
		KFVECDIMCMP(a.x >= b, a.y >= b, a.z >= b, a.w >= b);
	}

	template <typename TT, int DIM, typename TT2>
	inline Vec<bool, DIM> operator>=(const TT2& a, const VTD& b)
	{
		KFVECDIMCMP(a >= b.x, a >= b.y, a >= b.z, a >= b.w);
	}

	template <typename TT, int DIM>
	inline bool approx(const VTD& a, const VTD& b, const TT& tolerance)
	{
		bool nea = true;
		if constexpr (DIM >= 1)
			nea = nea && std::abs(a.x - b.x) <= tolerance;
		if constexpr (DIM >= 2)
			nea = nea && std::abs(a.y - b.y) <= tolerance;
		if constexpr (DIM >= 3)
			nea = nea && std::abs(a.z - b.z) <= tolerance;
		if constexpr (DIM >= 4)
			nea = nea && std::abs(a.w - b.w) <= tolerance;
		return nea;
	}

	template <typename TT, int DIM>
	inline bool approx(const VTD& a, const VTD& b, const VTD& tolerance)
	{
		bool nea = true;
		if constexpr (DIM >= 1)
			nea = nea && std::abs(a.x - b.x) <= tolerance.x;
		if constexpr (DIM >= 2)
			nea = nea && std::abs(a.y - b.y) <= tolerance.y;
		if constexpr (DIM >= 3)
			nea = nea && std::abs(a.z - b.z) <= tolerance.z;
		if constexpr (DIM >= 4)
			nea = nea && std::abs(a.w - b.w) <= tolerance.w;
		return nea;
	}

	template <typename TT, int DIM>
	inline VTD minimum(const VTD& a, const VTD& b)
	{
		KFVECDIM(kf::minimum(a.x, b.x), kf::minimum(a.y, b.y), kf::minimum(a.z, b.z), kf::minimum(a.w, b.w));
	}

	template <typename TT, int DIM>
	inline VTD maximum(const VTD& a, const VTD& b)
	{
		KFVECDIM(kf::maximum(a.x, b.x), kf::maximum(a.y, b.y), kf::maximum(a.z, b.z), kf::maximum(a.w, b.w));
	}

	template <typename TT, int DIM>
	inline void reorder(const VTD& src1, const VTD& src2, VTD& dst1, VTD& dst2)
	{

		if (src1.x <= src2.x)
		{
			dst1.x = src1.x;
			dst2.x = src2.x;
		}
		else
		{
			dst1.x = src2.x;
			dst2.x = src1.x;
		}
		if constexpr (DIM >= 2)
		{
			if (src1.y <= src2.y)
			{
				dst1.y = src1.y;
				dst2.y = src2.y;
			}
			else
			{
				dst1.y = src2.y;
				dst2.y = src1.y;
			}
		}
		if constexpr (DIM >= 3)
		{
			if (src1.z <= src2.z)
			{
				dst1.z = src1.z;
				dst2.z = src2.z;
			}
			else
			{
				dst1.z = src2.z;
				dst2.z = src1.z;
			}
		}
		if constexpr (DIM >= 4)
		{
			if (src1.w <= src2.w)
			{
				dst1.w = src1.w;
				dst2.w = src2.w;
			}
			else
			{
				dst1.w = src2.w;
				dst2.w = src1.w;
			}
		}
	}

#pragma endregion

#pragma region Compound Operators
	// Operator+=
	template <typename TT, int DIM>
	inline VTD& operator+=(VTD& a, const VTD& b)
	{
		KFVECDIMDIRECT(a.x += b.x, a.y += b.y, a.z += b.z, a.w += b.w);
		return a;
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD& operator+=(VTD& a, const TT2& b)
	{
		KFVECDIMDIRECT(a.x += b, a.y += b, a.z += b, a.w += b);
		return a;
	}

	// Operator-=
	template <typename TT, int DIM>
	inline VTD& operator-=(VTD& a, const VTD& b)
	{
		KFVECDIMDIRECT(a.x -= b.x, a.y -= b.y, a.z -= b.z, a.w -= b.w);
		return a;
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD& operator-=(VTD& a, const TT2& b)
	{
		KFVECDIMDIRECT(a.x -= b, a.y -= b, a.z -= b, a.w -= b);
		return a;
	}

	// Operator*=
	template <typename TT, int DIM>
	inline VTD& operator*=(VTD& a, const VTD& b)
	{
		KFVECDIMDIRECT(a.x *= b.x, a.y *= b.y, a.z *= b.z, a.w *= b.w);
		return a;
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD& operator*=(VTD& a, const TT2& b)
	{
		KFVECDIMDIRECT(a.x *= b, a.y *= b, a.z *= b, a.w *= b);
		return a;
	}

	// Operator/=
	template <typename TT, int DIM, typename TT2>
	inline VTD& operator/=(VTD& a, const Vec<TT2,2>& b)
	{
		KFVECDIMDIRECT(a.x /= b.x, a.y /= b.y, a.z /= b.z, a.w /= b.w);
		return a;
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD& operator/=(VTD& a, const TT2& b)
	{
		KFVECDIMDIRECT(a.x /= b, a.y /= b, a.z /= b, a.w /= b);
		return a;
	}

	// Operator%=
	template <typename TT, int DIM>
	inline VTD& operator%=(VTD& a, const VTD& b)
	{
		KFVECDIMDIRECT(a.x %= b.x, a.y %= b.y, a.z %= b.z, a.w %= b.w);
		return a;
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD& operator%=(VTD& a, const TT2& b)
	{
		KFVECDIMDIRECT(a.x %= b, a.y %= b, a.z %= b, a.w %= b);
		return a;
	}

	// Operator&=
	template <typename TT, int DIM>
	inline VTD& operator&=(VTD& a, const VTD& b)
	{
		KFVECDIMDIRECT(a.x &= b.x, a.y &= b.y, a.z &= b.z, a.w &= b.w);
		return a;
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD& operator&=(VTD& a, const TT2& b)
	{
		KFVECDIMDIRECT(a.x &= b, a.y &= b, a.z &= b, a.w &= b);
		return a;
	}

	// Operator|=
	template <typename TT, int DIM>
	inline VTD& operator|=(VTD& a, const VTD& b)
	{
		KFVECDIMDIRECT(a.x |= b.x, a.y |= b.y, a.z |= b.z, a.w |= b.w);
		return a;
	}

	template <typename TT, int DIM, typename TT2>
	inline VTD& operator|=(VTD& a, const TT2& b)
	{
		KFVECDIMDIRECT(a.x |= b, a.y |= b, a.z |= b, a.w |= b);
		return a;
	}
#pragma endregion

#pragma region Aggregate Functions
	// Any
	template <typename TT, int DIM>
	inline bool any(const VTD& a)
	{
		KFVECDIMAGR(return a.x, a.y, a.z, a.w, || );
	}

	// All
	template <typename TT, int DIM>
	inline bool all(const VTD& a)
	{
		KFVECDIMAGR(return a.x, a.y, a.z, a.w, &&);
	}

	// None
	template <typename TT, int DIM>
	inline bool none(const VTD& a)
	{
		KFVECDIMAGR(return !a.x, !a.y, !a.z, !a.w, &&);
	}

	// Sum
	template <typename TT, int DIM>
	inline TT sum(const VTD& a)
	{
		KFVECDIMAGR(return a.x, a.y, a.z, a.w, +);
	}

	// Average
	template <typename TT, int DIM>
	inline TT average(const VTD& a)
	{
		if constexpr (DIM == 1) return a.x; 
		if constexpr (DIM == 2) return (a.x + a.y) / TT(2);
		if constexpr (DIM == 3) return (a.x + a.y + a.z) / TT(3);
		if constexpr (DIM == 4) return (a.x + a.y + a.z + a.w) / TT(4);
	}

	// Minimal component
	template <typename TT, int DIM>
	inline TT minimum(const VTD& a)
	{
		if constexpr (DIM == 2) return kf::minimum(a.x, a.y);
		if constexpr (DIM == 3) return kf::minimum(kf::minimum(a.x, a.y), a.z);
		if constexpr (DIM == 4) return kf::minimum(kf::minimum(kf::minimum(a.x, a.y), a.z), a.w);
		return TT(0);
	}

	// Maximal component
	template <typename TT, int DIM>
	inline TT maximum(const VTD& a)
	{
		if constexpr (DIM == 2) return kf::maximum(a.x, a.y);
		if constexpr (DIM == 3) return kf::maximum(kf::maximum(a.x, a.y), a.z);
		if constexpr (DIM == 4) return kf::maximum(kf::maximum(kf::maximum(a.x, a.y), a.z), a.w);
		return TT(0);
	}

#pragma endregion

#pragma region Trig Functions
	// sin
	template <typename TT, int DIM>
	inline VTD sin(const VTD& a)
	{
		KFVECDIM(std::sin(a.x), std::sin(a.y), std::sin(a.z), std::sin(a.w));
	}

	// cos
	template <typename TT, int DIM>
	inline VTD cos(const VTD& a)
	{
		KFVECDIM(std::cos(a.x), std::cos(a.y), std::cos(a.z), std::cos(a.w));
	}

	// tan
	template <typename TT, int DIM>
	inline VTD tan(const VTD& a)
	{
		KFVECDIM(std::tan(a.x), std::tan(a.y), std::tan(a.z), std::tan(a.w));
	}

	// acos
	template <typename TT, int DIM>
	inline VTD acos(const VTD& a)
	{
		KFVECDIM(std::acos(a.x), std::acos(a.y), std::acos(a.z), std::acos(a.w));
	}

	// asin
	template <typename TT, int DIM>
	inline VTD asin(const VTD& a)
	{
		KFVECDIM(std::asin(a.x), std::asin(a.y), std::asin(a.z), std::asin(a.w));
	}

	// atan
	template <typename TT, int DIM>
	inline VTD atan(const VTD& a)
	{
		KFVECDIM(std::atan(a.x), std::atan(a.y), std::atan(a.z), std::atan(a.w));
	}
#pragma endregion

#pragma region Arithmetic Functions
	// sqrt
	template <typename TT, int DIM>
	inline VTD sqrt(const VTD& a)
	{
		KFVECDIM(std::sqrt(a.x), std::sqrt(a.y), std::sqrt(a.z), std::sqrt(a.w));
	}

	// log
	template <typename TT, int DIM>
	inline VTD log(const VTD& a)
	{
		KFVECDIM(std::log(a.x), std::log(a.y), std::log(a.z), std::log(a.w));
	}

	// pow
	template <typename TT, int DIM>
	inline VTD pow(const VTD& a, const VTD& b)
	{
		KFVECDIM(std::pow(a.x, b.x), std::pow(a.y, b.y), std::pow(a.z, b.z), std::pow(a.w, b.w));
	}

	// pow
	template <typename TT, int DIM>
	inline VTD pow(const VTD& a, const TT& b)
	{
		KFVECDIM(std::pow(a.x, b), std::pow(a.y, b), std::pow(a.z, b), std::pow(a.w, b));
	}

	// pow
	template <typename TT, int DIM>
	inline VTD pow(const TT& a, const VTD& b)
	{
		KFVECDIM(std::pow(a, b.x), std::pow(a, b.y), std::pow(a, b.z), std::pow(a, b.w));
	}

	// exp
	template <typename TT, int DIM>
	inline VTD exp(const VTD& a)
	{
		KFVECDIM(std::exp(a.x), std::exp(a.y), std::exp(a.z), std::exp(a.w));
	}

	// abs
	template <typename TT, int DIM>
	inline VTD abs(const VTD& a)
	{
		KFVECDIM(std::abs(a.x), std::abs(a.y), std::abs(a.z), std::abs(a.w));
	}

	// sign
	template <typename TT, int DIM>
	inline VTD sign(const VTD& a)
	{
		KFVECDIM(kf::sign(a.x), kf::sign(a.y), kf::sign(a.z), kf::sign(a.w));
	}

	// Get the fractional part
	template <typename TT, int DIM>
	inline VTD frac(const VTD& a)
	{
		TT temp;
		KFVECDIM(std::modf(a.x, &temp), std::modf(a.y, &temp), std::modf(a.z, &temp), std::modf(a.w, &temp));
	}

	// Get the integer part
	template <typename TT, int DIM>
	inline VTD trunc(const VTD& a)
	{
		VTD result;
		KFVECDIMDIRECT(std::modf(a.x, &result.x), std::modf(a.y, &result.y), std::modf(a.z, &result.z), std::modf(a.w, &result.w));
	}
#pragma endregion

#pragma region Linear Functions
	// distance
	template <typename TT, int DIM>
	inline TT distance(const VTD& a, const VTD& b)
	{
		return length(a - b);
	}

	// reflect
	template <typename TT, int DIM>
	inline VTD reflect(const VTD& a, const VTD& b)
	{
		return (TT)2.0 * b * dot(a, b) - a;
	}

	// Stretch vector to specified length
	template <typename TT, int DIM, typename TT2>
	inline VTD stretch(const VTD& a, const TT2& b)
	{
		TT len = length(a) / b;
		if (len == 0)
			return VTD();
		len = 1 / len;
		return a * VTD(len);
	}

	// Dot product
	template <typename TT, int DIM>
	inline TT dot(const VTD& a, const VTD& b)
	{
		if constexpr (DIM == 1) return (a.x * b.x);
		if constexpr (DIM == 2) return (a.x * b.x + a.y * b.y);
		if constexpr (DIM == 3) return (a.x * b.x + a.y * b.y + a.z * b.z);
		if constexpr (DIM == 4) return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
//		return 0;
	}

	// ndot product
	template <typename TT, int DIM>
	inline TT ndot(const VTD& a, const VTD& b)
	{
		if constexpr (DIM == 1) return (a.x * b.x);
		if constexpr (DIM == 2) return (a.x * b.x - a.y * b.y);
		if constexpr (DIM == 3) return (a.x * b.x - a.y * b.y - a.z * b.z);
		if constexpr (DIM == 4) return (a.x * b.x - a.y * b.y - a.z * b.z - a.w * b.w);
		return 0;
	}

	// Cross product
	template <typename TT>
	inline VT3 cross(const VT3& a, const VT3& b)
	{
		return VT3(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x);
	}

	// Length
	template <typename TT, int DIM>
	inline TT length(const VTD& a)
	{
		return sqrt(dot(a, a));
	}

	// LengthSquared
	template <typename TT, int DIM>
	inline TT lengthSquared(const VTD& a)
	{
		return dot(a, a);
	}

	// Normalise
	template <typename TT, int DIM>
	inline VTD normalise(const VTD& a)
	{
		TT len = length(a);
		if (len != 0)
		{
			return a / len;
		}
		return VTD(TT(0));
	}

	// moveTo
	template <typename TT, int DIM>
	inline VTD moveTo(const VTD& a, const VTD& b, TT step)
	{
		VTD delta = b - a;
		if (lengthSquared(delta) <= step*step)
		{
			return b;
		}
		return a + normalise(delta) * step;
	}

	template <typename TT, int DIM>
	inline TT angle(const VTD& a, const VTD& b)
	{
		TT d = dot(normalise(a), normalise(b));
		d = kf::clamp(d, TT(-1), TT(1));
		return std::acos(d);
	}

	template <typename TT, typename TT2>
	inline VT3 rotate(const VT3& a, const VT3& b, TT2 angle)
	{
		VT3 k = normalise(b);
		return a * std::cos(angle) + cross(k, a) * std::sin(angle) + k * dot(a, k) * (1 - std::cos(angle));
	}

	template <typename TT, typename TT2>
	inline VT2 rotate(const VT2& a, TT2 angle)
	{
		float c = std::cos(angle);
		float s = std::sin(angle);
		return VT2(c * a.x - s * a.y, s * a.x + c * a.y);
	}

	template <typename TT>
	inline VT2 perpCW(const VT2& a)
	{
		return VT2(a.y, -a.x);
	}

	template <typename TT>
	inline VT2 perpCCW(const VT2& a)
	{
		return VT2(-a.y, a.x);
	}

	template <typename TT>
	inline VT3 perpCWX(const VT3& a)
	{
		return VT3(a.x, a.y, -a.z);
	}

	template <typename TT>
	inline VT3 perpCCWX(const VT3& a)
	{
		return VT3(a.x, -a.y, a.z);
	}

	template <typename TT>
	inline VT3 perpCWY(const VT3& a)
	{
		return VT3(a.z, a.y, -a.x);
	}

	template <typename TT>
	inline VT3 perpCCWY(const VT3& a)
	{
		return VT3(-a.z, a.y, a.x);
	}

	template <typename TT>
	inline VT3 perpCWZ(const VT3& a)
	{
		return VT3(a.y, -a.x, a.z);
	}

	template <typename TT>
	inline VT3 perpCCWZ(const VT3& a)
	{
		return VT3(-a.y, a.x, a.z);
	}

	//template <typename TT, typename TT2>
	//inline VT3 rotateX(const Vec<TT, 2>& a, TT2 angle)
	//{
	//	float c = cos(angle);
	//	float s = sin(angle);
	//	return Vec<TT, 2>(c * a.x - s * a.y, s * a.x + c * a.y);
	//}


#pragma endregion

#pragma region Predicates
	//orthogonal, opposite, colinear
	template <typename TT, int DIM>
	inline bool isColinear(const VTD& a, const VTD& b, TT epsilon = 0.0001)
	{
		TT d = dot(normalise(a), normalise(b));
		return d >= 1.0 - epsilon;
	}

	template <typename TT, int DIM>
	inline bool isOpposite(const VTD& a, const VTD& b, TT epsilon = 0.0001)
	{
		TT d = dot(normalise(a), normalise(b));
		return d <= -1.0 + epsilon;
	}

	template <typename TT, int DIM>
	inline bool isOrthogonal(const VTD& a, const VTD& b, TT epsilon = 0.0001)
	{
		TT d = dot(normalise(a), normalise(b));
		return std::abs(d) < epsilon;
	}

	template <typename TT, int DIM>
	inline bool isLonger(const VTD& a, TT len)
	{
		return dot(a, a) > len * len;
	}

	template <typename TT, int DIM>
	inline bool isShorter(const VTD& a, TT len)
	{
		return dot(a, a) < len * len;
	}
#pragma endregion

#pragma region IO
	template <typename TT, int DIM>
	inline std::ostream &operator<<(std::ostream &o, const VTD& a)
	{
		o << "<" << a.x << ", " << a.y;
		if constexpr (DIM >= 3) o << ", " << a.z;
		if constexpr (DIM >= 4) o << ", " << a.w;
		o << ">";
		return o;
	}
#pragma endregion

#pragma region Constraint Functions
	template <typename TT, int DIM, typename TT2>
	inline VTD clamp(const VTD& a, const TT2& b, const TT2& c)
	{
		return maximum(minimum(a, VTD(c)), VTD(b));
	}

	template <typename TT, int DIM>
	inline VTD saturate(const VTD& a)
	{
		return maximum(minimum(a, VTD::one()), VTD::zero());
	}
#pragma endregion

#pragma region Component Functions
	template <typename TT, int DIM>
	inline VT2 swizzle(const VTD& a, int c1, int c2)
	{
		return VT2((&a.x)[c1], (&a.x)[c2]);
	}

	template <typename TT, int DIM>
	inline VT3 swizzle(const VTD& a, int c1, int c2, int c3)
	{
		return VT3((&a.x)[c1], (&a.x)[c2], (&a.x)[c3]);
	}

	template <typename TT, int DIM>
	inline VT4 swizzle(const VTD& a, int c1, int c2, int c3, int c4)
	{
		return VT4((&a.x)[c1], (&a.x)[c2], (&a.x)[c3], (&a.x)[c4]);
	}

	template <typename TT, int DIM>
	inline unsigned int dominantAxis(const VTD& a)
	{
		VTD ab = abs(a);
		if constexpr (DIM == 2)
		{
			if (ab.y > ab.x)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		if constexpr (DIM == 3)
		{
			if (ab.y > ab.x)
			{
				if (ab.z > ab.y)
					return 2;
				else
					return 1;
			}
			else
			{
				if (ab.z > ab.x)
					return 2;
				else
					return 0;
			}
		}
		if constexpr (DIM == 4)
		{
			if (ab.y > ab.x)
			{
				if (ab.z > ab.y)
				{
					if (ab.w > ab.z)
						return 3;
					else
						return 2;
				}
				else
				{
					if (ab.w > ab.y)
						return 3;
					else
						return 1;
				}
			}
			else
			{
				if (ab.z > ab.x)
				{
					if (ab.w > ab.z)
						return 3;
					else
						return 2;
				}
				else
				{
					if (ab.w > ab.x)
						return 3;
					else
						return 0;
				}
			}
		}
		return 0;
	}

#pragma endregion

#pragma region Colour Functions
	
	// Convert linear to SRGB
	template <typename TT, int DIM>
	inline VTD toSRGB(const VTD& a)
	{
		VTD result;
		if constexpr (DIM >= 1)
		{
			if (a.r <= (TT)0.0031308)
				result.r = a.r * (TT)12.92;
			else
				result.r = (TT)(1.055 * ::pow(a.r, 1.0 / 2.4) - 0.055);
		}
		if constexpr (DIM >= 2)
		{
			if (a.g <= (TT)0.0031308)
				result.g = a.g * (TT)12.92;
			else
				result.g = (TT)(1.055 * ::pow(a.g, 1.0 / 2.4) - 0.055);
		}
		if constexpr (DIM >= 3)
		{
			if (a.b <= (TT)0.0031308)
				result.b = a.b * (TT)12.92;
			else
				result.b = (TT)(1.055 * ::pow(a.b, 1.0 / 2.4) - 0.055);
		}
		if constexpr (DIM >= 4)
		{
			result.a = a.a;
		}

		return result;
	}

	// Convert SRGB to linear
	template <typename TT, int DIM>
	inline VTD toLinear(const VTD& a)
	{
		VTD result;
		if constexpr (DIM >= 1)
		{
			if (a.r <= (TT)0.04045)
				result.r = a.r / (TT)12.92;
			else
				result.r = (TT)::pow((a.r + 0.055) / 1.055, 2.4);
		}
		if constexpr (DIM >= 2)
		{
			if (a.g <= (TT)0.04045)
				result.g = a.g / (TT)12.92;
			else
				result.g = (TT)::pow((a.g + 0.055) / 1.055, 2.4);
		}
		if constexpr (DIM >= 3)
		{
			if (a.b <= (TT)0.04045)
				result.b = a.b / (TT)12.92;
			else
				result.b = (TT)::pow((a.b + 0.055) / 1.055, 2.4);
		}
		if constexpr (DIM >= 4)
		{
			result.a = a.a;
		}

		return result;
	}
#pragma endregion


	// Todo:
	// -trig (cos, sin, tan)
	// rotate
	// -stretch (make length)
	// -cross
	// -sign
	// -abs
	// -min
	// -max
	// -pow, 
	// -exp, 
	// -sqrt, 
	// -log
	// -zero, one, unit
	// -srgb
	// -distance
	// comma
	// assignment, set
	// constructors
	// -swizzle
	// -reflect
	// dominantAxis
	// nonDominantAxis
	// -saturate
	// -clamp
	// -length squared
	// -moveto
	// rotateto
	// up
	// right
	// angle
	// perp
	// round, ceil, floor
	// swap
	// -negative
	// narrowing
	// -operator[]
	// bool operator== and operator!=
	// -unary +
	// parallel, orthogonal, opposite, colinear
	// hsv, hsb



#pragma region Typedefs
	typedef Vec<float,  2> Vec2;
	typedef Vec<float,  2> Vec2f;
	typedef Vec<double, 2> Vec2d;
	typedef Vec<int,    2> Vec2i;
	typedef Vec<unsigned int, 2> Vec2u;
	typedef Vec<bool,   2> Vec2b;
	typedef Vec<float, 2> Vector2;
	typedef Vec<float, 2> Vector2f;
	typedef Vec<double, 2> Vector2d;
	typedef Vec<int, 2> Vector2i;
	typedef Vec<unsigned int, 2> Vector2u;
	typedef Vec<bool, 2> Vector2b;

	typedef Vec<float,  3> Vec3;
	typedef Vec<float,  3> Vec3f;
	typedef Vec<double, 3> Vec3d;
	typedef Vec<int,    3> Vec3i;
	typedef Vec<unsigned int, 2> Vec3u;
	typedef Vec<bool,   3> Vec3b;

	typedef Vec<float,  4> Vec4;
	typedef Vec<float,  4> Vec4f;
	typedef Vec<double, 4> Vec4d;
	typedef Vec<int,    4> Vec4i;
	typedef Vec<unsigned int, 2> Vec4u;
	typedef Vec<bool,   4> Vec4b;

	typedef Vec<float,  3> RGBf;
	typedef Vec<float,  4> RGBAf;
#pragma endregion
#pragma region Macros
#undef VTD
#undef VT2
#undef VT3
#undef VT4
#pragma endregion
}

#endif

