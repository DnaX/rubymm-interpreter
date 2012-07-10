#ifndef EXECUTE_H
#define EXECUTE_H

#include <vector>
#include "FunctionTree.h"
#include "ParamExprTree.h"

///
/// @file   Execute.h
///
/// @brief  Header della classe Execute e ExecuteException
///
///
///

///
/// @brief Classe per le eccezioni dell'Execute
///
/// Gestisce le eccezioni lanciate dall'Execute
///
class ExecuteException
{
    public:
        ///
        /// Costruttore della classe che gestisce le eccezioni dell'Execute
        ///
        /// @param err una stringa del massaggio d'errore
        /// @param expr l'espressione dove si verifica l'errore
        ///
        ExecuteException(string err, ExpressionTree* expr);

        ///
        /// Costruttore della classe che gestisce le eccezioni dell'Execute
        ///
        /// @param err una stringa del massaggio d'errore
        ///
        ExecuteException(string err);

        /// Stampa a video il tipo di errore incontrato con le opportune formattazioni
        void printError();
    protected:
    private:
        string error;
        ExpressionTree* myExpr;
};

///
/// @brief Classe Execute che esegue il codice
///
/// Esegue il codice partendo dalla funzione main
///
class Execute
{
    public:
        ///
        /// Costruttore dell'Execute
        ///
        /// @param functions il vettore di funzioni
        /// @param debug TRUE per attivare i messaggi di debug, FALSE altrimenti
        ///
        Execute(const std::vector<FunctionTree*>* functions, bool debug) throw(ExecuteException);
        ///
        /// Restituisce il ritorno della funzione principale
        ///
        /// @return numero intero del ritorno
        ///
        int getReturnVal();
        virtual ~Execute();
    protected:
    private:
        /// valore di ritorno del main
        int returnVal;
        /// Indica se bisogna stampare info di debug
        bool debugActive;
        /// puntatore al vettore delle funzioni
        const std::vector<FunctionTree*>* functions;

        /// Esegue una funzione
        LiteralTree* ExecuteFunction(FunctionTree* function, ParamExprTree* params, int level);
        /// Esegue un comando
        LiteralTree* ExecuteCommand(Command* command, Environment* env, int level);
        /// Valuta una espressione
        LiteralTree* EvaluateExpression(ExpressionTree* expr, Environment* env, int level);
        /// Valuta i parametri di una funzione restituendo una nuova lista da parametri
        /// costituiti da soli literali
        ParamExprTree* EvaluateFunctionParams(ExpressionTree* param, Environment* env, int level);
        /// riempe l'ambiente di esecuzione con i parametri attuali della funzione chiamata
        void fillEnvironment(Environment* env, vector<IdentifierTree*>*identifiers, int iIndex, ExpressionTree* params);

        /// built-in function: length()
        LiteralTree* functionLength(ParamExprTree* params);
        /// built-in function: to_str()
        LiteralTree* functionToStr( ParamExprTree* params);
        /// built-in function: is_str()
        LiteralTree* functionIsStr( ParamExprTree* params);
};

#endif // EXECUTE_H
