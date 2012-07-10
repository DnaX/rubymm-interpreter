#ifndef PUTSTREE_H
#define PUTSTREE_H

#include "Command.h"
#include "ExpressionTree.h"

///
/// @brief Classe comando stampa a video
///
/// Questa classe rappresenta il comando di stampa a video "puts"
///
class PutsTree : public Command
{
    public:
        PutsTree(ExpressionTree* expr);
        void printCommand();
        bool isPutsTree();
        /// Restituisce l'espressione contenuta nel comando
        ///
        /// @return l'espressione contenuta
        ExpressionTree* getExpression();
        virtual ~PutsTree();
    protected:
    private:
        ExpressionTree* myExpr;
};

#endif // PUTSTREE_H
