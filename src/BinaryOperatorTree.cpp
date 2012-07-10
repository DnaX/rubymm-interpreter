#include "BinaryOperatorTree.h"

BinaryOperatorTree::BinaryOperatorTree(string myOperator, ExpressionTree* left_operand, TermTree* right_operand)
{
    myOpString = myOperator;
    leftChild = left_operand;
    rightChild = right_operand;

    if (myOperator == "+")
        myOp = PLUS;
    else if (myOperator == "-")
        myOp = MINUS;
    else if (myOperator == "%")
        myOp = MOD;
    else if (myOperator == "==")
        myOp = EQUAL;
    else if (myOperator == "!=")
        myOp = NOTEQUAL;
    else if (myOperator == "or")
        myOp = OR;
    else if (myOperator == "and")
        myOp = AND;
    else if (myOperator == "<=")
        myOp = MINEQ;
    else if (myOperator == ">=")
        myOp = MAXEQ;
    else if (myOperator == "<")
        myOp = MIN;
    else if (myOperator == ">")
        myOp = MAX;
    else if (myOperator == "*")
        myOp = MULT;
    else if (myOperator == "/")
        myOp = DIV;

    //enum OPERATOR_TYPE {PLUS, MINUS, MULT, DIV, MOD, OR, AND, EQUAL, NOTEQUAL, MINEQ, MAXEQ, MIN, MAX};
}

BinaryOperatorTree::~BinaryOperatorTree()
{
    delete leftChild;
    leftChild = NULL;
    delete rightChild;
    rightChild = NULL;
}

bool BinaryOperatorTree::isBinaryOperatorTree()
{
    return true;
}

bool BinaryOperatorTree::isStringOperator()
{
    // è uno degli operatori ammessi
    return ( myOp == PLUS );

}

bool BinaryOperatorTree::isCompareOperator()
{
    // è uno degli operatori ammessi
    return (myOp == EQUAL || myOp == EQUAL || myOp == EQUAL || myOp == NOTEQUAL || myOp == MINEQ || myOp == MAXEQ || myOp == MIN || myOp == MAX);

}

bool BinaryOperatorTree::isNumberOperator()
{
    // è uno degli operatori ammessi
    return (myOp == PLUS || myOp == MINUS || myOp == MULT || myOp == DIV || myOp == MOD);

}

bool BinaryOperatorTree::isBoolOperator()
{
    return (myOp == OR || myOp == AND);
}

string BinaryOperatorTree::toString()
{
    return "(BinOp: " + leftChild->toString() + " " + myOpString + " " + rightChild->toString() + ")";
}


ExpressionTree* BinaryOperatorTree::getLeftChild()
{
    return leftChild;
}

TermTree* BinaryOperatorTree::getRightChild()
{
    return rightChild;
}

OPERATOR_TYPE BinaryOperatorTree::getOperator()
{
    return myOp;
}

