#  Chase Isabelle
#  Calculator
#  Makefile


main:  main.cpp globals.o calculator.o node.o lex.yy.o y.tab.o
	g++ -g -Wall -o main main.cpp globals.o calculator.o node.o lex.yy.o y.tab.o -lfl

globals.o:  globals.h globals.cpp
	g++ -g -Wall -c globals.cpp

calculator.o:  calculator.h calculator.cpp
	g++ -g -Wall -c calculator.cpp

node.o:  node.h node.cpp
	g++ -g -Wall -c node.cpp

lex.yy.o:  y.tab.h lex.yy.c
	g++ -g -Wall -c lex.yy.c

y.tab.o:  y.tab.c y.tab.h
	g++ -g -Wall -c y.tab.c

lex.yy.c:  scanner.l
	flex scanner.l

y.tab.c y.tab.h:  parser.y
	bison -d -y -v parser.y


clean:
	rm -f *.o *~ *# main y.output lex.yy.c y.tab.c y.tab.h core
	clear