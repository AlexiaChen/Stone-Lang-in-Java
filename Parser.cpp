#include "Parser.h"

Parser::ASTreePtr Parser::parse(const std::shared_ptr<Lexer>& lexer)
{
    return std::make_shared<ASTree>();
}

bool Parser::match(const std::shared_ptr<Lexer>& lexer)
{
    return false;
}