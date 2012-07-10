#include "IfTree.h"

IfTree::IfTree(ExpressionTree* expr, DoubleCmdTree* doublecmd)
{
    myExpr = expr;
    myCmd = doublecmd;
}

bool IfTree::isIfTree()
{
    return true;
}

void IfTree::printCommand()
{
    if (myExpr != 0 && myCmd != 0)
    {
        cout << ">> \e[0;33m" << "If condition" << "\e[0m" << " (" << myExpr->toString() << ") " << "\e[0;33m" << "is true then execute command:" << "\e[0m" << endl;
        myCmd->getLeftChild()->printCommand();
        cout << ">> \e[0;33m" << "Else execute command:" << "\e[0m" << endl;
        myCmd->getRightChild()->printCommand();
        cout << "<< \e[0;33mEnd If\e[0m" << endl;
    }
}

ExpressionTree* IfTree::getExpression()
{
    return myExpr;
}

Command* IfTree::getCommands()
{
    return myCmd;
}

IfTree::~IfTree()
{
    delete myExpr;
    myExpr = NULL;
    delete myCmd;
    myCmd = NULL;
}
