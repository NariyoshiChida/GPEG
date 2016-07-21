#ifndef GROUPING_H
#define GROUPING_H

#include"node.h"

class Grouping {
 private:
  Node *next;
 public:
  void set(Node *tmp) { next = tmp; }
  Node* get() { return next; }
};

#endif
