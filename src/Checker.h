#ifndef CHECKER_H
#define CHECKER_H

#include <vector>
#include <string>
#include "FunctionTree.h"
#include "Command.h"

///
/// @file   Checker.h
///
/// @brief  Header della classe Checker e CheckingException
///
///
///

///
/// @brief Classe per le eccezioni del Checker
///
/// Gestisce le eccezioni lanciate del Checker
///
class CheckingException
{
    public:
        ///
        /// Costruttore della classe che gestisce le eccezioni del Checker
        ///
        /// @param err una stringa del massaggio d'errore
        /// @param expr l'espressione dove si verifica l'errore
        /// @param func la funzione dove si verifica l'errore
        ///
        CheckingException(string err, ExpressionTree* expr, FunctionTree* func);

        /// Stampa a video il tipo di errore incontrato con le opportune formattazioni
        void printError();
    protected:
    private:
        string error;
        ExpressionTree* myExpr;
        FunctionTree* myFunc;
};

///
/// @brief Il Checker
///
/// Controllera` tutto l'albero alla ricerca  di errori semantici
///
class Checker
{
    public:
        /// Costruttore di Checker
        ///
        /// @param functions il vettore delle funzioni
        /// @param debug TRUE per attivare i messaggi di debug, FALSE altrimenti
        ///
        Checker(const std::vector<FunctionTree*>* functions, bool debug);
        virtual ~Checker();
    protected:
    private:
        /// puntatore al vettore delle funzioni
        const std::vector<FunctionTree*>* functions;
        /// indice della funzione corrente (per eccezioni)
        unsigned int currentFuncIndex;
        /// vettore con il vettore dei simboli (solo per controllo di esistenza)
        std::vector<IdentifierTree*> currentIdentifiers;
        /// Indica se bisogna stampare info di debug
        bool debugActive;

        /// controlla la correttezza di ogni funzione
        void checkFunction(FunctionTree* func) throw(CheckingException);
        /// controlla la correttezza di ogni comando
        void checkCommand(Command* cmd) throw(CheckingException);
        /// controlla la correttezza di ogni espressione
        /// @return il tipo dell'espressione
        TERM_TYPE checkExpression (ExpressionTree* tree) throw(CheckingException);
        /// controlla la correttezza di ogni chiamata a funzione
        void checkFunctionCall(ExpressionTree* tree) throw(CheckingException);
        /// controlla la correttezza di ogni parametro della chiamata a funzione
        /// @return il numero di parametri analizzati
        int checkParams(ExpressionTree* param) throw(CheckingException);
};

#endif // CHECKER_H
