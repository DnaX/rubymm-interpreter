#include "PutsTree.h"

PutsTree::PutsTree(ExpressionTree* expr)
{
    myExpr = expr;
}

bool PutsTree::isPutsTree()
{
    return true;
}

void PutsTree::printCommand()
{
    cout << "\e[0;33m" << "Puts: " << "\e[0m" << myExpr->toString() << endl;
}

ExpressionTree* PutsTree::getExpression()
{
    return myExpr;
}


PutsTree::~PutsTree()
{
    delete myExpr;
    myExpr = NULL;
}
