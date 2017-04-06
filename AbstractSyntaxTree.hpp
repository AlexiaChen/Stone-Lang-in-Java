#ifndef ASTREE_HPP
#define ASTREE_HPP

#include <cstdint>
#include <string>
#include <vector>

// represent Abstract Syntax Tree
class ASTree
{
public:
    virtual ASTree child(uint32_t i); // return the child node of index-i of the list of child of the node
    virtual uint32_t numChildren(); // return the number of children
    virtual std::string location(); // return the string of the location of the node in text
    virtual std::vector<ASTree>::iterator children(); // return the iterator of the list of the child of the node
    virtual std::string toString() { return std::string(""); }
public:
    std::vector<ASTree>::iterator iterator() { return children(); }
};
#endif