#ifndef CHAR_H
#define CHAR_H

#include<string>
#include<iostream>

class Char {
 private:
  char value;
 public:
  void setValue(char c) {
    value = c;
  }
  char getValue() {
    return value;
  }
};

#endif
