#ifndef TOKEN_H
#define TOKEN_H

#include <cstdint>
#include <string>
#include <memory>

#include "StoneException.h"
class Token
{
public:
	static const std::shared_ptr<Token> EOF_TOEKN; // end of file
	static const std::string EOL_TOKEN; // end of line
public:
	virtual int32_t getLineNumber() const { return m_line_number; }
	virtual bool isIdentifier() { return false; }
	virtual bool isNumber() { return false; }
	virtual bool isString() { return false; }
	virtual int32_t getNumber() { throw StoneException("not number token"); }
	virtual std::string getText(){ return std::string(""); }
public:
	explicit Token(int32_t line):m_line_number(line){}
private:
	int32_t m_line_number;

};


#endif

