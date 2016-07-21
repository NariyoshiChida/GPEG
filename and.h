#ifndef AND_H
#define AND_H

class And {
 private:
  Node* next;
 public:
  void set(Node* tmp) { next = tmp; }
  Node* get() { return next; }
};

#endif
