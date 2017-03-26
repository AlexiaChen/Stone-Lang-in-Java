#ifndef STR_COMMON_H
#define STR_COMMON_H
 
#include <string>
#include <vector>
#include <regex>

class StrCommon
{
public:
	static std::vector<std::string> split(const std::string& s, std::string rgx_str = "\\s+")
	{
		std::vector<std::string> elems;

		std::regex rgx(rgx_str);
		std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
		std::sregex_token_iterator end;

		while (iter != end)
		{
			elems.push_back(*iter);
			++iter;
		}

		return elems;
	}

};



#endif