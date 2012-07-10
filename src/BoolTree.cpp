#include "BoolTree.h"

BoolTree::BoolTree(bool value)
{
    myValue = value;
}

BoolTree::~BoolTree()
{
    //dtor
}

bool BoolTree::isBoolTree()
{
    return true;
}

string BoolTree::toString()
{
    return myValue ? "(\e[0;34mBool \e[1;34mtrue\e[0m)" : "(\e[0;34mBool \e[1;34mfalse\e[0m)";
}

bool BoolTree::getValue()
{
    return myValue;
}

string BoolTree::strValue()
{
    return myValue ? "true" : "false";
}

LiteralTree& BoolTree::operator and (const LiteralTree& literal)
{
    BoolTree* value = NULL;

    value = new BoolTree(myValue and ((BoolTree&)literal).myValue);

    return *value;
}

LiteralTree& BoolTree::operator or (const LiteralTree& literal)
{
    BoolTree* value = NULL;

    value = new BoolTree(myValue || ((BoolTree&)literal).myValue);

    return *value;
}

LiteralTree& BoolTree::operator == (const LiteralTree& literal)
{
    BoolTree* value = NULL;

    value = new BoolTree(myValue == ((BoolTree&)literal).myValue);

    return *value;
}

LiteralTree& BoolTree::operator != (const LiteralTree& literal)
{
   BoolTree* value = NULL;

    value = new BoolTree(myValue != ((BoolTree&)literal).myValue);

    return *value;
}

LiteralTree& BoolTree::operator >= (const LiteralTree& literal)
{
   BoolTree* value = NULL;

    value = new BoolTree(myValue >= ((BoolTree&)literal).myValue);

    return *value;
}

LiteralTree& BoolTree::operator <= (const LiteralTree& literal)
{
   BoolTree* value = NULL;

    value = new BoolTree(myValue <= ((BoolTree&)literal).myValue);

    return *value;
}

LiteralTree& BoolTree::operator > (const LiteralTree& literal)
{
   BoolTree* value = NULL;

    value = new BoolTree(myValue > ((BoolTree&)literal).myValue);

    return *value;
}

LiteralTree& BoolTree::operator < (const LiteralTree& literal)
{
   BoolTree* value = NULL;

    value = new BoolTree(myValue < ((BoolTree&)literal).myValue);

    return *value;
}

LITERAL_TYPE BoolTree::getType()
{
    return TBOOL;
}
