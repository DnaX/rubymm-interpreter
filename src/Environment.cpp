#include "Environment.h"
#include <iostream>

///
/// @file   Environment.cpp
///
/// @brief  Implementazione della classe Environment
///
///
///

Environment::Environment()
{
    envList env;

    i = env.begin();
}

void Environment::setIdentifier(IdentifierTree* id, LiteralTree* value)
{
    // cerco se la variabile è già stata asegnata
    for( envList::iterator iter = env.begin(); iter != env.end(); ++iter )
    {
        // Dereferenzazione per permettere il confronto tra classi
        if( *(*iter).first == *id )
        {
            // aggiorno la variabile col nuovo valore
            LiteralTree* old = env[(*iter).first];
            // cout << old->toString() << endl;
            env[(*iter).first] = value;
            delete old;
            old = NULL;
            return;
        }
    }
    // variabile non ancora assegnata, inserisco
    env[id] = value;
}

LiteralTree* Environment::getIdentifier(IdentifierTree* id)
{

    for( envList::iterator iter = env.begin(); iter != env.end(); ++iter )
    {
        // Dereferenzazione per permettere il confronto tra classi
        if( *(*iter).first == *id )
            return (*iter).second;

    }
    return NULL;
}

void Environment::clear()
{
    for( envList::iterator iter = env.begin(); iter != env.end(); ++iter )
    {
        delete env[(*iter).first];
        env[(*iter).first] = NULL;
    }

    env.clear();
}

bool Environment::isEmpty()
{
    if (env.size() > 0)
        return false;
    else
        return true;
}

void Environment::printEnvironment()
{
    envList::iterator iter;

    string buf = "";

    //buf += "\e[0;33m---------------------------------------------------------------------\n";
    buf += "\e[0;34mEnvironment:\e[0m ";

    for( iter = env.begin(); iter != env.end(); ++iter ) {
        buf += (*iter).first->getName() + " => " + (*iter).second->toString();
        if(iter != --env.end())
            buf += ", ";
    }

    if(iter == env.begin())
        buf += "<vuoto>";

    buf +=     "\n";
    //buf += "\e[0;33m---------------------------------------------------------------------\e[0m\n";

    cout << buf;
}

Environment::~Environment()
{
    //dtor
}
