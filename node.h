/**
 *  @author:  chase isabelle
 *  @file:  node.h
 *  @project:  calculator
 *
 *  @description:  super-class node class def.  Also includes the class defs for direct decendents of class node.
 */


#ifndef _node_h_
#define _node_h_


#include <iostream>         //< standard i/o methods


#define MAXTREES 1000       //< max number of roots for repeat construct
#define MAXSYMBOLS 1000     //< max number of local symbols for repeat construct


using namespace std;        //< using standard namespace


/// this typedef is for the op class
typedef enum {INVALID, ADD, SUB, INC, DEC, MUL, DIV, LSH, RSH, NEG, EQL} opType;


/// pre-defs for op/number classes
class op;
class number;
class symbol;


/// node class definition
/// super-class
class node {
  
 private:

  ///! No Private Members!

 public:

  /// default constructor
  node ();

  /// destructor
  virtual ~node ();

  /// pure virtual method
  virtual number eval () const;

  /// method is for number child class
  /// @param value is ignored
  void setValue (const double& value);

  /// keepFlag determines weather his node can be destroyed by the calc
  /// @return false for just nodes (true for some child classes)
  virtual bool keepFlag () const;

};


/// op class def (child of node)
/// op is the operator class
class op : public node {

 private:

  /// operation will specifiy the operation that this operator will perform
  opType operation;

  /// lhs is a pointer to the left hand side of the operator
  node* lhs;

  /// rhs is a pointer to the right hand side of the operator
  node* rhs;

 public:

  /// constructor
  /// @param lhs will be this's lhs pointer
  /// @param rhs will be this's rhs pointer
  /// @param operation will be this's operation
  op (node* lhs, node* rhs, const opType& operation);

  /// destructor
  ~op ();

  /// eval will evaluate the operation and return a number
  number eval () const;

  /// keepFlag will be false for ops
  /// @return false
  bool keepFlag () const;
  
};


/// number is the class for a number object
/// number objects contain information about a number value
class number : public node {
  
 private:

  /// value will be the "value" of the number
  double value;

 public:

  /// constructor
  /// @param vlaue will be this's value
  number (const double& value);

  /// destrcutor
  virtual ~number ();

  /// setValue will set the value of this number
  /// @param value will be this's new value
  void setValue (const double& value);

  /// getValue will get the value fo the number
  /// @return a copy of the value of his number
  double getValue () const;

  /// eval will return this number
  /// @return a copy of this
  number eval () const;

  /// keepFlag is false for numbers
  /// @return false
  virtual bool keepFlag () const;

  /// overloaded addition operator
  /// @param other is the rhs of ths + operation
  /// @return this number plus the other number, their sum
  number operator+ (const number& other) const;

  /// overloaded subraction operator
  /// @param other is the number on the right of the operator
  /// @return this number minus the other number
  number operator- (const number& other) const;

  /// overloaded multiplication operator
  /// @param other is the other number
  /// @return this number times the other number, their product
  number operator* (const number& other) const;

  /// overloaded division operator
  /// @param other is the denominator
  /// @return this number divided by other number
  number operator/ (const number& other) const;

  /// overloaded pre-increment operator
  /// @return this number plus 1
  number operator++ () const;

  /// overloaded pre-decrement operator
  /// @return this number minus 1
  number operator-- () const;

  /// overloaded left shift operator
  /// @param other is the rhs of the operator
  /// @return this number shift over by other number to the left
  number operator<< (const number& other) const;

  /// overloaded right shift op
  /// @param other is the rhs of the op
  /// @return this number shifted right by other number
  number operator>> (const number& other) const;

};


/// symbol class def
class symbol : public number {

 private:

  /// each symbol has an id
  string id;

 public:

  /// constructor
  symbol (const string& id, const double& value);

  /// destructor
  ~symbol ();

  /// getId will return the id of this symbol
  /// @return a copy of id
  string getId () const;

  /// keepFlag will determine weather this node can be deleted by the calc
  /// @return will return true for symbols because they are part of the symbol table
  bool keepFlag () const;

};


/// repeat clas def
class repeat : public node {
  
 private:

  /// each repeat will have an iteration value
  int iterationValue;

  /// each repeat will have an array of nodes
  /// that are eval trees
  node* roots[MAXTREES+1];

  /// repeat will have a symbol table (local)
  symbol* symTab[MAXSYMBOLS+1];

 public:

  /// constructor
  repeat (const int& iterationValue);

  /// destructor
  ~repeat ();

  /// addTree will add a tree to the roots mmber
  /// @param newRoot is the new tree's root
  void addTree (node* newRoot);

  /// eval will evaluate all the trees in roots
  /// @return a dummy number
  number eval () const;

};


#endif
