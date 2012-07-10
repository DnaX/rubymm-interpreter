#include "DoubleCmdTree.h"

DoubleCmdTree::DoubleCmdTree(Command* left, Command* right)
{
    leftChild = left;
    rightChild = right;
}

bool DoubleCmdTree::isDoubleCmdTree() {
    return true;
}

Command* DoubleCmdTree::getLeftChild() {
    return leftChild;
}

Command* DoubleCmdTree::getRightChild() {
    return rightChild;
}

DoubleCmdTree::~DoubleCmdTree()
{
    delete leftChild;
    leftChild = NULL;
    delete rightChild;
    rightChild = NULL;
}

void DoubleCmdTree::printCommand()
{
    leftChild->printCommand();
    rightChild->printCommand();
}
