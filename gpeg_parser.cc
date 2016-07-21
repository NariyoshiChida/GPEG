#include"gpeg_parser.h"
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

using gpeg_parser::GPEGParser;

bool show_trace = false;


std::ostream& operator << (std::ostream& os, const GPEGParser& gpp) {
  os << "[[GPEG Parser]]";
  return os;
}

inline std::string itos(int i) { std::stringstream ss; ss << i; return ss.str(); }

void GPEGParser::debug() {
  std::cout << "---debug info---" << std::endl;
  std::cout << "compiled = " << GPEGParser::compiled << std::endl;
  std::cout << "ptr = " << GPEGParser::ptr << std::endl;
  std::cout << "clen = " << clen << std::endl;
  std::cout << GPEGParser::context << std::endl;
}

void GPEGParser::reset(std::string tmp) {
  delete_grammar();
  context = tmp;
  clen = (int)context.size();
  ptr = 0;
  compiled = false;
  indent = 0;
}

// <--- encode --->
/*
  条件 :
  * create したら pop する ( success の場合は、 fail ならそのまま落ちて終わり)
  *create をしている関数でmodify_ret != OFFであるならば、
   goto modify_ret をする前に状態を関数呼び出し前に戻す必要がある
   
 */

const int LABEL_MAX = 200;
std::map<std::string,int> nt_map; // nonterminal name -> label

void GPEGParser::dispatch(std::string vari) {
  write("switch(" + vari + ") {");
  for(int i=0;i<LABEL_MAX;++i) {
    if( i == 1 ) continue;
    write("case " + itos(i) + ": goto _" + itos(i) + "; ");
  } 
  writeln("}");
}

void GPEGParser::writeln(std::string s) {
  std::cout << std::string(indent*2,' ') << s << std::endl;
}

void GPEGParser::write(std::string s) {
  std::cout << std::string(indent*2,' ') << s;
}

void GPEGParser::write_add() {
  writeln("void add(int L,GSSNode u,int j) {"), ++indent;
  writeln("if( !U[j].count(pair<int,GSSNode>(L,u)) ) {"), ++indent;
  writeln("U[j].insert(pair<int,GSSNode>(L,u));");
  writeln("R.push((Descriptor){L,u,j});");
  --indent, writeln("}"); // if
  --indent, writeln("}"); // add
}

void GPEGParser::write_pop() {
  writeln("void pop(GSSNode u,int j) {"), ++indent;
  writeln("if( !( u == u0 ) ) {"), ++indent;
  writeln("P.insert(pair<GSSNode,int>(u,j));");
  writeln("int u_id = created[u];");/************/
  writeln("for(int k=0;k<(int)GSS[u_id].size();++k) {"), ++indent;
  writeln("GSSNode v = GSS[u_id][k];");
  writeln("add(node_vec[u_id].L,v,j);");
  --indent, writeln("}"); // for
  --indent, writeln("}"); // if
  --indent, writeln("}"); // pop
}

void GPEGParser::write_create() {
  writeln("GSSNode create(int L,GSSNode u,int j) {"), ++indent;
  writeln("GSSNode v = (GSSNode){L,j};");
  writeln("if(!created.count(v)) {"), ++indent;
  writeln("created[v] = (int)node_vec.size();");
  writeln("GSS.push_back(vector<GSSNode>());");
  writeln("node_vec.push_back(v);");
  --indent, writeln("}"); // if
  writeln("bool hasEdge = false;");
  writeln("int v_id = created[v];");
  writeln("for(int k=0;k<(int)GSS[v_id].size();++k) {"), ++indent;
  writeln("if(GSS[v_id][k] == u) {"), ++indent;
  writeln("hasEdge = true;");
  writeln("break;");
  --indent, writeln("}"); // if
  --indent, writeln("}"); // for
  writeln("if(!hasEdge) {"), ++indent;
  writeln("GSS[v_id].push_back(u);");
  writeln("for(set<pair<GSSNode,int>>::iterator itr=P.begin();itr!=P.end();++itr) {"), ++indent;
  writeln("if(itr->first == v) {"), ++indent;
  writeln("add(L,u,itr->second);");
  --indent, writeln("}"); // if
  --indent, writeln("}"); // for
  --indent, writeln("}"); // if
  writeln("return v;");
  --indent, writeln("}"); // create
}

/*
  modify_ret 
  if the matching is failed, replace _0 to modify_ret
  sorry for my poor English
 */
void GPEGParser::encode() {
  if( !compiled ) return;
  next_label = 2;

  writeln("#include<bits/stdc++.h>");
  writeln("");
  writeln("using namespace std;");
  writeln("");
  writeln("string I; // input text");
  writeln("int m; // length of the input");
  writeln("");

  writeln("struct GSSNode {"), ++indent; 
  writeln("int L, j;");
  writeln("bool operator == (const GSSNode &node) const {"), ++indent;
  writeln("return L == node.L && j == node.j;");
  --indent, writeln("}");
  writeln("bool operator < (const GSSNode &node) const {"), ++indent;
  writeln("return ( L != node.L ) ? L < node.L : j < node.j;");
  --indent, writeln("}");
  --indent, writeln("};");
  writeln("");

  writeln("struct Descriptor {"), ++indent;
  writeln("int L;");
  writeln("GSSNode u;");
  writeln("int j;");
  --indent, writeln("};");
  writeln("");

  writeln("const GSSNode u0 = (GSSNode){-1,-1};");
  writeln("const GSSNode u1 = (GSSNode){0,0};");
  writeln("map<GSSNode,int> created; // map GSSNode to an index of node_vec");
  writeln("vector<GSSNode> node_vec;");
  writeln("vector<vector<GSSNode>> GSS;");
  writeln("GSSNode cu;");
  writeln("set<pair<GSSNode,int>> P;");
  writeln("queue<Descriptor> R;");
  writeln("vector<set<pair<int,GSSNode>>> U;");
  writeln("");

  write_add();
  writeln("");

  write_pop();
  writeln("");

  write_create();
  writeln("");

  writeln("bool compute() {"), ++indent;
  writeln("I += \"$\";");
  writeln("int i;");
  writeln("GSS.clear(), created.clear(), node_vec.clear();");
  writeln("created[u0] = 0;");
  writeln("created[u1] = 1;");
  writeln("node_vec.push_back(u0);");
  writeln("node_vec.push_back(u1);");
  writeln("GSS.resize(2,vector<GSSNode>()); // GSS[0] = u0 = $, GSS[1] = u1 = L00");
  writeln("GSS[1].push_back(u0);");
  writeln("cu = u1, i = 0;");
  writeln("U.clear();");
  writeln("U.resize(m+1);");
  writeln("while( R.size() ) R.pop();");
  writeln("P.clear();");
  writeln("");
  writeln("goto _" + itos(next_label) + ";");
  writeln("");
  writeln("_0:;");
  writeln("if(R.empty()) {"), ++indent;
  writeln("if(U[m].count(pair<int,GSSNode>(0,u0))) {"), ++indent;
  writeln("return true;");
  --indent, writeln("} else {"), ++indent;
  writeln("return false;");
  --indent, writeln("}");
  --indent, writeln("} else {"), ++indent;
  writeln("Descriptor desc = R.front(); R.pop();");
  writeln("cu = desc.u, i = desc.j;");
  //disp = dispatch("desc.L");
  dispatch("desc.L");
  --indent, writeln("}");
  
  std::vector<Nonterminal*> nonterminals = grammar->getNonterminals();

  assert( nonterminals.size() );
  // nonterminals[0] is a start nonterminal
  for(int i=0;i<(int)nonterminals.size();++i) {
    nt_map[nonterminals[i]->getName()] = next_label++;
  }
  for(int i=0;i<(int)nonterminals.size();++i) {
    writeln("_"+itos(nt_map[nonterminals[i]->getName()])+":;");
    encode(nonterminals[i],OFF); 
  }
  
  for(;next_label<LABEL_MAX;++next_label) {
    write("_"+itos(next_label)+":;");
  } 
  writeln("");
  
  --indent, writeln("}"); // compute
  writeln("");

  writeln("int main() {"), ++indent;
  writeln("getline(cin,I);");
  writeln("m = (int)I.size();");
  writeln("cout << (compute()?\"success\":\"fail\") << endl;");
  writeln("return 0;");
  --indent, writeln("}"); // main
}

void GPEGParser::encode(Node *node,int modify_ret) {
  int type = node->type;
  if( type == NONTERMINAL ) {
    Nonterminal* tmp = (Nonterminal*)node->values[NONTERMINAL];
    encode(tmp,modify_ret);
  } else if( type == SLASH ) {
    Slash* tmp = (Slash*)node->values[SLASH];
    encode(tmp,modify_ret);
  } else if( type == ALTERNATION ) {
    Alternation* tmp = (Alternation*)node->values[ALTERNATION];
    encode(tmp,modify_ret);
  } else if( type == CHAR ) {
    Char* tmp = (Char*)node->values[CHAR];
    encode(tmp,modify_ret);
  } else if( type == AND ) {
    And* tmp = (And*)node->values[AND];
    encode(tmp,modify_ret);
  } else if( type == NOT ) {
    Not* tmp = (Not*)node->values[NOT];
    encode(tmp,modify_ret);
  } else if( type == SEQUENCE ) {
    Sequence* tmp = (Sequence*)node->values[SEQUENCE];
    encode(tmp,modify_ret);
  } else if( type == QUESTION ) {
    Question* tmp = (Question*)node->values[QUESTION];
    encode(tmp,modify_ret);
  } else if( type == STAR ) {
    Star* tmp = (Star*)node->values[STAR];
    encode(tmp,modify_ret);
  } else if( type == PLUS ) {
    Plus* tmp = (Plus*)node->values[PLUS];
    encode(tmp,modify_ret);
  } else if( type == ANY ) {
    Any* tmp = (Any*)node->values[ANY];
    encode(tmp,modify_ret);
  } else if( type == RANGE ) {
    Range* tmp = (Range*)node->values[RANGE];
    encode(tmp,modify_ret);
  } else if( type == GPEG_STRING ) {
    Gpeg_string *tmp = (Gpeg_string*)node->values[GPEG_STRING];
    encode(tmp,modify_ret);
  } else if( type == GROUPING ) {
    Grouping *tmp = (Grouping*)node->values[GROUPING];
    encode(tmp,modify_ret);
  } else {
    std::cerr << "what is [[" << type << "]]?" << std::endl;
    assert(false);
  }
}

void GPEGParser::encode(Nonterminal *cur,int modify_ret) {
  if( cur->getExpression() == nullptr ) { // in a parsing expression ( e.g A <- 'a' [[A]]
    writeln("/* Nonterminal ("+cur->getName()+","+itos(modify_ret)+") */");
    int ret_label = next_label++;
    writeln("cu = create("+itos(ret_label)+",cu,i);");
    writeln("goto _"+itos(nt_map[cur->getName()])+";");
    writeln("_"+itos(ret_label)+":;");
  } else { // definition ( e.g. [[A <- 'a' A]]
    assert( modify_ret == OFF );
    encode(cur->getExpression(),modify_ret);
    writeln("pop(cu,i); /* Definition Success */");
    writeln("goto _0;");
  }
}


void GPEGParser::encode(Slash *tmp,int modify_ret) { 
  std::deque<Node*> alternates = tmp->getAlternates();
  int succ_label = next_label++;
  int ret_label  = next_label++;
  int modify_label = next_label++;
  int label_stamp = next_label;
  next_label += (int)alternates.size();

  writeln("cu = create("+itos(ret_label)+",cu,i); /* Slash */");

  for(int i=0;i<(int)alternates.size();++i) {
    writeln("_"+itos(label_stamp+i)+":;");
    if( i ) {
      writeln("i = cu.j;");
    }
    if( i+1 < (int)alternates.size() ) {
      encode(alternates[i],label_stamp+i+1);
      writeln("goto _"+itos(succ_label)+";");
    } else {
      encode(alternates[i],modify_label);
      writeln("goto _"+itos(succ_label)+";");
    }
  }

  writeln("_"+itos(modify_label)+":;");
  if( modify_ret != OFF ) {
    writeln("assert((int)GSS[created[cu]].size()==1);");
    writeln("cu = GSS[created[cu]][0];");
    writeln("goto _"+itos(modify_ret)+";");
  } else {
    writeln("goto _0;");
  }

  writeln("_"+itos(succ_label)+":;");
  writeln("pop(cu,i);");
  writeln("goto _0;");
  writeln("_"+itos(ret_label)+":;");
}

void GPEGParser::encode(Alternation *tmp,int modify_ret) {
  std::deque<Node*> alternates = tmp->getAlternates();
  int ret_label = next_label++;
  int modify_label = next_label++;
  int label_stamp = next_label;
  next_label += (int)alternates.size();
  writeln("cu = create("+itos(ret_label)+",cu,i); /* Alternation */");
  for(int i=0;i<(int)alternates.size();++i) {
    writeln("add("+itos(label_stamp+i)+",cu,i);");
  }
  writeln("goto _0;");
  for(int i=0;i<(int)alternates.size();++i) {
    writeln("_"+itos(label_stamp+i)+":;");
    encode(alternates[i],modify_label);
    writeln("pop(cu,i);");
    writeln("goto _0;");
  }

  writeln("_"+itos(modify_label)+":;");
  if( modify_ret != OFF ) {
    writeln("assert((int)GSS[created[cu]].size()==1);");
    writeln("cu = GSS[created[cu]][0];");
    writeln("goto _"+itos(modify_ret)+";");
  } else {
    writeln("goto _0;");
  }


  writeln("_"+itos(ret_label)+":;");
}

void GPEGParser::encode(Char *tmp,int modify_ret) {
  char value = tmp->getValue();
  if( !( value == '\\' ) && ( isgraph(value) || value == ' ' ) ) {
    writeln("if(i<m&&I[i]=='"+std::string(1,value)+"') {"), ++indent;
  } else {
    writeln("if(i<m&&I[i]==(char)"+itos((int)value)+") {"), ++indent;
  }
  writeln("i = i + 1;");
  --indent, writeln("} else {"), ++indent;
  if( modify_ret == OFF ) {
    writeln("goto _0;");
  } else {
    writeln("goto _"+itos(modify_ret)+";");
  }
  --indent, writeln("}"); // else
}

void GPEGParser::encode(And *cur,int modify_ret) {
  Node *next = cur->get();
  int predicate_label = next_label++;
  int ret_label = next_label++;
  writeln("/* And */");
  writeln("cu = create("+itos(ret_label)+",cu,i);");
  encode(next,predicate_label);
  writeln("pop(cu,cu.j);");
  writeln("goto _0;");

  writeln("_"+itos(predicate_label)+":;");
  if( modify_ret == OFF ) {
    writeln("goto _0;");
  } else {
    writeln("assert((int)GSS[created[cu]].size()==1);");
    writeln("cu = GSS[created[cu]][0];");
    writeln("goto _"+itos(modify_ret)+";");
  }

  writeln("_"+itos(ret_label)+":;");
}

void GPEGParser::encode(Not *cur,int modify_ret) {
  Node *next = cur->get();
  int predicate_label = next_label++;
  int ret_label = next_label++;
  writeln("/* Not */");
  writeln("cu = create("+itos(ret_label)+",cu,i);");
  encode(next,predicate_label);
  if( modify_ret == OFF ) {
    writeln("goto _0;");
  } else {
    writeln("assert((int)GSS[created[cu]].size()==1);");
    writeln("cu = GSS[created[cu]][0];");
    writeln("goto _"+itos(modify_ret)+";");
  }
  writeln("_"+itos(predicate_label)+":;");
  writeln("pop(cu,cu.j);");
  writeln("goto _0;");
  writeln("_"+itos(ret_label)+":;");
}

void GPEGParser::encode(Sequence *tmp,int modify_ret) {
  std::deque<Node*> sequence = tmp->getSequence();
  assert( sequence.size() );
  for(int i=0;i<(int)sequence.size();++i) {
    encode(sequence[i],modify_ret);
  }
}

void GPEGParser::encode(Question *cur,int modify_ret) {
  int ret_label = next_label++;
  int fail_ret_label = next_label++;
  writeln("cu = create("+itos(ret_label)+",cu,i); /* Question */");
  Node *next = cur->get();

  encode(next,fail_ret_label);
  writeln("pop(cu,i);");
  writeln("goto _0;");
  writeln("_"+itos(fail_ret_label)+":;");
  writeln("pop(cu,cu.j); /* Question */");
  writeln("goto _0;");
  writeln("_"+itos(ret_label)+":;");
}

void GPEGParser::encode(Star *cur,int modify_ret) {
  Node *next = cur->get();
  int loop_label = next_label++;
  int pre_fail_label = next_label++;
  int fail_label = next_label++;
  writeln("/* star */");
  writeln("add("+itos(loop_label)+",cu,i);");
  writeln("add("+itos(fail_label)+",cu,i);");
  writeln("goto _0;");
  writeln("_"+itos(loop_label)+":;");
  encode(next,pre_fail_label);
  writeln("if( !R.empty() && R.front().L == " + itos(fail_label) + " ) {"), ++indent;
  writeln("R.pop();");
  --indent, writeln("}");
  writeln("add("+itos(loop_label)+",cu,i);");
  writeln("add("+itos(fail_label)+",cu,i);");
  writeln("goto _0;");
  writeln("_"+itos(pre_fail_label)+":;");
  writeln("goto _0;");
  writeln("_"+itos(fail_label)+":;");
}

void GPEGParser::encode(Plus *cur,int modify_ret) {
  Node *next = cur->get();
  int loop_label = next_label++;
  int pre_fail_label = next_label++;
  int fail_label = next_label++;
  writeln("/* plus ( e+ => ee* ) */");
  encode(next,modify_ret);
  writeln("add("+itos(loop_label)+",cu,i);");
  writeln("add("+itos(fail_label)+",cu,i);");
  writeln("goto _0;");
  writeln("_"+itos(loop_label)+":;");
  encode(next,pre_fail_label);
  writeln("if( !R.empty() && R.front().L == " + itos(fail_label) + " ) {"), ++indent;
  writeln("R.pop();");
  --indent, writeln("}");
  writeln("add("+itos(loop_label)+",cu,i);");
  writeln("add("+itos(fail_label)+",cu,i);");
  writeln("goto _0;");
  writeln("_"+itos(pre_fail_label)+":;");
  writeln("goto _0;");
  writeln("_"+itos(fail_label)+":;");
}

void GPEGParser::encode(Any *cur,int modify_ret) {
  writeln("if(i<m&&(isgraph((char)I[i])||(I[i]==' '))) {//any character"), ++indent;
  writeln("i = i + 1;");
  --indent, writeln("} else {"), ++indent;
  if( modify_ret == OFF ) {
    writeln("goto _0;");
  } else {
    writeln("goto _"+itos(modify_ret)+";");
  }
  --indent, writeln("}");
}

void GPEGParser::encode(Range *cur,int modify_ret) {
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
	  condition += ("I[i]=='"+std::string(1,c)+"'");
	} else {
	  condition += ("I[i]==(char)"+itos((int)c)+"");
	}
      }
      i += 2;
    } else {
      if( !( cs[i] == '\\' ) && ( isgraph(cs[i]) || cs[i] == ' ' ) ) {
	condition += ("I[i]=='"+std::string(1,cs[i])+"'");
      } else {
	condition += ("I[i]==(char)"+itos((int)cs[i])+"");
      }
    }
  }
  writeln("if(i<m&&("+condition+")) {"), ++indent;
  writeln("i = i + 1;");
  --indent, writeln("} else {"), ++indent;
  if( modify_ret == OFF ) {
    writeln("goto _0;");
  } else {
    writeln("goto _"+itos(modify_ret)+";");
  }
  --indent, writeln("}");
}

void GPEGParser::encode(Gpeg_string *tmp,int modify_ret) {
  std::string str = tmp->get();
  for(int i=0;i<(int)str.size();++i) {
    if( !( str[i] == '\\' ) && ( isgraph(str[i]) || str[i] ==' ' ) ) {
      writeln("if(i<m&&I[i]=='"+std::string(1,str[i])+"') {"), ++indent;
    } else {
      writeln("if(i<m&&I[i]==(char)"+itos((int)str[i])+") {"), ++indent;
    }
    writeln("i = i + 1;");
    --indent, writeln("} else { "), ++indent;
    if( modify_ret == OFF ) {
      writeln("goto _0;");
    } else {
      writeln("goto _"+itos(modify_ret)+";");
    }
    --indent, writeln("}");
  }
}

void GPEGParser::encode(Grouping *tmp,int modify_ret) {
  assert( false ); /* DO NOT USE THIS FUNCTION */
  int dst_label = next_label++;
  writeln("cu = create("+itos(dst_label)+",cu,i);");
  Node *next = tmp->get();
  encode(next,modify_ret);
  writeln("pop(cu,i);");
  ///////?????? writeln("goto _0;") ha?
  writeln("_"+itos(dst_label)+":;");
}


// <--- delete grammar --->
void GPEGParser::delete_grammar() {
  std::vector<Nonterminal*> nvec = grammar->getNonterminals();
  for(int i=0;i<(int)nvec.size();++i) {
    delete_dfs(nvec[i]->getExpression());
  }
  delete grammar;
}

void GPEGParser::delete_dfs(Node* node) {
  int type = node->type;
  if( type == NONTERMINAL ) {
    Nonterminal* tmp = (Nonterminal*)node->values[NONTERMINAL];
    delete_dfs(tmp);
  } else if( type == SLASH ) {
    Slash* tmp = (Slash*)node->values[SLASH];
    delete_dfs(tmp);
  } else if( type == ALTERNATION ) {
    Alternation* tmp = (Alternation*)node->values[ALTERNATION];
    delete_dfs(tmp);
  } else if( type == CHAR ) {
    Char* tmp = (Char*)node->values[CHAR];
    delete_dfs(tmp);
  } else if( type == AND ) {
    And* tmp = (And*)node->values[AND];
    delete_dfs(tmp);
  } else if( type == NOT ) {
    Not* tmp = (Not*)node->values[NOT];
    delete_dfs(tmp);
  } else if( type == SEQUENCE ) {
    Sequence* tmp = (Sequence*)node->values[SEQUENCE];
    delete_dfs(tmp);
  } else if( type == QUESTION ) {
    Question* tmp = (Question*)node->values[QUESTION];
    delete_dfs(tmp);
  } else if( type == STAR ) {
    Star* tmp = (Star*)node->values[STAR];
    delete_dfs(tmp);
  } else if( type == PLUS ) {
    Plus* tmp = (Plus*)node->values[PLUS];
    delete_dfs(tmp);
  } else if( type == ANY ) {
    Any* tmp = (Any*)node->values[ANY];
    delete_dfs(tmp);
  } else if( type == RANGE ) {
    Range* tmp = (Range*)node->values[RANGE];
    delete_dfs(tmp);
  } else if( type == GPEG_STRING ) {
    Gpeg_string* tmp = (Gpeg_string*)node->values[GPEG_STRING];
    delete_dfs(tmp);
  } else if( type == GROUPING ) {
  } else {
    std::cerr << "what is [[" << type << "]]?" << std::endl;
    assert(false);
  }
}

void GPEGParser::delete_dfs(Nonterminal *tmp) { delete tmp; }

void GPEGParser::delete_dfs(Slash *tmp) { 
  std::deque<Node*> alternate = tmp->getAlternates();
  for(int i=0;i<(int)alternate.size();++i) {
    delete_dfs(alternate[i]);
  }
  delete tmp;
}

void GPEGParser::delete_dfs(Alternation *tmp) {
  std::deque<Node*> alternate = tmp->getAlternates();
  for(int i=0;i<(int)alternate.size();++i) {
    delete_dfs(alternate[i]);
  }
  delete tmp;
}

void GPEGParser::delete_dfs(Char *tmp) { delete tmp; }

void GPEGParser::delete_dfs(And *tmp) {
  delete_dfs(tmp->get());
  delete tmp;
}

void GPEGParser::delete_dfs(Not *tmp) {
  delete_dfs(tmp->get());
  delete tmp;
}
void GPEGParser::delete_dfs(Sequence *tmp) {
  std::deque<Node*> sequence = tmp->getSequence();
  for(int i=0;i<(int)sequence.size();++i) {
    delete_dfs(sequence[i]);
  }
  delete tmp;
}

void GPEGParser::delete_dfs(Question *tmp){ 
  delete_dfs(tmp->get());
  delete tmp;
}
void GPEGParser::delete_dfs(Star *tmp) {
  delete_dfs(tmp->get());
  delete tmp;
}
void GPEGParser::delete_dfs(Plus *tmp) {
  delete_dfs(tmp->get());
  delete tmp;
}
void GPEGParser::delete_dfs(Any *tmp) {
  delete tmp;
}
void GPEGParser::delete_dfs(Range *tmp) {
  delete tmp;
}
void GPEGParser::delete_dfs(Gpeg_string *tmp) {
  delete tmp;
}
void GPEGParser::delete_dfs(Grouping *tmp) {
  Node *next = tmp->get();
  delete_dfs(next);
  delete tmp;
}

// <--- parse --->

Grammar* GPEGParser::parse() {
  if( compiled ) return grammar;
  compiled = true;
  return grammar = GPEGParser::pGrammar();
}

inline bool isIdentifier(char c) { return ( 'a' <= c && c <= 'z' ) || ( 'A' <= c && c <= 'Z' ) || c == '_'; }

inline bool isIdentCont(char c) { return isIdentifier(c) || ( '0' <= c && c <= '9' ); }

std::string GPEGParser::pIdentifier() {
  if( show_trace ) { std::cerr << ">>pIdentifier" << std::endl; }
  assert( ptr < clen );
  assert( isIdentifier(context[ptr]) );
  std::string identifier = std::string(1,context[ptr++]);
  while( ptr < clen && isIdentCont(context[ptr]) ) {
    identifier += std::string(1,context[ptr++]);
  }
  pSpacing();
  return identifier;
}

char GPEGParser::pSLASH() {
  if( show_trace ) { std::cerr << ">>pSLASH" << std::endl; }
  assert( ptr < clen && context[ptr] == '/' );
  ++ptr;
  pSpacing();
  return '/';
}

char GPEGParser::pALTERNATION() {
  if( show_trace ) { std::cerr << ">>pALTERNATION" << std::endl; }
  assert( ptr < clen && context[ptr] == '|' );
  ++ptr;
  pSpacing();
  return '|';
}

bool GPEGParser::isDefinition() { // Identifier !LEFTARROW
  if( !isIdentifier(context[ptr]) ) return false;
  int back_ptr = ptr;
  pIdentifier();
  bool left_arrow = false;
  if( ptr+1 < clen && context[ptr] == '<' && context[ptr+1] == '-' ) left_arrow = true;
  ptr = back_ptr; /*backtracking*/
  return left_arrow;
}

inline bool isLiteral(char c) { return c == '\'' || c == '"'; }

bool GPEGParser::isSequence() {
  char c = context[ptr];
  return c == '&' || c == '!' || ( isIdentifier(c) && !isDefinition() ) || c == '(' || isLiteral(c) || c == '[' || c == '.';
}

void GPEGParser::pAND() {
  if( show_trace ) { std::cerr << ">>pAND" << std::endl; }
  assert( ptr < clen );
  assert( context[ptr] == '&' );
  ++ptr;
  pSpacing();
}

void GPEGParser::pNOT() {
  if( show_trace ) { std::cerr << ">>pNOT" << std::endl; }
  assert( ptr < clen );
  assert( context[ptr] == '!' );
  ++ptr;
  pSpacing();
}

void GPEGParser::pQUESTION() {
  if( show_trace ) { std::cerr << ">>pQUESTION" << std::endl; }
  assert( ptr < clen );
  assert( context[ptr] == '?' );
  ++ptr;
  pSpacing();
}

void GPEGParser::pSTAR() {
  if( show_trace ) { std::cerr << ">>pSTAR" << std::endl; }
  assert( ptr < clen );
  assert( context[ptr] == '*' );
  ++ptr;
  pSpacing();
}

void GPEGParser::pPLUS() {
  if( show_trace ) { std::cerr << ">>pPLUS" << std::endl; }
  assert( ptr < clen );
  assert( context[ptr] == '+' );
  ++ptr;
  pSpacing();
}

void GPEGParser::pOPEN() {
  if( show_trace ) { std::cerr << ">>pOPEN" << std::endl; }
  assert( ptr < clen );
  assert( context[ptr] == '(' );
  ++ptr;
  pSpacing();
}

void GPEGParser::pCLOSE() {
  if( show_trace ) { std::cerr << ">>pCLOSE" << std::endl; }
  assert( ptr < clen );
  assert( context[ptr] == ')' );
  ++ptr;
  pSpacing();
}

void GPEGParser::pDOT() {
  if( show_trace ) { std::cerr << ">>pDOT" << std::endl; }
  assert( ptr < clen );
  assert( context[ptr] == '.' );
  ++ptr;
  pSpacing();
}

char GPEGParser::pChar() {
  if( show_trace ) { std::cerr << ">>pChar" << std::endl; }
  assert( ptr < clen );
  if( context[ptr] == '\\' ) {
    ++ptr;
    if( context[ptr] == 'n' ) {
      ++ptr;
      return '\n';
    } else if( context[ptr] == 'r' ) {
      ++ptr;
      return '\r';
    } else if( context[ptr] == 't' ) {
      ++ptr;
      return '\t';
    } else if( context[ptr] == '\\' ) {
      ++ptr;
      return '\\';
    }
  }
  return context[ptr++];
}

std::string GPEGParser::pLiteral() {
  if( show_trace ) { std::cerr << ">>pLiteral" << std::endl; }
  assert( ptr < clen );
  assert( isLiteral(context[ptr]) );
  char origin = context[ptr];
  ++ptr;
  std::string buffer = "";
  while( ptr < clen ) {
    bool escape = false;
    if( context[ptr] == '\\' ) escape = true;
    char c = pChar();
    if( !escape && c == origin ) break;
    buffer += std::string(1,c);
  }
  return buffer;
}
/*
Sequence* toSequence(std::string str) {
  Sequence* seq = new Sequence;
  for(int i=0;i<(int)str.size();++i) {
    Node* node = new Node;
    Char* c = new Char;
    c->setValue(str[i]);
    node->setValue(c);
    seq->add(node);
  }
  return seq;
}
*/

// 若干定義通りではないので注意 | [...] のとき、 ... を全て取り出す
std::string GPEGParser::pRange() {
  std::string characters = "";
  char c;
  while( 1 ) {
    bool escape = false;
    if( context[ptr] == '\\' ) escape = true;
    c = pChar();
    if( !escape && c == ']' ) break;
    characters += std::string(1,c);
  }
  return characters;
}

Node* GPEGParser::pPrimary() {
  if( show_trace ) { std::cerr << ">>pPrimary" << std::endl; }
  assert( ptr < clen );
  char c = context[ptr];
  Node* node = new Node;
  if( isIdentifier(c) && !isDefinition() ) { // nonterminal
    Nonterminal* tmp = new Nonterminal;
    std::string name = pIdentifier();
    tmp->setName(name);
    node->setValue(tmp);
  } else if( c == '(' ) {
    pOPEN();
    Node* tmp = pExpression();
    //Grouping *gp = new Grouping;
    //gp->set(tmp);
    node = tmp;
    pCLOSE();
    //node->setValue(gp);
  } else if( isLiteral(c) )  {
    std::string buffer = pLiteral();
    if( (int)buffer.size() == 1 ) {
      Char *tmp = new Char;
      tmp->setValue(buffer[0]);
      node->setValue(tmp);
    } else {
      Gpeg_string* tmp = new Gpeg_string;
      tmp->set(buffer);
      node->setValue(tmp);
    }
    pSpacing();
  } else if( c == '[' ) {
    ++ptr;
    std::string characters = pRange();
    assert( ptr-1 >= 0 && context[ptr-1] == ']' );
    pSpacing();
    Range* tmp = new Range;
    tmp->set(characters);
    node->setValue(tmp);
  } else if( c == '.' ) {
    pDOT();
    node->setType(10);
  } else {
    std::cerr << "syntax error :: what is [[" << c << "]] in pPrimary()" << std::endl;
    assert(false);
  }
  return node;
}

Node* GPEGParser::pSuffix() {
  if( show_trace ) { std::cerr << ">>pSuffix" << std::endl; }

  Node* suffix = pPrimary();
  if( ptr < clen ) {
    if( context[ptr] == '?' ) {
      pQUESTION();
      Question* tmp = new Question;
      tmp->set(suffix);
      Node* node = new Node;
      node->setValue(tmp);
      return node;
    } else if( context[ptr] == '*' ) {
      pSTAR();
      Star* tmp = new Star;
      tmp->set(suffix);
      Node* node = new Node;
      node->setValue(tmp);
      return node;
    } else if( context[ptr] == '+' ) {
      pPLUS();
      Plus* tmp = new Plus;
      tmp->set(suffix);
      Node* node = new Node;
      node->setValue(tmp);
      return node;
    }
  } 
  return suffix;
}

Node* GPEGParser::pSequence() {
  if( show_trace ) { puts(">>pSequence"); }
  /* debug 
  Node* tmp = new Node;
  tmp->setType(3);
  ((Char*)tmp->values[3])->setValue(context[ptr]);
  ++ptr;
  return tmp;
  */
  Sequence* seq = new Sequence;
  while( ptr < clen && isSequence() ) {
    char c = context[ptr];
    if( c == '&' ) {
      pAND();
      And* tmp = new And;
      tmp->set(pSuffix());
      Node* node = new Node;
      node->setValue(tmp);
      seq->add(node);
      continue;
    } else if( c == '!' ) {
      pNOT();
      Not* tmp = new Not;
      tmp->set(pSuffix());
      Node* node = new Node;
      node->setValue(tmp);
      seq->add(node);
      continue;
    }
    Node* node = pSuffix();
    seq->add(node);
  }
  Node* ret = new Node;
  ret->setValue(seq);
  return ret;
}

Node* GPEGParser::pExpression() {
  if( show_trace ) { std::cerr << ">>pExpression" << std::endl; }
  std::deque<char> operators;
  std::deque<Node*> values;
  values.push_back(pSequence());
  while( ptr < clen && ( context[ptr] == '/' || context[ptr] == '|' ) ) {
    operators.push_back((context[ptr]=='/')?pSLASH():pALTERNATION());
    values.push_back(pSequence());
    /*
    Char * tmp = (Char*)values[(int)values.size()-1]->values[3];
    std::cout << "UUUUKLL :: " << tmp->getValue() << std::endl;
    */
  }
  assert( !values.empty() );
  if( operators.empty() ) {
    assert( (int)values.size() == 1 );
    return values[0];
  }

  assert( (int)operators.size()+1 == (int)values.size() );
  std::deque<Node*> buffer;
  buffer.push_back(values[0]);

  for(int i=0;i<(int)operators.size();++i) {

    char c = operators[i];
    Node* obj = new Node;
    obj->setType((c=='/')?1:2);

    if( !buffer.empty() ) {
      obj->add(buffer[0]);
      buffer.pop_front();
    }
    assert( i + 1 < (int)values.size() );
    obj->add(values[i+1]);
    ++i;
    while( i < (int)operators.size() && operators[i] == c ) {
      assert( i + 1 < (int)values.size() );
      obj->add(values[i+1]);

      ++i;
    };
    --i;
    buffer.push_back(obj);
  }
  assert((int)buffer.size() == 1);
  return buffer[0];
}

void GPEGParser::pLEFTARROW() {
  if( show_trace ) { std::cerr << ">>pLEFTARROW" << std::endl; }
  assert( ptr+1 < clen && context[ptr] == '<' && context[ptr+1] == '-' && "syntax error");
  ptr += 2; // skip <-
  pSpacing();
}

Nonterminal* GPEGParser::pDefinition() {
  if( show_trace ) { std::cerr << ">>pDefinition" << std::endl; }
  Nonterminal* nonterminal = new Nonterminal;

  nonterminal->setName(pIdentifier());

  pLEFTARROW();

  nonterminal->setExpression(pExpression());
  
  return nonterminal;
}

Grammar* GPEGParser::pGrammar() {
  if( show_trace ) { std::cerr << ">>pGrammar" << std::endl; }
  Grammar * g = new Grammar;
  pSpacing();
  while( ptr < clen && isIdentifier(context[ptr]) ) {
    g->add(pDefinition());
  }
  return g;
}

inline bool isEndOfLine(char c) { return /*c == '\r\n' ||*/ c == '\n' || c == '\r'; }

void GPEGParser::pSpacing() {
  //if( show_trace ) { std::cerr << ">>pSpacing" << std::endl; }
  bool update = true;
  while( ptr < clen && update ) {
    update = false;
    char c = context[ptr];
    if( c == ' ' || c == '\t' || /*c == '\r\n' ||*/ c == '\n' || c == '\r' ) ++ptr, update = true;
    else if( c == '#' ) {
      ++ptr, update = true;
      while( ptr < clen && !isEndOfLine(context[ptr++]) );
    }
  }
}



