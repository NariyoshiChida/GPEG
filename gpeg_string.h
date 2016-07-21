#ifndef GPEG_STRING_H
#define GPEG_STRING_H

#include<string>

class Gpeg_string {
 private:
  std::string str;
 public:
  void set(std::string tmp) { str = tmp; }
  std::string get() { return str; }
};
#endif
