#ifndef STR_COMMON_H
#define STR_COMMON_H
 
#include <string>
#include <vector>
#include <regex>
#include <memory>
#include <algorithm> 
#include <functional> 
#include <cctype>

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

    static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            [](char c){return !std::isspace(c); }));
	    return s;
    }

    // trim from end
    static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(),
            [](char c){return !std::isspace(c); }).base(), s.end());
	    return s;
    }

    // trim from both ends
    static inline std::string &trim(std::string &s) {
	    return ltrim(rtrim(s));
    }
};
#endif