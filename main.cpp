#include <iostream>
#include <regex>
#include <vector>

#include "Lexer.h"

void testRegexPattern();
void testRegexPatternFromSrc();


int main(int argc, char* argv[])
{
	//testRegexPattern();
	testRegexPatternFromSrc();
	return 0;
}

void testRegexPattern()
{
	std::vector<std::string> tests = { { "  word   " }, { "  ==  " }, { ">" },
	{ ">=" }, { "<=" }, { "||" }, { "&&" }, { "//comments" }, { "\"string literal\"" }, { "=" }, { ">" }, { "<" } };
	//std::regex lex_regex("[A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|>|<|=|&&|\\|\\|");
	std::regex lex_regex(Lexer::regex_pattern);


	for (const auto& str : tests)
	{
		std::cout << str << ": " << std::regex_match(str, lex_regex) << '\n';
	}

	
	int n;
	std::cin >> n;
}

void testRegexPatternFromSrc()
{
	std::string src_file = "C:/Users/MathxH/Desktop/Stone-Lang/tests/stone-src.txt";
	std::shared_ptr<Lexer> lex = std::make_shared<Lexer>(src_file);

	std::shared_ptr<Token> token;
	token = lex->read();
	while (token->getLineNumber() != Token::EOF_TOEKN->getLineNumber())
	{
		std::cout << "=> "<< token->getText() << std::endl;
		token = lex->read();
	}

	int n;
	std::cin >> n;
}