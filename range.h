#ifndef RANGE_H
#define RANGE_H

#include<string>

class Range {
 private:
  std::string characters;
 public:
 Range() : characters("") {}
  void set(std::string tmp) { characters = tmp; }
  std::string get() { return characters; }
};

#endif
