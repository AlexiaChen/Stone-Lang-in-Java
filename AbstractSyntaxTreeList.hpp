#ifndef ASTREE_LIST_HPP
#define ASTREE_LIST_HPP
#include "AbstractSyntaxTree.hpp"

class ASTreeList : public ASTree
{
public:
    explicit ASTreeList(const std::vector<ASTree>& list) :m_children(list){}
    ASTree child(uint32_t i) override { return m_children[i]; }
    uint32_t numChildren() override { return m_children.size(); }
    std::vector<ASTree>::iterator children() override { return m_children.begin(); }
    std::string location() override {
        for (auto& child: m_children)
        {
            std::string s = child.location();
            if (!s.empty()) return s;
        }
        return std::string("");
    }
    std::string toString() override {
        std::string str_builder;
        str_builder.append("(");
        std::string sep;
        for (auto& child : m_children)
        {
            str_builder.append(sep);
            sep.assign(" ");
            str_builder.append(child.toString());
        }
        str_builder.append(")");
        return str_builder;
    }

protected:
    std::vector<ASTree> m_children;
};

#endif