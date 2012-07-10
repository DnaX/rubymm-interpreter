#include "Parser.h"

ParsingException::ParsingException(Token* tokenError)
{
    myTokenError = tokenError;
}

void ParsingException::printError()
{
    if (myTokenError != 0)
        cerr << "\e[1;31m==> Parsing error: \e[0munexpected token " << myTokenError->toString() << " at line " << myTokenError->lineNumber << endl;
    else
        cerr << "\e[1;31m==> Parsing error: \e[0munexpected end of tokens." << endl;
}

Parser::Parser(const TokenList::iterator start, const TokenList::iterator end, bool debug)
{
    myIterator = start;
    fine = end;
    debugActive = debug;

    if (debugActive)
        cout << "\e[1;37m## Parser phase ##\e[0m" << endl << endl;

    // Riconosce le funzioni e le inserisce nell'apposito vettore.
    // Notare che recognizeFunction aggiorna automaticamente myIterator.
    while (myIterator != fine)
        functions.push_back(recognizeFunction(myIterator));
}

Parser::~Parser()
{
    //dtor
}

vector<FunctionTree*> Parser::getFunctions()
{
    return functions;
}

FunctionTree* Parser::recognizeFunction(TokenList::iterator& myIterator) throw (ParsingException)
{
    bool error = false; // variabile usata per segnalare le condizioni di errore

    // Variabili che costituiscono la funzione da riconoscere (al momento inizializzate con valori di default)
    string functionName = "";
    vector<IdentifierTree*> parameters;
    Command* command = 0;

    // Presupposto: il token attuale è un "def" e la funzione terminerà con il token "end", altrimenti errore
    // Controlla quindi che la funzione inizi con il token puntato dall'iteratore myIterator
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == DEF)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);

    myIterator++;

    // Il token successivo e' l'identificatore della funzione
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isIdentifier())
            error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);

    functionName = ((Identifier*)(*myIterator))->name;

    myIterator++;

    // I token successivi contengono gli identificatori dei parametri racchiusi tra parentesi
    // Scorre e salva la lista dei parametri (eventualmente vuota)

    // Il token successivo e' "aperta parentesi tonda"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isSymbol())
            if (((Symbol*)(*myIterator))->name.compare("(") == 0)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Chiama la recognizeParams()
    parameters = recognizeParams(myIterator);

    // Il token successivo e' "chiusa parentesi tonda"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isSymbol())
            if (((Symbol*)(*myIterator))->name.compare(")") == 0)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Richiama la recognizeCommand() passandole per riferimento l'iteratore attuale
    command = recognizeCommand(myIterator);

    // Infine, controlla che effettivamente il corpo della funzione sia terminato,
    // aggiorna l'iteratore del chiamante e restituisce la funzione

    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == END)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    try
    {
        return new FunctionTree(functionName, parameters, command);
    }
    catch (string s)
    {
        cerr << "\e[1;31m==> Parsing error: \e[0m" << s << endl;
        exit(EXIT_FAILURE);
    }
}

vector<IdentifierTree*> Parser::recognizeParams(TokenList::iterator& myIterator) throw (ParsingException)
{
    bool error = false;
    vector<IdentifierTree*> result;

    // itera finche' non trova "chiusa parentesi tonda"
    while ((myIterator != fine) && !(((*myIterator)->isSymbol()) && (((Symbol*)(*myIterator))->name.compare(")") == 0)))
    {
        // il token suguente e' un identificatore di un parametro
        error = true;
        if (myIterator != fine)
            if ((*myIterator)->isIdentifier())
                error = false;
        if (error && myIterator != fine) throw ParsingException(*myIterator);
        if (error && myIterator == fine) throw ParsingException(0);
        result.push_back (new IdentifierTree(((Identifier*)(*myIterator))->name));
        myIterator++;

        // se il token seguente e' una virgola, allora itera, altrimenti interrompe il ciclo
        error = true;
        if (myIterator != fine)
            if ((*myIterator)->isSymbol())
                error = false;
        if (error && myIterator != fine) throw ParsingException(*myIterator);
        if (error && myIterator == fine) throw ParsingException(0);
        if (((Symbol*)(*myIterator))->name.compare(",") == 0)
            myIterator++;
        else
            break; // fine parametri
    }
    return result;
}

Command* Parser::recognizeCommand(TokenList::iterator& myIterator) throw (ParsingException)
{
    Command* result = 0;

    // Riconosce ricorsivamente un comando

    // Identifica un comando tra le varie alternative possibili
    if (myIterator != fine)
    {

        // ASSEGNAMENTO (AssignmentTree)
        // Se il primo token e' un identificatore, allora il comando e' un assegnamento
        if ((*myIterator)->isIdentifier())
            result = recognizeAssignment(myIterator);

        // Altrimenti, se il primo token e' una keyword...
        else if ((*myIterator)->isKeyword())
        {

            // RETURN (ReturnTree)
            // Se il primo token e' una keyword RETURN, allora il comando e' un return
            if (((Keyword*)(*myIterator))->name == RETURN)
                result = recognizeReturn(myIterator);

            // CICLO IF..ELSE (IfTree)
            // Se il primo token e' una keyword IF, allora il comando e' un ciclo if..then
            else if (((Keyword*)(*myIterator))->name == IF)
                result = recognizeIf(myIterator);

            // CICLO WHILE (WhileTree)
            // Se il primo token e' una keyword WHILE, allora il comando e' un ciclo while
            else if (((Keyword*)(*myIterator))->name == WHILE)
                result = recognizeWhile(myIterator);

            // FUNZIONE INTERNA PUTS (PutsTree)
            // Se il primo token e' una keyword PUTS, allora il comando e' la funzione interna "puts"
            else if (((Keyword*)(*myIterator))->name == PUTS)
                result = recognizePuts(myIterator);

            // FUNZIONE INTERNA GETS (GetsTree)
            // Se il primo token e' una keyword GETS, allora il comando e' la funzione interna "gets"
            else if (((Keyword*)(*myIterator))->name == GETS)
                result = recognizeGets(myIterator);
        }
    }

    // Se il comando non e' stato identificato, lancia un'eccezione
    if (myIterator != fine && result == 0) throw ParsingException(*myIterator);
    if (myIterator == fine && result == 0) throw ParsingException(0);

    // CASO BASE: se non ci sono altri comandi (cioe' se il token seguente e' un END oppure ELSE), fa un return
    bool fineComandi = false;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if ((((Keyword*)(*myIterator))->name == END) || (((Keyword*)(*myIterator))->name == ELSE))
                fineComandi = true;
    if (fineComandi) return result;

    // CASO RICORSIVO
    // Il precedente comando diventa il figlio sinistro di un nuovo DoubleCmdTree,
    // mentre il successivo comando ne diventa il figlio destro
    Command* left = result;
    Command* right = recognizeCommand(myIterator);
    if (right == 0) throw ParsingException(*myIterator);
    result = new DoubleCmdTree(left, right);
    if (result == 0) throw ParsingException(*myIterator);

    return result;
}

AssignmentTree* Parser::recognizeAssignment(TokenList::iterator& myIterator) throw (ParsingException)
{
    bool error = false;
    AssignmentTree* result = 0;
    IdentifierTree* id = 0;
    ExpressionTree* expr = 0;

    // Il primo token e' un identificatore
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isIdentifier())
            error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    id = new IdentifierTree(((Identifier*)(*myIterator))->name);
    if (id == 0) throw ParsingException(*myIterator);
    myIterator++;

    // Il token seguente e' un simbolo di uguaglianza "="
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isSymbol())
            if (((Symbol*)(*myIterator))->name.compare("=") == 0)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Segue una espressione
    expr = recognizeExpression (myIterator);
    if (expr == 0) throw ParsingException(*myIterator);

    // Il token seguente e' un punto e virgola ";"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isSymbol())
            if (((Symbol*)(*myIterator))->name.compare(";") == 0)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Istanzia l'AssignmentTree
    result = new AssignmentTree(id, expr);
    if (result == 0) throw ParsingException(*myIterator);

    return result;
}

ReturnTree* Parser::recognizeReturn(TokenList::iterator& myIterator) throw (ParsingException)
{
    bool error = false;
    ReturnTree* result;

    ExpressionTree* expr = 0;

    // Il primo token e' la keyword RETURN
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == RETURN)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Segue una espressione
    expr = recognizeExpression (myIterator);
    if (expr == 0) throw ParsingException(*myIterator);

    // Il token seguente e' un punto e virgola ";"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isSymbol())
            if (((Symbol*)(*myIterator))->name.compare(";") == 0)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Istanzia l'AssignmentTree
    result = new ReturnTree(expr);
    if (result == 0) throw ParsingException(*myIterator);

    return result;
}

IfTree* Parser::recognizeIf(TokenList::iterator& myIterator) throw (ParsingException)
{
    bool error = false;
    IfTree* result = 0;
    ExpressionTree* expr = 0;
    Command* leftChild = 0;
    Command* rightChild = 0;
    DoubleCmdTree* cmd = 0;

    // Riconosce un costrutto if..else..end

    // Il primo token e' la keyword "if"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == IF)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Segue l'espressione che esprime una condizione
    expr = recognizeExpression(myIterator);
    if (expr == 0) throw ParsingException(*myIterator);

    // Segue il commando da eseguire quando la condizione e' verificata
    leftChild = recognizeCommand(myIterator);
    if (leftChild == 0) throw ParsingException(*myIterator);

    // Segue la keyword "else"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == ELSE)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Segue il commando da eseguire quando la condizione non e' verificata
    rightChild = recognizeCommand(myIterator);
    if (rightChild == 0) throw ParsingException(*myIterator);

    // Segue la keyword "end"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == END)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Istanzia l'oggetto IfTree
    cmd = new DoubleCmdTree(leftChild, rightChild);
    if (cmd == 0) throw ParsingException(*myIterator);
    result = new IfTree(expr, cmd);
    if (result == 0) throw ParsingException(*myIterator);

    return result;
}


WhileTree* Parser::recognizeWhile(TokenList::iterator& myIterator) throw (ParsingException)
{
    bool error = false;
    ExpressionTree* expr = 0;
    Command* cmd = 0;
    WhileTree* result;

    // Riconosce un costrutto while..end

    // Il primo token e' la keyword "while"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == WHILE)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Segue l'espressione che esprime una condizione
    expr = recognizeExpression(myIterator);
    if (expr == 0) throw ParsingException(*myIterator);

    // Segue il commando da eseguire finche' la condizione e' verificata
    cmd = recognizeCommand(myIterator);
    if (cmd == 0) throw ParsingException(*myIterator);

    // Segue la keyword "end"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == END)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Istanzia l'oggetto WhileTree
    result = new WhileTree (expr, cmd);
    if (result == 0) throw ParsingException(*myIterator);

    return result;
}


PutsTree* Parser::recognizePuts(TokenList::iterator& myIterator) throw (ParsingException)
{
    bool error = false;
    ExpressionTree* expr = 0;
    PutsTree* result = 0;

    // Riconosce il comando "puts"

    // Il primo token e' la keyword "puts"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == PUTS)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Segue l'espressione da valutare
    expr = recognizeExpression(myIterator);
    if (expr == 0) throw ParsingException(*myIterator);

    // Il token seguente e' un punto e virgola ";"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isSymbol())
            if (((Symbol*)(*myIterator))->name.compare(";") == 0)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Istanzia l'oggetto PutsTree
    result = new PutsTree(expr);
    if (result == 0) throw ParsingException(*myIterator);

    return result;
}

GetsTree* Parser::recognizeGets(TokenList::iterator& myIterator) throw (ParsingException)
{
    bool error = false;
    IdentifierTree* id = 0;
    GetsTree* result = 0;

    // Riconosce il comando "gets"

    // Il primo token e' la keyword "gets"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isKeyword())
            if (((Keyword*)(*myIterator))->name == GETS)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Il token seguente e' un identificatore
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isIdentifier())
        {
            id = new IdentifierTree(((Identifier*)(*myIterator))->name);
            error = false;
        }
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Il token seguente e' un punto e virgola ";"
    error = true;
    if (myIterator != fine)
        if ((*myIterator)->isSymbol())
            if (((Symbol*)(*myIterator))->name.compare(";") == 0)
                error = false;
    if (error && myIterator != fine) throw ParsingException(*myIterator);
    if (error && myIterator == fine) throw ParsingException(0);
    myIterator++;

    // Istanzia l'oggetto GetsTree
    result = new GetsTree(id);
    if (result == 0) throw ParsingException(*myIterator);

    return result;
}


ExpressionTree* Parser::recognizeExpression(TokenList::iterator& myIterator, bool onlyTermTree) throw (ParsingException)
{
    ExpressionTree* result = 0;

    // Riconosce ricorsivamente una espressione

    // Identifica una espressione tra le varie alternative possibili
    if (myIterator != fine)
    {
        // PRIMO CASO BASE: l'espressione e' un LiteralTree
        if ((*myIterator)->isLiteral())
        {
            // LiteralTree -> StringTree
            if ((*myIterator)->isString())
                result = new StringTree(((String*)(*myIterator))->name);

            // LiteralTree -> NumberTree
            else if ((*myIterator)->isNumber())
                result = new NumberTree(((Number*)(*myIterator))->number);

            // LiteralTree -> BoolTree
            else if ((*myIterator)->isBool())
                result = new BoolTree(((Bool*)(*myIterator))->value);

            // LiteralTree -> NilTree
            else if ((*myIterator)->isNilLit())
                result = new NilTree();
        }

        // SECONDO CASO BASE: l'espressione e' un IdentifierTree
        else if ((*myIterator)->isIdentifier())
            result = new IdentifierTree(((Identifier*)(*myIterator))->name);

        // PRIMO CASO RICORSIVO: l'espressione e' un BlockTree
        else if (((*myIterator)->isSymbol()) && (((Symbol*)(*myIterator))->name.compare("(") == 0))
        {
            myIterator++;
            ExpressionTree* inside = recognizeExpression(myIterator);
            if (inside == 0) throw ParsingException(*myIterator);
            if (((*myIterator)->isSymbol()) && (((Symbol*)(*myIterator))->name.compare(")") == 0))
                result = new BlockTree(inside);
            else throw ParsingException(*myIterator);
        }

        // In assenza di errori, uno dei precedenti casi (che sono TermTree) deve essere stato riconosciuto.
        // A questo punto sono possibili due ulteriori casi ricorsivi.
        if (result != 0)
        {
            myIterator++; // ATTENZIONE: da qui in poi il programma e' andato avanti di un token!
            if (myIterator != fine)
            {

                // SECONDO CASO RICORSIVO: l'espressione e' una chiamata di funzione (FunctionCallTree)
                // Se l'espressione e' composta da un identificatore (precedentemente riconosciuto) seguito
                // da una parentesi tonda aperta, allora l'espressione e' una chiamata di funzione
                if ((result -> isIdentifierTree()) && (myIterator != fine) && ((*myIterator)->isSymbol()) && (((Symbol*)(*myIterator))->name.compare("(") == 0))
                {
                    myIterator++;
                    // OK: Segue lista di espressioni (almeno una) fino a "parentesi tonda chiusa"
                    IdentifierTree* id = (IdentifierTree*)result;
                    ParamExprTree* parameters = 0;
                    FunctionCallTree* fcall = 0;
                    while ((myIterator != fine) && (!(((*myIterator)->isSymbol()) && (((Symbol*)(*myIterator))->name.compare(")") == 0))))
                    {
                        ExpressionTree* child = recognizeExpression(myIterator);
                        //cout << "Ho riconosciuto l'espressione: " << child->toString() << endl;
                        if (child == 0) throw ParsingException(*myIterator);
                        ParamExprTree* param = new ParamExprTree(child);
                        if (param == 0) throw ParsingException(*myIterator);

                        if (parameters == 0) // Questo e' il primo parametro (espressione)
                            parameters = param;
                        else // Questo parametro (espressione) deve essere aggiunto ai precedenti
                        {
                            parameters->addOtherExpr(param);
                            //cout << "Ho aggiunto il parametro: " << param->toString() << endl;
                        }

                        // Se segue una virgola, allora ci sono altre espressioni come parametri, altrimenti no
                        if (((*myIterator)->isSymbol()) && (((Symbol*)(*myIterator))->name.compare(",") == 0))
                            myIterator++;
                        else
                            break;
                    }

                    if (parameters == 0) throw ParsingException(*myIterator);
                    fcall = new FunctionCallTree(id,parameters);
                    if (fcall == 0) throw ParsingException(*myIterator);
                    result = fcall;
                    myIterator++;
                }

                // Se e' stato chiesto di ricercare esclusivamente un TermTree, la ricerca finisce qui
                if (onlyTermTree)
                {
                    if (result == 0) throw ParsingException(*myIterator);
                    return result;
                }

                // TERZO CASO RICORSIVO: l'espressione e' una operazione binaria (BinaryOperatorTree)
                // *** Vale l'ASSOCIATIVITA' A SINISTA ***
                // Se l'espressione e' composta da una espressione precedentemente riconosciuta,
                // seguita da un operatore binario e un'ulteriore espressione, allora l'espressione complessiva
                // costituisce un BinaryOperatorTree
                else while ((result -> isExpressionTree()) && ((*myIterator)->isBinaryOperator()))
                    {
                        // OK: il token attuale e' un operatore binario
                        ExpressionTree* leftChild = result;
                        // cout << "Il figlio sinistro e': " << leftChild->toString() << endl;
                        TermTree* rightChild = 0;
                        string myOperator = ((Symbol*)(*myIterator))->name; // Da notare che BinaryOperator e' un tipo derivato di Symbol
                        myIterator++;

                        // Segue TermTree
                        ExpressionTree* nextExpr = recognizeExpression(myIterator, true);
                        if (nextExpr == 0) throw ParsingException(*myIterator);
                        // cout << "Il figlio destro e': " << nextExpr->toString() << endl;
                        if (nextExpr->isTermTree())
                            rightChild = (TermTree*) nextExpr;
                        else throw ParsingException(*myIterator);

                        result = new BinaryOperatorTree(myOperator, leftChild, rightChild);

                        // L'espressione e' conclusa?
                        // Se l'espressione e' conclusa, il ciclo while termina qui, altrimenti vale l'associativita' a sinistra, ovvero:
                        // se l'espressione non e' conclusa, l'attuale espressione, che e' un BinaryOperatorTree, diventera' il figlio sinistro di un nuovo BinaryOperatorTree.

                    }
            }
            else throw ParsingException(*myIterator);
        }
    }

    if (result == 0) throw ParsingException(*myIterator);
    return result;
}



