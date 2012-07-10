#ifndef ANALYZER_HH
#define ANALYZER_HH

///
/// @file   analyzer.hh
/// @author Luca Martini
/// @date   Thu Feb 28 16:42:25 2008
/// 
/// @brief  Dichiarazione delle classi Analyzer e ParserError
/// 


#include "token.hh"

using namespace std;

///
/// @brief Analizzatore sintattico
///
/// Generato con Flex++ questo analizzatore sintattico legge un programma in
/// linguaggio J-- e crea una lista dei suoi Token sintattici
///
class Analyzer : public yyFlexLexer {
  TokenList tl;			///< La lista dei Token letti

  ///
  /// Aggiunge un Token in fondo alla lista
  ///
  /// @param tp Il puntatore al Token da aggiungere 
  void addToken(Token* tp) { tp->lineNumber = lineno(); tl.push_back(tp); }
  
public:
  
  /// 
  ///
  /// @param arg_yyin un puntatore allo stream da cui leggere il programma da
  /// analizzare
  /// @param arg_yyout un puntatore allo stream su cui scrivere eventuali errori
  ///
  /// @return 
  Analyzer(istream* arg_yyin = 0, ostream* arg_yyout = 0) : yyFlexLexer(arg_yyin,arg_yyout){};
  
  /// 
  /// La funzione che aggiunge un token letto dall'input alla lista
  ///
  /// @return 0 se non ci sono piu token da leggere
  /// @throws ParserError se si incontrano errori nell'analisi
  ///
  virtual int yylex();  

  /// 
  /// Riferimento alla lista dei Token
  ///
  /// @return 
  ///
  TokenList& getTokenList() { return tl; };

  /// 
  /// Distruttore: dealloca anche tutti i Token presenti nella lista
  ///
  /// @return 
  ///
  ~Analyzer() {
    TokenList::iterator i;
    for (i=tl.begin();i!=tl.end();i++) {
      //cerr << "Deleting " << (*i)->toString() << endl; 
      delete (*i);
    }
  }
};

///
/// @brief Un errore generato durante l'analisi 
///
class ParserError {
  string message;		///< il messaggio d'errore
  int lineNumber;		///< il numero di linea a cui e` avvenuto l'errore
public:
  ParserError(string m, int l) : message(m), lineNumber(l){};
  friend ostream& operator<<(ostream&, const ParserError&);
};

#endif
