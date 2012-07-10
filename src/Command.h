#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>

#include "ExpressionTree.h"

///
/// @file   Command.h
///
/// @brief  Header della classe Command
///
///
///

using namespace std;

///
/// @brief Classe Comando
///
/// Questa è la rappresentazione di ogni comando
///
class Command
{
    public:
        virtual ~Command();
        /// @return TRUE se è un assegnamento, FALSE altrimenti
        virtual bool isAssignmentTree();
        /// @return TRUE se è un ritorno di funzione, FALSE altrimenti
        virtual bool isReturnTree();
        /// @return TRUE se è una condizione, FALSE altrimenti
        virtual bool isIfTree();
        /// @return TRUE se è un ciclo, FALSE altrimenti
        virtual bool isWhileTree();
        /// @return TRUE se è un comando di stampa a video, FALSE altrimenti
        virtual bool isPutsTree();
        /// @return TRUE se è un comando di input da tastiera, FALSE altrimenti
        virtual bool isGetsTree();
        /// @return TRUE se è un doppio comando, FALSE altrimenti
        virtual bool isDoubleCmdTree();
        /// Stampa il contenuto del comando con le opportune formattazioni
        virtual void printCommand();
        /// @return l'espressione contenuta nel comando
        virtual ExpressionTree* getExpression();
        /// @return l'eventuale comando innestato
        virtual Command* getCommands();
    protected:
        Command();
    private:
};

#endif // COMMAND_H
