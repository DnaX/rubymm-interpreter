#ifndef BOOLTREE_H
#define BOOLTREE_H

#include <string>
#include "LiteralTree.h"

///
/// @brief Classe tipo booleano
///
/// Questa classe rappresenta una variabile booleana
///
class BoolTree : public LiteralTree
{
    public:
        BoolTree(bool value);
        bool isBoolTree();
        string toString();
        /// @return il valore del booleano
        bool getValue();
        /// @return il valore del literal in formato testuale
        string strValue();
        LiteralTree& operator and (const LiteralTree& literal);
        LiteralTree& operator or (const LiteralTree& literal);
        LiteralTree& operator == (const LiteralTree& literal);
        LiteralTree& operator != (const LiteralTree& literal);
        LiteralTree& operator >= (const LiteralTree& literal);
        LiteralTree& operator <= (const LiteralTree& literal);
        LiteralTree& operator >  (const LiteralTree& literal);
        LiteralTree& operator <  (const LiteralTree& literal);
        /// @return il tipo del literal
        LITERAL_TYPE getType();
        virtual ~BoolTree();
    protected:
    private:
        bool myValue;
};

#endif // BOOLTREE_H
