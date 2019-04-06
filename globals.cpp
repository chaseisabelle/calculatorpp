/**
 *  @author:  chase isabelle
 *  @file:  globals.cpp
 *  @project:  calculator
 *
 *  @description:  source code for the globals.h defs
 */


#include "globals.h"


void utils::printError (const string& message) {
  // print default error display
  cout << "+--------" << flush;
  for (unsigned int i = 0 ;
       i <= message.length () ;
       i++) {
    cout << "-" << flush;
  }
  cout << "---------+" << endl;
  cout << "| !ERROR! " << flush;
  cout << message << flush;
  cout << " !ERROR! |" << endl;
  cout << "+--------" << flush;
  for (unsigned int i = 0 ;
       i <= message.length () ;
       i++) {
    cout << "-" << flush;
  }
  cout << "---------+" << endl;
}

void utils::printError (const char* message) {
  // pass this to the string print eror
  printError (string (message));
}
       
