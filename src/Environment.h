#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "IdentifierTree.h"
#include "LiteralTree.h"

#include <map>

///
/// @file   Environment.h
///
/// @brief  Header della classe Environment
///
///

///
/// Typedef per la mappa di variabili
///
typedef map <IdentifierTree*, LiteralTree*> envList;

///
/// @brief L'ambiente di esecuzione
///
/// Ambiente di esecuzione con la memorizzazione di tutte
/// le variabili e relativi valori.
///
class Environment
{
    public:
        Environment();

        /// Imposta una variabile nell'ambiente di esecuzione
        ///
        /// @param identifier il nome della variabile
        /// @param literal un puntatore al valore della variabile
        ///
        void setIdentifier(IdentifierTree* id, LiteralTree* value);

        /// Restituisce una variabile dell'ambiente di esecuzione
        ///
        /// @param identifier il nome della variabile
        ///
        /// @return il literale trovato, un puntatore nullo altrimenti (NULL)
        LiteralTree* getIdentifier(IdentifierTree* id);

        /// Svuota l'ambiente di esecuzione
        void clear();

        /// @return true se l'ambiente e` vuoto, false altrimenti
        bool isEmpty();

        /// Stampa il contenuto dell'ambiente di esecuzione opportunamente formattato
        void printEnvironment();

        virtual ~Environment();
    protected:
    private:
        envList env;
        envList::iterator i;
};

#endif // ENVIRONMENT_H
