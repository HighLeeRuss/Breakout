////////////////////////////////////////////////////////////
// KF - Kojack Framework
// Copyright (C) 2019 Kojack (rajetic@gmail.com)
//
// KF is released under the MIT License  
// https://opensource.org/licenses/MIT
////////////////////////////////////////////////////////////

#ifndef KF_TAG_HEADER
#define KF_TAG_HEADER

#include <set>
#include <string>
#include <vector>

// Tags are strings that identify properties of objects.
namespace kf
{
	class Tags
	{
	protected:
		std::vector<std::string> m_tags;

	public:
		void add(const std::string &s)		// Add a tag to the collection.
		{
			auto it = std::find(m_tags.begin(), m_tags.end(), s);
			if (it == m_tags.end())
			{
				m_tags.push_back(s);
			}
		}

		void remove(const std::string &s)	// Remove a tag from the collection.
		{
			auto it = std::find(m_tags.begin(), m_tags.end(), s);
			if (it != m_tags.end())
				m_tags.erase(it);
		}

		bool has(const std::string &s)		// Return true if the collection contains the tag.
		{
			return std::find(m_tags.begin(), m_tags.end(), s) != m_tags.end();
		}

		std::vector<std::string> &getVector()
		{
			return m_tags;
		}
	};
}


#endif
