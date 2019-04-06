/**
 *  @author:  chase isabelle
 *  @file:  calc.cpp
 *  @project:  calculator
 *
 *  @description:  source code for calc.h
 */


#include "calculator.h"        //< for calc class def


////////////////////////////
// calc class source code //
////////////////////////////

calculator::calculator () {
  // set symTab pointer to NULL
  for (unsigned int i = 0 ;
       i <= MAXSYMBOLS ;
       i++) {
    symTab[i] = NULL;
  }

  // set the scopIndex
  scopeIndex = 0;
}

calculator::~calculator () {
  // delete root of the eval tree
  delete root;
}

void calculator::setRoot (node* root) {
  // destroy the old root
  if (root != NULL) {
    if (root->keepFlag ()) {
      //delete this->root;
    }
  }

  // and set the root to the new root
  this->root = root;
}

node* calculator::getRoot () const {
  // reurn the pointer to the root nodfe
  return root;
}

double calculator::evaluate () const {
  // evalutate the root
  return ((this->root)->eval ()).getValue ();
}

number calculator::eval () const {
  // evaluate the root
  return this->root->eval ();
}

void calculator::setSym (symbol* s) {
  // set the symbol and value for the symbol table

  // first, iterate through the array to see if symbol exsists
  for (int i = scopeIndex ;
       i >= 0 ;
       i--) {
    
    // first, see if the symbol needs to be set into the table
    if (symTab[i] == NULL) {
      symTab[i] = s;
      return;
    }

    // compare each symbol's id to s's id
    if (symTab[i]->getId () == s->getId ()) {
      delete symTab[i];
      symTab[i] = s;
      return;
    }
  }

  // if the loops cannot find a matching symbol then
  // s is a new symbol oin he tbale
  scopeIndex += 1;
  if (symTab[scopeIndex] != NULL) {
    delete symTab[scopeIndex];
  }
  symTab[scopeIndex] = s;
}

symbol* calculator::getSym (const string& id) const {
  // return  a pointer to the number with respect to the symbol
  for (int i = scopeIndex ;
       i >=  0;
       i--) {
    if (symTab[i] == NULL) {
      return NULL;
    }
    if (symTab[i]->getId () == id) {
      return symTab[i];
    }
  }

  return NULL;
}

symbol* calculator::getSym (const char* symbol) const {
  // return string overloaded method
  return this->getSym (string (symbol));
}

