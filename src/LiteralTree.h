#ifndef LITERALTREE_H
#define LITERALTREE_H

#include "TermTree.h"

enum LITERAL_TYPE {TBOOL, TNUMBER, TSTRING, TNIL};

///
/// @brief Classe valore costante (literal)
///
/// Questa è la rappresentazione di ogni valore costrante
///
class LiteralTree : public TermTree
{
    public:
        bool isLiteralTree();

        virtual LiteralTree& operator + (const LiteralTree& literal);
        virtual LiteralTree& operator - (const LiteralTree& literal);
        virtual LiteralTree& operator * (const LiteralTree& literal);
        virtual LiteralTree& operator / (const LiteralTree& literal);
        virtual LiteralTree& operator % (const LiteralTree& literal);

        virtual LiteralTree& operator == (const LiteralTree& literal);
        virtual LiteralTree& operator != (const LiteralTree& literal);
        virtual LiteralTree& operator >= (const LiteralTree& literal);
        virtual LiteralTree& operator <= (const LiteralTree& literal);
        virtual LiteralTree& operator > (const LiteralTree& literal);
        virtual LiteralTree& operator < (const LiteralTree& literal);
        virtual LiteralTree& operator or (const LiteralTree& literal);
        virtual LiteralTree& operator and (const LiteralTree& literal);

        /// Restituisce una stringa con il contenuto del valore costante
        ///
        /// @return la stringa
        virtual string strValue();

        /// Restituisce il tipo del valore costante
        ///
        /// @return il tipo
        virtual LITERAL_TYPE getType();

        virtual ~LiteralTree();
    protected:
        LiteralTree();
    private:
};

#endif // LITERALTREE_H
