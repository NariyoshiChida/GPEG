#include<string>
#include<map>
#include<set>
#include<vector>
#include"grammar.h"
#include"node.h"

#ifndef GENERALIZED_PACKRAT_PARSER_H
#define GENERALIZED_PACKRAT_PARSER_H

#define OFF -1

namespace generalized_packrat_parser {
  
  // GPEG parser by Recursive Descent
  class GeneralizedPackratParser {
  private:
    //const bool inline_ = true;
    // Options
    const bool matching_time = true;
    const bool packrat       = true;


    const std::string ptr_name = "i";
    const std::string backtracking_ptr_for_packrat = "backtracking_ptr_for_packrat";
    const std::string succ_buffer = "result";
    Grammar* grammar;
    int suffix;
    std::vector<std::string> buffer;
    std::vector<std::string> prot;
    int first_ID;
    int last_ID;

    int next_label;
    void writeln(std::string,int,int);
    void write(std::string,int,int);
    void write_packrat_return(int);
    void write_packrat_assign(int,int);
    void encode(Node*,int,int);/**/
    void encode(Nonterminal*,int,int);
    void encode(Slash*,int,int);
    void encode(Alternation*,int,int);
    void encode(Char*,int,int);/**/
    void encode(And*,int,int);/**/
    void encode(Not*,int,int);/**/
    void encode(Sequence*,int,int);/**/
    void encode(Question*,int,int);
    void encode(Star*,int,int);
    void encode(Plus*,int,int);
    void encode(Any*,int,int);/**/
    void encode(Range*,int,int);/**/
    void encode(Gpeg_string*,int,int);/**/
    void encode(Grouping*,int,int);
    void dump();

  public:

    GeneralizedPackratParser(){
      suffix = 0;
      grammar = nullptr;
      buffer.clear();
      prot.clear();
    }
    
    // encode the grammar
    void encode();

    void set(Grammar*);

  };

} // generalized_packrat_parser

#endif // GENERALIZED_PACKRAT_PARSER_H
