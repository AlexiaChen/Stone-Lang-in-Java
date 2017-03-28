#include <iostream>
#include <regex>
#include <vector>

#include "Lexer.h"
#include "StrCommon.hpp"

void testRegexPattern();
void testLexer();


int main(int argc, char* argv[])
{
    //testRegexPattern();
    testLexer();
    return 0;
}

void testRegexPattern()
{
    std::vector<std::string> tests = { { "  word   " }, { "  ==  " }, { ">" },
    { ">=" }, { "<=" }, { "||" }, { "&&" }, { "//comments" }, { "\"string literal\"" }, { "=" }, { ">" }, { "<" } };
    //std::regex lex_regex("[A-Z_a-z][A-Z_a-z0-9]*|==|<=|>=|>|<|=|&&|\\|\\|");
    std::regex lex_regex(Lexer::regex_pattern);


    //for (const auto& str : tests)
    //{
        //std::cout << str << ": " << std::regex_match(str, lex_regex) << '\n';
        //std::smatch match;
        //if (std::regex_search(str, match, lex_regex))
        //{
        //std::cout << "matched :" << str << "is :"<< match[1] << std::endl;
        //}
    //}

    std::string line = "  sum = 3  //this is comments  ";
    line.assign("strTest = \"dwdw\"");
	
    while (!line.empty())
    {
        std::smatch strM;
        line = StrCommon::trim(line);
        if (std::regex_search(line, strM, lex_regex))
        {
            std::cout << "matched :" << "is :" << strM[1] << std::endl;
            if (line.find_first_of(strM[1]) != std::string::npos)
            {
                line.erase(line.find_first_of(strM[1]), strM[1].length());
            }
            else
            {
                line.clear();
                continue;
            }
        }
	}
    int n;
    std::cin >> n;
}

void testLexer()
{
    std::string src_file = "C:/Users/MathxH/Desktop/Stone-Lang/tests/stone-src.st";
    std::shared_ptr<Lexer> lex = std::make_shared<Lexer>(src_file);

    std::shared_ptr<Token> token;
	
    try{
		
	    for (token = lex->read();
		    token->getLineNumber() != Token::EOF_TOEKN->getLineNumber(); token = lex->read())
	    {
		    std::cout << "Line Num " << token->getLineNumber() << " => " << token->getText() << std::endl;
	    }
    }
    catch (const std::exception& exp)
    {
        std::cout << exp.what() << std::endl;
    }

    int n;
    std::cin >> n;
}