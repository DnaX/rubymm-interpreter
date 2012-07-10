#include "Checker.h"
#include <iostream>
#include <sstream>
#include "Command.h"

#include "ExpressionTree.h"
#include "BinaryOperatorTree.h"
#include "FunctionCallTree.h"
#include "DoubleCmdTree.h"
#include "BlockTree.h"
#include "AssignmentTree.h"


CheckingException::CheckingException(string err, ExpressionTree* expr, FunctionTree* func)
{
    error = err;
    myExpr = expr;
    myFunc = func;
}

void CheckingException::printError()
{
    cerr << "\e[1;31m==> Semantic error: \e[0mOn function " << myFunc->getName() << ": " << error.c_str() << endl;
    if(myExpr != NULL)
        cerr << "    near to: " << myExpr->toString() << endl;
}


Checker::Checker(const std::vector<FunctionTree*>* func, bool debug)
{

    functions = func;
    debugActive = debug;

    currentFuncIndex = 0;



    if(debugActive)
        cout << "\e[1;37m## Checker phase ##\e[0m" << endl << endl;

    for (unsigned int i=0; i<functions->size(); i++)
    {
        // mantiene l'indice della funzione corrente
        currentFuncIndex = i;

        // controllo la funzione
        checkFunction( (*functions)[i] );

    }
}

Checker::~Checker()
{

}

void Checker::checkFunction(FunctionTree* func) throw(CheckingException)
{

    // controllo se la funzione ha il nome uguale a quelle built-in
    if(func->getName() == "length" || func->getName() == "to_str" || func->getName() == "is_str")
        throw CheckingException("cannot redeclare built-in functions", NULL, func);


    // controllo che il numero dei paramentri della chiamata sia identico
    // al numero dei parametri nella dichiarazione della funzione.
    for (unsigned int c=0; c<currentFuncIndex; c++)
    {
        if( func->getName() == (*functions)[c]->getName() )
            throw CheckingException("function already declared", NULL, func);

    }

    // prendo il vettore di parametri
    vector<IdentifierTree*> *funcParams = func->getParams();

    // aggiungo gli identificatori della funzione alla mappa dei simboli
    for (unsigned int c=0; c<funcParams->size(); c++)
        currentIdentifiers.push_back( (*funcParams)[c] );

    // controllo i comandi
    checkCommand( func->getCommand() );

    // svuoto la mappa dei simboli
    currentIdentifiers.clear();

}

void Checker::checkCommand(Command* cmd) throw(CheckingException)
{

    // controlla se è un doppio comando
    if(cmd->isDoubleCmdTree())
    {
        // casi ricorsivi
        checkCommand ( ((DoubleCmdTree*) cmd)->getLeftChild());
        checkCommand ( ((DoubleCmdTree*) cmd)->getRightChild());

    }
    else
    {
        // caso base
        if(cmd->isAssignmentTree())
            currentIdentifiers.push_back( ((AssignmentTree*) cmd)->getIdentifier() );

        // caso base
        if(cmd->isGetsTree())
            currentIdentifiers.push_back((IdentifierTree*) cmd->getExpression() );

        // controlla l'espressione contenuta nel comando
        checkExpression(cmd->getExpression());

        if (cmd->isIfTree() || cmd->isWhileTree())
            // comandi innestati
            checkCommand(cmd->getCommands());

    }
}

TERM_TYPE Checker::checkExpression (ExpressionTree* tree) throw(CheckingException)
{
    // L'algoritmo ricorsivo di analisi semantica si basa su una visita pre-order

    // Caso base: il nodo è un TermTree
    if (tree->isTermTree())
    {
        if (tree->isBoolTree()) return BOOL;
        else if (tree->isStringTree()) return STRING;
        else if (tree->isNumberTree()) return NUMBER;
        else if (tree->isNilTree()) return NIL;

        // e` un identificatore
        else if (tree->isIdentifierTree())
        {

            // cerco se la variabile è già stata asegnata
            for (unsigned int i=0; i<currentIdentifiers.size(); i++)
            {
                // Dereferenzazione per permettere il confronto tra classi
                if( *currentIdentifiers[i] == *((IdentifierTree*)tree) )
                    return IDENTIFIER;
            }
            // fine del ciclo senza aver trovato niente, errore.
            throw CheckingException("identifier not assigned", tree, (*functions)[currentFuncIndex]);

        }
        // e` un blocco, faccio una ricorsione in esso
        else if (tree->isBlockTree())
            return checkExpression(((BlockTree*)tree)->getExpressions());

        // e' una chiamata a funzione, la controllo
        else if (tree->isFunctionCallTree())
        {
            // controllo i parametri
            checkFunctionCall(tree);
            return FUNCTION_CALL;
        }
        else throw CheckingException("unknown Term type", tree, (*functions)[currentFuncIndex]);
    }

    // Caso ricorsivo: il nodo è un operatore binario
    else if (tree->isBinaryOperatorTree())
    {
        TERM_TYPE left = checkExpression( ((BinaryOperatorTree*)(tree)) -> getLeftChild());
        TERM_TYPE right = checkExpression( ((BinaryOperatorTree*)(tree)) -> getRightChild());

        // ignora la diversità di tipo Identifier e Nil, verrà controllata in esecuzione
        if(left == IDENTIFIER || left == NIL || left == BLOCK || left == FUNCTION_CALL)
            left = right;
        if(right == IDENTIFIER || right == NIL || right == BLOCK || right == FUNCTION_CALL)
            right = left;

        if (left == right)
        {
            if (left == BOOL && ((BinaryOperatorTree*)(tree)) -> isBoolOperator() ) return BOOL;
            else if (left == NUMBER && ((BinaryOperatorTree*)(tree)) -> isNumberOperator()) return NUMBER;
            else if (left == STRING && ((BinaryOperatorTree*)(tree)) -> isStringOperator()) return STRING;
            // e` un operatore di comparazione, ritorno un tipo bool
            else if ( ((BinaryOperatorTree*)(tree)) -> isCompareOperator() ) return BOOL;
            else if (left == IDENTIFIER) return IDENTIFIER;
            else if (left == NIL) return NIL;
            else if (left == FUNCTION_CALL) return FUNCTION_CALL;
            else throw CheckingException("variable types are different from operator type", tree, (*functions)[currentFuncIndex]);
        }
        else throw CheckingException("different variable types applied to the same operator", tree, (*functions)[currentFuncIndex]);
    }

    // Errore: l'esecuzione non dovrebbe mai arrivare a questo punto.
    throw CheckingException("unknown error", tree, (*functions)[currentFuncIndex]);
}

void Checker::checkFunctionCall(ExpressionTree* tree) throw(CheckingException)
{
    // controllo la validita` dei paramentri e memorizzo il loro numero
    int num_params = checkParams( ((FunctionCallTree*) tree)->getParams() );

    if((*((FunctionCallTree*) tree)->getIdentifier() == string("length")) || (*((FunctionCallTree*) tree)->getIdentifier() == string("is_str")) || (*((FunctionCallTree*) tree)->getIdentifier() == string("to_str")))
    {
        if( num_params != 1)
        {
            // lancio una eccezione, numero dei paramentri sbagliato
            string errorStr;
            stringstream out;
            out << "function require 1 param(s) but " << num_params << " param(s) are given";

            errorStr = out.str();
            throw CheckingException(errorStr.c_str() , tree, (*functions)[currentFuncIndex]);
        }
        else
            return;
    }
    if(*((FunctionCallTree*) tree)->getIdentifier() == string("to_str"))
    {
        if( num_params != 1)
        {
            // lancio una eccezione, numero dei paramentri sbagliato
            string errorStr;
            stringstream out;
            out << "function require 1 param(s) but " << num_params << " param(s) are given";

            errorStr = out.str();
            throw CheckingException(errorStr.c_str() , tree, (*functions)[currentFuncIndex]);
        }
        else
            return;
    }
    // controllo che il numero dei paramentri della chiamata sia identico
    // al numero dei parametri nella dichiarazione della funzione.
    for (unsigned int i=0; i<functions->size(); i++)
    {

        // controllo che la funzione esista nel vettore
        if( (*functions)[i]->getName() == ((FunctionCallTree*) tree)->getIdentifier()->getName()  )
        {
            // numeri dei parametri diverso dalla dichiarazione
            if( (*functions)[i]->getParamsNum() != num_params)
            {
                // lancio una eccezione, numero dei paramentri sbagliato
                string errorStr;
                stringstream out;
                out << "function require "
                    << (*functions)[i]->getParamsNum()
                    << " param(s) but "
                    << num_params
                    << " param(s) are given";

                errorStr = out.str();
                throw CheckingException(errorStr.c_str() , tree, (*functions)[currentFuncIndex]);
            }
        }
        else if( i == functions->size() )
            // La funzione non esiste
            throw CheckingException("function " + ((FunctionCallTree*) tree)->getIdentifier()->getName() + " not declared" , tree, (*functions)[currentFuncIndex]);
    }
}

int Checker::checkParams(ExpressionTree* param) throw(CheckingException)
{
    // controllo la correttezza delle espressioni di ogni parametro della
    // chiamata a funzione e nel frttempo lo numero
    if(param != NULL && param->isParamExprTree())
    {
        // figlio destro -> ricorsione
        return 1 + checkParams( ((ParamExprTree*)param)->getRightChild() );
        // figlio sinistro -> caso base
        checkExpression( ((ParamExprTree*)param)->getLeftChild() );
    }
    return 0;
}
