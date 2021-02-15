////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_MEMORY_FILE_HEADER
#define KF_MEMORY_FILE_HEADER

#include "kf/kf_memBlock.h"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <ostream>
#include <string>

// to do: add search to memBlock

namespace kf
{
   class MemFile
   {
   public:
	   MemFile()
	   {
		   m_handleFile = INVALID_HANDLE_VALUE;
		   m_handleMap = INVALID_HANDLE_VALUE;
		   m_readOnly = true;
		   m_size = 0;
	   }

	   MemFile(const std::string &name, bool read_only = true, bool create_new = false, u32 size = 0)
	   {
		   if (create_new)
		   {
			   create(name, size);
		   }
		   else
		   {
			   open(name, read_only);
		   }
	   }

	   ~MemFile()
	   {
		   close();
	   }

	   bool open(const std::string &name, bool read_only = true)
	   {
		   OFSTRUCT of;

		   m_handleFile = INVALID_HANDLE_VALUE;
		   m_handleMap = INVALID_HANDLE_VALUE;
		   m_readOnly = read_only;
		   m_size = 0;
		   m_memBlock.setRange(NULL, 0);
		   m_name = name;

		   m_handleFile = (HANDLE)OpenFile(m_name.c_str(), &of, (read_only ? OF_READ : OF_READWRITE));
		   if (m_handleFile != INVALID_HANDLE_VALUE)
		   {
			   m_size = GetFileSize(m_handleFile, NULL);
			   if (m_size>600000000)
			   {
				   m_size = 600000000;
			   }
			   return map();
		   }
		   return false;
	   }

	   bool create(const std::string &name, u32 size)
	   {
		   m_handleFile = INVALID_HANDLE_VALUE;
		   m_handleMap = INVALID_HANDLE_VALUE;
		   m_readOnly = false;
		   m_size = size;
		   m_memBlock.setRange(NULL, 0);
		   m_name = name;

		   m_handleFile = CreateFile(name.c_str(),
			   GENERIC_WRITE | GENERIC_READ,
			   FILE_SHARE_WRITE,
			   NULL,
			   CREATE_ALWAYS,
			   FILE_ATTRIBUTE_NORMAL,
			   NULL);
		   if (m_handleFile != INVALID_HANDLE_VALUE)
		   {
			   return map();
		   }
		   return false;
	   }

	  void close()
	  {
		  if (m_handleMap != INVALID_HANDLE_VALUE)
		  {
			  CloseHandle(m_handleMap);
			  m_handleMap = INVALID_HANDLE_VALUE;
		  }
		  if (m_handleFile != INVALID_HANDLE_VALUE)
		  {
			  CloseHandle(m_handleFile);
			  m_handleFile = INVALID_HANDLE_VALUE;
		  }
	  }

	  bool isGood() const
	  {
		  return m_handleMap != INVALID_HANDLE_VALUE;
	  }

	  MemBlock getBlock()
	  {
		  return m_memBlock;
	  }

   protected:
	   bool map()
	   {
		   m_handleMap = CreateFileMapping(m_handleFile, NULL, (m_readOnly ? PAGE_READONLY : PAGE_READWRITE), 0, m_size, NULL);
		   if (m_handleMap != INVALID_HANDLE_VALUE)
		   {
			   void *vp;
			   vp = MapViewOfFile(m_handleMap, (m_readOnly ? FILE_MAP_READ : FILE_MAP_WRITE), 0, 0, m_size);
			   if (vp)
			   {
				   m_memBlock.setRange((u8 *)vp, m_size);
				   return true;
			   }
		   }
		   return false;
	   }

      HANDLE m_handleFile;
	  HANDLE m_handleMap;
      u32 m_size;
      bool m_readOnly;
      MemBlock m_memBlock;
      std::string m_name;
   };
}

#endif
