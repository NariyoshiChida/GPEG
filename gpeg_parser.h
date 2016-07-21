#include<string>
#include<map>
#include<set>
#include"grammar.h"
#include"node.h"

#ifndef GPEG_PARSER_H
#define GPEG_PARSER_H

#define OFF -1

namespace gpeg_parser {
  
  // GPEG parser by Recursive Descent
  class GPEGParser {
  private:
    bool compiled;
    int ptr, clen, indent;
    std::string context;
    Grammar* grammar = nullptr;
    void pSpacing();
    Grammar* pGrammar();
    Nonterminal* pDefinition();
    std::string pIdentifier();
    void pLEFTARROW();
    Node* pExpression();
    char pSLASH();
    char pALTERNATION();
    Node* pSequence();
    bool isDefinition();
    bool isSequence();
    Node* pSuffix();
    void pAND();
    void pNOT();
    void pQUESTION();
    void pSTAR();
    void pPLUS();
    Node* pPrimary();
    void pOPEN();
    void pCLOSE();
    void pDOT();
    std::string pLiteral();
    char pChar();
    std::string pRange();
    
    void delete_grammar();
    void delete_dfs(Node*);
    void delete_dfs(Nonterminal*);
    void delete_dfs(Slash*);
    void delete_dfs(Alternation*);
    void delete_dfs(Char*);
    void delete_dfs(And*);
    void delete_dfs(Not*);
    void delete_dfs(Sequence*);
    void delete_dfs(Question*);
    void delete_dfs(Star*);
    void delete_dfs(Plus*);
    void delete_dfs(Any*);
    void delete_dfs(Range*);
    void delete_dfs(Gpeg_string*);
    void delete_dfs(Grouping*);


    int next_label;
    void writeln(std::string);
    void write(std::string);
    void write_add();
    void write_pop();
    void write_create();
    void dispatch(std::string);
    void encode(Node*,int);
    void encode(Nonterminal*,int);
    void encode(Slash*,int);/**/
    void encode(Alternation*,int);
    void encode(Char*,int);
    void encode(And*,int);/**/
    void encode(Not*,int);/**/
    void encode(Sequence*,int);
    void encode(Question*,int);/**/
    void encode(Star*,int);/**/
    void encode(Plus*,int);/**/
    void encode(Any*,int);
    void encode(Range*,int);
    void encode(Gpeg_string*,int);
    void encode(Grouping*,int);
    
  public:

  GPEGParser(std::string context) : compiled(false), ptr(0), context(context) {
      grammar = nullptr;
      clen = (int)context.size();
      indent = 0;
    }
    ~GPEGParser(){ if( grammar != nullptr ) delete_grammar();  }
    
    // parse the context
    // if already parsed (i.e. compiled == true), return the result (Node* root)
    Grammar* parse();
    
    // reset the context
    void reset(std::string tmp);

    // encode the grammar
    void encode();
    

    void debug();

  };

} // gpeg_parser

#endif // GPEG_PARSER_H
