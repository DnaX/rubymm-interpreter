#ifndef BLOCKTREE_H
#define BLOCKTREE_H

#include <string>
#include "TermTree.h"

using namespace std;

///
/// @brief Classe blocco
///
/// Questa classe rappresenta un blocco di espressioni
///
class BlockTree : public TermTree
{
    public:
        BlockTree(ExpressionTree* expr);
        bool isBlockTree();
        string toString();
        /// Restituisce l'espressioni contenute nel blocco
        ///
        /// @return puntatore a classe ExpressionTree
        ExpressionTree* getExpressions();
        virtual ~BlockTree();
    protected:
    private:
        ExpressionTree* myExpr;
};

#endif // BLOCKTREE_H
