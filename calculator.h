/**
 *  @author:  chase isabelle
 *  @file:  calc.h
 *  @project:  calculator
 *
 *  @description:  this is the user interface for the calculator
 */


#ifndef _calc_h_
#define _calc_h_


#include "node.h"        //< for node/op/number/symbol class defs


#define MAXSYMBOLS 1000  //< max number of symbols in symbolTable
#define MAXROOTS   1000  //< max number of root in repeat objects


/// calc class def
/// calc is the driver for the calculator
class calculator : public node {

 protected:

  /// root is start of the main evaluation tree for the calculator
  node* root;

  /// symTab is the symbol table for this calc
  symbol* symTab[MAXSYMBOLS+1];

  /// scopeIndex is the index of the most local scope
  int scopeIndex;

 public: 

  /// constrcutor
  calculator ();

  /// destructor
  ~calculator ();

  /// setRoot will set the root of the eval tree for his calc
  /// @param root is the ew root for the tree
  void setRoot (node* root);

  /// getRoot will get the pointer to the root node of the eval tree
  /// @return the pointer to the root node of the eval tree
  node* getRoot () const;

  /// evaluate will evaluate this's root (main eval tree)
  double evaluate () const;

  /// eval will evaluate this's root and return a nmber objetc
  number eval () const;

  /// setSym will set a symbol in this's symTab
  /// @param entry is the symbol entry for the symTab
  void setSym (symbol* entry);

  /// getSym will return a pointer to a number in the symbol table
  /// @param symbol is this the name of the number's symbol
  /// @return the pointer to the symbol's number
  symbol* getSym (const string& id) const;
  symbol* getSym (const char* id) const;

};


#endif
