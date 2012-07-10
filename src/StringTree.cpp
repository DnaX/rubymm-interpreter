#include "StringTree.h"
#include "BoolTree.h"
#include <iostream>

StringTree::StringTree(std::string value)
{
    myValue = value;
}

StringTree::~StringTree()
{
    //dtor
}

bool StringTree::isStringTree()
{
    return true;
}

string StringTree::toString()
{
    string s;
    stringstream out;
    out << "(" << "\e[0;35m" << "String " << "\e[1;35m" << myValue << "\e[0m" << ")";
    s = out.str();
    return s;
}

string StringTree::getValue()
{
    return myValue;
}

string StringTree::strValue()
{
    return myValue;
}

LiteralTree& StringTree::operator + (const LiteralTree& literal)
{
    StringTree* str = NULL;
    string buf;

    buf = myValue + ((StringTree&)literal).myValue;
    str = new StringTree(buf);

    return *str;
}

LiteralTree& StringTree::operator == (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue == ((StringTree&)literal).myValue);

    return *ret;
}

LiteralTree& StringTree::operator != (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue != ((StringTree&)literal).myValue);

    return *ret;
}

LiteralTree& StringTree::operator >= (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue >= ((StringTree&)literal).myValue);

    return *ret;
}

LiteralTree& StringTree::operator <= (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue <= ((StringTree&)literal).myValue);

    return *ret;
}

LiteralTree& StringTree::operator > (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue > ((StringTree&)literal).myValue);

    return *ret;
}

LiteralTree& StringTree::operator < (const LiteralTree& literal)
{
    LiteralTree* ret = NULL;

    ret = new BoolTree(myValue < ((StringTree&)literal).myValue);

    return *ret;
}

LITERAL_TYPE StringTree::getType()
{
    return TSTRING;
}
