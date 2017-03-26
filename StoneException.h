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


class ParseException : public std::exception
{
public:
	explicit ParseException(const std::string& msg):m_msg(msg){}

	const char* what(){ return m_msg.c_str(); }
private:
	std::string m_msg;
};


#endif