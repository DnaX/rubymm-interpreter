#ifndef PARAMEXPRTREE_H
#define PARAMEXPRTREE_H

#include <string>
#include <sstream>
#include "ExpressionTree.h"

using namespace std;

///
/// @brief Classe ParamExprTree
///
/// Questa è la rappresentazione dell'elenco di parametri di ogni chiamata di funzione
/// implementata come un albero ricorsivo di espressioni
///
class ParamExprTree : public ExpressionTree
{
    public:
        ParamExprTree(ExpressionTree* expr);

        /// @return TRUE se è un albero di parametri, FALSE altrimenti
        bool isParamExprTree();

        /// @param otherExpr Una espressione da aggiungere all'elenco di parametri
        void addOtherExpr(ParamExprTree* otherExpr);

        /// @return l'espressione del figlio sinistro
        ExpressionTree* getLeftChild();
        /// @return l'espressione del figlio destro
        ExpressionTree* getRightChild();

        string toString();
        virtual ~ParamExprTree();
    protected:
    private:
        ExpressionTree* myExpr;     // figlio sinistro
        ParamExprTree* myOtherExpr; // figlio destro
};

#endif // PARAMEXPRTREE_H
