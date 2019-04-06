%{

#include "node.h"
#include "globals.h"
#include <stdlib.h>
#include <stdio.h>

#define MAXOPERANDS  100
#define MAXOPERATORS 100

extern int   yylex ();
extern char* yytext;

node* operand_stack[MAXOPERANDS];
int   operator_stack[MAXOPERATORS];
node* lhs;
node* rhs;
node* root;

int operator_sp = 0;
int operand_sp = 0;
int repeatDepth = 0;

int yyerror (char* s) {
  return 1;
}

%}

%token SYM
%token NUM
%token EOLN
%token BAD
%token LSHIFT
%token RSHIFT
%token PINC
%token PDEC
%token STOP
%token REPEAT

%union {
  double num;
  char* sym;
}

%type <num> NUM
%type <sym> SYM

%start program

%%

program:
  STOP EOLN
    {
      if (repeatDepth == 1) {
	repeatDepth = 0;
	if (repeatDepth == 0) {
	  c.setRoot (root);
	  operand_sp = operator_sp = 0;
	  cout << "OUTPUT:  " << c.evaluate () << endl;
	}
	cout << "INPUT:   " << flush;
      }
      else if (repeatDepth > 1) {
	c.setRoot (NULL);
	return 0;
      }
      else {
	repeatDepth--;
      }
    }
  |
  command EOLN
  ;

command:
  exp
    {
      if (repeatDepth == 0) {
	c.setRoot (root);
	operand_sp = operator_sp = 0;
	cout << "OUTPUT:  " << c.evaluate () << endl;
      }
      cout << "INPUT:   " << flush;
    }
  |
  command EOLN exp
    {
      if (repeatDepth == 0) {
	c.setRoot (root);
	operand_sp = operator_sp = 0;
	cout << "OUTPUT:  " << c.evaluate () << endl;
      }
      cout << "INPUT:   " << flush;
    }
  |
  REPEAT NUM
    {
      cout << "i got here" << endl;
      root = new repeat (3);
      repeatDepth++;
      cout << "INPUT:   " << flush;
    }
  ;  

exp:
  EOLN exp
  |
  term
  |
  exp addop term
    {
      rhs = operand_stack[--operand_sp];
      lhs = operand_stack[--operand_sp];
      switch (operator_stack[--operator_sp]) {
      case '+':
	root = new op (lhs, rhs, ADD);
	break;
      case '-':
	root = new op (lhs, rhs, SUB);
	break;
      case LSHIFT:
	root = new op (lhs, rhs, LSH);
	break;
      case RSHIFT:
	root = new op (lhs, rhs, RSH);
	break;
      }
      operand_stack[operand_sp++] = root;
    }
  ;

term:
  fact
  |
  term mulop fact
    {
      rhs = operand_stack[--operand_sp];
      lhs = operand_stack[--operand_sp];
      switch (operator_stack[--operator_sp]) {
      case '*':
	root = new op (lhs, rhs, MUL);
	break;
      case '/':
	root = new op (lhs, rhs, DIV);
	break;
      }
      operand_stack[operand_sp++] = root;
    }
  ;

fact:
  SYM
    {
      if (c.getSym ($1) == NULL) {
	c.setSym (new symbol($1, 0));
      }
      operand_stack[operand_sp++] = c.getSym ($1);
      root = operand_stack[operand_sp - 1];
    }
  |
  NUM
    {
      operand_stack[operand_sp++] = new number ($1);
      root = operand_stack[operand_sp - 1];
    }
  |
  SYM '=' exp
    {
      if (c.getSym ($1) == NULL) {
	c.setSym (new symbol ($1, 0));
      }
      lhs = c.getSym ($1);
      rhs = operand_stack[--operand_sp];
      root = new op (lhs, rhs, EQL);
      operand_stack[operand_sp++] = root;
    }
  |
  '-' exp
    {
      root = new op (NULL, operand_stack[--operand_sp], NEG);
      operand_stack[operand_sp++] = root;
    }
  |
  PINC exp
    {
      root = new op (NULL, operand_stack[--operand_sp], INC);
      operand_stack[operand_sp++];
    }
  |
  PDEC exp
    {
      root = new op (NULL, operand_stack[--operand_sp], DEC);
      operand_stack[operand_sp++];
    }
  |
  '(' exp ')'
  ;

addop:
  '+'
    {
      operator_stack[operator_sp++] = '+';
    }
  |  
  '-'
    {
      operator_stack[operator_sp++] = '-';
    }
  |
  LSHIFT
    {
      operator_stack[operator_sp++] = LSHIFT;
    }
  |
  RSHIFT
    {
      operator_stack[operator_sp++] = RSHIFT;
    }
  ;

mulop:
  '*'
    {
      operator_stack[operator_sp++] = '*';
    }
  |
  '/'
    {
      operator_stack[operator_sp++] = '/';
    }
  ;

%%
