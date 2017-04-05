#include <iostream>
#include <regex>
#include <vector>

#include "../Lexer.h"
#include "../StrCommon.hpp"

#define BOOST_TEST_MODULE lexer_test 
#include <boost/test/unit_test.hpp>



BOOST_AUTO_TEST_CASE(regex_pattern)
{
    std::vector<std::string> tests = { { "word" }, { "==" }, { ">" },
    { ">=" }, { "<=" }, { "||" }, { "&&" }, { "//comments" }, { "\"string literal\"" }, { "=" }, { ">" }, { "<" } };
    
    std::regex lex_regex(Lexer::regex_pattern);


    for (const auto& str : tests)
    {
        BOOST_CHECK(std::regex_match(str, lex_regex));
    }

    std::string line = "  sum = 3  //this is comments  ";
    std::vector<std::string> tokens;
    

    while (!line.empty())
    {
        std::smatch strM;
        line = StrCommon::trim(line);
        if (std::regex_search(line, strM, lex_regex))
        {
            tokens.push_back(strM[1]);
            if (line.find_first_of(strM[1]) != std::string::npos)
            {
                line.erase(line.find_first_of(strM[1]), strM[1].length());
            }
        }
    }

    BOOST_CHECK_EQUAL(tokens.size(),4u);
    BOOST_CHECK(tokens[0].compare("sum") == 0);
    BOOST_CHECK(tokens[1].compare("=") == 0);
    BOOST_CHECK(tokens[2].compare("3") == 0);
    BOOST_CHECK(tokens[3].compare("//this is comments") == 0);
    for (const auto& token : tokens)
    {
        BOOST_CHECK(std::regex_match(token, lex_regex));
    }

    line.assign("strTest = \"String Literal\"");
    tokens.clear();

    while (!line.empty())
    {
        std::smatch strM;
        line = StrCommon::trim(line);
        if (std::regex_search(line, strM, lex_regex))
        {
            tokens.push_back(strM[1]);
            if (line.find_first_of(strM[1]) != std::string::npos)
            {
                line.erase(line.find_first_of(strM[1]), strM[1].length());
            }
        }
    }

    BOOST_CHECK_EQUAL(tokens.size(), 3u);
    BOOST_CHECK(tokens[0].compare("strTest") == 0);
    BOOST_CHECK(tokens[1].compare("=") == 0);
    BOOST_CHECK(tokens[2].compare("\"String Literal\"") == 0);
    for (const auto& token : tokens)
    {
        BOOST_CHECK(std::regex_match(token, lex_regex));
    }


}

BOOST_AUTO_TEST_CASE(lexer)
{
    std::string src_file = "../Testing/stone-src.st";
    std::shared_ptr<Lexer> lex = std::make_shared<Lexer>(src_file);

    std::shared_ptr<Token> token;

    try{

        for (token = lex->read();
            token->getLineNumber() != Token::EOF_TOEKN->getLineNumber(); token = lex->read())
        {
            std::cout << "Line Num " << token->getLineNumber() << " => " << 
                "(" << token->getType() << "," << token->getText() << ")" << std::endl;
            
            BOOST_CHECK(!token->getText().empty());
        }
    }
    catch (const std::exception& e)
    {
        BOOST_FAIL(e.what());
    }

}
