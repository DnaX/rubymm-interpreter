#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <string>

using namespace std;

/// @brief Tipo enumerato dei tipi di Term
enum TERM_TYPE {BOOL, NUMBER, STRING, NIL, IDENTIFIER, BLOCK, FUNCTION_CALL};

///
/// @brief Classe espressione
///
/// Questa è la rappresentazione di ogni espressione
///
class ExpressionTree
{
    public:
        virtual ~ExpressionTree();
        /// @return TRUE se è un albero di espressioni, FALSE altrimenti
        bool isExpressionTree();
        /// @return TRUE se è un operatore binario, FALSE altrimenti
        virtual bool isBinaryOperatorTree();
        /// @return TRUE se è una lista di parametri, FALSE altrimenti
        virtual bool isParamExprTree();
        /// @return TRUE se è una chiamata a funzione, FALSE altrimenti
        virtual bool isFunctionCallTree();
        /// @return TRUE se è un term, FALSE altrimenti
        virtual bool isTermTree();
        /// @return TRUE se è un identiicatore, FALSE altrimenti
        virtual bool isIdentifierTree();
        /// @return TRUE se è un blocco, FALSE altrimenti
        virtual bool isBlockTree();
        /// @return TRUE se è un valore costante, FALSE altrimenti
        virtual bool isLiteralTree();
        /// @return TRUE se è una stringa, FALSE altrimenti
        virtual bool isStringTree();
        /// @return TRUE se è un numero, FALSE altrimenti
        virtual bool isNumberTree();
        /// @return TRUE se è un booleano, FALSE altrimenti
        virtual bool isBoolTree();
        /// @return TRUE se è un valore nullo, FALSE altrimenti
        virtual bool isNilTree();
        /// Restituisce una stringa rappresentativa del contenuto della classe
        virtual string toString();
    protected:
        ExpressionTree();
    private:
};

#endif // EXPRESSIONTREE_H
