#include "GetsTree.h"

GetsTree::GetsTree(IdentifierTree* id)
{
    myId = id;
}

bool GetsTree::isGetsTree()
{
    return true;
}

void GetsTree::printCommand()
{
    cout << "\e[0;33m" << "Gets: " << "\e[0m" << myId->toString() << endl;
}

ExpressionTree* GetsTree::getExpression()
{
    return myId;
}

GetsTree::~GetsTree()
{
    delete myId;
    myId = NULL;
}
