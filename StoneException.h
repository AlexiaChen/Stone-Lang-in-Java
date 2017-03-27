#ifndef STONE_EXCEPTION_H
#define STONE_EXCEPTION_H
#include <exception>
#include <string>

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
    explicit ParseException(const std::string& msg) :std::exception(msg.c_str()){};
    ~ParseException(){}

    const char* what() const { return std::exception::what(); }
};
#endif