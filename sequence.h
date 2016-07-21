#ifndef SEQUENCE_H
#define SEQUENCE_H

#include<deque>

class Sequence {
 private:
  std::deque<Node*> sequence;
 public:
  void add(Node* tmp) {
    sequence.push_back(tmp);
  }
  std::deque<Node*> getSequence() {
    return sequence;
  }
};

#endif
