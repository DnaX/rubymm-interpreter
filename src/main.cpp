// C Library e C++ STL
#include <iostream>
#include <vector>
#include <fstream>

// Tokenizer (Analisi lessicale)
#include <FlexLexer.h>
#include "analyzer.hh"

// Parser (Analisi sintattica)
#include "Parser.h"
#include "Checker.h"
#include "Execute.h"
#include "FunctionTree.h"

#define PROGRAM_NAME "RmmInterpreter"
#define PROGRAM_VERSION "1.0"

using namespace std;

void print_help()
{
    cout << "Usage:" << endl;
    cout << "  " << PROGRAM_NAME << " [OPTION...] [FILE] - A interpreter for Rubymm language" << endl << endl;

    cout << "Help Options:" << endl;
    cout << "  -?, --help        Show help options" << endl << endl;

    cout << "Application Options:" << endl;
    cout << "      --printT      Print the tree structure (with colored output)" << endl;
    cout << "      --absDebug    Allow debug messages" << endl;
    cout << "  -c, --copyright   Show copyright info" << endl;
    cout << "  -v, --version     Show version and exit" << endl;
}

void print_version()
{
    cout << PROGRAM_NAME " " PROGRAM_VERSION << endl;
}


void print_copyright()
{
    cout << PROGRAM_NAME " - Copyright (C) 2009 Francesco Galgani, Napolitano Daniele" << endl;
    cout << PROGRAM_NAME " is free software licensed with GPLv3" << endl;
}

int main(int argc, char** argv)
{
    bool printT = false;
    bool absDebug = false;
    string temp;
    string fileToOpen = "";

    // analizza i parametri
    for (int i = 1; i < argc; i++)
    {
        temp = argv[i];

        if ( temp == "--printT")
            printT = true;
        else if ( temp == "--absDebug")
            absDebug = true;
        else if ( temp == "--help" || temp == "-?")
        {
            print_help();
            return 0;
        }
        else if ( temp == "--copyright" || temp == "-c")
        {
            print_copyright();
            return 0;
        }
        else if ( temp == "--version" || temp == "-v")
        {
            print_version();
            return 0;
        }
        else if (argv[i][0] != '-')
            fileToOpen = temp;

    }

    // controlla che sia stato specificato un file
    if(fileToOpen.length() == 0)
    {
        print_help();
        return -2;
    }

    // apre il file
    ifstream file(fileToOpen.c_str());
    if (!file)
    {
        cerr << "Could not open file " << fileToOpen << endl;
        return -2;
    }


    // esamina il codice sorgente, crea la TokenList e iteratori
    Analyzer lexer;
    TokenList tl;
    TokenList::iterator begin;
    TokenList::iterator end;

    try
    {
        lexer = Analyzer(&file, &cerr);
        while (lexer.yylex() != 0);
        tl = lexer.getTokenList();
        begin = tl.begin();
        end = tl.end();
    }
    catch (ParserError err)
    {
        cerr << err << endl;
        return -3;
    }

    // passa gli iteratori della TokenList a Parser e
    // ottiene gli alberi sintattici corrispondenti alla funzioni
    vector<FunctionTree*> functions;

    try
    {
        Parser myCode = Parser (begin, end, absDebug);
        functions = myCode.getFunctions();
    }
    catch (ParsingException err)
    {
        err.printError();
        return -4;
    }


    if(printT || absDebug)
    {
        // stampa gli alberi sintattici
        for (unsigned int i=0; i<functions.size(); i++)
            functions[i]->printFunction();
    }

    try
    {
        Checker check = Checker(&functions, absDebug);
    }
    catch (CheckingException err)
    {
        err.printError();
        return -5;
    }

    Execute* exec;

    try
    {
        exec = new Execute(&functions, absDebug);
    }
    catch (ExecuteException err)
    {
        err.printError();
        return -6;
    }

    // ritorno il valore di ritorno della funzione eseguita (il main)
    return exec->getReturnVal();
}
