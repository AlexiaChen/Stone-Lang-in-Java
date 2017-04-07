#ifndef PARSER_H
#define PARSER_H
#include <unordered_set>
#include <memory>
#include "AbstractSyntaxTree.hpp"
#include "Lexer.h"

class Parser
{
public:
    typedef std::shared_ptr<ASTree> ASTreePtr;
    ASTreePtr parse(const std::shared_ptr<Lexer>& lexer);
protected:
    friend class Tree;
    friend class OrTree;
    friend class Repeat;
    bool match(const std::shared_ptr<Lexer>& lexer);
    
};
#endif