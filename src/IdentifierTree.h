#ifndef IDENTIFIERTREE_H
#define IDENTIFIERTREE_H

#include "TermTree.h"
#include <string>

using namespace std;

///
/// @brief Classe identificatore
///
/// Questa classe rappresenta un identificatore di variabile o funzione
///
class IdentifierTree : public TermTree
{
    public:
        IdentifierTree(string name);
        bool isIdentifierTree();
        /// @return il nome dell'identificatore
        string getName();
        string toString();
        bool operator == (const IdentifierTree& identifier);
        bool operator == (const string& strIdentifier);
        virtual ~IdentifierTree();
    protected:
    private:
        string myName;
};

#endif // IDENTIFIERTREE_H
