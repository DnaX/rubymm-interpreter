#ifndef RETURNTREE_H
#define RETURNTREE_H

#include "Command.h"
#include "ExpressionTree.h"

///
/// @brief Classe comando ritorno a funzione
///
/// Questa classe rappresenta il comando di ritorno a funzione "return"
///
class ReturnTree : public Command
{
    public:
        ReturnTree(ExpressionTree* expr);
        bool isReturnTree();
        void printCommand();
        /// Restituisce l'espressione contenuta nel comando
        ///
        /// @return l'espressione contenuta
        ExpressionTree* getExpression();
        virtual ~ReturnTree();
    protected:
    private:
        ExpressionTree* myExpr;
};

#endif // RETURNTREE_H
