#ifndef NODE_H
#define NODE_H

#include"slash.h" 
#include"alternation.h" 
#include"char.h"
#include"sequence.h"
#include"and.h"
#include"not.h"
#include"question.h"
#include"star.h"
#include"plus.h"
#include"any.h"
#include"range.h"
#include"gpeg_string.h"
#include"grouping.h"
#include<iostream>
#include<string>
#include<cassert>


#define MAX_TYPE 14

#define NONTERMINAL 0
#define SLASH 1
#define ALTERNATION 2
#define CHAR 3
#define AND 4
#define NOT 5
#define SEQUENCE 6
#define QUESTION 7
#define STAR 8
#define PLUS 9
#define ANY 10
#define RANGE 11
#define GPEG_STRING 12
#define GROUPING 13

class Node {
 public:
  int type;
  void* values[MAX_TYPE];

 Node():type(-1){}
  
  void setType(int);  

  void add(Node*);

  void setValue(Nonterminal*);

  void setValue(Slash*);

  void setValue(Alternation*);

  void setValue(Sequence*);

  void setValue(Char*);

  void setValue(And*);

  void setValue(Not*);

  void setValue(Question*);

  void setValue(Star*);

  void setValue(Plus*);

  void setValue(Any*);

  void setValue(Range*);

  void setValue(Gpeg_string*);

  void setValue(Grouping*);

  std::string toString();
  
};

#endif
