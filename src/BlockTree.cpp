#include "BlockTree.h"

BlockTree::BlockTree(ExpressionTree* expr)
{
    myExpr = expr;
}

BlockTree::~BlockTree()
{
    delete myExpr;
    myExpr = NULL;
}

bool BlockTree::isBlockTree()
{
    return true;
}

string BlockTree::toString()
{
    return "[" + myExpr->toString() + "]";
}

ExpressionTree* BlockTree::getExpressions()
{
    return myExpr;
}

