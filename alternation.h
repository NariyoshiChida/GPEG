#ifndef ALTERNATION_H
#define ALTERNATION_H

#include<deque>
#include<iostream>
#include"node.h"
class Node;

class Alternation {
 private:
  std::deque<Node*> alternate;
 public:
  void add(Node* tmp) {
    alternate.push_back(tmp);
  }
  std::deque<Node*> getAlternates() {
    return alternate;
  }
};

#endif
