////////////////////////////////////////////////////////////
// KAGE2D
// Copyright (C) 2021 Kojack (rajetic@gmail.com)
//
// KAGE2D is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#include "kage/system.h"

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

namespace kage
{
	bool s_initialised = false;

    bool initDirectory()
    {
		if (s_initialised)
			return true;
        char buf[MAX_PATH+1];
        GetModuleFileName(NULL,buf,MAX_PATH);
        char *p = buf;
        char *lastslash=NULL;
        while(*p)
        {
            if(*p=='\\' || *p=='/')
            {
                lastslash = p;
            }
            p++;
        }
        if(lastslash)
        {
            *lastslash=0;
        }
        SetCurrentDirectory(buf);
		s_initialised = true;
        return true;
    }
}
