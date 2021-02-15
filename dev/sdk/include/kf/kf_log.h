////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2016 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_LOG_HEADER
#define KF_LOG_HEADER

#include <iostream>
#include <ostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "kf/kf_types.h"
#include "kf/kf_streams.h"

#define kf_log_detail(KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<__FILE__<<"("<<kf::u32(__LINE__)<<") : "<<KFLOGMACROTEXT<<std::endl; kf::LogSystem::getDefault().log(0, "", tempstream);}
#define kf_log_detail2(KFLOGMACROLEVEL, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<__FILE__<<"("<<kf::u32(__LINE__)<<") : "<<KFLOGMACROTEXT<<std::endl; kf::LogSystem::getDefault().log(KFLOGMACROLEVEL, "", tempstream);}
#define kf_log_detail3(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<__FILE__<<"("<<kf::u32(__LINE__)<<") : "<<KFLOGMACROTEXT<<std::endl; kf::LogSystem::getDefault().log(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, tempstream);}
#define kf_log(KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT<<std::endl; kf::LogSystem::getDefault().log(0, "", tempstream);}
#define kf_log2(KFLOGMACROLEVEL, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT<<std::endl; kf::LogSystem::getDefault().log(KFLOGMACROLEVEL, "", tempstream);}
#define kf_log3(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT<<std::endl; kf::LogSystem::getDefault().log(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, tempstream);}
#define kf_log_no_lf(KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT; kf::LogSystem::getDefault().log(0, "", tempstream);}
#define kf_log_no_lf2(KFLOGMACROLEVEL, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT; kf::LogSystem::getDefault().log(KFLOGMACROLEVEL, "", tempstream);}
#define kf_log_no_lf3(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT; kf::LogSystem::getDefault().log(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, tempstream);}

namespace kf
{
	class LogCallBack
	{
	public:
		typedef void(*log_callback_t)(unsigned int level, const std::string &subsys, const std::string &s, void *userdata);
		LogCallBack(log_callback_t callback, void *userdata = NULL, bool auto_delete = false) :
			m_function(callback),
			m_user_data(userdata),
			m_auto_delete(auto_delete)
		{
		}
		~LogCallBack()
		{
			if (m_auto_delete)
			{
				delete m_user_data;
			}
		}
		void call(unsigned int level, const std::string &subsys, const std::string &s)
		{
			m_function(level, subsys, s, m_user_data);
		}
		log_callback_t getFunction()
		{
			return m_function;
		}
		void *getUserData()
		{
			return m_user_data;
		}
		bool getAutoDelete()
		{
			return m_auto_delete;
		}
	protected:
		log_callback_t m_function;
		void *m_user_data;
		bool m_auto_delete;
	};

	class LogEntry
	{
	public:
		LogEntry(unsigned int level, const std::string &subsys, const std::string &s) :
			m_level(level),
			m_subsys(subsys),
			m_text(s)
		{
		}
		~LogEntry()
		{
		}
		unsigned int getLevel() const 
		{
			return m_level;
		}
		const std::string &getSubSystem() const
		{
			return m_subsys;
		}
		const std::string &getText() const
		{
			return m_text;
		}
	protected:
		unsigned int m_level;
		std::string m_subsys;
		std::string m_text;
	};

	class LogFileInfo
	{
	public:
		LogFileInfo(std::fstream *file, unsigned int min_level, unsigned int max_level) :
			m_file(file), m_min_level(min_level), m_max_level(max_level)
		{
		}
		~LogFileInfo()
		{
			delete m_file;
		}
		std::fstream *m_file;
		unsigned int m_min_level;
		unsigned int m_max_level;
	};

	class LogSystem
	{
	public:
		static LogSystem &getDefault()
		{
			static LogSystem *g_default_log = 0;
			if (!g_default_log) g_default_log = new LogSystem;
			return *g_default_log;
		}

		LogSystem(unsigned int level = 0) : m_minLevel(level)
		{
		}
		~LogSystem()
		{
		}
		void log(unsigned int level, const std::string &subsys, const std::stringstream &ss)
		{
			log(level, subsys, ss.str());
		}
		void log(unsigned int level, const std::string &subsys, const std::string &s)
		{
			if (level<m_minLevel)
			{
				return;
			}
			if (m_callbacks.size() == 0)
			{
				m_cachedEntries.push_back(new LogEntry(level, subsys, s));
				return;
			}
			for (std::vector<LogCallBack *>::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			{
				(*it)->call(level, subsys, s);
			}
		}
		void setMinLevel(unsigned int level)
		{
			m_minLevel = level;
		}

		unsigned int getMinLevel() const
		{
			return m_minLevel;
		}

		void addCallBack(LogCallBack::log_callback_t func, void *userdata = NULL, bool auto_delete = false)
		{
			m_callbacks.push_back(new LogCallBack(func, userdata, auto_delete));
			if (m_cachedEntries.size()>0)
			{
				for (unsigned int i = 0; i<m_cachedEntries.size(); i++)
				{
					func(m_cachedEntries[i]->getLevel(), m_cachedEntries[i]->getSubSystem(), m_cachedEntries[i]->getText(), userdata);
					delete m_cachedEntries[i];
				}
				m_cachedEntries.clear();
			}
		}

		void removeCallBack(LogCallBack::log_callback_t func, void *userdata)
		{
			for (std::vector<LogCallBack *>::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
			{
				if (func == (*it)->getFunction() && userdata == (*it)->getUserData())
				{
					if ((*it)->getAutoDelete())
					{
						delete (*it)->getUserData();
					}
					m_callbacks.erase(it);
					return;
				}
			}
		}

		//void removeCallBack(LogCallBack::log_callback_t func);

		static void logToCout(unsigned int level, const std::string &subsys, const std::string &s, void *userdata)
		{
			if (level >= ((std::pair<unsigned int, unsigned int>*)userdata)->first && level <= ((std::pair<unsigned int, unsigned int>*)userdata)->second)
			{
				if (subsys == "")
					std::cout << s;
				else
					std::cout << subsys << ": " << s;
				std::cout.flush();
			}
		}

		static void logToFile(unsigned int level, const std::string &subsys, const std::string &s, void *userdata)
		{
			IGNORE_VARIABLE(level);
			if (((LogFileInfo *) userdata)->m_file->is_open())
			{
				if (subsys == "")
					*(((LogFileInfo *) userdata)->m_file) << s;
				else
					*(((LogFileInfo *) userdata)->m_file) << (subsys) << ": " << s;
				((LogFileInfo *) userdata)->m_file->flush();
			}
		}

		void addCout(unsigned int minLevel = 0, unsigned int maxLevel = 0xffffffff)
		{
			addCallBack(logToCout, new std::pair<unsigned int, unsigned int>(minLevel, maxLevel), true);
		}

		void addFile(const std::string &filename, unsigned int minLevel = 0, unsigned int maxLevel = 0xffffffff)
		{
			std::fstream *file = new std::fstream(filename.c_str(), std::ios::out);
			if (file->is_open())
			{
				addCallBack(logToFile, new LogFileInfo(file, minLevel, maxLevel), true);
			}
		}
	protected:
		std::stringstream m_logStreamCache;
		std::vector<LogCallBack *> m_callbacks;
		std::vector<LogEntry *> m_cachedEntries;
		unsigned int m_minLevel;
	};
}

#endif
