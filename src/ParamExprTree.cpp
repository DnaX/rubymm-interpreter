#include "ParamExprTree.h"

ParamExprTree::ParamExprTree(ExpressionTree* expr)
{
    myExpr = expr;
    myOtherExpr = 0;
}

ParamExprTree::~ParamExprTree()
{
    delete myExpr;
    myExpr = NULL;
    delete myOtherExpr;
    myOtherExpr = NULL;
}

bool ParamExprTree::isParamExprTree()
{
    return true;
}

void ParamExprTree::addOtherExpr(ParamExprTree* otherExpr)
{
    // Aggiunge ricorsivamente un parametro

    // CASO BASE
    if (myOtherExpr == 0)
        myOtherExpr = otherExpr;

    // CASO RICORSIVO
    else myOtherExpr->addOtherExpr(otherExpr);
}

string ParamExprTree::toString()
{
    // Visita ricorsivamente l'elenco dei parametri (che sono espressioni)

    // CASO BASE
    if (myOtherExpr == 0)
        return myExpr -> toString();

    // CASO RICORSIVO
    else return myExpr -> toString() + " " + myOtherExpr -> toString();
}

ExpressionTree* ParamExprTree::getLeftChild()
{
    return myExpr;
}

ExpressionTree* ParamExprTree::getRightChild()
{
    return myOtherExpr;
}
