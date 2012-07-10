#ifndef ASSIGNMENTTREE_H
#define ASSIGNMENTTREE_H

#include "Command.h"
#include "IdentifierTree.h"

///
/// @brief Classe assegnamento
///
/// Questa classe rappresenta il comando assegnamento
///
class AssignmentTree : public Command
{
    public:
        AssignmentTree(IdentifierTree* id, ExpressionTree* expr);
        bool isAssignmentTree();
        void printCommand();
        virtual ~AssignmentTree();
        /// Restituisce l'espressione
        ///
        /// @return puntatore ad espressione
        ExpressionTree* getExpression();

        /// Restituisce l'identificatore
        ///
        /// @return puntatore ad identificatore
        IdentifierTree* getIdentifier();

    protected:
    private:
        IdentifierTree* myId;
        ExpressionTree* myExpr;
};

#endif // ASSIGNMENTTREE_H
