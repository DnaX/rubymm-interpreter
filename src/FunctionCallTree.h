#ifndef FUNCTIONCALLTREE_H
#define FUNCTIONCALLTREE_H

#include <string>
#include "ExpressionTree.h"
#include "IdentifierTree.h"
#include "ParamExprTree.h"

using namespace std;

///
/// @brief Classe chiamata a funzione
///
/// Questa classe rappresenta una chiamata a funzione
///
class FunctionCallTree : public TermTree
{
    public:
        FunctionCallTree(IdentifierTree* id, ParamExprTree* parameters);
        bool isFunctionCallTree();
        string toString();
        /// @return i parametri della chiamata di funzione
        ParamExprTree* getParams();
        /// @return l'identificatore della chiamata di funzione
        IdentifierTree* getIdentifier();
        virtual ~FunctionCallTree();
    protected:
    private:
        IdentifierTree* myId;
        ParamExprTree* myParam;
};

#endif // FUNCTIONCALLTREE_H
