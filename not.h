#ifndef NOT_H
#define NOT_H

class Not {
 private:
  Node* next;
 public:
  void set(Node* tmp) { next = tmp; }
  Node* get() { return next; }
};

#endif
