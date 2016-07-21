#ifndef PLUS_H
#define PLUS_H

class Plus {
 private:
  Node* next;
 public:
  void set(Node* tmp) { next = tmp; }
  Node* get() { return next; }
};

#endif
