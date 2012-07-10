#ifndef BINARYOPERATORTREE_H
#define BINARYOPERATORTREE_H

#include <string>
#include "ExpressionTree.h"
#include "TermTree.h"

using namespace std;

enum OPERATOR_TYPE {PLUS, MINUS, MULT, DIV, MOD, OR, AND, EQUAL, NOTEQUAL, MINEQ, MAXEQ, MIN, MAX};

///
/// @brief Classe operatore binario
///
/// Questa classe rappresenta l'operatore binario con i suoi operandi
///
class BinaryOperatorTree : public ExpressionTree
{
    public:
        BinaryOperatorTree(string myOperator, ExpressionTree* left_operand, TermTree* right_operand);
        virtual ~BinaryOperatorTree();
        string toString();
        bool isBinaryOperatorTree();

        /// @return TRUE se è un operatore aritmetico, FALSE altrimenti
        bool isNumberOperator();

        /// @return TRUE se è un operatore su stringhe, FALSE altrimenti
        bool isStringOperator();

        /// @return TRUE se è un operatore booleano, FALSE altrimenti
        bool isBoolOperator();

        /// @return TRUE se è un operatore di confronto, FALSE altrimenti
        bool isCompareOperator();

        /// Restituisce l'espressioni del figlio sinistro
        ///
        /// @return puntatore ad espressione
        ExpressionTree* getLeftChild();
        /// Restituisce il termine del figlio destro
        ///
        /// @return puntatore a termine
        TermTree* getRightChild();

        /// Restituisce l'operatore
        ///
        /// @return puntatore a stringa
        OPERATOR_TYPE getOperator();
    protected:
    private:
        string myOpString;
        OPERATOR_TYPE myOp;
        ExpressionTree* leftChild;
        TermTree* rightChild;

};

#endif // BINARYOPERATORTREE_H
