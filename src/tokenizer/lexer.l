%option debug
%option yylineno
%option yyclass="Analyzer"
%{
#include "token.hh"
#include "analyzer.hh"
#include <cstdlib>
int yywrap();
%}
ALPHA				[a-zA-Z_]
BINARYOPERATOR                  and|or|\+=|-=|\*=|\/=|<=|>=|==|!=|<|>|=|\*|\/|&&|&|%|\|\||\||\+|\-
DIGIT				[0-9]
ALNUM				{ALPHA}|{DIGIT}
BLANK				[ \t\n]
NUMBER                          {DIGIT}+
IDENTIFIER                      {ALPHA}({ALPHA}|{DIGIT}|_)*
SYMBOL                          \(|\)|\{|\}|=>|;|\?|:|\[|\]|,|\.
STRING                          \"([^\"\n])*\"
UNTERMINATEDSTRING              \"([^\"\n])*$

%x SCOMMENT
%%
"#"                             BEGIN(SCOMMENT);
<SCOMMENT>\n                    BEGIN(INITIAL);
<SCOMMENT>.                     /* ignore */
{BLANK}*                        /* ignore */
nil                             addToken(new NilLit());
while                           addToken(new Keyword(WHILE));
if                              addToken(new Keyword(IF));
else                            addToken(new Keyword(ELSE));
return                          addToken(new Keyword(RETURN));
break                           addToken(new Keyword(BREAK));
continue                        addToken(new Keyword(CONTINUE));
switch                          addToken(new Keyword(SWITCH));
case                            addToken(new Keyword(CASE));
for                             addToken(new Keyword(FOR));
default                         addToken(new Keyword(DEFAULT));
do                              addToken(new Keyword(DO));
def                             addToken(new Keyword(DEF));
end                             addToken(new Keyword(END));
puts                            addToken(new Keyword(PUTS));
gets                            addToken(new Keyword(GETS));
true                            addToken(new Bool(true));
false                           addToken(new Bool(false));
{BINARYOPERATOR}                addToken(new BinaryOperator(YYText()));
{NUMBER}                        addToken(new Number(atoi(YYText())));
{IDENTIFIER}                    addToken(new Identifier(YYText()));
{SYMBOL}                        addToken(new Symbol(YYText()));
{STRING}                        addToken(new String(YYText()));
{UNTERMINATEDSTRING}            throw ParserError(string("Unterminated string ")+YYText(),lineno());
.                               throw ParserError(string("Undefined token ")+YYText(),lineno());
%%

int
yyFlexLexer::
yywrap() { return 1;};


std::ostream& operator<<(ostream& out, const ParserError& pe) {
  return (out << "\e[1;31m==> Syntax error: \e[0m" << pe.message << " at line " << pe.lineNumber);
}
