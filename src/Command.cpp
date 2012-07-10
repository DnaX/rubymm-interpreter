#include "Command.h"

#include "DoubleCmdTree.h"

Command::Command()
{
    //ctor
}

Command::~Command()
{
    //dtor
}

bool Command::isAssignmentTree()
{
    return false;
}

bool Command::isReturnTree()
{
    return false;
}

bool Command::isIfTree()
{
    return false;
}

bool Command::isWhileTree()
{
    return false;
}

bool Command::isPutsTree()
{
    return false;
}

bool Command::isGetsTree()
{
    return false;
}

bool Command::isDoubleCmdTree()
{
    return false;
}

ExpressionTree* Command::getExpression()
{
    return NULL;
}

Command* Command::getCommands()
{
    return NULL;
}

void Command::printCommand()
{

}
