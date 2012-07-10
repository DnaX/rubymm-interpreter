#ifndef IFTREE_H
#define IFTREE_H

#include "Command.h"
#include "ExpressionTree.h"
#include "DoubleCmdTree.h"

///
/// @brief Classe comando condizionale
///
/// Questa classe rappresenta il comando condizionale IfElse
///
class IfTree : public Command
{
    public:
        IfTree(ExpressionTree* expr, DoubleCmdTree* doublecmd);
        bool isIfTree();
        void printCommand();
        /// Restituisce l'espressione da valutare nel comando condizionale
        ///
        /// @return l'espressione da valutare
        ExpressionTree* getExpression();
        /// Restituisce i comandi TRUE a FALSE del comando If
        ///
        /// @return l'oggetto DoubleCmdTree con i comandi
        Command* getCommands();
        virtual ~IfTree();
    protected:
    private:
        ExpressionTree* myExpr;
        DoubleCmdTree* myCmd;
};

#endif // IFTREE_H
