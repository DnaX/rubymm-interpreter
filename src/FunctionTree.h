#ifndef FUNCTIONTREE_H
#define FUNCTIONTREE_H

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include "Command.h"
#include "IdentifierTree.h"
#include "Environment.h"

using namespace std;

///
/// @brief Classe funzione
///
/// Questa classe rappresenta una funzione
///
class FunctionTree
{
    public:
        FunctionTree(const std::string& name, const std::vector<IdentifierTree*>& parameters, Command* command) throw (string);

        /// Stampa a video il contenuto della funzione
        void printFunction();

        /// @return il nome della funzione
        string getName();

        /// @return i comandi presenti nella funzione
        Command* getCommand();

        /// @return il numero dei parametri accettati
        int getParamsNum();

        /// @return un vettore con gli identificatori dei parametri
        vector<IdentifierTree*>* getParams();

        virtual ~FunctionTree();
    protected:
    private:
        string myName;
        vector<IdentifierTree*> param;
        Command* cmd;
};

#endif // FUNCTIONTREE_H
