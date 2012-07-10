#ifndef NILTREE_H
#define NILTREE_H

#include <string>
#include "LiteralTree.h"

using namespace std;

///
/// @brief Classe tipo nullo
///
/// Questa classe rappresenta una variabile nulla (nil)
///
class NilTree : public LiteralTree
{
    public:
        NilTree();
        virtual ~NilTree();
        bool isNilTree();
        /// @return il valore del literal in formato testuale
        string strValue();
        string toString();
        /// @return il tipo del literal
        LITERAL_TYPE getType();
    protected:
    private:
};

#endif // NILTREE_H
