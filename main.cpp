#include <iostream>
#include <regex>
#include <vector>

#include "Lexer.h"

int main(int argc, char* argv[])
{
	std::vector<std::string> tests = { { "word" }, { "  ==" }, { ">" }, 
	{ ">=" }, { "<=" }, { "||" }, { "&&" }, { "//comments" }, { "\"string literal\"" }, { "=" }, { ">" }, {"<"} };
	//std::regex lex_regex("[A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|>|<|=|&&|\\|\\|");
	std::regex lex_regex(Lexer::regex_pattern);

	for (const auto& str : tests)
	{
		std::cout << str << ": " << std::regex_match(str, lex_regex) << '\n';
	}
	
	int n;
	std::cin >> n;
	
	return 0;
}