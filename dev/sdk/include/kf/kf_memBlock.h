////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_MEMORY_BLOCK_HEADER
#define KF_MEMORY_BLOCK_HEADER

#include "kf/kf_types.h"
#include "kf/kf_math.h"

#include <ostream>
#include <string>

// to do: add search to memBlock

namespace kf
{
	template <typename T>
	class MemBlock_T
	{
	public:
		inline MemBlock_T()
		{
			m_begin = NULL;
			m_end = NULL;
			m_current = NULL;
		}

		inline MemBlock_T(T start, u64 length)
		{
			m_begin = start;
			m_end = m_begin + length;
			m_current = m_begin;
		}

		inline ~MemBlock_T()
		{
		}

		inline void setRange(T start, u64 length)
		{
			m_begin = start;
			m_end = m_begin + length;
			m_current = m_begin;
		}

		inline bool seek(s64 offset, bool relative = false)
		{
			if (relative)
			{
				if (offset >= 0)
				{
					u64 distance = m_end - m_current;
					if ((u64) offset <= distance)
					{
						m_current += offset;
						return true;
					}
					else
					{
						m_current += distance;
						return false;
					}
				}
				else
				{
					offset = -offset;
					u64 distance = m_current - m_begin;
					if ((u64) offset <= distance)
					{
						m_current -= offset;
						return true;
					}
					else
					{
						m_current -= distance;
						return false;
					}
				}
			}
			else
			{
				if (offset < 0)
					offset = 0;

				if (m_end - m_begin > (u64) offset)
				{
					m_current = m_begin + (u64) offset;
					return true;
				}
				else
				{
					m_current = m_end;
					return false;
				}
			}
		}

		inline MemBlock_T &operator+=(s64 offset)
		{
			seek(offset, true);
			return *this;
		}

		inline MemBlock_T &operator-=(s64 offset)
		{
			seek(-offset, true);
			return *this;
		}

		inline MemBlock_T &operator++()
		{
			if (m_current != m_end)
			{
				m_current++;
			}
			return *this;
		}

		inline MemBlock_T &operator--()
		{
			if (m_current != m_begin)
			{
				m_current--;
			}
			return *this;
		}

		inline bool operator==(const MemBlock_T &rhs)
		{
			return m_current == rhs.m_current && m_begin == rhs.m_begin && m_end == rhs.m_end;
		}

		inline MemBlock_T &operator=(const MemBlock_T &rhs)
		{
			m_current = rhs.m_current;
			m_begin = rhs.m_begin;
			m_end = rhs.m_end;
			return *this;
		}

		inline T begin() const
		{
			return m_begin;
		}

		inline T end() const
		{
			return m_end;
		}

		inline T current() const
		{
			return m_current;
		}

		inline u64 index() const
		{
			return m_current - m_begin;
		}

		inline bool index(u64 o)
		{
			if(m_begin + o <= m_end)
				m_current = m_begin + o;
			else
				m_current = m_end;
		}

		u64 size() const
		{
			return (m_end - m_begin);
		}

		template<typename T2>
		inline T2 peek() const
		{
			if (m_end - m_current >= sizeof(T2))
			{
				return *((T2 *) m_current);
			}
			else
			{
				return T2();
			}
		}

		template<typename T2>
		inline T2 get()
		{
			T2 temp = peek<T2>();
			this->operator+=(sizeof(T2));
			return temp;
		}

		template<typename T2>
		inline MemBlock_T &set(const T2 &value)
		{
			if (m_end - m_current >= sizeof(T2))
			{
				*((T2 *) m_current) = value;
				this->operator+=(sizeof(T2));
			}
			return *this;
		}

		inline u8 getU8()
		{
			return get<u8>();
		}

		inline u16 getU16()
		{
			return get<u16>();
		}

		inline u32 getU24()
		{
			unsigned char a = get<u8>();
			unsigned char b = get<u8>();
			unsigned char c = get<u8>();

			return a|(b<<8)|(c<<16);
		}

		inline u32 getU32()
		{
			return get<u32>();
		}

		inline u64 getU64()
		{
			return get<u64>();
		}

		inline s8 getS8()
		{
			return get<s8>();
		}

		inline s16 getS16()
		{
			return get<s16>();
		}

		inline s32 getS24()
		{
			unsigned char a = get<u8>();
			unsigned char b = get<u8>();
			unsigned char c = get<u8>();

			return a | (b << 8) | (c << 16) | (c&0x80?0xff0000:0x000000);
		}

		inline s32 getS32()
		{
			return get<s32>();
		}

		inline s64 getS64()
		{
			return get<s64>();
		}

		inline float getFloat()
		{
			return get<float>();
		}

		inline double getDouble()
		{
			return get<double>();
		}
		
		inline void getBlock(u8 *destination, u64 length)
		{
			T temp = m_current;
			operator+=(length);
			memcpy(destination, temp, (u64) (m_current - temp));
		}
		
		std::string getString(u64 length = 0, bool move = true)
		{
			std::string s;
			T temp = m_current;
			if (length > m_end - m_begin)
			{
				length = m_end - m_begin;
			}
			while (m_current < m_end)
			{
				if (*m_current == 0 || (length > 0 && (u64)(m_current - temp) >= length))
				{
					s = std::string(temp, m_current);
					if (length > 0)
					{
						m_current = temp + length;
					}
					else
					{
						m_current++;
					}
					return s;
				}
				m_current++;
			}
			return std::string(temp, m_end);
		}



		inline MemBlock_T &setU8(u8 value)
		{
			return set<u8>(value);
		}

		inline MemBlock_T &setU16(u16 value)
		{
			return set<u16>(value);
		}

		inline MemBlock_T &setU32(u32 value)
		{
			return set<u32>(value);
		}

		inline MemBlock_T &setU64(u64 value)
		{
			return set<u64>(value);
		}

		inline MemBlock_T &setS8(s8 value)
		{
			return set<s8>(value);
		}

		inline MemBlock_T &setS16(s16 value)
		{
			return set<s16>(value);
		}

		inline MemBlock_T &setS32(s32 value)
		{
			return set<s32>(value);
		}

		inline MemBlock_T &setS64(s64 value)
		{
			return set<s64>(value);
		}

		inline MemBlock_T &setFloat(float value)
		{
			return set<float>(value);
		}

		inline MemBlock_T &setDouble(double value)
		{
			return set<double>(value);
		}

		std::string getHex(u64 length, u64 division = 0)
		{
			std::string s;
			//s.resize(length * 2 + (division>0)? length / division : 0);
			for (unsigned int i = 0; i < kf::minimum<kf::u64>(length,m_end-m_current); i++)
			{
				s += nibbleToHex(m_current[i] >> 4);
				s += nibbleToHex(m_current[i] & 0x0f);
				if (division && i%division == division - 1)
				{
					s += ' ';
				}
			}
			operator+=(length);
			return s;
		}

		void setBlock(u8 *source, u64 length)
		{
			u8 *temp = m_current;
			operator+=(length);
			memcpy(temp, source, m_current - temp);
		}

		void setString(const std::string &value, bool include_terminator = true, u64 length = 0, bool pad = false)
		{
			u8 *temp = m_current;
			u64 stringlength = u64(value.size()) + (include_terminator ? 1 : 0);


			if (length > 0)
			{
				if (length < stringlength)
				{
					stringlength = length - (include_terminator ? 1 : 0);
					if (include_terminator)
					{
						temp[length - 1] = 0;
					}
				}
				operator+=(length);
			}
			else
			{
				operator+=(stringlength);
			}
			memcpy(temp, value.c_str(), stringlength);
			if (length > 0) 
			{
				if (stringlength < length && pad)
				{
					temp += stringlength;
					for (u64 i = 0; i < length - stringlength; i++)
					{
						if (temp >= m_end)
						{
							return;
						}
						*(temp++) = 0;
					}
				}
			}
		}

		bool bit(kf::u64 b) const
		{
			if (b < (m_end - m_begin) * 8)
			{
				return m_begin[b / 8] & (1 << (b % 8));
			}
			return false;
		}

		void bit(kf::u64 b, bool value)
		{
			if (b < (m_end - m_begin) * 8)
			{
				kf::u8 bit = (1 << (b % 8));
				if (value)
					m_begin[b / 8] = m_begin[b / 8] | (bit);
				else
					m_begin[b / 8] = m_begin[b / 8] & (~bit);
			}
		}

		kf::u8 byte(kf::u64 b) const
		{
			if (b < (m_end - m_begin))
			{
				return m_begin[b];
			}
			return 0;
		}

		void byte(kf::u64 b, kf::u8 value)
		{
			if (b < (m_end - m_begin))
			{
				m_begin[b] = value;
			}
		}

		kf::u64 bits(kf::u64 b, kf::u8 count) const
		{
			kf::u64 value = 0;
			for (int i = 0; i < count / 8 + 1 +(b%8==0?0:1); ++i)
			{
				value = (value << 8) | byte(b / 8 + i);
			}
			value = value >> (b % 8);
			return value;
		}







/*

		void getBlock(u8 *destination, u64 length, bool move = true)
		{
			u8 *temp = m_current;
			operator+=(length);
			memcpy(destination, temp, (u32) (m_current - temp));
		}

		std::string getString(u64 length=0, bool move = true)
		{
			std::string s;
			u8 *temp = m_current;
			if (length > m_end - m_begin)
			{
				length = m_end - m_begin;
			}
			while (m_current < m_end)
			{
				if (*m_current == 0 || (length > 0 && (u32) (m_current - temp) >= length))
				{
					s = std::string(temp, m_current);
					if (length > 0)
					{
						m_current = temp + length;
					}
					else
					{
						m_current++;
					}
					return s;
				}
				m_current++;
			}
			return std::string(temp, m_end);
		}

		void setBlock(u8 *source, u64 length, bool move = true)
		{
			u8 *temp = m_current;
			operator+=(length);
			memcpy(temp, src, m_current - temp);
		}

		void setString(const std::string &value, bool include_terminator = true, u64 length = 0, bool pad = false, bool move = true)
		{
			u8 *temp = m_current;
			u64 stringlength = u64(value.size()) + (include_terminator ? 1 : 0);


			if (length > 0)
			{
				if (length < stringlength)
				{
					stringlength = length - (include_terminator ? 1 : 0);
				}
				operator+=(length);
			}
			else
			{
				operator+=(stringlength);
			}
			memcpy(temp, value.c_str(), stringlength);
			if (length > 0 && stringlength < length && pad)
			{
				temp += stringlength;
				for (u64 i = 0; i < length - stringlength; i++)
				{
					if (temp >= m_end)
					{
						return;
					}
					*(temp++) = 0;
				}
			}
		}

		*/

		/*
		MemBlock &operator<<(dword value);
		MemBlock &operator<<(sdword value);
		MemBlock &operator<<(word value);
		MemBlock &operator<<(sword value);
		MemBlock &operator<<(byte value);
		MemBlock &operator<<(sbyte value);
		MemBlock &operator<<(float value);
		MemBlock &operator<<(double value);
		MemBlock &operator<<(const std::string &value);
		*/

	protected:
		T m_begin;
		T m_end;
		T m_current;
	};

	typedef MemBlock_T<kf::u8 *> MemBlock;
	typedef MemBlock_T<const kf::u8 *> MemBlockC;

	inline std::ostream &operator<<(std::ostream &os, const MemBlockC &src)
	{
		u8 c;
		u8 buf[81] = { 0 };
		u64 i, j;
		u64 address;
		MemBlockC mi(src);
		mi.seek(0);

		for (j = 0; j < (mi.size() + 15) / 16; j++)
		{
			for (i = 0; i < 79; i++)
			{
				buf[i] = ' ';
			}
			address = ((u64) mi.begin()) + j * 16;
			for (i = 0; i < 8; i++)
			{
				buf[i] = nibbleToHex((u8) ((address >> ((7 - i) * 4)) & 0xff));
			}

			for (i = 0; i < 16; i++)
			{
				if (i + j * 16 >= mi.size())
				{
					break;
				}
				c = mi.get<u8>();
				buf[i * 3 + 9 + (i / 4)] = nibbleToHex(c >> 4);
				buf[i * 3 + 10 + (i / 4)] = nibbleToHex(c & 0x0f);

				if (c >= 32 && c <= 127)
				{
					buf[63 + i] = c;
				}
				else
				{
					buf[63 + i] = '.';
				}
			}
			os << buf << "\n";
		}
		return os;
	}

	inline std::ostream &operator<<(std::ostream &os, const MemBlock &src)
	{
		MemBlockC temp(src.begin(), src.size());
		return operator<<(os, temp);
	}

	template <u64 S>
	class MemBlockAllocStack: public MemBlock
	{
	public:
		kf::u8 m_stackData[S];
		MemBlockAllocStack()
		{
			m_begin = m_stackData;
			m_end = m_begin + S;
			m_current = m_begin;
		}
	};
	template <u64 S>
	class MemBlockAllocHeap : public MemBlock
	{
	public:
		kf::u8 *m_heapData;
		MemBlockAllocHeap()
		{
			m_heapData = new u8[S];
			m_begin = m_heapData;
			m_end = m_begin + S;
			m_current = m_begin;
		}
		~MemBlockAllocHeap()
		{
			delete [] m_heapData;
			m_heapData = 0;
		}
	};
}

#endif
