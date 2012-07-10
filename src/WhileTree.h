#ifndef WHILETREE_H
#define WHILETREE_H

#include "Command.h"
#include "ExpressionTree.h"

///
/// @brief Classe comando ciclo condizionato
///
/// Questa classe rappresenta il comando di ciclo condizionato "while"
///
class WhileTree : public Command
{
    public:
        WhileTree(ExpressionTree* expr, Command* cmd);
        bool isWhileTree();
        void printCommand();
        /// Restituisce l'espressione contenuta nel comando
        ///
        /// @return l'espressione contenuta
        ExpressionTree* getExpression();
        /// Restituisce il comando o i comandi contenuti nel ciclo while
        ///
        /// @return il comando
        Command* getCommands();
        virtual ~WhileTree();
    protected:
    private:
        ExpressionTree* myExpr;
        Command* myCmd;
};

#endif // WHILETREE_H
