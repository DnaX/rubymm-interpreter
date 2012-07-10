#ifndef STRINGTREE_H
#define STRINGTREE_H

#include <string>
#include <sstream>
#include "LiteralTree.h"

using namespace std;

///
/// @brief Classe tipo stringa
///
/// Questa classe rappresenta una variabile stringa
///
class StringTree : public LiteralTree
{
    public:
        StringTree(std::string value);
        bool isStringTree();
        virtual ~StringTree();
        string toString();
        /// @return il valore della stringa
        string getValue();
        /// @return il valore del literal in formato testuale
        string strValue();
        LiteralTree& operator + (const LiteralTree& literal);
        LiteralTree& operator == (const LiteralTree& literal);
        LiteralTree& operator != (const LiteralTree& literal);
        LiteralTree& operator >= (const LiteralTree& literal);
        LiteralTree& operator <= (const LiteralTree& literal);
        LiteralTree& operator > (const LiteralTree& literal);
        LiteralTree& operator < (const LiteralTree& literal);

        /// @return il tipo del literal
        LITERAL_TYPE getType();
    protected:
    private:
        string myValue;
};

#endif // STRINGTREE_H
