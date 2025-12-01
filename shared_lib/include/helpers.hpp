#pragma once

#include <string>
#include <vector>

namespace InlineHelpers
{

inline std::vector<std::string> split_string(const std::string& s, const std::string& delimiter)
{
	std::vector<std::string> tokens;
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	while((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		tokens.push_back(token);
	}
	tokens.push_back(s.substr(pos_start));
	return tokens;
}

inline float range_to_range(float x, float y, float a, float b, float n)
{
	return (((n - x) / (y - x)) * (b - a)) + a;
}

} // namespace InlineHelpers
