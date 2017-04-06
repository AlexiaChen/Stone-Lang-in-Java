#ifndef ASTREE_LEAF_HPP
#define ASTREE_LEAF_HPP
#include <exception>
#include "AbstractSyntaxTree.hpp"
#include "Token.h"

class ASTreeLeaf : public ASTree
{
public:
    explicit ASTreeLeaf(Token t):m_token(t) {}
    ASTree child(uint32_t i) override { throw std::out_of_range("Index out of bound exception"); }
    uint32_t numChildren() override { return 0; }
    std::vector<ASTree>::iterator children() override { return m_empty.begin(); }
    std::string location() override { return std::string("at line ") + std::to_string(m_token.getLineNumber()); }
    std::string toString() override { return m_token.getText(); }
    Token token() const { return m_token; }
protected:
    Token m_token;
private:
    static std::vector<ASTree> m_empty;
};

#endif