#include"generalized_packrat_parser.h"
#include"grammar.h"
#include"slash.h"
#include"char.h"
#include"alternation.h"
#include"node.h"
#include"sequence.h"
#include"gpeg_string.h"
#include<iostream>
#include<string>
#include<vector>
#include<cassert>
#include<deque>
#include<sstream>
#include<cmath>
#include<map>
#include<set>
#include<functional>

using generalized_packrat_parser::GeneralizedPackratParser;

//bool show_trace = false; // duplicateになる

std::ostream& operator << (std::ostream& os, const GeneralizedPackratParser& gpp) {
  os << "[[Generalized Packrat Parser]]";
  return os;
}

inline std::string itos(int i) { std::stringstream ss; ss << i; return ss.str(); }


void GeneralizedPackratParser::set(Grammar *tmp) { grammar = tmp; }

// <--- encode --->

// replaced by dispatch_macro

void GeneralizedPackratParser::writeln(std::string s,int ID=-1,int indent=0) {
  if( ID == -1 ) {
    std::cout << std::string(indent*2,' ') << s << std::endl;
  } else {
    assert( ID < (int)buffer.size() );
    buffer[ID] += ( std::string(indent*2,' ') + s + "\n" );
  }
}

void GeneralizedPackratParser::write(std::string s,int ID=-1,int indent=0) {
  if( ID == -1 ) {
    std::cout << std::string(indent*2,' ') << s;
  } else {
    assert( ID < (int)buffer.size() );
    buffer[ID] += ( std::string(indent*2,' ') + s );
  }
}

void GeneralizedPackratParser::dump() {
  std::cout << buffer[first_ID];
  std::cout << std::endl;
  for(int i=0;i<(int)prot.size();++i) {
    std::cout << "deque<int> " << prot[i] << "();" << std::endl;
  }
  std::cout << std::endl;
  for(int i=0;i<(int)buffer.size();++i) {
    if( i == first_ID || i == last_ID ) continue;
    std::cout << buffer[i];
    std::cout << std::endl;
  }
  std::cout << buffer[last_ID];
}

void GeneralizedPackratParser::write_packrat_return(int ID) {
  // -1 is for adjustment by first_ID
  writeln("if(memo.count(key("+itos(ID-1)+","+ptr_name+"))) {",ID,1);
  writeln("return memo[key("+itos(ID-1)+","+ptr_name+")];",ID,2);
  writeln("}",ID,1);
  writeln("int " + backtracking_ptr_for_packrat + itos(ID-1) +"=" + ptr_name + ";",ID,1);
}

void GeneralizedPackratParser::write_packrat_assign(int ID,int indent) {
  writeln("return memo[key("+itos(ID-1)+","+backtracking_ptr_for_packrat+itos(ID-1)+")] = result;",ID,indent);
}

void GeneralizedPackratParser::write_hash_function(int ID,int indent,int base_size) {
  long long base = 1;
  for(int i=0;i<base_size;++i) {
    base *= 10LL;
  }
  writeln("const long long base = " + itos(base) + "; // for hash",ID,indent);
  writeln("",ID,indent);
  writeln("namespace std {",ID,indent++);
  writeln("template <>",ID,indent);
  writeln("class hash<std::pair<int, int>> {",ID,indent++);
  writeln("public:",ID,indent);
  writeln("size_t operator()(const std::pair<int, int>& x) const {",ID,indent++);
  writeln("return base * x.second + x.first;",ID,indent);
  writeln("}",ID,--indent);
  writeln("};",ID,--indent);
  writeln("}",ID,--indent);
}

void GeneralizedPackratParser::encode() {
  buffer.clear();
  first_ID = buffer.size();
  buffer.push_back("");
  //writeln("#include<bits/stdc++.h>",first_ID);
  writeln("#include<iostream>",first_ID);
  writeln("#include<chrono>",first_ID);
  writeln("#include<deque>",first_ID);
  writeln("#include<cassert>",first_ID);
  writeln("#include<climits>",first_ID);
  if( packrat ) {
    if( hash_map ) {
      writeln("#include<unordered_map>",first_ID);
    } else {
      writeln("#include<map>",first_ID);
    }
  }
  writeln("#include<algorithm>",first_ID);
  writeln("",first_ID);
  writeln("#define FAIL -1",first_ID);
  writeln("",first_ID);
  writeln("using namespace std;",first_ID);
  writeln("",first_ID);
  writeln("int m;",first_ID);
  writeln("int "+ptr_name+";",first_ID);
  writeln("string I;",first_ID);

  if( packrat ) {
    writeln("typedef pair<int,int> key;",first_ID);

  }

  std::vector<Nonterminal*> nonterminals = grammar->getNonterminals();
  assert( nonterminals.size() );
  for(int i=0;i<(int)nonterminals.size();++i) {
    encode(nonterminals[i],-1,0);
  }

  if( hash_map ) {
    int base_size = (int)log10(suffix) + 1;
    write_hash_function(first_ID,0,base_size);
  }

  if(packrat) {
    if( hash_map ) {
      writeln("unordered_map<key,deque<int>> memo;",first_ID);
    } else {
      writeln("map<key,deque<int>> memo;",first_ID);
    }
  }

  

  last_ID = buffer.size();
  buffer.push_back("");
  writeln("",last_ID);
  writeln("int main() {",last_ID);
  writeln("getline(cin,I);",last_ID,1);
  writeln("m = (int)I.size();",last_ID,1);
  
  writeln(ptr_name+"=0;",last_ID,1);
  // 完全マッチにしたければ parse_XXX(0) == true && ptr_name == (int)I.size()
  if( matching_time ) {
    writeln("auto st = chrono::system_clock::now();",last_ID,1);
  }
  writeln("deque<int> result = parse_"+nonterminals[0]->getName()+"();",last_ID,1);
  if( matching_time ) {
    writeln("auto ed = chrono::system_clock::now();",last_ID,1);
  }
  writeln("sort(result.begin(),result.end());",last_ID,1);
  writeln("result.erase(unique(result.begin(),result.end()),result.end());",last_ID,1);
  writeln("for(int i=0;i<(int)result.size();++i) {",last_ID,1);
  writeln("if(result[i] == -1) {",last_ID,2);
  writeln("cout << \"fail\" << endl;",last_ID,3);
  writeln("} else {",last_ID,2);
  writeln("cout << \"consumed :: [\" << result[i] << \"/\" << m << \"]\" << endl;",last_ID,3);
  writeln("}",last_ID,2);
  writeln("}",last_ID,1);

  if( matching_time ) {
    writeln("cout << \"matching time :: \" << chrono::duration_cast<chrono::milliseconds>(ed-st).count() << \"msec\" << endl;",last_ID,1);
  }
  //writeln("cout << (parse_"+nonterminals[0]->getName()+"()?\"success\":\"fail\") << endl;",last_ID,1);
  writeln("return 0;",last_ID,1);
  writeln("}",last_ID); // main

  dump();
}

void GeneralizedPackratParser::encode(Node *node,int ID,int indent) {
  int type = node->type;
  if( type == NONTERMINAL ) {
    Nonterminal* tmp = (Nonterminal*)node->values[NONTERMINAL];
    encode(tmp,ID,indent);
  } else if( type == SLASH ) {
    Slash* tmp = (Slash*)node->values[SLASH];
    encode(tmp,ID,indent);
  } else if( type == ALTERNATION ) {
    Alternation* tmp = (Alternation*)node->values[ALTERNATION];
    encode(tmp,ID,indent);
  } else if( type == CHAR ) {
    Char* tmp = (Char*)node->values[CHAR];
    encode(tmp,ID,indent);
  } else if( type == AND ) {
    And* tmp = (And*)node->values[AND];
    encode(tmp,ID,indent);
  } else if( type == NOT ) {
    Not* tmp = (Not*)node->values[NOT];
    encode(tmp,ID,indent);
  } else if( type == SEQUENCE ) {
    Sequence* tmp = (Sequence*)node->values[SEQUENCE];
    encode(tmp,ID,indent);
  } else if( type == QUESTION ) {
    Question* tmp = (Question*)node->values[QUESTION];
    encode(tmp,ID,indent);
  } else if( type == STAR ) {
    Star* tmp = (Star*)node->values[STAR];
    encode(tmp,ID,indent);
  } else if( type == PLUS ) {
    Plus* tmp = (Plus*)node->values[PLUS];
    encode(tmp,ID,indent);
  } else if( type == ANY ) {
    Any* tmp = (Any*)node->values[ANY];
    encode(tmp,ID,indent);
  } else if( type == RANGE ) {
    Range* tmp = (Range*)node->values[RANGE];
    encode(tmp,ID,indent);
  } else if( type == GPEG_STRING ) {
    Gpeg_string *tmp = (Gpeg_string*)node->values[GPEG_STRING];
    encode(tmp,ID,indent);
  } else if( type == GROUPING ) {
    Grouping *tmp = (Grouping*)node->values[GROUPING];
    encode(tmp,ID,indent);
  } else {
    std::cerr << "what is [[" << type << "]]?" << std::endl;
    assert(false);
  }
}

void GeneralizedPackratParser::encode(Nonterminal *cur,int ID=-1,int indent=0){
  if( cur->getExpression() == nullptr ) { // in a parsing expression ( e.g A <- 'a' [[A]]
    writeln("/* Nonterminal ("+cur->getName()+") */",ID,indent);
    
    std::string i = "i" + itos(suffix++);
    std::string next_prev = "next_prev" + itos(suffix++);
    writeln("deque<int> "+next_prev+";",ID,indent);
    writeln("for(int "+i+"=0;"+i+"<(int)prev.size();++"+i+") {",ID,indent), ++indent;
    writeln("if( prev["+i+"] == FAIL ) {",ID,indent), ++indent;
    writeln("if(!(!"+next_prev+".empty() && "+next_prev+".front() == FAIL )) {",ID,indent), ++indent;
    writeln(next_prev+".push_front(FAIL);",ID,indent);
    --indent, writeln("}",ID,indent); // if(!(!
    writeln("continue;",ID,indent);
    --indent, writeln("}",ID,indent);//(if( prev[

    writeln(ptr_name+" = prev["+i+"];",ID,indent);
    writeln("tmp = parse_"+cur->getName()+"();",ID,indent);
    writeln("",ID,indent);
    writeln("for(int "+i+"=0;"+i+"<(int)tmp.size();++"+i+") {",ID,indent), ++indent;
    writeln("if( tmp["+i+"] == FAIL ) {",ID,indent), ++indent;
    assert(ID>=1);
    writeln("if(!( !"+next_prev+".empty() && "+next_prev+"[0] == FAIL )) {",ID,indent), ++indent;
    writeln(next_prev+".push_front(FAIL);",ID,indent);
    --indent, writeln("}",ID,indent); // !( !next_prev
    --indent, writeln("} else {",ID,indent), ++indent; // !( !tmp[i] == FAIL
    writeln(next_prev+".push_back(tmp["+i+"]);",ID,indent);
    --indent, writeln("}",ID,indent); // } else {
    --indent, writeln("}",ID,indent); // for
    --indent, writeln("}",ID,indent); // for
    writeln("prev = "+next_prev+";",ID,indent);

  } else { // definition ( e.g. [[A <- 'a' A]]
    assert( ID == -1 );
    ID = buffer.size();
    buffer.push_back("");
    prot.push_back("parse_"+cur->getName());
    writeln("deque<int> parse_"+cur->getName()+"(){",ID,indent), ++indent;
    if( packrat ){
      write_packrat_return(ID);
    }
    writeln("deque<int> "+succ_buffer+"; // we use -1 to denote failure",ID,indent);
    writeln("deque<int> tmp;",ID,indent);
    std::string i = "i" + itos(suffix++);
    writeln("deque<int> prev; //ちょうど今失敗せずに残っているポインタ",ID,indent);
    writeln("prev.push_back("+ptr_name+");",ID,indent);
    encode(cur->getExpression(),ID,indent);
    //i = "i" + itos(suffix++);
    writeln("for(int "+i+"=0;"+i+"<(int)prev.size();++"+i+") {",ID,indent), ++indent;
    writeln("if( prev["+i+"] == FAIL ) {",ID,indent), ++indent;
    writeln("if(!( !"+succ_buffer+".empty() && "+succ_buffer+"[0] == FAIL )) {",ID,indent), ++indent;
    writeln(succ_buffer+".push_front(FAIL);",ID,indent);
    --indent, writeln("}",ID,indent);
    --indent, writeln("} else {",ID,indent), ++indent;
    writeln(succ_buffer+".push_back(prev["+i+"]);",ID,indent);
    --indent, writeln("}",ID,indent);
    --indent,writeln("}",ID,indent);
    if( packrat ) {
      write_packrat_assign(ID,indent);
    } else {
      writeln("return "+succ_buffer+";",ID,indent);
    }
    --indent, writeln("}",ID,indent);
  }
}


void GeneralizedPackratParser::encode(Slash *tmp,int ID=-1,int indent=0) {  // MODIFIED
  std::deque<Node*> alternates = tmp->getAlternates();
  writeln("/* Prioritized Choice */",ID,indent);
  std::string i = "i" + itos(suffix++);
  std::string next_prev = "next_prev" + itos(suffix++);
  std::string final_prev = "prioritized_choice_final_prev" + itos(suffix++);
  writeln("deque<int> "+next_prev+";",ID,indent);
  writeln("deque<int> "+final_prev+";",ID,indent);
  for(int j=0;j<(int)alternates.size();++j) {
    writeln(next_prev+".clear();",ID,indent);
    writeln("for(int "+i+"=0;"+i+"<(int)prev.size();++"+i+") {",ID,indent), ++indent;
    writeln(ptr_name+" = prev["+i+"];",ID,indent);

    // parse_slash -- BEGIN
    std::string name_of_slash = "parse_slash" + itos(suffix++);
    int slash_ID = buffer.size();
    buffer.push_back("");
    prot.push_back(name_of_slash);
    writeln("inline deque<int> " + name_of_slash + "() { ",slash_ID);
    if( packrat ) {
      write_packrat_return(slash_ID);
    }
    writeln("deque<int> "+succ_buffer+"; // we use -1 to denote failure",slash_ID,1);
    writeln("deque<int> tmp;",slash_ID,1);
    std::string k = "i" + itos(suffix++);
    writeln("deque<int> prev; //ちょうど今失敗せずに残っているポインタ",slash_ID,1);
    writeln("prev.push_back("+ptr_name+");",slash_ID,1);
    encode(alternates[j],slash_ID,1);
    writeln("for(int "+k+"=0;"+k+"<(int)prev.size();++"+k+") {",slash_ID,1);
    writeln("if( prev["+k+"] == FAIL ) {",slash_ID,2);
    writeln("if(!( !"+succ_buffer+".empty() && "+succ_buffer+"[0] == FAIL )) {",slash_ID,3);
    writeln(succ_buffer+".push_front(FAIL);",slash_ID,4);
    writeln("}",slash_ID,3); // if(!(
    writeln("} else {",slash_ID,2); // if( prev
    writeln(succ_buffer+".push_back(prev["+k+"]);",slash_ID,3); 
    writeln("}",slash_ID,2); // else
    writeln("}",slash_ID,1); // for prev
    if( packrat ) {
      write_packrat_assign(slash_ID,1);
    } else {
      writeln("return "+succ_buffer+";",slash_ID,1);
    }
    writeln("}",slash_ID,0); // parse_slash
    // parse_slash -- END



    writeln("tmp = "+name_of_slash+"();",ID,indent);
    writeln("if(!tmp.empty()&&tmp[0]==FAIL) { " + next_prev +".push_back(prev["+i+"]); }",ID,indent);
    std::string l = "i"+itos(suffix++);
    writeln("for(int "+l+"=0;"+l+"<(int)tmp.size();++"+l+") {",ID,indent), ++indent;
    writeln("if( tmp["+l+"] != FAIL ) {",ID,indent), ++indent;    
    writeln(final_prev+".push_back(tmp["+l+"]);",ID,indent); 
    --indent, writeln("}",ID,indent); // if
    --indent, writeln("}",ID,indent); // for
    --indent, writeln("}",ID,indent); // for
    writeln("prev = "+next_prev+";",ID,indent);
    
  }
  
  writeln("if(!prev.empty()) {",ID,indent), ++indent;
  writeln("if(!(!"+final_prev+".empty() && "+final_prev+".front() == FAIL )) {",ID,indent), ++indent;
  writeln(final_prev + ".push_front(FAIL);",ID,indent);
  --indent, writeln("}",ID,indent); // if ! final_prev
  --indent, writeln("}",ID,indent); // if ! prev.empty()
  writeln("prev = " + final_prev + ";",ID,indent);
  
}

/*
 * A <- 'a' ( 'b' | 'c' ) 'd'
 */
void GeneralizedPackratParser::encode(Alternation *tmp,int ID=-1,int indent=0) { // MODIFIED
  std::deque<Node*> alternates = tmp->getAlternates();
  writeln("/* Alternation */",ID,indent);
  std::string next_prev = "next_prev" + itos(suffix++);
  std::string tmp_prev = "tmp" + itos(suffix++);
  writeln("deque<int> " + next_prev + ";",ID,indent);
  writeln("deque<int> " + tmp_prev + ";",ID,indent);
  
  std::string index2 = "i" + itos(suffix++);
  writeln("for(int "+index2+"=0;"+index2+"<(int)prev.size();++"+index2+") {",ID,indent), ++indent;



  for(int i=0;i<(int)alternates.size();++i) {


    writeln(ptr_name + " = prev["+index2+"];",ID,indent);

    // parse_alternation -- BEGIN
    std::string name_of_alternate = "parse_alternation" + itos(suffix++);
    int alternation_ID = buffer.size();
    buffer.push_back("");
    prot.push_back(name_of_alternate);
    writeln("inline deque<int> " + name_of_alternate + "() { ",alternation_ID);
    if( packrat ) {
      write_packrat_return(alternation_ID);
    }
    writeln("deque<int> "+succ_buffer+"; // we use -1 to denote failure",alternation_ID,1);
    writeln("deque<int> tmp;",alternation_ID,1);
    std::string k = "i" + itos(suffix++);
    writeln("deque<int> prev; //ちょうど今失敗せずに残っているポインタ",alternation_ID,1);
    writeln("prev.push_back("+ptr_name+");",alternation_ID,1);
    encode(alternates[i],alternation_ID,1);
    writeln("for(int "+k+"=0;"+k+"<(int)prev.size();++"+k+") {",alternation_ID,1);
    writeln("if( prev["+k+"] == FAIL ) {",alternation_ID,2);
    writeln("if(!( !"+succ_buffer+".empty() && "+succ_buffer+"[0] == FAIL )) {",alternation_ID,3);
    writeln(succ_buffer+".push_front(FAIL);",alternation_ID,4);
    writeln("}",alternation_ID,3); // if(!(
    writeln("} else {",alternation_ID,2); // if( prev
    writeln(succ_buffer+".push_back(prev["+k+"]);",alternation_ID,3); 
    writeln("}",alternation_ID,2); // else
    writeln("}",alternation_ID,1); // for prev
    if( packrat ) {
      write_packrat_assign(alternation_ID,1);
    } else {
      writeln("return "+succ_buffer+";",alternation_ID,1);
    }
    writeln("}",alternation_ID,0); // parse_slash
    // parse_alternation -- END    

    writeln(tmp_prev+"="+name_of_alternate+"();",ID,indent);
    std::string index = "i" + itos(suffix++);
    writeln("for(int "+index+"=0;"+index+"<(int)"+tmp_prev+".size();++"+index+") {",ID,indent), ++indent;
    //writeln("if( "+tmp_prev+"["+index+"] == FAIL ) {",ID,indent), ++indent; 
    //writeln("if(!(!"+next_prev+".empty()&&"+next_prev+".front()==FAIL)) {",ID,indent), ++indent;
    //writeln(next_prev+".push_front(FAIL);",ID,indent);
    //--indent, writeln("}",ID,indent); // if(!(!next_prev
    //--indent, writeln("} else {",ID,indent), ++indent; // if ( tmp_prev[index] == FAIL
    writeln("if( " + tmp_prev + "[" + index + "] != FAIL ) {",ID,indent), ++indent; // after
    writeln(next_prev+".push_back("+tmp_prev+"["+index+"]);",ID,indent);
    --indent, writeln("}",ID,indent); // } else {
    --indent, writeln("}",ID,indent); // for

  }


  --indent, writeln("}",ID,indent); // for(int index2=0;index2<(int)prev.size();++index2) {

  writeln("if( " + next_prev + ".empty() ) {",ID,indent), ++indent; //after
  writeln(next_prev + ".push_back(FAIL);",ID,indent);//after
  --indent, writeln("}",ID,indent);//after

  writeln("prev = " + next_prev + ";",ID,indent);
 
}

void GeneralizedPackratParser::encode(Char *tmp,int ID=-1,int indent=0) { // MODIFIED

  writeln("tmp.clear();",ID,indent);
  std::string i = "i" + itos(suffix++);
  writeln("for(int "+i+"=0;"+i+"<(int)prev.size();++"+i+") {",ID,indent), ++indent;
    writeln("if( prev["+i+"] == FAIL ) {",ID,indent), ++indent;
    writeln("if(!(!tmp.empty()&&tmp.front()==FAIL)) {",ID,indent), ++indent;
    writeln("tmp.push_front(FAIL);",ID,indent);
    --indent, writeln("}",ID,indent); // if(!(!tmp.empty()
    writeln("continue;",ID,indent);
    --indent, writeln("}",ID,indent); // if ( prev[j]
  char value = tmp->getValue();
  if( !( value == '\\' || value == '\'' ) && ( isgraph(value) || value == ' ' ) ) {
    writeln("if(prev["+i+"]<m&&I[prev["+i+"]]=='"+std::string(1,value)+"') {",ID,indent), ++indent;
  } else {
    writeln("if(prev["+i+"]<m&&I[prev["+i+"]]==(char)"+itos((int)value)+") {",ID,indent), ++indent;
  }
  writeln("tmp.push_back(prev["+i+"]+1);",ID,indent);
  --indent, writeln("} else {",ID,indent), ++indent;
  writeln("if(!( !tmp.empty() && tmp[0] == FAIL )){",ID,indent), ++indent;
  writeln("tmp.push_front(FAIL);",ID,indent);
  --indent, writeln("}",ID,indent);
  --indent, writeln("}",ID,indent); // else
  --indent, writeln("}",ID,indent); // for
  writeln("prev = tmp;",ID,indent);
}

void GeneralizedPackratParser::encode(And *cur,int ID=-1,int indent=0) {
  Node *next = cur->get();

// parse_and -- BEGIN
  std::string name_of_and = "parse_and" + itos(suffix++);
  int and_ID = buffer.size();
  buffer.push_back("");
  prot.push_back(name_of_and);
  writeln("inline deque<int> " + name_of_and + "() { ",and_ID);
  if( packrat ) {
    write_packrat_return(and_ID);
  }
  writeln("deque<int> "+succ_buffer+"; // we use -1 to denote failure",and_ID,1);
  writeln("deque<int> tmp;",and_ID,1);
  std::string k = "i" + itos(suffix++);
  writeln("deque<int> prev; //ちょうど今失敗せずに残っているポインタ",and_ID,1);
  writeln("prev.push_back("+ptr_name+");",and_ID,1);
  encode(next,and_ID,1);
  writeln("for(int "+k+"=0;"+k+"<(int)prev.size();++"+k+") {",and_ID,1);
  writeln("if( prev["+k+"] == FAIL ) {",and_ID,2);
  writeln("if(!( !"+succ_buffer+".empty() && "+succ_buffer+"[0] == FAIL )) {",and_ID,3);
  writeln(succ_buffer+".push_front(FAIL);",and_ID,4);
  writeln("}",and_ID,3); // if(!(
  writeln("} else {",and_ID,2); // if( prev
  writeln(succ_buffer+".push_back(prev["+k+"]);",and_ID,3); 
  writeln("}",and_ID,2); // else
  writeln("}",and_ID,1); // for prev
  if( packrat ) {
    write_packrat_assign(and_ID,1);
  } else {
    writeln("return "+succ_buffer+";",and_ID,1);
  }
  writeln("}",and_ID,0); // parse_slash
  // parse_and -- END

  
  writeln("/* And */",ID,indent);
  std::string index = "i" + itos(suffix++);
  std::string next_prev = "next_prev" + itos(suffix++);
  writeln("deque<int> "+next_prev+";",ID,indent);
  writeln("for(int "+index+"=0;"+index+"<(int)prev.size();++"+index+") {",ID,indent), ++indent;
  writeln(ptr_name + " = prev["+index+"];",ID,indent);
  writeln("tmp = " + name_of_and + "();",ID,indent);


  writeln("if(!tmp.empty() && tmp[(int)tmp.size()-1] != FAIL) {",ID,indent), ++indent;
  writeln("if(!(!"+next_prev+".empty()&&"+next_prev+".front()==FAIL)) {",ID,indent), ++indent;
  writeln(next_prev + ".push_back(prev["+index+"]);",ID,indent);
  --indent, writeln("}",ID,indent);
  // --indent, writeln("}",ID,indent);
  --indent, writeln("} else if(!tmp.empty() && tmp[0] == FAIL) {",ID,indent), ++indent;
  writeln(next_prev+".push_front(FAIL);",ID,indent);
  --indent,writeln("}",ID,indent);

  --indent, writeln("}",ID,indent); // for int index=0;
  writeln("prev = " + next_prev+";",ID,indent);

}

void GeneralizedPackratParser::encode(Not *cur,int ID=-1,int indent=0) {
  Node *next = cur->get();

  // parse_not -- BEGIN
  std::string name_of_not = "parse_not" + itos(suffix++);
  int not_ID = buffer.size();
  buffer.push_back("");
  prot.push_back(name_of_not);
  writeln("inline deque<int> " + name_of_not + "() { ",not_ID);
  if( packrat ) {
    write_packrat_return(not_ID);
  }
  writeln("deque<int> "+succ_buffer+"; // we use -1 to denote failure",not_ID,1);
  writeln("deque<int> tmp;",not_ID,1);
  std::string k = "i" + itos(suffix++);
  writeln("deque<int> prev; //ちょうど今失敗せずに残っているポインタ",not_ID,1);
  writeln("prev.push_back("+ptr_name+");",not_ID,1);
  encode(next,not_ID,1);
  writeln("for(int "+k+"=0;"+k+"<(int)prev.size();++"+k+") {",not_ID,1);
  writeln("if( prev["+k+"] == FAIL ) {",not_ID,2);
  writeln("if(!( !"+succ_buffer+".empty() && "+succ_buffer+"[0] == FAIL )) {",not_ID,3);
  writeln(succ_buffer+".push_front(FAIL);",not_ID,4);
  writeln("}",not_ID,3); // if(!(
  writeln("} else {",not_ID,2); // if( prev
  writeln(succ_buffer+".push_back(prev["+k+"]);",not_ID,3); 
  writeln("}",not_ID,2); // else
  writeln("}",not_ID,1); // for prev
  if( packrat ) {
    write_packrat_assign(not_ID,1);
  } else {
    writeln("return "+succ_buffer+";",not_ID,1);
  }
  writeln("}",not_ID,0); // parse_slash
  // parse_not -- END

  
  writeln("/* Not */",ID,indent);
  std::string index = "i" + itos(suffix++);
  std::string next_prev = "next_prev" + itos(suffix++);
  writeln("deque<int> "+next_prev+";",ID,indent);
  writeln("for(int "+index+"=0;"+index+"<(int)prev.size();++"+index+") {",ID,indent), ++indent;
  writeln(ptr_name + " = prev["+index+"];",ID,indent);
  writeln("tmp = " + name_of_not + "();",ID,indent);
  
  writeln("if(!tmp.empty() && tmp[(int)tmp.size()-1] != FAIL) {",ID,indent), ++indent;
  writeln("if(!(!"+next_prev+".empty()&&"+next_prev+".front()==FAIL)) {",ID,indent), ++indent;
  writeln(next_prev+".push_front(FAIL);",ID,indent);
  --indent, writeln("}",ID,indent);
  //--indent, writeln("}",ID,indent);
  --indent, writeln("} else if(!tmp.empty() && tmp[0] == FAIL) {",ID,indent), ++indent;
  writeln(next_prev + ".push_back(prev["+index+"]);",ID,indent);
  --indent,writeln("}",ID,indent);



  --indent, writeln("}",ID,indent); // for int index=0;
  writeln("prev = " + next_prev+";",ID,indent);
  
}

void GeneralizedPackratParser::encode(Sequence *tmp,int ID=-1,int indent=0) {
  std::deque<Node*> sequence = tmp->getSequence();
  assert( sequence.size() );
  for(int i=0;i<(int)sequence.size();++i) { 
    writeln("if(!((int)prev.size()==1&&prev.front()==FAIL)) {",ID,indent), ++indent; // CHECK
    encode(sequence[i],ID,indent);
    writeln("sort(prev.begin(),prev.end());",ID,indent); // proto type
    writeln("prev.erase(unique(prev.begin(),prev.end()),prev.end());",ID,indent); // proto type
    --indent, writeln("}",ID,indent); // CHECK
  }
}

void GeneralizedPackratParser::encode(Question *cur,int ID=-1,int indent=0) {
  
  Node* question = new Node;
  question->setType(1); // SLASH
  question->add(cur->get());
  {
    Node* node = new Node;
    Gpeg_string* tmp = new Gpeg_string;
    tmp->set("");
    node->setValue(tmp);
    question->add(node);
  }
  encode(question,ID,indent);

}

void GeneralizedPackratParser::encode(Star *cur,int ID=-1,int indent=0) { // MODIFIED
  Node *next = cur->get();

  // parse_while -- BEGIN
  std::string name_of_while = "parse_while" + itos(suffix++);
  int while_ID = buffer.size();
  buffer.push_back("");
  prot.push_back(name_of_while);
  writeln("inline deque<int> " + name_of_while + "() { ",while_ID);
  if( packrat ) {
    write_packrat_return(while_ID);
  }
  writeln("deque<int> "+succ_buffer+"; // we use -1 to denote failure",while_ID,1);
  writeln("deque<int> tmp;",while_ID,1);
  std::string k = "i" + itos(suffix++);
  writeln("deque<int> prev; //ちょうど今失敗せずに残っているポインタ",while_ID,1);
  writeln("prev.push_back("+ptr_name+");",while_ID,1);
  encode(next,while_ID,1);
  writeln("for(int "+k+"=0;"+k+"<(int)prev.size();++"+k+") {",while_ID,1);
  writeln("if( prev["+k+"] == FAIL ) {",while_ID,2);
  writeln("if(!( !"+succ_buffer+".empty() && "+succ_buffer+"[0] == FAIL )) {",while_ID,3);
  writeln(succ_buffer+".push_front(FAIL);",while_ID,4);
  writeln("}",while_ID,3); // if(!(
  writeln("} else {",while_ID,2); // if( prev
  writeln(succ_buffer+".push_back(prev["+k+"]);",while_ID,3); 
  writeln("}",while_ID,2); // else
  writeln("}",while_ID,1); // for prev
  if( packrat ) {
    write_packrat_assign(while_ID,1);
  } else {
    writeln("return "+succ_buffer+";",while_ID,1);
  }
  writeln("}",while_ID,0); // parse_slash
  // parse_while -- END  

  writeln("/* Star */",ID,indent);
  std::string next_prev = "next_prev" + itos(suffix++);
  std::string final_prev = "star_final_prev" + itos(suffix++);
  writeln("deque<int> "+next_prev+";",ID,indent);
  writeln("deque<int> "+final_prev+";",ID,indent);

  writeln("while(!((int)prev.size()==1&&prev.front()==FAIL)) {",ID,indent), ++indent;
  writeln(next_prev+".clear();",ID,indent);
  std::string index = "i" + itos(suffix++);
  writeln("for(int "+index+"=0;"+index+"<(int)prev.size();++"+index+") {",ID,indent), ++indent;
  writeln(ptr_name + " = prev["+index+"];",ID,indent);
  writeln("tmp = " + name_of_while + "();",ID,indent);
  writeln("if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {",ID,indent), ++indent;
  writeln(final_prev+".push_back(prev["+index+"]);",ID,indent);
  --indent, writeln("}",ID,indent);
  std::string index2 = "i" + itos(suffix++);
  writeln("for(int "+index2+"=0;"+index2+"<(int)tmp.size();++"+index2+") {",ID,indent), ++indent;
  writeln("if(tmp["+index2+"]==FAIL) {",ID,indent), ++indent;
  //writeln(final_prev+".push_back(prev["+index+"]);",ID,indent);
  writeln("if(!( !"+next_prev+".empty() && "+next_prev+".front() == FAIL )) {",ID,indent), ++indent; 
  writeln(next_prev+".push_front(FAIL);",ID,indent);
  --indent, writeln("}",ID,indent); // if(!(!
  --indent, writeln("} else {",ID,indent), ++indent; // if(tmp[index2]
  writeln(next_prev+".push_back(tmp["+index2+"]);",ID,indent);
  --indent, writeln("}",ID,indent); // } else {
  --indent, writeln("}",ID,indent); // for int index2 = 0;
  --indent, writeln("}",ID,indent); // for int index = 0;
  writeln("prev = " + next_prev + ";",ID,indent);
  --indent, writeln("}",ID,indent); // while(1)
  writeln("prev = " + final_prev + ";",ID,indent);
}

void GeneralizedPackratParser::encode(Plus *cur,int ID=-1,int indent=0) {
  Node* plus = new Node;
  plus->setType(6); // SEQUENCE
  plus->add(cur->get());
  {
    Node* tmp = new Node;
    Star* star = new Star;
    star->set(cur->get());
    tmp->setValue(star);
    plus->add(tmp);
  }
  encode(plus,ID,indent);
}

void GeneralizedPackratParser::encode(Any *cur,int ID=-1,int indent=0) { // MODIFIED
  writeln("tmp.clear();",ID,indent);
  std::string i = "i" + itos(suffix++);
  writeln("for(int "+i+"=0;"+i+"<(int)prev.size();++"+i+") {",ID,indent), ++indent;
  writeln("if( prev["+i+"] == FAIL ) {",ID,indent), ++indent;
  writeln("if(!(!tmp.empty()&&tmp.front()==FAIL)) {",ID,indent), ++indent;
  writeln("tmp.push_front(FAIL);",ID,indent);
  --indent, writeln("}",ID,indent); // if(!(!tmp.empty()
  writeln("continue;",ID,indent);
  --indent, writeln("}",ID,indent); // if ( prev[j]
  //writeln("if(prev["+i+"]<m&&(isgraph((char)I[prev["+i+"]])||(I[prev["+i+"]]==' '))) {//any character",ID,indent), ++indent;
  writeln("if(prev["+i+"]<m) {//any character",ID,indent), ++indent;
  writeln("tmp.push_back(prev["+i+"]+1);",ID,indent);
  --indent, writeln("} else {",ID,indent), ++indent;
  writeln("if(!( !tmp.empty() && tmp.front() == FAIL )){",ID,indent), ++indent;
  writeln("tmp.push_front(FAIL);",ID,indent);
  --indent, writeln("}",ID,indent);
  --indent, writeln("}",ID,indent); // else
  --indent, writeln("}",ID,indent); // for
  writeln("prev = tmp;",ID,indent);
}

void GeneralizedPackratParser::encode(Range *cur,int ID=-1,int indent=0) { // MODIFIED
  std::string cs = cur->get();
  std::string condition = "";
  std::string i = "i" + itos(suffix++);
  for(int j=0;j<(int)cs.size();++j) {
    if( j ) {
      condition += "||";
    }
    if( j+2 < (int)cs.size() && cs[j+1] == '-' ) { // incorrect
      for(char c=cs[j];c<=cs[j+2];++c) {
	if( c != cs[j] ) condition += "||";
	if( !( c == '\\' || c == '\'' || c == '"' ) && ( isgraph(c) || c == ' ' ) ) {
	  condition += ("I[prev["+i+"]]=='"+std::string(1,c)+"'");
	} else {
	  condition += ("I[prev["+i+"]]==(char)"+itos((int)c)+"");
	}
      }
      j += 2;
    } else {
      if( !( cs[j] == '\\' || cs[j] == '\'' ) && ( isgraph(cs[j]) || cs[j] == ' ' ) ) {
	condition += ("I[prev["+i+"]]=='"+std::string(1,cs[j])+"'");
      } else {
	condition += ("I[prev["+i+"]]==(char)"+itos((int)cs[j])+"");
      }
    }
  }


  writeln("tmp.clear();",ID,indent);

  writeln("for(int "+i+"=0;"+i+"<(int)prev.size();++"+i+") {",ID,indent), ++indent;
  writeln("if( prev["+i+"] == FAIL ) {",ID,indent), ++indent;
  writeln("if(!(!tmp.empty()&&tmp.front()==FAIL)) {",ID,indent), ++indent;
  writeln("tmp.push_front(FAIL);",ID,indent);
  --indent, writeln("}",ID,indent); // if(!(!tmp.empty()
  writeln("continue;",ID,indent);
  --indent, writeln("}",ID,indent); // if ( prev[j]
  writeln("if(prev["+i+"]<m&&("+condition+")) {",ID,indent), ++indent;
  writeln("tmp.push_back(prev["+i+"]+1);",ID,indent);
  --indent, writeln("} else {",ID,indent), ++indent;
  writeln("if(!( !tmp.empty() && tmp.front() == FAIL )){",ID,indent), ++indent;
  writeln("tmp.push_front(FAIL);",ID,indent);
  --indent, writeln("}",ID,indent);
  --indent, writeln("}",ID,indent); // else
  --indent, writeln("}",ID,indent); // for
  writeln("prev = tmp;",ID,indent);


}

void GeneralizedPackratParser::encode(Gpeg_string *tmp,int ID=-1,int indent=0) {  // MODIFIED
  std::string str = tmp->get();
  for(int i=0;i<(int)str.size();++i) {
    writeln("tmp.clear();",ID,indent);
    std::string j = "i" + itos(suffix++);
    writeln("for(int "+j+"=0;"+j+"<(int)prev.size();++"+j+") {",ID,indent), ++indent;
    
    writeln("if( prev["+j+"] == FAIL ) {",ID,indent), ++indent;
    writeln("if(!(!tmp.empty()&&tmp.front()==FAIL)) {",ID,indent), ++indent;
    writeln("tmp.push_front(FAIL);",ID,indent);
    --indent, writeln("}",ID,indent); // if(!(!tmp.empty()
    writeln("continue;",ID,indent);
    --indent, writeln("}",ID,indent); // if ( prev[j]
    
    char value = str[i];
    if( !( value == '\\' ) && ( isgraph(value) || value == ' ' ) ) {
      writeln("if(prev["+j+"]<m&&I[prev["+j+"]]=='"+std::string(1,value)+"') {",ID,indent), ++indent;
    } else {
      writeln("if(prev["+j+"]<m&&I[prev["+j+"]]==(char)"+itos((int)value)+") {",ID,indent), ++indent;
    }
    writeln("tmp.push_back(prev["+j+"]+1);",ID,indent);
    --indent, writeln("} else {",ID,indent), ++indent;
    writeln("if(!( !tmp.empty() && tmp[0] == FAIL )){",ID,indent), ++indent;
    writeln("tmp.push_front(FAIL);",ID,indent);
    --indent, writeln("}",ID,indent);
    --indent, writeln("}",ID,indent); // else
    --indent, writeln("}",ID,indent); // for
    writeln("prev = tmp;",ID,indent);
  }
}

void GeneralizedPackratParser::encode(Grouping *tmp,int ID=-1,int indent=0) {
  assert( false ); /* DO NOT USE THIS FUNCTION */
  Node *next = tmp->get();
  encode(next,ID,indent);
}



