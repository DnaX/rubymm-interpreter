#ifndef PARSER_H
#define PARSER_H

#include <cstdlib>
#include <exception>
#include <vector>
#include <string>
#include <FlexLexer.h>
#include "analyzer.hh"
#include "FunctionTree.h"
#include "token.hh"
#include <typeinfo>

#include "AssignmentTree.h"
#include "BinaryOperatorTree.h"
#include "BlockTree.h"
#include "BoolTree.h"
#include "Command.h"
#include "DoubleCmdTree.h"
#include "ExpressionTree.h"
#include "FunctionCallTree.h"
#include "IdentifierTree.h"
#include "IfTree.h"
#include "LiteralTree.h"
#include "NilTree.h"
#include "NumberTree.h"
#include "ParamExprTree.h"
#include "PutsTree.h"
#include "GetsTree.h"
#include "ReturnTree.h"
#include "StringTree.h"
#include "TermTree.h"
#include "WhileTree.h"


using namespace std;

///
/// @file   Parser.h
///
/// @brief  Header della classe Parser e ParsingException
///
///
///

///
/// @brief Classe per le eccezioni del Parser
///
/// Gestisce le eccezioni lanciate dal Parser
///
class ParsingException
{
    public:
        ///
        /// Costruttore della classe che gestisce le eccezioni del Parser
        ///
        /// @param tokenError il token responsabile dell'errore
        ///
        ParsingException(Token* tokenError);
        void printError();
    protected:
    private:
        Token* myTokenError;
};

///
/// @brief Il Parser
///
/// Costruira` l'albero in memoria e controllera` per eventuali errori sintattici
///
class Parser
{
    public:
        ///
        /// Costruttore del Parser
        ///
        /// @param start L'inizio dei token
        /// @param start La fine dei token
        /// @param debug TRUE per attivare i messaggi di debug, FALSE altrimenti
        ///
        Parser(const TokenList::iterator start, const TokenList::iterator end, bool debug);
        ///
        /// Restituisce le funzioni analizzate
        ///
        /// @return il vettore delle funzioni
        ///
        vector<FunctionTree*> getFunctions();
        virtual ~Parser();
    protected:
    private:
        // variabili interne
        vector<FunctionTree*> functions;
        TokenList::iterator fine;
        TokenList::iterator myIterator;
        bool debugActive;

        // riconoscimento di una funzione
        FunctionTree* recognizeFunction(TokenList::iterator& myIterator) throw (ParsingException);
        vector<IdentifierTree*> recognizeParams(TokenList::iterator& myIterator) throw (ParsingException);

        // riconoscimento di un comando
        Command* recognizeCommand(TokenList::iterator& myIterator) throw (ParsingException);
        AssignmentTree* recognizeAssignment(TokenList::iterator& myIterator) throw (ParsingException);
        ReturnTree* recognizeReturn(TokenList::iterator& myIterator) throw (ParsingException);
        IfTree* recognizeIf(TokenList::iterator& myIterator) throw (ParsingException);
        WhileTree* recognizeWhile(TokenList::iterator& myIterator) throw (ParsingException);
        PutsTree* recognizePuts(TokenList::iterator& myIterator) throw (ParsingException);
        GetsTree* recognizeGets(TokenList::iterator& myIterator) throw (ParsingException);

        // riconoscimento di una espressione
        ExpressionTree* recognizeExpression(TokenList::iterator& myIterator, bool onlyTermTree = false) throw (ParsingException);

};

#endif // PARSER_H
