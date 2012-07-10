#include "FunctionTree.h"

FunctionTree::FunctionTree(const std::string& name, const std::vector<IdentifierTree*>& parameters, Command* command) throw (string)
{
    myName = name;
    param = parameters;
    cmd = command;

    // controlla che tutti gli identificatori siano diversi
    set<string> mySet;
    vector<IdentifierTree*>::iterator it;
    vector<IdentifierTree*>::iterator end = param.end();
    for (it=param.begin(); it < end; it++)
        mySet.insert((*it)->getName());
    if (param.size() != mySet.size())
    {
        throw "parameters names of function " + myName + " must be different.";
    }
}

FunctionTree::~FunctionTree()
{
    delete cmd;
    cmd = NULL;
}

void FunctionTree::printFunction()
{
    cout << "\e[0;37m" << "==> " << "\e[0;32m" << "Albero sintattico della funzione \"" << "\e[1;32m" << myName << "\e[0;32m" <<  "\"" << endl;
    cout << "    Lista degli identificatori (parametri):" << "\e[1;32m";
    if (param.size() == 0)
        cout << "  < vuota >";
    else
        for (unsigned int i=0; i<param.size(); i++)
            cout << " " << param[i]->getName();
    cout << endl;
    cout << "\e[0;32m" << "    Lista dei comandi:\e[0m" << endl;
    cmd->printCommand();
    cout << endl;
}

string FunctionTree::getName()
{
    return myName;
}

Command* FunctionTree::getCommand()
{
    return cmd;
}

Environment* FunctionTree::getEnvironment()
{
    return &env;
}

int FunctionTree::getParamsNum()
{
    return param.size();
}

vector<IdentifierTree*>* FunctionTree::getParams()
{
    return &param;
}
