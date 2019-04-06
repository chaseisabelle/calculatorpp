/**
 *  @author:  chase isabelle
 *  @file:  globals.h
 *  @project:  calculator
 *
 *  @description:  this file contains all the global variables/defs for the calculator
 */


#ifndef _globals_h_
#define _globals_h_


#include <iostream>          //< all standard i/o methods
#include "calculator.h"      //< for calc class def, globals variable c


#define MAXREPEATS 1000


using namespace std;         //< using standard namespace


extern calculator c;         //< global calculator driver


/// utils namespace def
/// includes all defult utility methods
namespace utils {

  /// printError is a default error alert for program
  /// @param message is the error message that will be displayed
  void printError (const string& message);
  void printError (const char* message);

};


#endif
