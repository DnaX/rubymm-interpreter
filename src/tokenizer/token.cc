#include "token.hh"
#include <iostream>
#include <sstream>

///
/// @file   token.cc
/// @author Luca Martini
/// @date   Thu Feb 28 16:20:15 2008
///
/// @brief  Implementazioni della classe Token e derivati (vers. modificata da Francesco Galgani)
///
///
///
using namespace std;

string Number::toString() const {
  stringstream ss;
  ss << "NUMBER("<< number << ")";
  return ss.str();
}

string Identifier::toString() const {
  return "IDENTIFIER("+name+")";
}

string String::toString() const {
  return "STRING("+name+")";
}

string Bool::toString() const {
  return "BOOL("+(value?string("true"):string("false"))+")";
}

string Symbol::toString() const {
  return "SYMBOL("+name+")";
}

string BinaryOperator::toString() const {
  return "BINARYOPERATOR("+name+")";
}

string NilLit::toString() const {
  return "NIL";
}

string Keyword::toString() const {
  switch (name) {
  case WHILE:
    return "KEYWORD(WHILE)";
  case IF:
    return "KEYWORD(IF)";
  case ELSE:
    return "KEYWORD(ELSE)";
  case RETURN:
    return "KEYWORD(RETURN)";
  case BREAK:
    return "KEYWORD(BREAK)";
  case CONTINUE:
    return "KEYWORD(CONTINUE)";
  case SWITCH:
    return "KEYWORD(SWITCH)";
  case CASE:
    return "KEYWORD(CASE)";
  case FOR:
    return "KEYWORD(FOR)";
  case DEFAULT:
    return "KEYWORD(DEFAULT)";
  case DO:
    return "KEYWORD(DO)";
  case DEF:
    return "KEYWORD(DEF)";
  case END:
    return "KEYWORD(END)";
  case PUTS:
    return "KEYWORD(PUTS)";
  case GETS:
    return "KEYWORD(GETS)";
  default:
    return "KEYWORD(ERROR)";
  }
}

/// Funzione globale per la stampa di un Token su uno stream
///
/// @param out un riferimento allo stream di uscita
/// @param t un puntatore al token che si intende stampare
///
/// @return lo stream di uscita modificato
ostream& operator<<(std::ostream& out, const Token* t) {
  out << t->lineNumber << ": " << t->toString();
  return out;
}
