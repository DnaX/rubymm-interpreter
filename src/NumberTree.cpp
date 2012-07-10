#include "NumberTree.h"
#include "LiteralTree.h"

NumberTree::NumberTree(int value)
{
    myValue = value;
}

NumberTree::~NumberTree()
{
    //dtor
}

bool NumberTree::isNumberTree()
{
    return true;
}

string NumberTree::toString()
{
    string s;
    stringstream out;
    out << "(" << "\e[0;36m" << "Number " << "\e[1;36m" << myValue << "\e[0m" << ")";
    s = out.str();
    return s;
}

int NumberTree::getValue()
{
    return myValue;
}

string NumberTree::strValue()
{
    string s;
    stringstream out;
    out << myValue;
    s = out.str();
    return s;
}

LiteralTree& NumberTree::operator + (const LiteralTree& literal)
{
    NumberTree* number = NULL;

    number = new NumberTree(myValue + ((NumberTree&)literal).myValue);

    return *number;
}

LiteralTree& NumberTree::operator - (const LiteralTree& literal)
{
    NumberTree* number = NULL;

    number = new NumberTree(myValue - ((NumberTree&)literal).myValue);

    return *number;
}

LiteralTree& NumberTree::operator * (const LiteralTree& literal)
{
    NumberTree* number = NULL;

    number = new NumberTree(myValue * ((NumberTree&)literal).myValue);

    return *number;
}

LiteralTree& NumberTree::operator / (const LiteralTree& literal)
{
    NumberTree* number = NULL;

    number = new NumberTree(myValue / ((NumberTree&)literal).myValue);

    return *number;
}

LiteralTree& NumberTree::operator % (const LiteralTree& literal)
{
    NumberTree* number = NULL;

    number = new NumberTree(myValue % ((NumberTree&)literal).myValue);

    return *number;
}

LiteralTree& NumberTree::operator == (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue == ((NumberTree&)literal).myValue);

    return *ret;
}

LiteralTree& NumberTree::operator != (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue != ((NumberTree&)literal).myValue);

    return *ret;
}

LiteralTree& NumberTree::operator >= (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue >= ((NumberTree&)literal).myValue);

    return *ret;
}

LiteralTree& NumberTree::operator <= (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue <= ((NumberTree&)literal).myValue);

    return *ret;
}

LiteralTree& NumberTree::operator > (const LiteralTree& literal)
{
    BoolTree* ret = NULL;

    ret = new BoolTree(myValue > ((NumberTree&)literal).myValue);

    return *ret;
}

LiteralTree& NumberTree::operator < (const LiteralTree& literal)
{
    LiteralTree* ret = NULL;

    ret = new BoolTree(myValue < ((NumberTree&)literal).myValue);

    return *ret;
}

LITERAL_TYPE NumberTree::getType()
{
    return TNUMBER;
}
