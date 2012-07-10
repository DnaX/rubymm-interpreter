#include "Execute.h"

#include "AssignmentTree.h"
#include "DoubleCmdTree.h"
#include "NumberTree.h"
#include "StringTree.h"
#include "BinaryOperatorTree.h"
#include "NilTree.h"
#include "BlockTree.h"
#include "BoolTree.h"
#include "FunctionCallTree.h"
#include "GetsTree.h"

#include <cstdlib>
#include <sstream>

ExecuteException::ExecuteException(string err, ExpressionTree* expr)
{
    error = err;
    myExpr = expr;
}

ExecuteException::ExecuteException(string err)
{
    error = err;
    myExpr = NULL;
}

void ExecuteException::printError()
{
    cerr << "\e[1;31m==> Execution error: \e[0m" << error.c_str() << endl;

    if(myExpr != NULL)
        cerr << "    near to: " << myExpr->toString() << endl;
}

Execute::Execute(const std::vector<FunctionTree*>* func, bool debug) throw(ExecuteException)
{
    functions = func;
    returnVal = 0;
    debugActive = debug;
    LiteralTree* literal;

    if(debugActive)
        cout << "\e[1;37m## Execute phase ##\e[0m" << endl << endl;

    bool mainFound = false;
    // cerco la funzione main
    for (unsigned int i=0; i<functions->size(); i++)
    {

        if( (*functions)[i]->getName().compare("main") == 0  )
        {
            mainFound = true;
            literal = ExecuteFunction( (*functions)[i], NULL, 1);

            // se il tipo ritornato è un numero ne memorizzo il valore
            if(literal->isNumberTree())
                returnVal = ((NumberTree*)literal)->getValue();

            break;
        }
    }
    // main non trovato, errore
    if(mainFound == false)
        throw ExecuteException("function main not found");
}

int Execute::getReturnVal()
{
    return returnVal;
}

Execute::~Execute()
{
    //dtor
}

LiteralTree* Execute::ExecuteFunction(FunctionTree* function, ParamExprTree* params, int level)
{
    // function->getEnvironment()->clear();
    if (!(function->getEnvironment()->isEmpty()))
        throw ExecuteException("function recursion is not supported yet.");


    if(debugActive){
        for(int i=0;i<level;i++)
            cout << "=> ";
        cout << "\e[0;33mExec function: \e[0m" << function->getName() << endl;
    }

    // riempo l'ambiente di esecuzione con i paramentri attuali
    fillEnvironment(function->getEnvironment(), function->getParams(), 0, params);

    if(debugActive)
        function->getEnvironment()->printEnvironment();

    // eseguo i comandi
    LiteralTree* ret = ExecuteCommand(function->getCommand(), function->getEnvironment(), level + 1 );

    // se il ritorno del comando è nullo ritorno un valore NilTree
    if(ret == NULL) ret = new NilTree();

    if(debugActive)
    {
        for(int i=0;i<level;i++)
            cout << "<= ";
        cout << "\e[0;33mFunction " << function->getName() << " end with return: \e[0m" << ret->toString() << endl;
    }

    // Il return svuota l'attuale ambiente di esecuzione
    function->getEnvironment()->clear();

    delete params;
    params = NULL;

    return ret;
}

void Execute::fillEnvironment(Environment* env, vector<IdentifierTree*>*identifiers, int iIndex, ExpressionTree* param)
{
    if(param == NULL) return;

    if(param->isParamExprTree())
    {
        // figlio destro -> ricorsione
        fillEnvironment( env, identifiers, iIndex + 1, ((ParamExprTree*)param)->getRightChild() );

        // figlio sinistro -> caso base
        env->setIdentifier((*identifiers)[iIndex], EvaluateExpression(((ParamExprTree*)param)->getLeftChild(), env, 0));
    }

    return;
}

ParamExprTree* Execute::EvaluateFunctionParams(ExpressionTree* param, Environment* env, int level)
{
    if(param == NULL) return NULL;

    // controllo necessario?
    if(param->isParamExprTree())
    {
        ParamExprTree* params;

        // figlio sinistro -> caso base
        params = new ParamExprTree (EvaluateExpression(((ParamExprTree*)param)->getLeftChild(), env, level));

        // figlio destro -> ricorsione
        params->addOtherExpr( EvaluateFunctionParams( ((ParamExprTree*)param)->getRightChild(), env, level));

        return params;

    }

    // necessario?
    return NULL;
}


LiteralTree* Execute::ExecuteCommand(Command* cmd, Environment* env, int level)
{

    LiteralTree* ret = NULL;

    if(cmd->isDoubleCmdTree())
    {
        // casi ricorsivi
        if( (ret = ExecuteCommand ( ((DoubleCmdTree*) cmd)->getLeftChild(), env, level) ) == NULL)
            // esegue l'albero destro solo se nel precedente non è stato ritornato nulla
            ret = ExecuteCommand ( ((DoubleCmdTree*) cmd)->getRightChild(), env, level);
    }
    else
    {
        if(debugActive)
        {
            for(int i=0;i<level;i++)
                cout << "-- ";
        }

        // casi base
        if(cmd->isAssignmentTree())
        {
            LiteralTree* literal;

            // if(debugActive)
            //        env->printEnvironment();

            literal = EvaluateExpression( cmd->getExpression(), env, level);


            env->setIdentifier( ((AssignmentTree*)cmd)->getIdentifier(), literal);

            if(debugActive)
            {
                cout << "\e[0;33mExec assignment: \e[0m" << ((AssignmentTree*)cmd)->getIdentifier()->toString() << " => " << literal->toString() << endl;
                env->printEnvironment();
            }
        }
        else if(cmd->isIfTree())
        {
            LiteralTree* literal;

            if(debugActive)
                cout << "\e[0;33mExec If: condition \e[0m" << cmd->getExpression()->toString() << " => ";


            literal = EvaluateExpression( cmd->getExpression(), env, level );

            if(debugActive)
                cout << literal->toString() << endl;

            if(literal->isBoolTree())
            {

                if( ((BoolTree*)literal)->getValue() )
                    // comandi sezione TRUE
                    ret = ExecuteCommand( ((DoubleCmdTree*)cmd->getCommands())->getLeftChild(), env, level+1);
                else
                    // comandi sezione FALSE
                    ret = ExecuteCommand( ((DoubleCmdTree*)cmd->getCommands())->getRightChild(), env, level+1);

                delete literal;
                literal = NULL;
            }
            else
                throw ExecuteException("unknown condition expression type", literal);
        }
        else if(cmd->isWhileTree())
        {
            LiteralTree* literal = NULL;

            if(debugActive)
            {
                for(int i=0;i<level;i++)
                        cout << "\e[D\e[D\e[D";
                for(int i=0;i<level;i++)
                        cout << "-> ";
                cout << "\e[0;33mExec While: condition \e[0m" << cmd->getExpression()->toString() << endl;
            }

            // controlla che il tipo dell'espressione sia booleano ed itera

            while( ((BoolTree*) (literal = EvaluateExpression( cmd->getExpression(), env, level )))->getValue() && literal->isBoolTree() )
            {
                // Attenzione, rallenta il ciclo while
                if(debugActive)
                {
                    for(int i=0;i<level;i++)
                        cout << "   ";
                    cout << "\e[0;33mExec While: loop result \e[0m" << literal->toString() << endl;
                }
                delete literal;
                literal = NULL;
                ret = ExecuteCommand( cmd->getCommands(), env, level+1);
            }


            if(debugActive)
            {
                for(int i=0;i<level;i++)
                    cout << "<- ";
                cout << "\e[0;33mExec While: end result \e[0m" << literal->toString() << endl;
            }

            if( literal != NULL && !literal->isBoolTree() )
                // tipo di espressione non ammessa
                throw ExecuteException("unknown condition expression type", literal);
        }
        else if(cmd->isPutsTree())
        {
            LiteralTree* literal;

            if(debugActive)
                cout << "\e[0;33mExec Puts: \e[0m" << cmd->getExpression()->toString() << " => ";

            literal = EvaluateExpression( cmd->getExpression(), env, level);

            if(debugActive)
                cout << literal->toString() << endl;

            cout << literal->strValue() << endl;

            delete literal;
            literal = NULL;

        }
        else if(cmd->isGetsTree())
        {
            string str;
            LiteralTree* literal;
            bool is_number = false;

            if(debugActive)
                cout << "\e[0;33mExec Gets: \e[0m" << cmd->getExpression()->toString() << endl;

            // prendo una stringa da tastiera
            cin >> str;

            // controllo se rappresenta un numero intero
            /* for (unsigned int i = 0; i < str.length(); i++) {
                if (!std::isdigit(str[i]))
                    is_number = false;
            }
            */
            istringstream inpStream(str);
            int integerNumber = 0;
            string myString;
            if ((inpStream >> integerNumber) && !(inpStream >> myString))
                is_number = true;

            if (is_number)
                // se e` un numero creo una istanza di NumberTree convertendo la stringa
                literal = new NumberTree( atoi(str.c_str()) );
            else
                // se e` una stringa creo una istanza di StringTree
                literal = new StringTree( str );

            if(debugActive)
            {
                for(int i=0;i<level;i++)
                    cout << "** ";
                cout << "\e[0;33mGets return: \e[0m" << literal->toString() << endl;
            }

            // memorizzo il valore nell'ambiente di esecuzione
            env->setIdentifier( (IdentifierTree*) cmd->getExpression(), literal );

            if(debugActive)
                env->printEnvironment();

        }
        else if(cmd->isReturnTree())
        {
            LiteralTree* literal;

            if(debugActive)
                cout << "\e[0;33mExec Return: \e[0m" << cmd->getExpression()->toString() << " => ";

            literal = EvaluateExpression( cmd->getExpression(), env, level);

            if(debugActive)
                cout << literal->toString() << endl;

            ret = literal;

        }

        //if(debugActive)
            // stampa l'ambiente di esecuzione dopo ogni comando
        //    env->printEnvironment();
    }
    return ret;
}

LiteralTree* Execute::functionLength( ParamExprTree* params )
{

    if(params->isParamExprTree())
    {

        if( params->getLeftChild()->isStringTree())
        {
            LiteralTree* literal;
            literal = new NumberTree(((StringTree*)params->getLeftChild())->getValue().length());
            delete params;
            params = NULL;
            return literal;
        }
        else
            throw ExecuteException("length() parameter 1 type mismatch", params);
    }
    return NULL;
}

LiteralTree* Execute::functionToStr( ParamExprTree* params )
{

    if(params->isParamExprTree())
    {

        if( params->getLeftChild()->isNumberTree() )
        {
            LiteralTree* literal;
            string s;
            stringstream out;

            out << ((NumberTree*)params->getLeftChild())->getValue();

            literal = new StringTree( out.str() );

            delete params;
            params = NULL;

            return literal;
        }
        else
            throw ExecuteException("to_str() parameter 1 type mismatch", params);
    }
    return NULL;
}

LiteralTree* Execute::functionIsStr( ParamExprTree* params )
{

    if(params->isParamExprTree())
    {

        if( params->getLeftChild()->isStringTree())
        {
            delete params;
            params = NULL;

            return new BoolTree(true);
        }
        else
        {
            delete params;
            params = NULL;

            return new BoolTree(false);
        }


    }
    return NULL;
}

LiteralTree* Execute::EvaluateExpression(ExpressionTree* expr, Environment* env, int level)
{
    // stampa l'espressione corrente
    //cout << "\e[0;33mEvaluateExpression(): \e[0m" << expr->toString() << endl;

    // e` un valore costante, lo ritorno

    if (expr->isLiteralTree())
    {
        LiteralTree* literal = NULL;
        if (expr->isBoolTree())
            literal = new BoolTree(((BoolTree*)expr)->getValue());

        else if (expr->isNumberTree())
            literal = new NumberTree(((NumberTree*)expr)->getValue());

        else if (expr->isNilTree())
            literal = new NilTree();

        else if (expr->isStringTree())
            literal = new StringTree(((StringTree*)expr)->getValue());

        return literal;
    }


    else if (expr->isBlockTree())
        return EvaluateExpression(((BlockTree*)expr)->getExpressions(), env, level);

    // e` un identifiatore, lo devo sostituire col suo valore
    // e ritornare tale valore
    else if (expr->isIdentifierTree())
    {
        LiteralTree* variable = NULL;
        LiteralTree* literal = NULL;

        // lo cerco nell'ambiente di esecuzione
        variable = env->getIdentifier( (IdentifierTree*) expr );

        if(variable != NULL)
        {
            if (variable->isBoolTree())
            literal = new BoolTree(((BoolTree*)variable)->getValue());

            else if (variable->isNumberTree())
            literal = new NumberTree(((NumberTree*)variable)->getValue());

            else if (variable->isNilTree())
            literal = new NilTree();

            else if (variable->isStringTree())
            literal = new StringTree(((StringTree*)variable)->getValue());

            return literal;
        }
        else
            // Errore: questo non dovrebbe accadere a tempo di esecuzione
            throw ExecuteException("unknown identifier", expr);

    }
    else if (expr->isFunctionCallTree())
    {

        // funzioni built-in
        if(*((FunctionCallTree*)expr)->getIdentifier() == string("length"))
            return functionLength( EvaluateFunctionParams(((FunctionCallTree*)expr)->getParams(), env, level));

        if(*((FunctionCallTree*)expr)->getIdentifier() == string("to_str"))
            return functionToStr( EvaluateFunctionParams(((FunctionCallTree*)expr)->getParams(), env, level));

        if(*((FunctionCallTree*)expr)->getIdentifier() == string("is_str"))
            return functionIsStr( EvaluateFunctionParams(((FunctionCallTree*)expr)->getParams(), env, level));

        // controllo se la funzione esiste
        for (unsigned int i=0; i<functions->size(); i++)
        {
            if( *((FunctionCallTree*)expr)->getIdentifier() == (*functions)[i]->getName() )
            {
                if(debugActive)
                    cout << "\e[0;33mFunction Call: \e[0m" << (*functions)[i]->getName() << endl;;
                // eseguo la funzione dopo aver valutato i parametri
                return ExecuteFunction( (*functions)[i], EvaluateFunctionParams(((FunctionCallTree*)expr)->getParams(), env, level), level+1);
            }
        }
        throw ExecuteException("unknown function", expr);

    }
    else if (expr->isBinaryOperatorTree())
    {
        LiteralTree* literal = NULL;

        LiteralTree* leftLiteral = EvaluateExpression(((BinaryOperatorTree*)expr)->getLeftChild(), env, level);
        LiteralTree* rightLiteral = EvaluateExpression(((BinaryOperatorTree*)expr)->getRightChild(), env, level);

        // uno dei due operandi è un NilTree, restituisco un NilTree
        if( leftLiteral->isNilTree() || rightLiteral->isNilTree())
            literal = new NilTree();

        // solo operatori numerici
        else if( leftLiteral->isNumberTree() && rightLiteral->isNumberTree() && ((BinaryOperatorTree*)expr)->isNumberOperator() )
        {

            if     ( ((BinaryOperatorTree*)expr)->getOperator() == PLUS)
                literal = &(*leftLiteral + *rightLiteral);
            else if( ((BinaryOperatorTree*)expr)->getOperator() == MINUS)
                literal = &(*leftLiteral - *rightLiteral);
            else if( ((BinaryOperatorTree*)expr)->getOperator() == MULT)
                literal = &(*leftLiteral * *rightLiteral);
            else if( ((BinaryOperatorTree*)expr)->getOperator() == MOD)
            {
                // divisione per 0
                if( ((NumberTree*)rightLiteral)->getValue() != 0 )
                    literal = &(*leftLiteral % *rightLiteral);
                else
                    throw ExecuteException("division by 0", expr);
            }
            else if( ((BinaryOperatorTree*)expr)->getOperator() == DIV)
            {
                // divisione per 0
                if( ((NumberTree*)rightLiteral)->getValue() != 0 )
                    literal = &(*leftLiteral / *rightLiteral);
                else
                    throw ExecuteException("division by 0", expr);
            }
        }

        // solo operatori di stringhe
        else if( leftLiteral->isStringTree() && rightLiteral->isStringTree() && ((BinaryOperatorTree*)expr)->isStringOperator() )
        {
            if( ((BinaryOperatorTree*)expr)->getOperator() == PLUS)
                literal = &(*leftLiteral + *rightLiteral);
        }

        // solo operatori booleani
        else if( leftLiteral->isBoolTree() && rightLiteral->isBoolTree() && ((BinaryOperatorTree*)expr)->isBoolOperator() )
        {
            if( ((BinaryOperatorTree*)expr)->getOperator() == AND)
                literal = & (*leftLiteral and *rightLiteral);
            else if( ((BinaryOperatorTree*)expr)->getOperator() == OR)
                literal = & (*leftLiteral or *rightLiteral);
        }

        // operatori di comparazione
        else if( (leftLiteral->getType() == rightLiteral->getType()) && ((BinaryOperatorTree*)expr)->isCompareOperator() )
        {
            if( ((BinaryOperatorTree*)expr)->getOperator() == EQUAL)
                literal = &(*leftLiteral == *rightLiteral);
            if( ((BinaryOperatorTree*)expr)->getOperator() == NOTEQUAL)
                literal = &(*leftLiteral != *rightLiteral);
            if( ((BinaryOperatorTree*)expr)->getOperator() == MINEQ)
                literal = &(*leftLiteral <= *rightLiteral);
            if( ((BinaryOperatorTree*)expr)->getOperator() == MAXEQ)
                literal = &(*leftLiteral >= *rightLiteral);
            if( ((BinaryOperatorTree*)expr)->getOperator() == MIN)
                literal = &(*leftLiteral < *rightLiteral);
            if( ((BinaryOperatorTree*)expr)->getOperator() == MAX)
                literal = &(*leftLiteral > *rightLiteral);
        }
        else
        {
            throw ExecuteException("operand type or operator type mismatch", expr);
        }
        //cout << leftLiteral->toString() << endl;
        delete leftLiteral;
        leftLiteral = NULL;
        //cout << rightLiteral->toString() << endl;
        delete rightLiteral;
        rightLiteral = NULL;
        return literal;
    }
    else
        // Errore: questo non dovrebbe accadere a tempo di esecuzione
        throw ExecuteException("unknown expression", expr);

    return NULL;
}
