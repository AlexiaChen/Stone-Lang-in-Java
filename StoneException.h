#ifndef STONE_EXCEPTION_H
#define STONE_EXCEPTION_H
#include <exception>
#include <string>

#include "Token.h"

class RunTimeException : public std::exception
{
public:
    explicit RunTimeException(const std::string &what_arg):std::exception(what_arg.c_str()){};
    ~RunTimeException() {}
	const char* what() const  { return std::exception::what(); }
};

class StoneException : public RunTimeException
{
public:
    explicit StoneException(const std::string &msg) : RunTimeException(msg){};
    ~StoneException() {}
    const char* what() const { return RunTimeException::what(); }
};

class ParseException : public std::exception
{
public:
    typedef std::shared_ptr<Token> TokenPtr;
    explicit ParseException(const std::string& msg) :std::exception(msg.c_str()){};
    explicit ParseException(TokenPtr t) :ParseException("", t){}
    explicit ParseException(const std::string& msg, TokenPtr t) :
    std::exception((std::string("Syntax error around ") + location(t) + std::string(". ") + msg).c_str())
    {}
    ~ParseException(){}
    const char* what() const { return std::exception::what(); }
private:
    static std::string location(TokenPtr t)
    {
        if (t->getLineNumber() == Token::EOF_TOEKN->getLineNumber()) return std::string("the last line");
        else return std::string("\"") + t->getText() + std::string("\"") + std::string(" at line ") + std::to_string(t->getLineNumber());
    }
};
#endif