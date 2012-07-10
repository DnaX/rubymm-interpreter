#include "ReturnTree.h"

ReturnTree::ReturnTree(ExpressionTree* expr)
{
    myExpr = expr;
}

bool ReturnTree::isReturnTree()
{
    return true;
}

void ReturnTree::printCommand()
{
    cout << "\e[0;33m" << "Return of expression: " << "\e[0m" << myExpr->toString() << endl;
}

ReturnTree::~ReturnTree()
{
    delete myExpr;
    myExpr = NULL;
}

ExpressionTree* ReturnTree::getExpression()
{
    return myExpr;
}
