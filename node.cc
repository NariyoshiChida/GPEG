#include"nonterminal.h"
#include"node.h"
#include<iostream>
#include<string>
#include<deque>
#include<cassert>
#include<cctype>
#include<algorithm>
#include<sstream>

std::string itos(int i) { std::stringstream ss; ss << i; return ss.str(); }

std::string Node::toString()  {
    std::string ret = "";
    if( type == NONTERMINAL ) {
      Nonterminal* tmp = (Nonterminal*)values[type];
      if( tmp->getExpression() != nullptr ) {
	ret += tmp->getName();
	ret += " <- ";
	ret += (tmp->getExpression())->toString();
      } else {
	ret = "(" + tmp->getName() + ")";
      }
    } else if( type == SLASH ) {
      Slash* tmp = (Slash*)values[type];
      std::deque<Node*> deq = tmp->getAlternates();
      for(int i=0;i<(int)deq.size();++i) {
	if( i ) ret += "/";
	ret += deq[i]->toString();
      }
      ret = "(" + ret + ")";/**/

    } else if( type == ALTERNATION ) {
      Alternation* tmp = (Alternation*)values[type];
      std::deque<Node*> deq = tmp->getAlternates();
      for(int i=0;i<(int)deq.size();++i) {
	if( i ) ret += "|";
	ret += deq[i]->toString();
      }
      ret = "(" + ret + ")";/**/

    } else if( type == CHAR ) {
      Char* tmp = (Char*)values[type];
      char value = tmp->getValue();
      if( isgraph(value) || value == ' ' ) {
	ret = "'" + std::string(1,value) + "'";
      } else {
	ret = "'" + itos((int)value) + "'";
      }

    } else if( type == AND ) {
      And* tmp = (And*)values[type];
      Node* next = tmp->get();
      ret = "&(" + ( next->toString() ) + ")";

    } else if( type == NOT ) {
      Not* tmp = (Not*)values[type];
      Node* next = tmp->get();
      ret = "!(" + ( next->toString() ) + ")";

    } else if( type == SEQUENCE ) {
      Sequence* tmp = (Sequence*)values[type];
      std::deque<Node*> deq = tmp->getSequence();
      for(int i=0;i<(int)deq.size();++i) {
	ret += deq[i]->toString();
      }

    } else if( type == QUESTION ) {
      Question* tmp = (Question*)values[type];
      Node* next = tmp->get();
      ret = "(" + ( next->toString() ) + ")?";

    } else if( type == STAR ) {
      Star* tmp = (Star*)values[type];
      Node* next = tmp->get();
      ret = "(" + ( next->toString() ) + ")*";

    } else if( type == PLUS ) { 
      Plus* tmp = (Plus*)values[type];
      Node* next = tmp->get();
      ret = "(" + ( next->toString() ) + ")+";
    } else if( type == ANY ) { 
      ret = ".";
    } else if( type == RANGE ) {
      Range* tmp = (Range*)values[type];
      std::string str = tmp->get();
      ret = "'";
      for(int i=0;i<(int)str.size();++i) {
	char value = str[i];
	if( isgraph(value) || value == ' ' ) {
	  ret += std::string(1,value);
	} else {
	  ret += ( "(" +itos((int)value) + ")" );
	}
      }
      ret += "'";

    } else if( type == GPEG_STRING ) {
      Gpeg_string *tmp = (Gpeg_string*)values[type];
      std::string str = tmp->get();

      ret = "'";
      for(int i=0;i<(int)str.size();++i) {
	char value = str[i];
	if( isgraph(value) || value == ' ' ) {
	  ret += std::string(1,value);
	} else {
	  ret += ( "(" + itos((int)value) + ")" );
	}
      }
      ret += "'";

    } else if( type == GROUPING ) {
      Grouping *tmp = (Grouping*)values[type];
      Node *next = tmp->get();
      ret = "(";
      ret += next->toString();
      ret += ")";
    } else {
      std::cerr << "What is the type [[" << type << "]]?" << std::endl;
      assert(false);
    }
    return ret;
  }

void Node::setType(int tmp) {
  type = tmp;
  if( tmp == NONTERMINAL ) {
    values[type] = new Nonterminal; 
  } else if( tmp == SLASH ) {
    values[type] = new Slash;
  } else if( tmp == ALTERNATION ) {
    values[type] = new Alternation;
  } else if( tmp == CHAR ) {
    values[type] = new Char;
  } else if( tmp == AND ) {
    values[type] = new And;
  } else if( tmp == NOT ) {
    values[type] = new Not;
  } else if( tmp == SEQUENCE ) {
    values[type] = new Sequence;
  } else if( tmp == QUESTION ) {
    values[type] = new Question;
  } else if( tmp == STAR ) {
    values[type] = new Star;
  } else if( tmp == PLUS ) {
    values[type] = new Plus;
  } else if( tmp == ANY ) {
    values[type] = new Any;
  } else if( tmp == RANGE ) {
    values[type] = new Range;
  } else if( tmp == GPEG_STRING ) {
    values[type] = new Gpeg_string;
  } else if( tmp == GROUPING ) {
    values[type] = new Grouping;
  } else {
    std::cerr << "type [[" << tmp << "]] not found in Node::setType(int tmp)" << std::endl;
    assert( false );
  }
}


void Node::add(Node* tmp) {
  if( type == SLASH ) {
    ((Slash*)values[type])->add(tmp);
  } else if( type == ALTERNATION ) {
    ((Alternation*)values[type])->add(tmp);
  } else if( type == SEQUENCE ) {
    ((Sequence*)values[type])->add(tmp);
  } else assert(false);
}

void Node::setValue(Nonterminal* tmp) {
  type = NONTERMINAL;
  values[NONTERMINAL] = tmp;
}

void Node::setValue(Slash* tmp){
  type = SLASH;
  values[SLASH] = tmp;
}

void Node::setValue(Alternation* tmp) {
  type = ALTERNATION;
  values[ALTERNATION] = tmp;
}

void Node::setValue(Sequence* tmp) {
  type = SEQUENCE;
  values[SEQUENCE] = tmp;
}

void Node::setValue(Char* tmp) {
  type = CHAR;
  values[CHAR] = tmp;
}

void Node::setValue(And* tmp) {
  type = AND;
  values[AND] = tmp;
}

void Node::setValue(Not* tmp) {
  type = NOT;
  values[NOT] = tmp;
}

void Node::setValue(Question* tmp) {
  type = QUESTION;
  values[QUESTION] = tmp;
}

void Node::setValue(Star* tmp) {
  type = STAR;
  values[STAR] = tmp;
}

void Node::setValue(Plus* tmp) {
  type = PLUS;
  values[PLUS] = tmp;
}

void Node::setValue(Any* tmp) {
  type = ANY;
  values[ANY] = tmp;
}

void Node::setValue(Range* tmp) {
  type = RANGE;
  values[RANGE] = tmp;
}

void Node::setValue(Gpeg_string *tmp) {
  type = GPEG_STRING;
  values[GPEG_STRING] = tmp;
}

void Node::setValue(Grouping *tmp) {
  type = GROUPING;
  values[GROUPING] = tmp;
}
