#ifndef STONE_EXCEPTION_H
#define STONE_EXCEPTION_H
#include <exception>
#include <string>

class RunTimeException : public std::exception
{
public:
	explicit RunTimeException(const std::string &what_arg){};
};



class StoneException : public RunTimeException
{
public:
	explicit StoneException(const std::string &msg) : RunTimeException(msg){};

};


#endif