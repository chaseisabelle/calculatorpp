/**
 *  @author:  chase isabelle
 *  @file:  main.cpp
 *  @project:  calculator
 *
 *  @description:  main function
 */


#include "globals.h"          //< globals vars/defs
#include "y.tab.h"            //< parse table/defs


extern int yyparse ();        //< parser, which will call the scanner itself

calculator c;                 //< global def of main calculator
bool quitFlag = false;        //< quitFlag will determine if the user wishes to quit program

int main (int argc, char* argv[]) {
  
  // execute scanner and parser
  do {
    // prompt user
    cout << "INPUT:   " << flush;

    // local flags
    bool quitFlag (false);

    // check program's status
    switch (yyparse ()) {
    case 0:
      // user wishes to quit
      quitFlag = true;
      break;
    case 1:
      // parser has returned a parsing error
      utils::printError ("Parsing Error");
      quitFlag = true;
      break;
    case 2:
      // calculator returned calculating error
      utils::printError ("Calculation Error");
      quitFlag = true;
      break;
    }
  } while (quitFlag);
  
  // normal termination
  cout << "Program Terminating." << endl;
  return 0;

}
