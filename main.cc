#include<bits/stdc++.h>
#include "gpeg_parser.h"

#define REP(i,s,n) for(int i=s;i<n;++i)
#define rep(i,n) REP(i,0,n)

using namespace std;

void code(Grammar *g) {
  vector<Nonterminal*> vec = g->getNonterminals();
  cout << "the nubmer of Nonterminals = " << vec.size() << endl;
  rep(i,(int)vec.size()) {
    Node* tmp = new Node;
    tmp->setType(0);
    tmp->values[0] = vec[i];
    cout << "[+[" << i+1 << "]+] " << tmp->toString() << endl;
  }
}



int main() {
  //string gpeg = "   nari <-.* \n yoshi <- 'aaa'\n";
  string gpeg="";
  string buf;
  while( getline(cin,buf) ) gpeg += (buf + "\n");
  gpeg_parser::GPEGParser tmp(gpeg);
  //tmp.debug();
  //std::cout << "vvv------v------vvv" << std::endl;
  Grammar* g = tmp.parse();
  //puts("---encoding finished---");
  //code(g);
  //std::cout << "^^^------^------^^^" << std::endl;
  //puts("");
  tmp.encode();
}
