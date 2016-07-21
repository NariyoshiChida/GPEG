
#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include<string>

class Node;

class Nonterminal {
 private:
  std::string name;
  Node* expression;
  
 public:

 Nonterminal() : expression(nullptr) {}
  
  void setName(std::string tmp) {
    name = tmp;
  }

  std::string getName() {
    return name;
  }

  void setExpression(Node* tmp) {
    expression = tmp;
  }

  Node* getExpression() {
    return expression;
  }

};

#endif
