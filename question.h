#ifndef QUESTION_H
#define QUESTION_H

class Question {
 private:
  Node* next;
 public:
  void set(Node* tmp) { next = tmp; }
  Node* get() { return next; }
};

#endif
