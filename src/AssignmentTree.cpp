#include "AssignmentTree.h"

AssignmentTree::AssignmentTree(IdentifierTree* id, ExpressionTree* expr)
{
    myId = id;
    myExpr = expr;
}

AssignmentTree::~AssignmentTree()
{
    delete myId;
    myId = NULL;
    delete myExpr;
    myExpr = NULL;
}

bool AssignmentTree::isAssignmentTree()
{
    return true;
}

void AssignmentTree::printCommand()
{
    cout << "\e[0;33m" << "Assignment to identifier " << "\e[1;33m" << myId->getName() << "\e[0;33m" << ": " << "\e[0m" << myExpr->toString() << endl;
}

ExpressionTree* AssignmentTree::getExpression()
{
    return myExpr;
}

IdentifierTree* AssignmentTree::getIdentifier()
{
    return myId;
}
