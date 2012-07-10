#include "WhileTree.h"

WhileTree::WhileTree(ExpressionTree* expr, Command* cmd)
{
    myExpr = expr;
    myCmd = cmd;
}

bool WhileTree::isWhileTree() {
    return true;
}

void WhileTree::printCommand()
{
    if (myExpr != 0 && myCmd != 0)
    {
        cout << ">> \e[0;33m" << "While condition" << "\e[0m" << " (" << myExpr->toString() << ") " << "\e[0;33m" << "is true then execute command:" << "\e[0m" << endl;
        myCmd->printCommand();
        cout << "<< \e[0;33m" << "End while" << "\e[0m" << endl << endl;
    }
}

ExpressionTree* WhileTree::getExpression()
{
    return myExpr;
}

Command* WhileTree::getCommands()
{
    return myCmd;
}

WhileTree::~WhileTree()
{
    delete myExpr;
    myExpr = NULL;
    delete myCmd;
    myCmd = NULL;
}
