#include"nonterminal.h"
#include<vector>

#ifndef GRAMMAR_H
#define GRAMMAR_H

class Grammar {
 private:
  std::vector<Nonterminal*> nvec;
 public:
  
  void add(Nonterminal* nt) {
    nvec.push_back(nt);
  }

  std::vector<Nonterminal*> getNonterminals() {
    return nvec;
  }
  
};

#endif
