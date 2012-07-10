#include "IdentifierTree.h"
#include <iostream>

IdentifierTree::IdentifierTree(string name)
{
    myName = name;
}

IdentifierTree::~IdentifierTree()
{
    //dtor
}

bool IdentifierTree::isIdentifierTree()
{
    return true;
}

string IdentifierTree::getName()
{
    return myName;
}

string IdentifierTree::toString()
{
    return "(\e[0;31mIdentifier \e[1;31m" + myName + "\e[0m)";
}

bool IdentifierTree::operator== (const IdentifierTree& identifier)
{
    return (myName == identifier.myName);
}

bool IdentifierTree::operator== (const string& strIdentifier)
{
    return (myName == strIdentifier);

}
