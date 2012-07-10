#include "FunctionCallTree.h"

FunctionCallTree::FunctionCallTree(IdentifierTree* id, ParamExprTree* parameters)
{
    myId = id;
    myParam = parameters;
}

FunctionCallTree::~FunctionCallTree()
{
    delete myId;
    myId = NULL;
    delete myParam;
    myParam = NULL;
}

bool FunctionCallTree::isFunctionCallTree()
{
    return true;
}

string FunctionCallTree::toString()
{
    return "\e[1;32m" + myId->getName() + "\e[0m (" + myParam->toString() + ")";
}

ParamExprTree* FunctionCallTree::getParams()
{
    return myParam;
}

IdentifierTree* FunctionCallTree::getIdentifier()
{
    return myId;
}
