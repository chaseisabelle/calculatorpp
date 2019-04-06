%{

#define ADDOP   '+'
#define SUBOP   '-'
#define MULOP   '*'
#define DIVOP   '/'
#define LPAREN  '('
#define RPAREN  ')'
#define LBRACE  '{'
#define RBRACE  '}'
#define EQUALS  '='

#include "y.tab.h"
#include <stdio.h>
#include <string.h>

%}

%%

[Ss][Tt][Oo][Pp]                   { return STOP; }

[Rr][Ee][Pp][Ee][Aa][Tt]           { return REPEAT; }

"+"                                { return ADDOP; }

"++"                               { return PINC; }

(\+[ \t]*\+\+)                     { unput ('+'); unput ('+'); return ADDOP; }

"-"                                { return SUBOP; }

"--"                               { return PDEC; }

(\-[ \t]*\-\-)                     { unput ('-'); unput ('-'); return SUBOP; }

"<<"                               { return LSHIFT; }

">>"                               { return RSHIFT; }

"*"                                { return MULOP; }

"/"                                { return DIVOP; }

"("                                { return LPAREN; }

")"                                { return RPAREN; }

"="                                { return EQUALS; }

"{"                                { return LBRACE; }

"}"                                { return RBRACE; }

"\n"                               { return EOLN; }

[0-9]+(\.[0-9]+)?                  { yylval.num = (double)atof (yytext); return NUM; }

[A-Za-z][0-9A-Za-z]*               { yylval.sym = strcpy (new char[(yyleng + 1)], yytext); return SYM; }

" " | "\t"                         ;

[^ \.\t\n\+\-\*\/\(\)\=\=\<\>\.\R\r\E\e\P\p\A\a\T\t\S\s\O\o]*  { return BAD; }

%%
