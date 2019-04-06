/**
 *  @author:  chase isabelle
 *  @file:  node.cpp
 *  @project:  calculator
 */


#include "node.h"


//////////////////////////////
//  node class source code  //
//////////////////////////////

node::node () {
  // empty body
}

node::~node () {
  // empty body
}

number node::eval () const {
  // empty body
  number num (0);
  return num;
}

void node::setValue (const double& value) {
  // empty body;
}

bool node::keepFlag () const {
  // return false
  return false;
}

//////////////////////////
// op class source code //
//////////////////////////

op::op (node* lhs, node* rhs, const opType& operation) {
  // set the members accordingly...
  this->lhs = lhs;
  this->rhs = rhs;
  this->operation = operation;
}

op::~op () {
  // destroy lhs and rhs

  // destroying lhs...
  if (!lhs->keepFlag ()) {
    delete lhs;
  }

  // destroying rhs...
  if (!rhs->keepFlag ()) {
    delete rhs;
  }
}

number op::eval () const {
  // evaluate according to this's operation
  switch (operation) {
  case ADD:
    return lhs->eval () + rhs->eval ();
  case SUB:
    return lhs->eval () - rhs->eval ();
  case INC:
    return ++rhs->eval ();
  case DEC:
    return --rhs->eval ();
  case MUL:
    return lhs->eval () * rhs->eval ();
  case DIV:
    return lhs->eval () / rhs->eval ();
  case LSH:
    return lhs->eval () << rhs->eval ();
  case RSH:
    return lhs->eval () >> rhs->eval ();
  case NEG:
    {
      // use curly-bracket for new scope with initialization of n
      number n (-(rhs->eval ()).getValue ());
      return n;
    }
  case EQL:
    static_cast<symbol*>(lhs)->setValue ((rhs->eval ()).getValue ());
    return lhs->eval ();
  case INVALID:
    number num (0);
    return num;
  }

  // code shouldn't get this far, but just incase
  number num (0);
  return num;
}

bool op::keepFlag () const {
  // return flase
  return false;
}

//////////////////////////////
// number class source code //
//////////////////////////////

number::number (const double& value) {
  // assign according members
  this->value = value;
}

number::~number () {
  // empty body
}

void number::setValue (const double& value) {
  // set this's vlaue to value
  this->value = value;
}

double number::getValue () const {
  // return a copy of this's value
  return value;
}

number number::eval () const {
  // return a copy of this number
  return *this;
}

bool number::keepFlag () const {
  // return false
  return false;
}

number number::operator+ (const number& other) const {
  // add the values of the two numbers together and return their
  // sum as a number object
  number sum (this->value + other.value);
  return sum;
}

number number::operator- (const number& other) const {
  // subtract the numbers and return their sum
  number sum (this->value - other.value);
  return sum;
}

number number::operator* (const number& other) const {
  // multiply the numbers and return their product
  number product (this->value * other.value);
  return product;
}

number number::operator/ (const number& other) const {
  // divide the numbers
  number product (this->value / other.value);
  return product;
}

number number::operator++ () const {
  // inrement this->value by one
  number num (this->value + 1);
  return num;
}

number number::operator-- () const {
  // sbtract this number by 1
  number num (this->value - 1);
  return num;
}

number number::operator<< (const number& other) const {
  // shift this number by the other number
  int thisValue ((int)this->value);
  int otherValue ((int)other.value);
  number num ((double)(thisValue << otherValue));
  return num;
}

number number::operator>> (const number& other) const {
  // shift this number by the other number
  int thisValue ((int)this->value);
  int otherValue ((int)other.value);
  number num ((double)(thisValue >> otherValue));
  return num;
}


//////////////////////////////
// symbol class source code //
//////////////////////////////


symbol::symbol (const string& id, const double& value) : number (value) {
  // constructor
  this->id = id;
}

symbol::~symbol () {
  // destrcutor
  // empty body
}

bool symbol::keepFlag () const {
  // return true for all symbols
  return true;
}

string symbol::getId () const {
  // return a copy of id
  return id;
}


//////////////////////////////
// repeat class source code //
//////////////////////////////


repeat::repeat (const int& iterationValue) {
  this->iterationValue = iterationValue;
}

repeat::~repeat () {
  delete[] symTab;
  delete[] roots;
}

void repeat::addTree (node* newRoot) {
  unsigned int i;
  for (i = 0 ;
       i <= MAXTREES && roots[i] != NULL ;
       i++);

  roots[i] = newRoot;
}

number repeat::eval () const {
  for (unsigned int ival = 1 ;
       (int)ival <= iterationValue ;
       ival++) {
    for (unsigned int i = 0 ;
	 i <= MAXTREES ;
	 i++) {
      cout << ">  " << (roots[i]->eval ()).getValue () << endl;
    }
  }

  return number (0);
}
