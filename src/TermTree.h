#ifndef TERMTREE_H
#define TERMTREE_H

#include "ExpressionTree.h"

///
/// @brief Classe termine
///
/// Questa classe rappresenta un termine di una espressione
///
class TermTree : public ExpressionTree
{
    public:
        virtual ~TermTree();
        bool isTermTree();
    protected:
        TermTree();
    private:
};

#endif // TERMTREE_H
