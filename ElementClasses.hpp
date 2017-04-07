#ifndef ELEMENT_CLASSES_HPP
#define ELEMENT_CLASSES_HPP

#include <memory>
#include "Lexer.h"
#include "AbstractSyntaxTree.hpp"
#include "AbstractSyntaxTreeList.hpp"
#include "Parser.h"

class Element
{
protected:
    typedef std::shared_ptr<ASTree> ASTreePtr;
    virtual void parse(const std::shared_ptr<Lexer>& lexer, std::vector<ASTreePtr>& list);
    virtual bool match(const std::shared_ptr<Lexer>& lexer);

};

 class Tree : public Element
{
protected:
    typedef std::shared_ptr<ASTree> ASTreePtr;
    typedef std::shared_ptr<Parser> ParserPtr;
    Tree(ParserPtr p) :m_parser(p){}
    void parse(const std::shared_ptr<Lexer>& lexer, std::vector<ASTreePtr>& list) override
    {
        list.push_back(m_parser->parse(lexer));
    }
    bool match(const std::shared_ptr<Lexer>& lexer) override
    {
        return m_parser->match(lexer);
    }
protected:
    ParserPtr m_parser;
};

 class OrTree :public Element
 {
 protected:
     typedef std::shared_ptr<ASTree> ASTreePtr;
     typedef std::shared_ptr<Parser> ParserPtr;
     OrTree(const std::vector<ParserPtr>& p) :m_parsers(p){}
     void parse(const std::shared_ptr<Lexer>& lexer, std::vector<ASTreePtr>& list) override
     {
         ParserPtr p = choose(lexer);
         if (!p)
             throw ParseException(lexer->peek(0));
         else
             list.push_back(p->parse(lexer));
     }
     bool match(const std::shared_ptr<Lexer>& lexer) override
     {
         return choose(lexer) != nullptr;
     }
     ParserPtr choose(const std::shared_ptr<Lexer>& lexer)
     {
         for (ParserPtr p : m_parsers)
         {
             if (p->match(lexer)) return p;
         }
         return nullptr;
     }
     // insert list head
     void insert(ParserPtr p)
     {
         m_parsers.insert(std::begin(m_parsers), p);
     }
 protected:
     std::vector<ParserPtr> m_parsers;
 };

 class Repeat : public Element
 {
 protected:
     typedef std::shared_ptr<ASTree> ASTreePtr;
     typedef std::shared_ptr<Parser> ParserPtr;
     Repeat(ParserPtr p, bool once):m_parser(p),m_only_once(once){}
     void parse(const std::shared_ptr<Lexer>& lexer, std::vector<ASTreePtr>& list) override
     {
         while (m_parser->match(lexer))
         {
             ASTreePtr t = m_parser->parse(lexer);
             if (std::string(typeid(*t).name()).compare(typeid(ASTreeList).name()) == 0) list.push_back(t);
             if (m_only_once) break;
         }
     }
     bool match(const std::shared_ptr<Lexer>& lexer) override
     {
         return m_parser->match(lexer);
     }
 protected:
     ParserPtr m_parser;
     bool m_only_once;
 };


#endif