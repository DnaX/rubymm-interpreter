#ifndef NUMBERTREE_H
#define NUMBERTREE_H

#include <string>
#include <sstream>
#include "LiteralTree.h"
#include "BoolTree.h"

using namespace std;

///
/// @brief Classe tipo numerico
///
/// Questa classe rappresenta una variabile numerica
///
class NumberTree : public LiteralTree
{
    public:
        NumberTree(int value);
        bool isNumberTree();
        string toString();
        /// @return il valore numerico
        int getValue();
        /// @return il valore del literal in formato testuale
        string strValue();

        LiteralTree& operator+ (const LiteralTree& literal);
        LiteralTree& operator- (const LiteralTree& literal);
        LiteralTree& operator* (const LiteralTree& literal);
        LiteralTree& operator/ (const LiteralTree& literal);
        LiteralTree& operator% (const LiteralTree& literal);
        LiteralTree& operator == (const LiteralTree& literal);
        LiteralTree& operator != (const LiteralTree& literal);
        LiteralTree& operator >= (const LiteralTree& literal);
        LiteralTree& operator <= (const LiteralTree& literal);
        LiteralTree& operator > (const LiteralTree& literal);
        LiteralTree& operator < (const LiteralTree& literal);

        /// @return il yipo del literal
        LITERAL_TYPE getType();
        virtual ~NumberTree();
    protected:
    private:
        int myValue;
};

#endif // NUMBERTREE_H
