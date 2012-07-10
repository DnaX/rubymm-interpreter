#include "NilTree.h"

NilTree::NilTree()
{
    //ctor
}

NilTree::~NilTree()
{
    //dtor
}

bool NilTree::isNilTree()
{
    return true;
}

string NilTree::toString()
{
    return "(\e[1;37mNIL\e[0m)";
}

string NilTree::strValue()
{
    return "nil";
}

LITERAL_TYPE NilTree::getType()
{
    return TNIL;
}
