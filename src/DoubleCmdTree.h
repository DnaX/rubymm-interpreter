#ifndef DOUBLECMDTREE_H
#define DOUBLECMDTREE_H

#include "Command.h"

///
/// @brief Classe dippo comando
///
/// Questa classe rappresenta due comandi
///
class DoubleCmdTree : public Command
{
    public:
        DoubleCmdTree(Command* left, Command* right);
        bool isDoubleCmdTree();
        /// @return il comando del figlio sinistro
        Command* getLeftChild();
        /// @return il comando del figlio destro
        Command* getRightChild();
        void printCommand();
        virtual ~DoubleCmdTree();
    protected:
    private:
        Command* leftChild;
        Command* rightChild;
};

#endif // DOUBLECMDTREE_H
