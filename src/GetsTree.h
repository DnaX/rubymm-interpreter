#ifndef GETSTREE_H
#define GETSTREE_H

#include "Command.h"
#include "IdentifierTree.h"

///
/// @brief Classe comando prendi dati da tastiera
///
/// Questa classe rappresenta il comando per ricevere input da tastiera "gets"
///
class GetsTree : public Command
{
    public:
        GetsTree(IdentifierTree* id);
        void printCommand();
        bool isGetsTree();
        /// Restituisce l'identificatore specificato dove
        /// andranno metti i dati da tastiera
        ///
        /// @return l'espressione contenuta
        ExpressionTree* getExpression();
        virtual ~GetsTree();
    protected:
    private:
        IdentifierTree* myId;
};

#endif // GETSTREE_H
