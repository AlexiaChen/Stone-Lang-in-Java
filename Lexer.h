#ifndef LEXER_H
#define LEXER_H
#include <cstdint>
#include <vector>
#include <memory>
#include <regex>
#include "Token.h"
#include "LineNumberReader.h"

class Lexer
{
public:
    static std::string regex_pattern;
public:
    explicit Lexer(const std::string& file);
    ~Lexer();
    typedef std::shared_ptr<Token> TokenPtr;
public:
    TokenPtr read();
    TokenPtr peek(uint32_t i);
protected:
    void readLine();
    void addToken(uint32_t line_num, const std::string& token);

private:
    std::string toStringLiteral(const std::string& str);
    bool fillQueue(uint32_t i);
private:
    std::vector<TokenPtr> m_queue;
    bool m_hasMore;
    std::shared_ptr<LineNumberReader> m_reader;
    std::regex m_pattern;
};


class NumToken : public Token
{
public:
    virtual bool isNumber() override { return true; }
    virtual std::string getText() override { return std::to_string(m_value); }
    virtual int32_t getNumber() override { return m_value; }
    virtual std::string getType() override { return std::string("Number"); }

    NumToken(int32_t line, int32_t value):Token(line),m_value(value){}
private:
    int32_t m_value;
};

class IdentifierToken : public Token
{
public:
    virtual bool isIdentifier() override { return true; }
    virtual std::string getText() override { return m_text; }
    virtual std::string getType() override { return std::string("Identifier"); }

    IdentifierToken(int32_t line, const std::string& id) :Token(line), m_text(id){}
private:
    std::string m_text;
};

class StringToken : public Token
{
public:
    virtual bool isString() override{ return true; }
    virtual std::string getText() override { return m_str; }
    virtual std::string getType() override { return std::string("String"); }

    StringToken(int32_t line, const std::string& str):Token(line),m_str(str){}
private:
    std::string m_str;
};

#endif