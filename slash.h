#ifndef SLASH_H
#define SLASH_H

#include<deque>
#include<iostream>
#include<string>
#include"node.h"

class Node;

class Slash {
 private:
  std::deque<Node*> alternate;
 public:
  Slash() {
    alternate.clear();
  }
  void add(Node* tmp) {
    alternate.push_back(tmp);
  }
  std::deque<Node*> getAlternates() {
    return alternate;
  }
};

#endif
