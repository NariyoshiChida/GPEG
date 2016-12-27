#include"packrat_parser.h"
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
#include<map>
#include<set>

using packrat_parser::PackratParser;

//bool show_trace = false; // duplicateになる

std::ostream& operator << (std::ostream& os, const PackratParser& gpp) {
  os << "[[Packrat Parser]]";
  return os;
}

inline std::string itos(int i) { std::stringstream ss; ss << i; return ss.str(); }

void PackratParser::set(Grammar *tmp) { grammar = tmp; }

// <--- encode --->

// replaced by dispatch_macro

void PackratParser::writeln(std::string s,int ID=-1,int indent=0) {
  if( ID == -1 ) {
    std::cout << std::string(indent*2,' ') << s << std::endl;
  } else {
    assert( ID < (int)buffer.size() );
    buffer[ID] += ( std::string(indent*2,' ') + s + "\n" );
  }
}

void PackratParser::write(std::string s,int ID=-1,int indent=0) {
  if( ID == -1 ) {
    std::cout << std::string(indent*2,' ') << s;
  } else {
    assert( ID < (int)buffer.size() );
    buffer[ID] += ( std::string(indent*2,' ') + s );
  }
}

void PackratParser::dump() {
  std::cout << buffer[first_ID];
  std::cout << std::endl;
  for(int i=0;i<(int)prot.size();++i) {
    std::cout << "bool " << prot[i] << "();" << std::endl;
  }
  std::cout << std::endl;
  for(int i=0;i<(int)buffer.size();++i) {
    if( i == first_ID || i == last_ID ) continue;
    std::cout << buffer[i];
    std::cout << std::endl;
  }
  std::cout << buffer[last_ID];
}

void PackratParser::write_packrat_return(int ID) {
  // -1 is for adjustment by first_ID
  writeln("if(memo["+itos(ID-1)+"]["+ptr_name+"].next_ptr != -1) {",ID,1);
  if( backtracking ) {
    writeln("if( i >= memo["+itos(ID-1)+"]["+ptr_name+"].next_ptr ) { // WARNING -- IS IT TRUE?",ID,2);
    writeln("++" + backtracking_counter + ";",ID,3);
    writeln("}",ID,2);
  }
  if( longest_backtracking_distance ) {
    writeln("if( i > memo["+itos(ID-1)+"]["+ptr_name+"].next_ptr ) { // WARNING -- IS IT TRUE?",ID,2);
    writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-memo["+itos(ID-1)+"]["+ptr_name+"].next_ptr);",ID,3);
    writeln("}",ID,2);
  }
  std::string tmp_variable = "tmp" + itos(suffix++);
  writeln("int " + tmp_variable + " = i;",ID,2);
  writeln("i = memo["+itos(ID-1)+"]["+ptr_name+"].next_ptr;",ID,2);
  writeln("return memo["+itos(ID-1)+"]["+tmp_variable+"].result;",ID,2);
  writeln("}",ID,1);
  writeln("int " + backtracking_ptr_for_packrat + itos(ID-1) +"=" + ptr_name + ";",ID,1);
}

void PackratParser::write_packrat_assign(int ID,bool result,int indent) {
  writeln("memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+itos(ID-1)+"].next_ptr = "+ptr_name+";",ID,indent);
  writeln("return memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+itos(ID-1)+"].result = "+(result?"true":"false")+";",ID,indent);
}

void PackratParser::encode() {
  buffer.clear();
  first_ID = buffer.size();
  buffer.push_back("");
  writeln("#include<bits/stdc++.h>",first_ID);
  writeln("",first_ID);
  writeln("using namespace std;",first_ID);
  writeln("",first_ID);
  writeln("int m;",first_ID);
  writeln("int "+ptr_name+";",first_ID);
  writeln("string I;",first_ID);

  if( packrat ) {
    writeln("struct Data {",first_ID);
    writeln("bool result;",first_ID,1);
    writeln("int next_ptr;",first_ID,1);
    writeln("};",first_ID);
  }

  writeln("",first_ID);

  std::vector<Nonterminal*> nonterminals = grammar->getNonterminals();
  assert( nonterminals.size() );
  for(int i=0;i<(int)nonterminals.size();++i) {
    encode(nonterminals[i],-1,0);
  }

  if( packrat ) {
    writeln("#define NUM_P "+itos(prot.size()),first_ID);
    writeln("vector<Data> memo[NUM_P];",first_ID);
  }
  
  if( backtracking ) {
    writeln("int "+backtracking_counter+";",first_ID);
  }

  if( longest_backtracking_distance ) {
    writeln("int "+longest_backtracking_distance_value+" = -1;",first_ID);
  }

  last_ID = buffer.size();
  buffer.push_back("");
  writeln("",last_ID);
  writeln("int main() {",last_ID);
  writeln("getline(cin,I);",last_ID,1);
  writeln("m = (int)I.size();",last_ID,1);
  if( packrat ) {
    writeln("for(int j=0;j<NUM_P;++j) {",last_ID,1);
    writeln("memo[j] = vector<Data>(m+1,(Data){false,-1});",last_ID,2);
    writeln("}",last_ID,1);
  }
  writeln(ptr_name+"=0;",last_ID,1);
  // 完全マッチにしたければ parse_XXX(0) == true && ptr_name == (int)I.size()
  if( matching_time ) {
    writeln("auto st = chrono::system_clock::now();",last_ID,1);
  }
  writeln("bool result = parse_"+nonterminals[0]->getName()+"();",last_ID,1);
  if( matching_time ) {
    writeln("auto ed = chrono::system_clock::now();",last_ID,1);
  }
  writeln("if( result ) {",last_ID,1);
  writeln("puts(\"success\");",last_ID,2);
  writeln("cout << \"consumed :: [\" << i << \"/\" << m << \"]\" << endl;",last_ID,2);
  writeln("} else {",last_ID,1);
  writeln("puts(\"fail\");",last_ID,2);
  writeln("}",last_ID,1);
  if( matching_time ) {
    writeln("cout << \"matching time :: \" << chrono::duration_cast<chrono::milliseconds>(ed-st).count() << \"msec\" << endl;",last_ID,1);
  }
  //writeln("cout << (parse_"+nonterminals[0]->getName()+"()?\"success\":\"fail\") << endl;",last_ID,1);
  if( backtracking ) {
    writeln("cout << \"backtracking :: [\" << " + backtracking_counter + " << \"]\" << endl;",last_ID,1);
  }
  if( longest_backtracking_distance ) {
    writeln("if("+longest_backtracking_distance_value+"==-1) {",last_ID,1);
    writeln("puts(\"longest backtracking distance :: [---]\");",last_ID,2);
    writeln("} else {",last_ID,1);
    writeln("cout << \"longest backtracking distance :: [\" << " + longest_backtracking_distance_value + " << \"]\" << endl;",last_ID,2);
    writeln("}",last_ID,1);
  }
  writeln("return 0;",last_ID,1);
  writeln("}",last_ID); // main

  dump();
}

void PackratParser::encode(Node *node,int ID,int indent) {
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

void PackratParser::encode(Nonterminal *cur,int ID=-1,int indent=0){
  if( cur->getExpression() == nullptr ) { // in a parsing expression ( e.g A <- 'a' [[A]]
    writeln("/* Nonterminal ("+cur->getName()+") */",ID,indent);
    
    if( !packrat ) {
      writeln("if(!parse_"+cur->getName()+"()) { return false; }",ID,indent);
    } else {
      writeln("if(!parse_"+cur->getName()+"()) {",ID,indent), ++indent;
      assert(ID>=1);
      if( packrat ) {
	write_packrat_assign(ID,false,indent+1);
      }
      //writeln("memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+itos(ID-1)+"].next_ptr = "+ptr_name+";",ID,indent+1);
      //writeln("return memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+itos(ID-1)+"].result = false;",ID,indent+1);
      --indent, writeln("}",ID,indent);
    }
    
  } else { // definition ( e.g. [[A <- 'a' A]]
    assert( ID == -1 );
    ID = buffer.size();
    buffer.push_back("");
    prot.push_back("parse_"+cur->getName());
    writeln("bool parse_"+cur->getName()+"(){",ID,indent), ++indent;
    if( trace ) {
      writeln("cout << __LINE__ << \": " + cur->getName() + " :\" << \"I[\" << i << \"] = \" << I[i] << endl;",ID,indent);
    }
    if( packrat ){
      write_packrat_return(ID);
    }
    encode(cur->getExpression(),ID,indent);
    if( packrat ) {
      write_packrat_assign(ID,true,indent+1);
      //writeln("memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+itos(ID-1)+"].next_ptr = "+ptr_name+";",ID,indent);
      //writeln("return memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+itos(ID-1)+"].result = true;",ID,indent);
    } else {
      writeln("return true;",ID,indent);
    }
    --indent, writeln("}",ID,indent);
  }
}


void PackratParser::encode(Slash *tmp,int ID=-1,int indent=0) { 
  std::deque<Node*> alternates = tmp->getAlternates();
  writeln("/* Prioritized Choice */",ID,indent);
  std::string success_flag = "success_flag"+itos(suffix++);
  writeln("bool " + success_flag + "=false;",ID,indent);
  for(int i=0;i<(int)alternates.size();++i) {
    std::string name_of_slash = "parse_slash" + itos(suffix++);
    int slash_ID = buffer.size();
    buffer.push_back("");
    prot.push_back(name_of_slash);
    writeln("inline bool " + name_of_slash + "() { ",slash_ID);
    if( packrat ){
      write_packrat_return(slash_ID);
    }
    encode(alternates[i],slash_ID,1);
    if( packrat ) {
      write_packrat_assign(slash_ID,true,indent);
      //writeln("memo["+itos(slash_ID-1)+"]["+backtracking_ptr_for_packrat+"].next_ptr = "+ptr_name+";",slash_ID,indent);
      //writeln("return memo["+itos(slash_ID-1)+"]["+backtracking_ptr_for_packrat+"].result = true;",slash_ID,indent);
    } else {
      writeln("return true;",slash_ID,1);
    }
    writeln("}",slash_ID);

    writeln("if(!"+success_flag+") {",ID,indent), ++indent;    
    std::string backtracking_ptr_name = "backtracking_ptr" + itos(suffix++);
    writeln("int "+backtracking_ptr_name+"="+ptr_name+";",ID,indent);
    writeln(success_flag+"|="+name_of_slash+"();",ID,indent);
    //writeln("if(!"+success_flag+") { "+ptr_name+"="+backtracking_ptr_name+"; }",ID,indent);
    writeln("if(!"+success_flag+") {",ID,indent), ++indent;
    if( longest_backtracking_distance ) {
      writeln("if("+ptr_name+">"+backtracking_ptr_name+") {",ID,indent), ++indent;
      writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-"+backtracking_ptr_name+");",ID,indent);
      --indent, writeln("}",ID,indent);
    }
    if( backtracking ) {
      writeln("if("+ptr_name+">="+backtracking_ptr_name+") {",ID,indent), ++indent;
      writeln("++"+backtracking_counter+";",ID,indent);
      --indent, writeln("}",ID,indent);
    }
    writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);

    --indent, writeln("}",ID,indent);
    --indent, writeln("}",ID,indent);

  }


  writeln("if(!"+success_flag+") {",ID,indent), ++indent;
  if( packrat ) {
    write_packrat_assign(ID,false,indent);
    //writeln("memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+"].next_ptr = "+ptr_name+";",ID,indent);
    //writeln("return memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+"].result = false;",ID,indent);
  } else {
    writeln("return false;",ID,indent);
  }

  --indent, writeln("}",ID,indent);

}

/*
 * A <- 'a' ( 'b' | 'c' ) 'd'
 */
void PackratParser::encode(Alternation *tmp,int ID=-1,int indent=0) {
  std::deque<Node*> alternates = tmp->getAlternates();
  writeln("/* Alternation */",ID,indent);
  std::string success_flag = "success_flag"+itos(suffix++);
  writeln("bool " + success_flag + "=false;",ID,indent);
  for(int i=0;i<(int)alternates.size();++i) {
    std::string name_of_alternate = "parse_alternation" + itos(suffix++);
    int alternation_ID = buffer.size();
    buffer.push_back("");
    prot.push_back(name_of_alternate);
    writeln("inline bool " + name_of_alternate + "() { ",alternation_ID);
    if( packrat ){
      write_packrat_return(alternation_ID);
    }
    encode(alternates[i],alternation_ID,1);
    if( packrat ) {
      write_packrat_assign(alternation_ID,true,indent);
      //writeln("memo["+itos(alternation_ID-1)+"]["+backtracking_ptr_for_packrat+"].next_ptr = "+ptr_name+";",alternation_ID,indent);
      //writeln("return memo["+itos(alternation_ID-1)+"]["+backtracking_ptr_for_packrat+"].result = true;",alternation_ID,indent);
    } else {
      writeln("return true;",alternation_ID,1);
    }
    writeln("}",alternation_ID);
    
    std::string backtracking_ptr_name = "backtracking_ptr" + itos(suffix++);
    writeln("int "+backtracking_ptr_name+"="+ptr_name+";",ID,indent);
    writeln(success_flag+"|="+name_of_alternate+"();",ID,indent);
    writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);

  }

  writeln("if(!"+success_flag+") {",ID,indent), ++indent;
  if( packrat ) {
    write_packrat_assign(ID,false,indent);
    //writeln("memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+"].next_ptr = "+ptr_name+";",ID,indent);
    //writeln("return memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+"].result = false;",ID,indent);
  } else {
    writeln("return false;",ID,indent);
  }
  --indent, writeln("}",ID,indent);
}

void PackratParser::encode(Char *tmp,int ID=-1,int indent=0) {
  char value = tmp->getValue();
  if( !( value == '\\' ) && ( isgraph(value) || value == ' ' ) ) {
    writeln("if("+ptr_name+"<m&&I["+ptr_name+"]=='"+std::string(1,value)+"') {",ID,indent), ++indent;
  } else {
    writeln("if("+ptr_name+"<m&&I["+ptr_name+"]==(char)"+itos((int)value)+") {",ID,indent), ++indent;
  }
  writeln("++"+ptr_name+";",ID,indent);
  --indent, writeln("} else {",ID,indent), ++indent;
  if( packrat ) {
    write_packrat_assign(ID,false,indent);
    //writeln("memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+"].next_ptr = "+ptr_name+";",ID,indent);
    //writeln("return memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+"].result = false;",ID,indent);
  } else {
    writeln("return false;",ID,indent);
  }
  --indent, writeln("}",ID,indent); // else
}

void PackratParser::encode(And *cur,int ID=-1,int indent=0) {
  Node *next = cur->get();
  std::string name_of_and = "parse_and" + itos(suffix++);
  int and_ID = buffer.size();
  buffer.push_back("");
  prot.push_back(name_of_and);
  writeln("inline bool " + name_of_and + "() { ",and_ID);
  if( packrat ){
    write_packrat_return(and_ID);
  }
  encode(next,and_ID,1);
  if( packrat ) {
    write_packrat_assign(and_ID,true,indent);
    //writeln("memo["+itos(and_ID-1)+"]["+backtracking_ptr_for_packrat+"].next_ptr = "+ptr_name+";",and_ID,indent);
    //writeln("return memo["+itos(and_ID-1)+"]["+backtracking_ptr_for_packrat+"].result = true;",and_ID,indent);
  } else {
    writeln("return true;",and_ID,1);
  }
  writeln("}",and_ID);
  
  writeln("/* And */",ID,indent);
  std::string backtracking_ptr_name = "backtracking_ptr" + itos(suffix++);
  writeln("int "+backtracking_ptr_name+"="+ptr_name+";",ID,indent);
  writeln("if(!"+name_of_and+"()) {",ID,indent), ++indent;
  if( longest_backtracking_distance ) {
    writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-"+backtracking_ptr_name+");",ID,indent);
  }

  if( backtracking ) {
    writeln("if("+ptr_name+">="+backtracking_ptr_name+") {",ID,indent), ++indent;
    writeln("++" + backtracking_counter + ";",ID,indent);
    --indent, writeln("}",ID,indent);
  }

  writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);

  if( packrat ) {
    write_packrat_assign(ID,false,indent);
    //writeln("memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+"].next_ptr = "+ptr_name+";",ID,indent);
    //writeln("return memo["+itos(ID-1)+"]["+backtracking_ptr_for_packrat+"].result = false;",ID,indent);
  } else {
    writeln("return false;",ID,indent);
  }
  --indent, writeln("}",ID,indent);
  if( longest_backtracking_distance ) {
    writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-"+backtracking_ptr_name+");",ID,indent);
  }
  if( backtracking ) {
    writeln("if("+ptr_name+">="+backtracking_ptr_name+") {",ID,indent), ++indent;
    writeln("++" + backtracking_counter + ";",ID,indent);
    --indent, writeln("}",ID,indent);
  }

  writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);
}

void PackratParser::encode(Not *cur,int ID=-1,int indent=0) {
  Node *next = cur->get();
  std::string name_of_not = "parse_not" + itos(suffix++);
  int not_ID = buffer.size();
  buffer.push_back("");
  prot.push_back(name_of_not);
  writeln("inline bool " + name_of_not + "() { ",not_ID);
  if( packrat ){
    write_packrat_return(not_ID);
  }
  encode(next,not_ID,1);
  if( packrat ) {
    write_packrat_assign(not_ID,true,1);
  } else {
    writeln("return true;",not_ID,1);
  }
  writeln("}",not_ID);
  
  writeln("/* Not */",ID,indent);
  std::string backtracking_ptr_name = "backtracking_ptr" + itos(suffix++);
  writeln("int "+backtracking_ptr_name+"="+ptr_name+";",ID,indent);
  writeln("if("+name_of_not+"()) {",ID,indent), ++indent;
  if( longest_backtracking_distance ) {
    writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-"+backtracking_ptr_name+");",ID,indent);
  }
  if( backtracking ) {
    writeln("if("+ptr_name+">="+backtracking_ptr_name+") {",ID,indent), ++indent;
    writeln("++" + backtracking_counter + ";",ID,indent);
    --indent, writeln("}",ID,indent);
  }
  writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);

  if( packrat ) {
    write_packrat_assign(ID,false,indent);
  } else {
    writeln("return false;",ID,indent);
  }
  --indent, writeln("}",ID,indent);
  if( longest_backtracking_distance ) {
    writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-"+backtracking_ptr_name+");",ID,indent);
  }
  if( backtracking ) {
    writeln("if("+ptr_name+">="+backtracking_ptr_name+") {",ID,indent), ++indent;
    writeln("++" + backtracking_counter + ";",ID,indent);
    --indent, writeln("}",ID,indent);
  }
  writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);
}

void PackratParser::encode(Sequence *tmp,int ID=-1,int indent=0) {
  std::deque<Node*> sequence = tmp->getSequence();
  assert( sequence.size() );
  for(int i=0;i<(int)sequence.size();++i) {
    encode(sequence[i],ID,indent);
  }
}

void PackratParser::encode(Question *cur,int ID=-1,int indent=0) {
  Node *next = cur->get();
  std::string name_of_question = "parse_question" + itos(suffix++);
  int question_ID = buffer.size();
  buffer.push_back("");
  prot.push_back(name_of_question);
  writeln("inline bool " + name_of_question + "() { ",question_ID);
  if( packrat ){
    write_packrat_return(question_ID);
  }
  encode(next,question_ID,1);
  if( packrat ) {
    write_packrat_assign(question_ID,true,1);
  } else {
    writeln("return true;",question_ID,1);
  }
  writeln("}",question_ID);
  
  writeln("/* Question */",ID,indent);
  std::string backtracking_ptr_name = "backtracking_ptr" + itos(suffix++);
  writeln("int "+backtracking_ptr_name+"="+ptr_name+";",ID,indent);
  writeln("if(!"+name_of_question+"()) {",ID,indent), ++indent;
  if( longest_backtracking_distance ) {
    writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-"+backtracking_ptr_name+");",ID,indent);
  }

  if( backtracking ) {
    writeln("if("+ptr_name+">="+backtracking_ptr_name+") {",ID,indent), ++indent;
    writeln("++" + backtracking_counter + ";",ID,indent);
    --indent, writeln("}",ID,indent);
  }
  writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);
  --indent, writeln("}",ID,indent);
}

void PackratParser::encode(Star *cur,int ID=-1,int indent=0) {
  Node *next = cur->get();
  std::string name_of_while = "parse_while" + itos(suffix++);
  int while_ID = buffer.size();
  buffer.push_back("");
  prot.push_back(name_of_while);
  writeln("inline bool " + name_of_while + "() {",while_ID);
  if( packrat ){
    write_packrat_return(while_ID);
  }
  encode(next,while_ID,1);
  if( packrat ) {
    write_packrat_assign(while_ID,true,1);
  } else {
    writeln("return true;",while_ID,1);
  }
  writeln("}",while_ID);
  
  writeln("/* Star */",ID,indent);
  std::string backtracking_ptr_name = "backtracking_ptr" + itos(suffix++);
  writeln("int "+backtracking_ptr_name+"="+ptr_name+";",ID,indent);
  writeln("while(" + name_of_while + "()) {",ID,indent),++indent;
  writeln(backtracking_ptr_name+"="+ptr_name+";",ID,indent);
  --indent,writeln("}",ID,indent);
  if( longest_backtracking_distance ) {
    writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-"+backtracking_ptr_name+");",ID,indent);
  }

  if( backtracking ) {
    writeln("if("+ptr_name+">="+backtracking_ptr_name+") {",ID,indent), ++indent;
    writeln("++" + backtracking_counter + ";",ID,indent);
    --indent, writeln("}",ID,indent);
  }
  writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);
}

void PackratParser::encode(Plus *cur,int ID=-1,int indent=0) {
  Node *next = cur->get();
  std::string name_of_while = "parse_while" + itos(suffix++);
  int while_ID = buffer.size();
  buffer.push_back("");
  prot.push_back(name_of_while);
  writeln("inline bool " + name_of_while + "() {",while_ID);
  if( packrat ){
    write_packrat_return(while_ID);
  }
  encode(next,while_ID,1);
  if( packrat ) {
    write_packrat_assign(while_ID,true,1);
  } else {
    writeln("return true;",while_ID,1);
  }
  writeln("}",while_ID);
  
  writeln("/* Plus */",ID,indent);
  if( !packrat ) {
    writeln("if(!"+name_of_while+"()) { return false; }",ID,indent);
  } else {
    writeln("if(!"+name_of_while+"()) {",ID,indent), ++indent;
    write_packrat_assign(ID,false,indent);
    --indent, writeln("}",ID,indent);
  }
  std::string backtracking_ptr_name = "backtracking_ptr" + itos(suffix++);
  writeln("int "+backtracking_ptr_name+"="+ptr_name+";",ID,indent);
  writeln("while(" + name_of_while + "()) {",ID,indent),++indent;
  writeln(backtracking_ptr_name+"="+ptr_name+";",ID,indent);
  --indent,writeln("}",ID,indent);
  if( longest_backtracking_distance ) {
    writeln(longest_backtracking_distance_value+" = max("+longest_backtracking_distance_value+","+ptr_name+"-"+backtracking_ptr_name+");",ID,indent);
  }
  if( backtracking ) {
    writeln("if("+ptr_name+">="+backtracking_ptr_name+") {",ID,indent), ++indent;
    writeln("++" + backtracking_counter + ";",ID,indent);
    --indent, writeln("}",ID,indent);
  }
  writeln(ptr_name+"="+backtracking_ptr_name+";",ID,indent);
}

void PackratParser::encode(Any *cur,int ID=-1,int indent=0) {
  writeln("if("+ptr_name+"<m&&(isgraph((char)I["+ptr_name+"])||(I["+ptr_name+"]==' '))) {//any character",ID,indent), ++indent;
  writeln("++"+ptr_name+";",ID,indent);
  --indent, writeln("} else {",ID,indent), ++indent;
  if( packrat ) {
    write_packrat_assign(ID,false,indent);
  } else {
    writeln("return false;",ID,indent);
  }
  --indent, writeln("}",ID,indent);
}

void PackratParser::encode(Range *cur,int ID=-1,int indent=0) {
  std::string cs = cur->get();
  std::string condition = "";
  for(int i=0;i<(int)cs.size();++i) {
    if( i ) {
      condition += "||";
    }
    if( i+2 < (int)cs.size() && cs[i+1] == '-' && cs[i] <= cs[i+2] ) { // incorrect
      for(char c=cs[i];c<=cs[i+2];++c) {
	if( c != cs[i] ) condition += "||";
	if( !( c == '\\' ) && ( isgraph(c) || c == ' ' ) ) {
	  condition += ("I["+ptr_name+"]=='"+std::string(1,c)+"'");
	} else {
	  condition += ("I["+ptr_name+"]==(char)"+itos((int)c)+"");
	}
      }
      i += 2;
    } else {
      if( !( cs[i] == '\\' ) && ( isgraph(cs[i]) || cs[i] == ' ' ) ) {
	condition += ("I["+ptr_name+"]=='"+std::string(1,cs[i])+"'");
      } else {
	condition += ("I["+ptr_name+"]==(char)"+itos((int)cs[i])+"");
      }
    }
  }
  writeln("if("+ptr_name+"<m&&("+condition+")) {",ID,indent), ++indent;
  writeln("++"+ptr_name+";",ID,indent);
  --indent, writeln("} else {",ID,indent), ++indent;
  if( packrat ) {
    write_packrat_assign(ID,false,indent);
  } else {
    writeln("return false;",ID,indent);
  }
  --indent, writeln("}",ID,indent);
}

void PackratParser::encode(Gpeg_string *tmp,int ID=-1,int indent=0) {
  std::string str = tmp->get();
  for(int i=0;i<(int)str.size();++i) {
    if( !( str[i] == '\\' ) && ( isgraph(str[i]) || str[i] ==' ' ) ) {
      writeln("if("+ptr_name+"<m&&I["+ptr_name+"]=='"+std::string(1,str[i])+"') {",ID,indent), ++indent;
    } else {
      writeln("if("+ptr_name+"<m&&I["+ptr_name+"]==(char)"+itos((int)str[i])+") {",ID,indent), ++indent;
    }
    writeln("++"+ptr_name+";",ID,indent);
    --indent, writeln("} else { ",ID,indent), ++indent;
    if( packrat ) {
      write_packrat_assign(ID,false,indent);
    } else {
      writeln("return false;",ID,indent);
    }
    --indent, writeln("}",ID,indent);
  }
}

void PackratParser::encode(Grouping *tmp,int ID=-1,int indent=0) {
  assert( false ); /* DO NOT USE THIS FUNCTION */
  Node *next = tmp->get();
  encode(next,ID,indent);
}



