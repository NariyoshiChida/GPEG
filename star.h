#ifndef STAR_H
#define STAR_H

class Star {
 private:
  Node* next;
 public:
  void set(Node* tmp) { next = tmp; }
  Node* get() { return next; }
};

#endif
