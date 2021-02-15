#pragma once

#include <string>
#include <vector>

namespace kf
{
	inline std::vector<std::string> split(const std::string s, char separator)
	{
		std::vector<std::string> results;
		size_t i = 0;
		size_t j = 0;
		while ((i = s.find_first_of(separator, i)) != std::string::npos)
		{
			results.push_back(s.substr(j,i-j));
			j = ++i;
		}
		if (j < s.size())
		{
			results.push_back(s.substr(j));
		}
		return results;
	}

	inline std::string concatenate(const std::vector<std::string>& arr, const std::string &separator, const std::string& prefix="", const std::string& suffix="")
	{
		if (arr.empty())
			return std::string();

		std::string s = prefix;
		for (size_t i = 0; i < arr.size()-1; ++i)
		{
			s += arr[i];
			s += separator;
		}
		s += arr.back();
		s += suffix;
		return s;
	}
	inline std::string trimWS(const std::string& s)
	{
		size_t start = s.find_first_not_of(" \t\n");
		size_t end = s.find_last_not_of(" \t\n");
		if (start == std::string::npos || end == std::string::npos)
		{
			return std::string();
		}
		return std::string(s.begin() + start, s.begin() + end + 1);
	}
}
