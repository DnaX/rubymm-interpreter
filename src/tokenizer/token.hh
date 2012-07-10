#ifndef TOKEN_HH
#define TOKEN_HH
#include <string>
#include <list>
#include <iostream>

///
/// @file   token.hh
/// @author Luca Martini
/// @date   Thu Feb 28 15:49:09 2008
///
/// @brief  Header file per Token e derivati (versione modificata da Francesco Galgani)
///
///
///

///
/// Le keyword in R--
///
enum KeywordName {WHILE, IF, ELSE, RETURN, BREAK, CONTINUE, SWITCH, CASE, FOR, DEFAULT, DO, DEF, END, PUTS, GETS};

// forward declarations
class Token;
class Keyword;
class Identifier;
class Symbol;
class BinaryOperator;
class Number;
class String;
class Literal;
class Bool;
class NilLit;

///
///
/// @brief Il visitor per la gerarchia di Token
///
/// Il visitor pattern per la gerarchia di classe realtiva ai token lessicali
class TokenVisitor {
public:
  virtual void visitToken(Token*) { std::cout << "T";};
  virtual void visitKeyword(Keyword*) {};
  virtual void visitIdentifier(Identifier*) {};
  virtual void visitSymbol(Symbol*) {};
  virtual void visitBinaryOperator(BinaryOperator*) {};
  virtual void visitLiteral(Literal*) {};
  virtual void visitBool(Bool*) {};
  virtual void visitNilLit(NilLit*) {};
  virtual void visitNumber(Number*) {};
  virtual void visitString(String*) {};
};

///
///
/// @brief Un token lessicale generico.
///
/// Ogni token rappresenta una unità del linguaggio considerato (come ad
/// esempio una parola chiave, un identificatore, etc).
class Token {
protected:
  ///
  /// Costruttore protetto: non è possibile creare un oggetto Token
  /// direttamente.
  ///
  Token() {};
public:
  int lineNumber;		///< il numero di linea corrente
  virtual ~Token() {};

  ///
  /// Controlla se il token è un identificatore
  ///
  /// @return true se il token è un identificatore, false altrimenti
  ///
  virtual bool isIdentifier() { return false; }

  ///
  /// Controlla se il token è un numero
  ///
  /// @return true se il token è un numero, false altrimenti
  ///
  virtual bool isNumber() { return false; }

  ///
  /// Controlla se il token è un simbolo
  ///
  /// @return true se il token è un simbolo, false altrimenti
  ///
  virtual bool isSymbol() { return false; };

  ///
  /// Controlla se il token è una keyword
  ///
  /// @return true se il token è una keyword, false altrimenti
  ///
  virtual bool isKeyword() { return false; };

  ///
  /// Controlla se il token è una stringa letterale
  ///
  /// @return true se il token è una stringa letterale, false altrimenti
  ///
  virtual bool isString() { return false; };

  ///
  /// Controlla se il token è una costante booleana
  ///
  /// @return true se il token è una costante booleana, false altrimenti
  ///
  virtual bool isBool() { return false; };

  ///
  /// Controlla se il token è un valore letterale nil
  ///
  /// @return true se il token è il letterale nil, false altrimenti
  ///
  virtual bool isNilLit() { return false; };

  ///
  /// Controlla se il token è un operatore binario
  ///
  /// @return true se il token è un operatore binario, false altrimenti
  ///
  virtual bool isBinaryOperator() {return false;}

  ///
  /// Controlla se il token è una costante letterale
  ///
  /// @return true se il token è una costante letterale, false altrimenti
  ///
  virtual bool isLiteral() {return false;}

  ///
  /// Conversione del token a stringa
  ///
  /// @return una rappresentazione del token come string
  ///
  virtual std::string toString() const = 0;

  ///
  /// La funzione che accetta un visitor
  ///
  /// @param v un riferimento al visitor accettato
  ///
  virtual void accept(TokenVisitor& v) { v.visitToken(this);}
};

///
/// Typedef per la lista di puntatori a Token
///
typedef std::list<Token*> TokenList;

///
/// @brief La rappresentazione di un literal
///
/// Token che rappresenta un numero espresso come valore letterale. Ogni literal
/// ha un suo tipo associato.
///
class Literal : public Token {
public:
  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitLiteral(this);
  }

  virtual bool isLiteral() { return true; }
};


///
/// @brief La rappresentazione di una costante numerica
///
/// Token che rappresenta un numero espresso come valore letterale.
///
class Number : public Literal {
public:
  int number;			///< Il numero rappresentato
  Number(int i) : number(i) {}
  std::string toString() const;

  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitNumber(this);
  }

  virtual bool isNumber() { return true; }
};

///
/// @brief La rappresentazione di un valore boolean
///
/// Token che rappresenta una costante booleana
///
class Bool : public Literal {
public:
  bool value;			///< Il valore rappresentato
  Bool(bool v) : value(v) {}
  std::string toString() const;

  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitBool(this);
  }

  virtual bool isBool() { return true; }
};

///
/// @brief La rappresentazione di un valore boolean
///
/// Token che rappresenta una costante booleana
///
class NilLit : public Literal {
public:
  NilLit() {}
  std::string toString() const;

  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitNilLit(this);
  }

  virtual bool isNilLit() { return true; }
};



///
/// @brief Un identificatore del linguaggio
///
class Identifier : public Token {
public:
  std::string name;		///< Il nome dell'identificatore
  Identifier(std::string s) : name(s) {};
  virtual bool isIdentifier() { return true; };
  std::string toString() const ;
  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitIdentifier(this);
  }
};

///
/// @brief Un simbolo del linguaggio
///
class Symbol : public Token {
public:
  std::string name;		///< Simbolo del linguaggio
  Symbol(std::string s) : name(s){};
  virtual bool isSymbol() { return true; };
  std::string toString() const;
  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitSymbol(this);
  }
};

///
/// @brief Un operatore binario del linguaggio
///
class BinaryOperator : virtual public Symbol {
public:
  BinaryOperator(std::string s) : Symbol(s){};
  virtual bool isBinaryOperator() { return true; };
  std::string toString() const;
  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitBinaryOperator(this);
  }
};

///
/// @brief Una parola chiave del linguaggio
///
class Keyword : public Token {
public:
  KeywordName name;		///< La parola chiave
  Keyword(KeywordName n) : name(n) {};
  virtual bool isKeyword() { return true; };
  std::string toString() const ;
  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitKeyword(this);
  }
};

///
/// @brief Un letterale stringa
///
class String : public Literal {
public:
  std::string name;		///< Stringa letterale
  String(std::string s) {
    name = s.substr(1,s.size()-2);
  };
  virtual bool isString() { return true; };
  std::string toString() const;
  virtual void accept(TokenVisitor& v) {
    v.visitToken(this);
    v.visitString(this);
  }
};

#endif

