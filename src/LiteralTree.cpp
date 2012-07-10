#include "LiteralTree.h"
#include "NilTree.h"

LiteralTree::LiteralTree()
{
    //ctor
}

LiteralTree::~LiteralTree()
{
    //dtor
}

bool LiteralTree::isLiteralTree()
{
    return true;
}

LiteralTree& LiteralTree::operator == (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator != (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator >= (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator <= (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator > (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator < (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator or (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator and (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator + (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator - (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator * (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator / (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

LiteralTree& LiteralTree::operator % (const LiteralTree& literal)
{
    LiteralTree* val = new NilTree();
    return *val;
}

string LiteralTree::strValue()
{
    return "";
}

LITERAL_TYPE LiteralTree::getType()
{
    return TNIL;
}
