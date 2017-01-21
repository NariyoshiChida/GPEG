#include<iostream>
#include<chrono>
#include<deque>
#include<cassert>
#include<climits>
#include<unordered_map>
#include<algorithm>

#define FAIL -1

using namespace std;

int m;
int i;
string I;
typedef pair<int,int> key;
const long long base = 1000; // for hash

namespace std {
  template <>
  class hash<std::pair<int, int>> {
    public:
    size_t operator()(const std::pair<int, int>& x) const {
      return base * x.second + x.first;
    }
  };
}
unordered_map<key,deque<int>> memo;

deque<int> parse_File();
deque<int> parse_slash4();
deque<int> parse_slash9();
deque<int> parse_slash15();
deque<int> parse_slash20();
deque<int> parse_Chunk();
deque<int> parse_Expr();
deque<int> parse_PROLOG();
deque<int> parse_while37();
deque<int> parse_not39();
deque<int> parse_while52();
deque<int> parse_DTD();
deque<int> parse_while63();
deque<int> parse_not65();
deque<int> parse_while76();
deque<int> parse_Xml();
deque<int> parse_while88();
deque<int> parse_while96();
deque<int> parse_slash107();
deque<int> parse_slash112();
deque<int> parse_while115();
deque<int> parse_while123();
deque<int> parse_slash128();
deque<int> parse_slash133();
deque<int> parse_while148();
deque<int> parse_Name();
deque<int> parse_NAME();
deque<int> parse_while161();
deque<int> parse_slash166();
deque<int> parse_slash170();
deque<int> parse_Attribute();
deque<int> parse_while181();
deque<int> parse_while190();
deque<int> parse_while200();
deque<int> parse_String();
deque<int> parse_while210();
deque<int> parse_not212();
deque<int> parse_Content();
deque<int> parse_slash227();
deque<int> parse_slash232();
deque<int> parse_slash237();
deque<int> parse_CDataSec();
deque<int> parse_while257();
deque<int> parse_CDATA();
deque<int> parse_while266();
deque<int> parse_not268();
deque<int> parse_not275();
deque<int> parse_slash296();
deque<int> parse_slash315();
deque<int> parse_COMMENT();
deque<int> parse_while323();
deque<int> parse_not325();
deque<int> parse_while340();
deque<int> parse_Text();
deque<int> parse_not349();
deque<int> parse_while355();
deque<int> parse_not357();
deque<int> parse_S();

deque<int> parse_File(){
  if(memo.count(key(0,i))) {
    return memo[key(0,i)];
  }
  int backtracking_ptr_for_packrat0=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Prioritized Choice */
    deque<int> next_prev2;
    deque<int> prioritized_choice_final_prev3;
    next_prev2.clear();
    for(int i1=0;i1<(int)prev.size();++i1) {
      i = prev[i1];
      tmp = parse_slash4();
      if(!tmp.empty()&&tmp[0]==FAIL) { next_prev2.push_back(prev[i1]); }
      for(int i8=0;i8<(int)tmp.size();++i8) {
        if( tmp[i8] != FAIL ) {
          prioritized_choice_final_prev3.push_back(tmp[i8]);
        }
      }
    }
    prev = next_prev2;
    next_prev2.clear();
    for(int i1=0;i1<(int)prev.size();++i1) {
      i = prev[i1];
      tmp = parse_slash9();
      if(!tmp.empty()&&tmp[0]==FAIL) { next_prev2.push_back(prev[i1]); }
      for(int i11=0;i11<(int)tmp.size();++i11) {
        if( tmp[i11] != FAIL ) {
          prioritized_choice_final_prev3.push_back(tmp[i11]);
        }
      }
    }
    prev = next_prev2;
    if(!prev.empty()) {
      if(!(!prioritized_choice_final_prev3.empty() && prioritized_choice_final_prev3.front() == FAIL )) {
        prioritized_choice_final_prev3.push_front(FAIL);
      }
    }
    prev = prioritized_choice_final_prev3;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Prioritized Choice */
    deque<int> next_prev13;
    deque<int> prioritized_choice_final_prev14;
    next_prev13.clear();
    for(int i12=0;i12<(int)prev.size();++i12) {
      i = prev[i12];
      tmp = parse_slash15();
      if(!tmp.empty()&&tmp[0]==FAIL) { next_prev13.push_back(prev[i12]); }
      for(int i19=0;i19<(int)tmp.size();++i19) {
        if( tmp[i19] != FAIL ) {
          prioritized_choice_final_prev14.push_back(tmp[i19]);
        }
      }
    }
    prev = next_prev13;
    next_prev13.clear();
    for(int i12=0;i12<(int)prev.size();++i12) {
      i = prev[i12];
      tmp = parse_slash20();
      if(!tmp.empty()&&tmp[0]==FAIL) { next_prev13.push_back(prev[i12]); }
      for(int i22=0;i22<(int)tmp.size();++i22) {
        if( tmp[i22] != FAIL ) {
          prioritized_choice_final_prev14.push_back(tmp[i22]);
        }
      }
    }
    prev = next_prev13;
    if(!prev.empty()) {
      if(!(!prioritized_choice_final_prev14.empty() && prioritized_choice_final_prev14.front() == FAIL )) {
        prioritized_choice_final_prev14.push_front(FAIL);
      }
    }
    prev = prioritized_choice_final_prev14;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (Xml) */
    deque<int> next_prev24;
    for(int i23=0;i23<(int)prev.size();++i23) {
      if( prev[i23] == FAIL ) {
        if(!(!next_prev24.empty() && next_prev24.front() == FAIL )) {
          next_prev24.push_front(FAIL);
        }
        continue;
      }
      i = prev[i23];
      tmp = parse_Xml();
      
      for(int i23=0;i23<(int)tmp.size();++i23) {
        if( tmp[i23] == FAIL ) {
          if(!( !next_prev24.empty() && next_prev24[0] == FAIL )) {
            next_prev24.push_front(FAIL);
          }
        } else {
          next_prev24.push_back(tmp[i23]);
        }
      }
    }
    prev = next_prev24;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i0=0;i0<(int)prev.size();++i0) {
    if( prev[i0] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i0]);
    }
  }
  return memo[key(0,backtracking_ptr_for_packrat0)] = result;
}

inline deque<int> parse_slash4() { 
  if(memo.count(key(1,i))) {
    return memo[key(1,i)];
  }
  int backtracking_ptr_for_packrat1=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (PROLOG) */
  deque<int> next_prev7;
  for(int i6=0;i6<(int)prev.size();++i6) {
    if( prev[i6] == FAIL ) {
      if(!(!next_prev7.empty() && next_prev7.front() == FAIL )) {
        next_prev7.push_front(FAIL);
      }
      continue;
    }
    i = prev[i6];
    tmp = parse_PROLOG();
    
    for(int i6=0;i6<(int)tmp.size();++i6) {
      if( tmp[i6] == FAIL ) {
        if(!( !next_prev7.empty() && next_prev7[0] == FAIL )) {
          next_prev7.push_front(FAIL);
        }
      } else {
        next_prev7.push_back(tmp[i6]);
      }
    }
  }
  prev = next_prev7;
  for(int i5=0;i5<(int)prev.size();++i5) {
    if( prev[i5] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i5]);
    }
  }
  return memo[key(1,backtracking_ptr_for_packrat1)] = result;
}

inline deque<int> parse_slash9() { 
  if(memo.count(key(2,i))) {
    return memo[key(2,i)];
  }
  int backtracking_ptr_for_packrat2=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  for(int i10=0;i10<(int)prev.size();++i10) {
    if( prev[i10] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i10]);
    }
  }
  return memo[key(2,backtracking_ptr_for_packrat2)] = result;
}

inline deque<int> parse_slash15() { 
  if(memo.count(key(3,i))) {
    return memo[key(3,i)];
  }
  int backtracking_ptr_for_packrat3=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (DTD) */
  deque<int> next_prev18;
  for(int i17=0;i17<(int)prev.size();++i17) {
    if( prev[i17] == FAIL ) {
      if(!(!next_prev18.empty() && next_prev18.front() == FAIL )) {
        next_prev18.push_front(FAIL);
      }
      continue;
    }
    i = prev[i17];
    tmp = parse_DTD();
    
    for(int i17=0;i17<(int)tmp.size();++i17) {
      if( tmp[i17] == FAIL ) {
        if(!( !next_prev18.empty() && next_prev18[0] == FAIL )) {
          next_prev18.push_front(FAIL);
        }
      } else {
        next_prev18.push_back(tmp[i17]);
      }
    }
  }
  prev = next_prev18;
  for(int i16=0;i16<(int)prev.size();++i16) {
    if( prev[i16] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i16]);
    }
  }
  return memo[key(3,backtracking_ptr_for_packrat3)] = result;
}

inline deque<int> parse_slash20() { 
  if(memo.count(key(4,i))) {
    return memo[key(4,i)];
  }
  int backtracking_ptr_for_packrat4=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  for(int i21=0;i21<(int)prev.size();++i21) {
    if( prev[i21] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i21]);
    }
  }
  return memo[key(4,backtracking_ptr_for_packrat4)] = result;
}

deque<int> parse_Chunk(){
  if(memo.count(key(5,i))) {
    return memo[key(5,i)];
  }
  int backtracking_ptr_for_packrat5=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (Xml) */
    deque<int> next_prev27;
    for(int i26=0;i26<(int)prev.size();++i26) {
      if( prev[i26] == FAIL ) {
        if(!(!next_prev27.empty() && next_prev27.front() == FAIL )) {
          next_prev27.push_front(FAIL);
        }
        continue;
      }
      i = prev[i26];
      tmp = parse_Xml();
      
      for(int i26=0;i26<(int)tmp.size();++i26) {
        if( tmp[i26] == FAIL ) {
          if(!( !next_prev27.empty() && next_prev27[0] == FAIL )) {
            next_prev27.push_front(FAIL);
          }
        } else {
          next_prev27.push_back(tmp[i26]);
        }
      }
    }
    prev = next_prev27;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i25=0;i25<(int)prev.size();++i25) {
    if( prev[i25] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i25]);
    }
  }
  return memo[key(5,backtracking_ptr_for_packrat5)] = result;
}

deque<int> parse_Expr(){
  if(memo.count(key(6,i))) {
    return memo[key(6,i)];
  }
  int backtracking_ptr_for_packrat6=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (Xml) */
    deque<int> next_prev30;
    for(int i29=0;i29<(int)prev.size();++i29) {
      if( prev[i29] == FAIL ) {
        if(!(!next_prev30.empty() && next_prev30.front() == FAIL )) {
          next_prev30.push_front(FAIL);
        }
        continue;
      }
      i = prev[i29];
      tmp = parse_Xml();
      
      for(int i29=0;i29<(int)tmp.size();++i29) {
        if( tmp[i29] == FAIL ) {
          if(!( !next_prev30.empty() && next_prev30[0] == FAIL )) {
            next_prev30.push_front(FAIL);
          }
        } else {
          next_prev30.push_back(tmp[i29]);
        }
      }
    }
    prev = next_prev30;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i28=0;i28<(int)prev.size();++i28) {
    if( prev[i28] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i28]);
    }
  }
  return memo[key(6,backtracking_ptr_for_packrat6)] = result;
}

deque<int> parse_PROLOG(){
  if(memo.count(key(7,i))) {
    return memo[key(7,i)];
  }
  int backtracking_ptr_for_packrat7=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i32=0;i32<(int)prev.size();++i32) {
      if( prev[i32] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i32]<m&&I[prev[i32]]=='<') {
        tmp.push_back(prev[i32]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i33=0;i33<(int)prev.size();++i33) {
      if( prev[i33] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i33]<m&&I[prev[i33]]=='?') {
        tmp.push_back(prev[i33]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i34=0;i34<(int)prev.size();++i34) {
      if( prev[i34] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i34]<m&&I[prev[i34]]=='x') {
        tmp.push_back(prev[i34]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i35=0;i35<(int)prev.size();++i35) {
      if( prev[i35] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i35]<m&&I[prev[i35]]=='m') {
        tmp.push_back(prev[i35]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i36=0;i36<(int)prev.size();++i36) {
      if( prev[i36] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i36]<m&&I[prev[i36]]=='l') {
        tmp.push_back(prev[i36]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev46;
    deque<int> star_final_prev47;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev46.clear();
      for(int i48=0;i48<(int)prev.size();++i48) {
        i = prev[i48];
        tmp = parse_while37();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev47.push_back(prev[i48]);
        }
        for(int i49=0;i49<(int)tmp.size();++i49) {
          if(tmp[i49]==FAIL) {
            if(!( !next_prev46.empty() && next_prev46.front() == FAIL )) {
              next_prev46.push_front(FAIL);
            }
          } else {
            next_prev46.push_back(tmp[i49]);
          }
        }
      }
      prev = next_prev46;
    }
    prev = star_final_prev47;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i50=0;i50<(int)prev.size();++i50) {
      if( prev[i50] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i50]<m&&I[prev[i50]]=='?') {
        tmp.push_back(prev[i50]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i51=0;i51<(int)prev.size();++i51) {
      if( prev[i51] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i51]<m&&I[prev[i51]]=='>') {
        tmp.push_back(prev[i51]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev56;
    deque<int> star_final_prev57;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev56.clear();
      for(int i58=0;i58<(int)prev.size();++i58) {
        i = prev[i58];
        tmp = parse_while52();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev57.push_back(prev[i58]);
        }
        for(int i59=0;i59<(int)tmp.size();++i59) {
          if(tmp[i59]==FAIL) {
            if(!( !next_prev56.empty() && next_prev56.front() == FAIL )) {
              next_prev56.push_front(FAIL);
            }
          } else {
            next_prev56.push_back(tmp[i59]);
          }
        }
      }
      prev = next_prev56;
    }
    prev = star_final_prev57;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i31=0;i31<(int)prev.size();++i31) {
    if( prev[i31] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i31]);
    }
  }
  return memo[key(7,backtracking_ptr_for_packrat7)] = result;
}

inline deque<int> parse_while37() { 
  if(memo.count(key(8,i))) {
    return memo[key(8,i)];
  }
  int backtracking_ptr_for_packrat8=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev44;
    for(int i43=0;i43<(int)prev.size();++i43) {
      i = prev[i43];
      tmp = parse_not39();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev44.push_back(prev[i43]);
      } else {
        if(!(!next_prev44.empty()&&next_prev44.front()==FAIL)) {
          next_prev44.push_front(FAIL);
        }
      }
    }
    prev = next_prev44;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i45=0;i45<(int)prev.size();++i45) {
      if( prev[i45] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i45]<m) {//any character
        tmp.push_back(prev[i45]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i38=0;i38<(int)prev.size();++i38) {
    if( prev[i38] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i38]);
    }
  }
  return memo[key(8,backtracking_ptr_for_packrat8)] = result;
}

inline deque<int> parse_not39() { 
  if(memo.count(key(9,i))) {
    return memo[key(9,i)];
  }
  int backtracking_ptr_for_packrat9=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i41=0;i41<(int)prev.size();++i41) {
    if( prev[i41] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i41]<m&&I[prev[i41]]=='?') {
      tmp.push_back(prev[i41]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i42=0;i42<(int)prev.size();++i42) {
    if( prev[i42] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i42]<m&&I[prev[i42]]=='>') {
      tmp.push_back(prev[i42]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i40=0;i40<(int)prev.size();++i40) {
    if( prev[i40] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i40]);
    }
  }
  return memo[key(9,backtracking_ptr_for_packrat9)] = result;
}

inline deque<int> parse_while52() { 
  if(memo.count(key(10,i))) {
    return memo[key(10,i)];
  }
  int backtracking_ptr_for_packrat10=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev55;
  for(int i54=0;i54<(int)prev.size();++i54) {
    if( prev[i54] == FAIL ) {
      if(!(!next_prev55.empty() && next_prev55.front() == FAIL )) {
        next_prev55.push_front(FAIL);
      }
      continue;
    }
    i = prev[i54];
    tmp = parse_S();
    
    for(int i54=0;i54<(int)tmp.size();++i54) {
      if( tmp[i54] == FAIL ) {
        if(!( !next_prev55.empty() && next_prev55[0] == FAIL )) {
          next_prev55.push_front(FAIL);
        }
      } else {
        next_prev55.push_back(tmp[i54]);
      }
    }
  }
  prev = next_prev55;
  for(int i53=0;i53<(int)prev.size();++i53) {
    if( prev[i53] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i53]);
    }
  }
  return memo[key(10,backtracking_ptr_for_packrat10)] = result;
}

deque<int> parse_DTD(){
  if(memo.count(key(11,i))) {
    return memo[key(11,i)];
  }
  int backtracking_ptr_for_packrat11=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i61=0;i61<(int)prev.size();++i61) {
      if( prev[i61] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i61]<m&&I[prev[i61]]=='<') {
        tmp.push_back(prev[i61]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i62=0;i62<(int)prev.size();++i62) {
      if( prev[i62] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i62]<m&&I[prev[i62]]=='!') {
        tmp.push_back(prev[i62]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev71;
    deque<int> star_final_prev72;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev71.clear();
      for(int i73=0;i73<(int)prev.size();++i73) {
        i = prev[i73];
        tmp = parse_while63();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev72.push_back(prev[i73]);
        }
        for(int i74=0;i74<(int)tmp.size();++i74) {
          if(tmp[i74]==FAIL) {
            if(!( !next_prev71.empty() && next_prev71.front() == FAIL )) {
              next_prev71.push_front(FAIL);
            }
          } else {
            next_prev71.push_back(tmp[i74]);
          }
        }
      }
      prev = next_prev71;
    }
    prev = star_final_prev72;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i75=0;i75<(int)prev.size();++i75) {
      if( prev[i75] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i75]<m&&I[prev[i75]]=='>') {
        tmp.push_back(prev[i75]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev80;
    deque<int> star_final_prev81;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev80.clear();
      for(int i82=0;i82<(int)prev.size();++i82) {
        i = prev[i82];
        tmp = parse_while76();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev81.push_back(prev[i82]);
        }
        for(int i83=0;i83<(int)tmp.size();++i83) {
          if(tmp[i83]==FAIL) {
            if(!( !next_prev80.empty() && next_prev80.front() == FAIL )) {
              next_prev80.push_front(FAIL);
            }
          } else {
            next_prev80.push_back(tmp[i83]);
          }
        }
      }
      prev = next_prev80;
    }
    prev = star_final_prev81;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i60=0;i60<(int)prev.size();++i60) {
    if( prev[i60] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i60]);
    }
  }
  return memo[key(11,backtracking_ptr_for_packrat11)] = result;
}

inline deque<int> parse_while63() { 
  if(memo.count(key(12,i))) {
    return memo[key(12,i)];
  }
  int backtracking_ptr_for_packrat12=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev69;
    for(int i68=0;i68<(int)prev.size();++i68) {
      i = prev[i68];
      tmp = parse_not65();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev69.push_back(prev[i68]);
      } else {
        if(!(!next_prev69.empty()&&next_prev69.front()==FAIL)) {
          next_prev69.push_front(FAIL);
        }
      }
    }
    prev = next_prev69;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i70=0;i70<(int)prev.size();++i70) {
      if( prev[i70] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i70]<m) {//any character
        tmp.push_back(prev[i70]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i64=0;i64<(int)prev.size();++i64) {
    if( prev[i64] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i64]);
    }
  }
  return memo[key(12,backtracking_ptr_for_packrat12)] = result;
}

inline deque<int> parse_not65() { 
  if(memo.count(key(13,i))) {
    return memo[key(13,i)];
  }
  int backtracking_ptr_for_packrat13=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i67=0;i67<(int)prev.size();++i67) {
    if( prev[i67] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i67]<m&&I[prev[i67]]=='>') {
      tmp.push_back(prev[i67]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i66=0;i66<(int)prev.size();++i66) {
    if( prev[i66] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i66]);
    }
  }
  return memo[key(13,backtracking_ptr_for_packrat13)] = result;
}

inline deque<int> parse_while76() { 
  if(memo.count(key(14,i))) {
    return memo[key(14,i)];
  }
  int backtracking_ptr_for_packrat14=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev79;
  for(int i78=0;i78<(int)prev.size();++i78) {
    if( prev[i78] == FAIL ) {
      if(!(!next_prev79.empty() && next_prev79.front() == FAIL )) {
        next_prev79.push_front(FAIL);
      }
      continue;
    }
    i = prev[i78];
    tmp = parse_S();
    
    for(int i78=0;i78<(int)tmp.size();++i78) {
      if( tmp[i78] == FAIL ) {
        if(!( !next_prev79.empty() && next_prev79[0] == FAIL )) {
          next_prev79.push_front(FAIL);
        }
      } else {
        next_prev79.push_back(tmp[i78]);
      }
    }
  }
  prev = next_prev79;
  for(int i77=0;i77<(int)prev.size();++i77) {
    if( prev[i77] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i77]);
    }
  }
  return memo[key(14,backtracking_ptr_for_packrat14)] = result;
}

deque<int> parse_Xml(){
  if(memo.count(key(15,i))) {
    return memo[key(15,i)];
  }
  int backtracking_ptr_for_packrat15=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i85=0;i85<(int)prev.size();++i85) {
      if( prev[i85] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i85]<m&&I[prev[i85]]=='<') {
        tmp.push_back(prev[i85]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (Name) */
    deque<int> next_prev87;
    for(int i86=0;i86<(int)prev.size();++i86) {
      if( prev[i86] == FAIL ) {
        if(!(!next_prev87.empty() && next_prev87.front() == FAIL )) {
          next_prev87.push_front(FAIL);
        }
        continue;
      }
      i = prev[i86];
      tmp = parse_Name();
      
      for(int i86=0;i86<(int)tmp.size();++i86) {
        if( tmp[i86] == FAIL ) {
          if(!( !next_prev87.empty() && next_prev87[0] == FAIL )) {
            next_prev87.push_front(FAIL);
          }
        } else {
          next_prev87.push_back(tmp[i86]);
        }
      }
    }
    prev = next_prev87;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev92;
    deque<int> star_final_prev93;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev92.clear();
      for(int i94=0;i94<(int)prev.size();++i94) {
        i = prev[i94];
        tmp = parse_while88();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev93.push_back(prev[i94]);
        }
        for(int i95=0;i95<(int)tmp.size();++i95) {
          if(tmp[i95]==FAIL) {
            if(!( !next_prev92.empty() && next_prev92.front() == FAIL )) {
              next_prev92.push_front(FAIL);
            }
          } else {
            next_prev92.push_back(tmp[i95]);
          }
        }
      }
      prev = next_prev92;
    }
    prev = star_final_prev93;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev100;
    deque<int> star_final_prev101;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev100.clear();
      for(int i102=0;i102<(int)prev.size();++i102) {
        i = prev[i102];
        tmp = parse_while96();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev101.push_back(prev[i102]);
        }
        for(int i103=0;i103<(int)tmp.size();++i103) {
          if(tmp[i103]==FAIL) {
            if(!( !next_prev100.empty() && next_prev100.front() == FAIL )) {
              next_prev100.push_front(FAIL);
            }
          } else {
            next_prev100.push_back(tmp[i103]);
          }
        }
      }
      prev = next_prev100;
    }
    prev = star_final_prev101;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Prioritized Choice */
    deque<int> next_prev105;
    deque<int> prioritized_choice_final_prev106;
    next_prev105.clear();
    for(int i104=0;i104<(int)prev.size();++i104) {
      i = prev[i104];
      tmp = parse_slash107();
      if(!tmp.empty()&&tmp[0]==FAIL) { next_prev105.push_back(prev[i104]); }
      for(int i111=0;i111<(int)tmp.size();++i111) {
        if( tmp[i111] != FAIL ) {
          prioritized_choice_final_prev106.push_back(tmp[i111]);
        }
      }
    }
    prev = next_prev105;
    next_prev105.clear();
    for(int i104=0;i104<(int)prev.size();++i104) {
      i = prev[i104];
      tmp = parse_slash112();
      if(!tmp.empty()&&tmp[0]==FAIL) { next_prev105.push_back(prev[i104]); }
      for(int i147=0;i147<(int)tmp.size();++i147) {
        if( tmp[i147] != FAIL ) {
          prioritized_choice_final_prev106.push_back(tmp[i147]);
        }
      }
    }
    prev = next_prev105;
    if(!prev.empty()) {
      if(!(!prioritized_choice_final_prev106.empty() && prioritized_choice_final_prev106.front() == FAIL )) {
        prioritized_choice_final_prev106.push_front(FAIL);
      }
    }
    prev = prioritized_choice_final_prev106;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev152;
    deque<int> star_final_prev153;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev152.clear();
      for(int i154=0;i154<(int)prev.size();++i154) {
        i = prev[i154];
        tmp = parse_while148();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev153.push_back(prev[i154]);
        }
        for(int i155=0;i155<(int)tmp.size();++i155) {
          if(tmp[i155]==FAIL) {
            if(!( !next_prev152.empty() && next_prev152.front() == FAIL )) {
              next_prev152.push_front(FAIL);
            }
          } else {
            next_prev152.push_back(tmp[i155]);
          }
        }
      }
      prev = next_prev152;
    }
    prev = star_final_prev153;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i84=0;i84<(int)prev.size();++i84) {
    if( prev[i84] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i84]);
    }
  }
  return memo[key(15,backtracking_ptr_for_packrat15)] = result;
}

inline deque<int> parse_while88() { 
  if(memo.count(key(16,i))) {
    return memo[key(16,i)];
  }
  int backtracking_ptr_for_packrat16=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev91;
  for(int i90=0;i90<(int)prev.size();++i90) {
    if( prev[i90] == FAIL ) {
      if(!(!next_prev91.empty() && next_prev91.front() == FAIL )) {
        next_prev91.push_front(FAIL);
      }
      continue;
    }
    i = prev[i90];
    tmp = parse_S();
    
    for(int i90=0;i90<(int)tmp.size();++i90) {
      if( tmp[i90] == FAIL ) {
        if(!( !next_prev91.empty() && next_prev91[0] == FAIL )) {
          next_prev91.push_front(FAIL);
        }
      } else {
        next_prev91.push_back(tmp[i90]);
      }
    }
  }
  prev = next_prev91;
  for(int i89=0;i89<(int)prev.size();++i89) {
    if( prev[i89] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i89]);
    }
  }
  return memo[key(16,backtracking_ptr_for_packrat16)] = result;
}

inline deque<int> parse_while96() { 
  if(memo.count(key(17,i))) {
    return memo[key(17,i)];
  }
  int backtracking_ptr_for_packrat17=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (Attribute) */
  deque<int> next_prev99;
  for(int i98=0;i98<(int)prev.size();++i98) {
    if( prev[i98] == FAIL ) {
      if(!(!next_prev99.empty() && next_prev99.front() == FAIL )) {
        next_prev99.push_front(FAIL);
      }
      continue;
    }
    i = prev[i98];
    tmp = parse_Attribute();
    
    for(int i98=0;i98<(int)tmp.size();++i98) {
      if( tmp[i98] == FAIL ) {
        if(!( !next_prev99.empty() && next_prev99[0] == FAIL )) {
          next_prev99.push_front(FAIL);
        }
      } else {
        next_prev99.push_back(tmp[i98]);
      }
    }
  }
  prev = next_prev99;
  for(int i97=0;i97<(int)prev.size();++i97) {
    if( prev[i97] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i97]);
    }
  }
  return memo[key(17,backtracking_ptr_for_packrat17)] = result;
}

inline deque<int> parse_slash107() { 
  if(memo.count(key(18,i))) {
    return memo[key(18,i)];
  }
  int backtracking_ptr_for_packrat18=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i109=0;i109<(int)prev.size();++i109) {
      if( prev[i109] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i109]<m&&I[prev[i109]]=='/') {
        tmp.push_back(prev[i109]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i110=0;i110<(int)prev.size();++i110) {
      if( prev[i110] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i110]<m&&I[prev[i110]]=='>') {
        tmp.push_back(prev[i110]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i108=0;i108<(int)prev.size();++i108) {
    if( prev[i108] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i108]);
    }
  }
  return memo[key(18,backtracking_ptr_for_packrat18)] = result;
}

inline deque<int> parse_slash112() { 
  if(memo.count(key(19,i))) {
    return memo[key(19,i)];
  }
  int backtracking_ptr_for_packrat19=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i114=0;i114<(int)prev.size();++i114) {
      if( prev[i114] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i114]<m&&I[prev[i114]]=='>') {
        tmp.push_back(prev[i114]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev119;
    deque<int> star_final_prev120;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev119.clear();
      for(int i121=0;i121<(int)prev.size();++i121) {
        i = prev[i121];
        tmp = parse_while115();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev120.push_back(prev[i121]);
        }
        for(int i122=0;i122<(int)tmp.size();++i122) {
          if(tmp[i122]==FAIL) {
            if(!( !next_prev119.empty() && next_prev119.front() == FAIL )) {
              next_prev119.push_front(FAIL);
            }
          } else {
            next_prev119.push_back(tmp[i122]);
          }
        }
      }
      prev = next_prev119;
    }
    prev = star_final_prev120;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev138;
    deque<int> star_final_prev139;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev138.clear();
      for(int i140=0;i140<(int)prev.size();++i140) {
        i = prev[i140];
        tmp = parse_while123();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev139.push_back(prev[i140]);
        }
        for(int i141=0;i141<(int)tmp.size();++i141) {
          if(tmp[i141]==FAIL) {
            if(!( !next_prev138.empty() && next_prev138.front() == FAIL )) {
              next_prev138.push_front(FAIL);
            }
          } else {
            next_prev138.push_back(tmp[i141]);
          }
        }
      }
      prev = next_prev138;
    }
    prev = star_final_prev139;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i142=0;i142<(int)prev.size();++i142) {
      if( prev[i142] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i142]<m&&I[prev[i142]]=='<') {
        tmp.push_back(prev[i142]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i143=0;i143<(int)prev.size();++i143) {
      if( prev[i143] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i143]<m&&I[prev[i143]]=='/') {
        tmp.push_back(prev[i143]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (NAME) */
    deque<int> next_prev145;
    for(int i144=0;i144<(int)prev.size();++i144) {
      if( prev[i144] == FAIL ) {
        if(!(!next_prev145.empty() && next_prev145.front() == FAIL )) {
          next_prev145.push_front(FAIL);
        }
        continue;
      }
      i = prev[i144];
      tmp = parse_NAME();
      
      for(int i144=0;i144<(int)tmp.size();++i144) {
        if( tmp[i144] == FAIL ) {
          if(!( !next_prev145.empty() && next_prev145[0] == FAIL )) {
            next_prev145.push_front(FAIL);
          }
        } else {
          next_prev145.push_back(tmp[i144]);
        }
      }
    }
    prev = next_prev145;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i146=0;i146<(int)prev.size();++i146) {
      if( prev[i146] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i146]<m&&I[prev[i146]]=='>') {
        tmp.push_back(prev[i146]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i113=0;i113<(int)prev.size();++i113) {
    if( prev[i113] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i113]);
    }
  }
  return memo[key(19,backtracking_ptr_for_packrat19)] = result;
}

inline deque<int> parse_while115() { 
  if(memo.count(key(20,i))) {
    return memo[key(20,i)];
  }
  int backtracking_ptr_for_packrat20=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev118;
  for(int i117=0;i117<(int)prev.size();++i117) {
    if( prev[i117] == FAIL ) {
      if(!(!next_prev118.empty() && next_prev118.front() == FAIL )) {
        next_prev118.push_front(FAIL);
      }
      continue;
    }
    i = prev[i117];
    tmp = parse_S();
    
    for(int i117=0;i117<(int)tmp.size();++i117) {
      if( tmp[i117] == FAIL ) {
        if(!( !next_prev118.empty() && next_prev118[0] == FAIL )) {
          next_prev118.push_front(FAIL);
        }
      } else {
        next_prev118.push_back(tmp[i117]);
      }
    }
  }
  prev = next_prev118;
  for(int i116=0;i116<(int)prev.size();++i116) {
    if( prev[i116] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i116]);
    }
  }
  return memo[key(20,backtracking_ptr_for_packrat20)] = result;
}

inline deque<int> parse_while123() { 
  if(memo.count(key(21,i))) {
    return memo[key(21,i)];
  }
  int backtracking_ptr_for_packrat21=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Prioritized Choice */
  deque<int> next_prev126;
  deque<int> prioritized_choice_final_prev127;
  next_prev126.clear();
  for(int i125=0;i125<(int)prev.size();++i125) {
    i = prev[i125];
    tmp = parse_slash128();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev126.push_back(prev[i125]); }
    for(int i132=0;i132<(int)tmp.size();++i132) {
      if( tmp[i132] != FAIL ) {
        prioritized_choice_final_prev127.push_back(tmp[i132]);
      }
    }
  }
  prev = next_prev126;
  next_prev126.clear();
  for(int i125=0;i125<(int)prev.size();++i125) {
    i = prev[i125];
    tmp = parse_slash133();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev126.push_back(prev[i125]); }
    for(int i137=0;i137<(int)tmp.size();++i137) {
      if( tmp[i137] != FAIL ) {
        prioritized_choice_final_prev127.push_back(tmp[i137]);
      }
    }
  }
  prev = next_prev126;
  if(!prev.empty()) {
    if(!(!prioritized_choice_final_prev127.empty() && prioritized_choice_final_prev127.front() == FAIL )) {
      prioritized_choice_final_prev127.push_front(FAIL);
    }
  }
  prev = prioritized_choice_final_prev127;
  for(int i124=0;i124<(int)prev.size();++i124) {
    if( prev[i124] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i124]);
    }
  }
  return memo[key(21,backtracking_ptr_for_packrat21)] = result;
}

inline deque<int> parse_slash128() { 
  if(memo.count(key(22,i))) {
    return memo[key(22,i)];
  }
  int backtracking_ptr_for_packrat22=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (Content) */
    deque<int> next_prev131;
    for(int i130=0;i130<(int)prev.size();++i130) {
      if( prev[i130] == FAIL ) {
        if(!(!next_prev131.empty() && next_prev131.front() == FAIL )) {
          next_prev131.push_front(FAIL);
        }
        continue;
      }
      i = prev[i130];
      tmp = parse_Content();
      
      for(int i130=0;i130<(int)tmp.size();++i130) {
        if( tmp[i130] == FAIL ) {
          if(!( !next_prev131.empty() && next_prev131[0] == FAIL )) {
            next_prev131.push_front(FAIL);
          }
        } else {
          next_prev131.push_back(tmp[i130]);
        }
      }
    }
    prev = next_prev131;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i129=0;i129<(int)prev.size();++i129) {
    if( prev[i129] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i129]);
    }
  }
  return memo[key(22,backtracking_ptr_for_packrat22)] = result;
}

inline deque<int> parse_slash133() { 
  if(memo.count(key(23,i))) {
    return memo[key(23,i)];
  }
  int backtracking_ptr_for_packrat23=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (COMMENT) */
    deque<int> next_prev136;
    for(int i135=0;i135<(int)prev.size();++i135) {
      if( prev[i135] == FAIL ) {
        if(!(!next_prev136.empty() && next_prev136.front() == FAIL )) {
          next_prev136.push_front(FAIL);
        }
        continue;
      }
      i = prev[i135];
      tmp = parse_COMMENT();
      
      for(int i135=0;i135<(int)tmp.size();++i135) {
        if( tmp[i135] == FAIL ) {
          if(!( !next_prev136.empty() && next_prev136[0] == FAIL )) {
            next_prev136.push_front(FAIL);
          }
        } else {
          next_prev136.push_back(tmp[i135]);
        }
      }
    }
    prev = next_prev136;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i134=0;i134<(int)prev.size();++i134) {
    if( prev[i134] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i134]);
    }
  }
  return memo[key(23,backtracking_ptr_for_packrat23)] = result;
}

inline deque<int> parse_while148() { 
  if(memo.count(key(24,i))) {
    return memo[key(24,i)];
  }
  int backtracking_ptr_for_packrat24=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev151;
  for(int i150=0;i150<(int)prev.size();++i150) {
    if( prev[i150] == FAIL ) {
      if(!(!next_prev151.empty() && next_prev151.front() == FAIL )) {
        next_prev151.push_front(FAIL);
      }
      continue;
    }
    i = prev[i150];
    tmp = parse_S();
    
    for(int i150=0;i150<(int)tmp.size();++i150) {
      if( tmp[i150] == FAIL ) {
        if(!( !next_prev151.empty() && next_prev151[0] == FAIL )) {
          next_prev151.push_front(FAIL);
        }
      } else {
        next_prev151.push_back(tmp[i150]);
      }
    }
  }
  prev = next_prev151;
  for(int i149=0;i149<(int)prev.size();++i149) {
    if( prev[i149] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i149]);
    }
  }
  return memo[key(24,backtracking_ptr_for_packrat24)] = result;
}

deque<int> parse_Name(){
  if(memo.count(key(25,i))) {
    return memo[key(25,i)];
  }
  int backtracking_ptr_for_packrat25=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (NAME) */
    deque<int> next_prev158;
    for(int i157=0;i157<(int)prev.size();++i157) {
      if( prev[i157] == FAIL ) {
        if(!(!next_prev158.empty() && next_prev158.front() == FAIL )) {
          next_prev158.push_front(FAIL);
        }
        continue;
      }
      i = prev[i157];
      tmp = parse_NAME();
      
      for(int i157=0;i157<(int)tmp.size();++i157) {
        if( tmp[i157] == FAIL ) {
          if(!( !next_prev158.empty() && next_prev158[0] == FAIL )) {
            next_prev158.push_front(FAIL);
          }
        } else {
          next_prev158.push_back(tmp[i157]);
        }
      }
    }
    prev = next_prev158;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i156=0;i156<(int)prev.size();++i156) {
    if( prev[i156] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i156]);
    }
  }
  return memo[key(25,backtracking_ptr_for_packrat25)] = result;
}

deque<int> parse_NAME(){
  if(memo.count(key(26,i))) {
    return memo[key(26,i)];
  }
  int backtracking_ptr_for_packrat26=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i160=0;i160<(int)prev.size();++i160) {
      if( prev[i160] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i160]<m&&(I[prev[i160]]=='A'||I[prev[i160]]=='B'||I[prev[i160]]=='C'||I[prev[i160]]=='D'||I[prev[i160]]=='E'||I[prev[i160]]=='F'||I[prev[i160]]=='G'||I[prev[i160]]=='H'||I[prev[i160]]=='I'||I[prev[i160]]=='J'||I[prev[i160]]=='K'||I[prev[i160]]=='L'||I[prev[i160]]=='M'||I[prev[i160]]=='N'||I[prev[i160]]=='O'||I[prev[i160]]=='P'||I[prev[i160]]=='Q'||I[prev[i160]]=='R'||I[prev[i160]]=='S'||I[prev[i160]]=='T'||I[prev[i160]]=='U'||I[prev[i160]]=='V'||I[prev[i160]]=='W'||I[prev[i160]]=='X'||I[prev[i160]]=='Y'||I[prev[i160]]=='Z'||I[prev[i160]]=='_'||I[prev[i160]]=='a'||I[prev[i160]]=='b'||I[prev[i160]]=='c'||I[prev[i160]]=='d'||I[prev[i160]]=='e'||I[prev[i160]]=='f'||I[prev[i160]]=='g'||I[prev[i160]]=='h'||I[prev[i160]]=='i'||I[prev[i160]]=='j'||I[prev[i160]]=='k'||I[prev[i160]]=='l'||I[prev[i160]]=='m'||I[prev[i160]]=='n'||I[prev[i160]]=='o'||I[prev[i160]]=='p'||I[prev[i160]]=='q'||I[prev[i160]]=='r'||I[prev[i160]]=='s'||I[prev[i160]]=='t'||I[prev[i160]]=='u'||I[prev[i160]]=='v'||I[prev[i160]]=='w'||I[prev[i160]]=='x'||I[prev[i160]]=='y'||I[prev[i160]]=='z'||I[prev[i160]]==':')) {
        tmp.push_back(prev[i160]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev174;
    deque<int> star_final_prev175;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev174.clear();
      for(int i176=0;i176<(int)prev.size();++i176) {
        i = prev[i176];
        tmp = parse_while161();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev175.push_back(prev[i176]);
        }
        for(int i177=0;i177<(int)tmp.size();++i177) {
          if(tmp[i177]==FAIL) {
            if(!( !next_prev174.empty() && next_prev174.front() == FAIL )) {
              next_prev174.push_front(FAIL);
            }
          } else {
            next_prev174.push_back(tmp[i177]);
          }
        }
      }
      prev = next_prev174;
    }
    prev = star_final_prev175;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i159=0;i159<(int)prev.size();++i159) {
    if( prev[i159] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i159]);
    }
  }
  return memo[key(26,backtracking_ptr_for_packrat26)] = result;
}

inline deque<int> parse_while161() { 
  if(memo.count(key(27,i))) {
    return memo[key(27,i)];
  }
  int backtracking_ptr_for_packrat27=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Prioritized Choice */
  deque<int> next_prev164;
  deque<int> prioritized_choice_final_prev165;
  next_prev164.clear();
  for(int i163=0;i163<(int)prev.size();++i163) {
    i = prev[i163];
    tmp = parse_slash166();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev164.push_back(prev[i163]); }
    for(int i169=0;i169<(int)tmp.size();++i169) {
      if( tmp[i169] != FAIL ) {
        prioritized_choice_final_prev165.push_back(tmp[i169]);
      }
    }
  }
  prev = next_prev164;
  next_prev164.clear();
  for(int i163=0;i163<(int)prev.size();++i163) {
    i = prev[i163];
    tmp = parse_slash170();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev164.push_back(prev[i163]); }
    for(int i173=0;i173<(int)tmp.size();++i173) {
      if( tmp[i173] != FAIL ) {
        prioritized_choice_final_prev165.push_back(tmp[i173]);
      }
    }
  }
  prev = next_prev164;
  if(!prev.empty()) {
    if(!(!prioritized_choice_final_prev165.empty() && prioritized_choice_final_prev165.front() == FAIL )) {
      prioritized_choice_final_prev165.push_front(FAIL);
    }
  }
  prev = prioritized_choice_final_prev165;
  for(int i162=0;i162<(int)prev.size();++i162) {
    if( prev[i162] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i162]);
    }
  }
  return memo[key(27,backtracking_ptr_for_packrat27)] = result;
}

inline deque<int> parse_slash166() { 
  if(memo.count(key(28,i))) {
    return memo[key(28,i)];
  }
  int backtracking_ptr_for_packrat28=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i168=0;i168<(int)prev.size();++i168) {
      if( prev[i168] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i168]<m&&I[prev[i168]]=='-') {
        tmp.push_back(prev[i168]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i167=0;i167<(int)prev.size();++i167) {
    if( prev[i167] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i167]);
    }
  }
  return memo[key(28,backtracking_ptr_for_packrat28)] = result;
}

inline deque<int> parse_slash170() { 
  if(memo.count(key(29,i))) {
    return memo[key(29,i)];
  }
  int backtracking_ptr_for_packrat29=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i172=0;i172<(int)prev.size();++i172) {
      if( prev[i172] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i172]<m&&(I[prev[i172]]=='.'||I[prev[i172]]=='0'||I[prev[i172]]=='1'||I[prev[i172]]=='2'||I[prev[i172]]=='3'||I[prev[i172]]=='4'||I[prev[i172]]=='5'||I[prev[i172]]=='6'||I[prev[i172]]=='7'||I[prev[i172]]=='8'||I[prev[i172]]=='9'||I[prev[i172]]==':'||I[prev[i172]]=='A'||I[prev[i172]]=='B'||I[prev[i172]]=='C'||I[prev[i172]]=='D'||I[prev[i172]]=='E'||I[prev[i172]]=='F'||I[prev[i172]]=='G'||I[prev[i172]]=='H'||I[prev[i172]]=='I'||I[prev[i172]]=='J'||I[prev[i172]]=='K'||I[prev[i172]]=='L'||I[prev[i172]]=='M'||I[prev[i172]]=='N'||I[prev[i172]]=='O'||I[prev[i172]]=='P'||I[prev[i172]]=='Q'||I[prev[i172]]=='R'||I[prev[i172]]=='S'||I[prev[i172]]=='T'||I[prev[i172]]=='U'||I[prev[i172]]=='V'||I[prev[i172]]=='W'||I[prev[i172]]=='X'||I[prev[i172]]=='Y'||I[prev[i172]]=='Z'||I[prev[i172]]=='_'||I[prev[i172]]=='a'||I[prev[i172]]=='b'||I[prev[i172]]=='c'||I[prev[i172]]=='d'||I[prev[i172]]=='e'||I[prev[i172]]=='f'||I[prev[i172]]=='g'||I[prev[i172]]=='h'||I[prev[i172]]=='i'||I[prev[i172]]=='j'||I[prev[i172]]=='k'||I[prev[i172]]=='l'||I[prev[i172]]=='m'||I[prev[i172]]=='n'||I[prev[i172]]=='o'||I[prev[i172]]=='p'||I[prev[i172]]=='q'||I[prev[i172]]=='r'||I[prev[i172]]=='s'||I[prev[i172]]=='t'||I[prev[i172]]=='u'||I[prev[i172]]=='v'||I[prev[i172]]=='w'||I[prev[i172]]=='x'||I[prev[i172]]=='y'||I[prev[i172]]=='z')) {
        tmp.push_back(prev[i172]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i171=0;i171<(int)prev.size();++i171) {
    if( prev[i171] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i171]);
    }
  }
  return memo[key(29,backtracking_ptr_for_packrat29)] = result;
}

deque<int> parse_Attribute(){
  if(memo.count(key(30,i))) {
    return memo[key(30,i)];
  }
  int backtracking_ptr_for_packrat30=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (Name) */
    deque<int> next_prev180;
    for(int i179=0;i179<(int)prev.size();++i179) {
      if( prev[i179] == FAIL ) {
        if(!(!next_prev180.empty() && next_prev180.front() == FAIL )) {
          next_prev180.push_front(FAIL);
        }
        continue;
      }
      i = prev[i179];
      tmp = parse_Name();
      
      for(int i179=0;i179<(int)tmp.size();++i179) {
        if( tmp[i179] == FAIL ) {
          if(!( !next_prev180.empty() && next_prev180[0] == FAIL )) {
            next_prev180.push_front(FAIL);
          }
        } else {
          next_prev180.push_back(tmp[i179]);
        }
      }
    }
    prev = next_prev180;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev185;
    deque<int> star_final_prev186;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev185.clear();
      for(int i187=0;i187<(int)prev.size();++i187) {
        i = prev[i187];
        tmp = parse_while181();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev186.push_back(prev[i187]);
        }
        for(int i188=0;i188<(int)tmp.size();++i188) {
          if(tmp[i188]==FAIL) {
            if(!( !next_prev185.empty() && next_prev185.front() == FAIL )) {
              next_prev185.push_front(FAIL);
            }
          } else {
            next_prev185.push_back(tmp[i188]);
          }
        }
      }
      prev = next_prev185;
    }
    prev = star_final_prev186;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i189=0;i189<(int)prev.size();++i189) {
      if( prev[i189] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i189]<m&&I[prev[i189]]=='=') {
        tmp.push_back(prev[i189]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev194;
    deque<int> star_final_prev195;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev194.clear();
      for(int i196=0;i196<(int)prev.size();++i196) {
        i = prev[i196];
        tmp = parse_while190();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev195.push_back(prev[i196]);
        }
        for(int i197=0;i197<(int)tmp.size();++i197) {
          if(tmp[i197]==FAIL) {
            if(!( !next_prev194.empty() && next_prev194.front() == FAIL )) {
              next_prev194.push_front(FAIL);
            }
          } else {
            next_prev194.push_back(tmp[i197]);
          }
        }
      }
      prev = next_prev194;
    }
    prev = star_final_prev195;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (String) */
    deque<int> next_prev199;
    for(int i198=0;i198<(int)prev.size();++i198) {
      if( prev[i198] == FAIL ) {
        if(!(!next_prev199.empty() && next_prev199.front() == FAIL )) {
          next_prev199.push_front(FAIL);
        }
        continue;
      }
      i = prev[i198];
      tmp = parse_String();
      
      for(int i198=0;i198<(int)tmp.size();++i198) {
        if( tmp[i198] == FAIL ) {
          if(!( !next_prev199.empty() && next_prev199[0] == FAIL )) {
            next_prev199.push_front(FAIL);
          }
        } else {
          next_prev199.push_back(tmp[i198]);
        }
      }
    }
    prev = next_prev199;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev204;
    deque<int> star_final_prev205;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev204.clear();
      for(int i206=0;i206<(int)prev.size();++i206) {
        i = prev[i206];
        tmp = parse_while200();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev205.push_back(prev[i206]);
        }
        for(int i207=0;i207<(int)tmp.size();++i207) {
          if(tmp[i207]==FAIL) {
            if(!( !next_prev204.empty() && next_prev204.front() == FAIL )) {
              next_prev204.push_front(FAIL);
            }
          } else {
            next_prev204.push_back(tmp[i207]);
          }
        }
      }
      prev = next_prev204;
    }
    prev = star_final_prev205;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i178=0;i178<(int)prev.size();++i178) {
    if( prev[i178] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i178]);
    }
  }
  return memo[key(30,backtracking_ptr_for_packrat30)] = result;
}

inline deque<int> parse_while181() { 
  if(memo.count(key(31,i))) {
    return memo[key(31,i)];
  }
  int backtracking_ptr_for_packrat31=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev184;
  for(int i183=0;i183<(int)prev.size();++i183) {
    if( prev[i183] == FAIL ) {
      if(!(!next_prev184.empty() && next_prev184.front() == FAIL )) {
        next_prev184.push_front(FAIL);
      }
      continue;
    }
    i = prev[i183];
    tmp = parse_S();
    
    for(int i183=0;i183<(int)tmp.size();++i183) {
      if( tmp[i183] == FAIL ) {
        if(!( !next_prev184.empty() && next_prev184[0] == FAIL )) {
          next_prev184.push_front(FAIL);
        }
      } else {
        next_prev184.push_back(tmp[i183]);
      }
    }
  }
  prev = next_prev184;
  for(int i182=0;i182<(int)prev.size();++i182) {
    if( prev[i182] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i182]);
    }
  }
  return memo[key(31,backtracking_ptr_for_packrat31)] = result;
}

inline deque<int> parse_while190() { 
  if(memo.count(key(32,i))) {
    return memo[key(32,i)];
  }
  int backtracking_ptr_for_packrat32=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev193;
  for(int i192=0;i192<(int)prev.size();++i192) {
    if( prev[i192] == FAIL ) {
      if(!(!next_prev193.empty() && next_prev193.front() == FAIL )) {
        next_prev193.push_front(FAIL);
      }
      continue;
    }
    i = prev[i192];
    tmp = parse_S();
    
    for(int i192=0;i192<(int)tmp.size();++i192) {
      if( tmp[i192] == FAIL ) {
        if(!( !next_prev193.empty() && next_prev193[0] == FAIL )) {
          next_prev193.push_front(FAIL);
        }
      } else {
        next_prev193.push_back(tmp[i192]);
      }
    }
  }
  prev = next_prev193;
  for(int i191=0;i191<(int)prev.size();++i191) {
    if( prev[i191] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i191]);
    }
  }
  return memo[key(32,backtracking_ptr_for_packrat32)] = result;
}

inline deque<int> parse_while200() { 
  if(memo.count(key(33,i))) {
    return memo[key(33,i)];
  }
  int backtracking_ptr_for_packrat33=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev203;
  for(int i202=0;i202<(int)prev.size();++i202) {
    if( prev[i202] == FAIL ) {
      if(!(!next_prev203.empty() && next_prev203.front() == FAIL )) {
        next_prev203.push_front(FAIL);
      }
      continue;
    }
    i = prev[i202];
    tmp = parse_S();
    
    for(int i202=0;i202<(int)tmp.size();++i202) {
      if( tmp[i202] == FAIL ) {
        if(!( !next_prev203.empty() && next_prev203[0] == FAIL )) {
          next_prev203.push_front(FAIL);
        }
      } else {
        next_prev203.push_back(tmp[i202]);
      }
    }
  }
  prev = next_prev203;
  for(int i201=0;i201<(int)prev.size();++i201) {
    if( prev[i201] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i201]);
    }
  }
  return memo[key(33,backtracking_ptr_for_packrat33)] = result;
}

deque<int> parse_String(){
  if(memo.count(key(34,i))) {
    return memo[key(34,i)];
  }
  int backtracking_ptr_for_packrat34=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i209=0;i209<(int)prev.size();++i209) {
      if( prev[i209] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i209]<m&&I[prev[i209]]=='"') {
        tmp.push_back(prev[i209]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev218;
    deque<int> star_final_prev219;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev218.clear();
      for(int i220=0;i220<(int)prev.size();++i220) {
        i = prev[i220];
        tmp = parse_while210();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev219.push_back(prev[i220]);
        }
        for(int i221=0;i221<(int)tmp.size();++i221) {
          if(tmp[i221]==FAIL) {
            if(!( !next_prev218.empty() && next_prev218.front() == FAIL )) {
              next_prev218.push_front(FAIL);
            }
          } else {
            next_prev218.push_back(tmp[i221]);
          }
        }
      }
      prev = next_prev218;
    }
    prev = star_final_prev219;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i222=0;i222<(int)prev.size();++i222) {
      if( prev[i222] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i222]<m&&I[prev[i222]]=='"') {
        tmp.push_back(prev[i222]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i208=0;i208<(int)prev.size();++i208) {
    if( prev[i208] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i208]);
    }
  }
  return memo[key(34,backtracking_ptr_for_packrat34)] = result;
}

inline deque<int> parse_while210() { 
  if(memo.count(key(35,i))) {
    return memo[key(35,i)];
  }
  int backtracking_ptr_for_packrat35=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev216;
    for(int i215=0;i215<(int)prev.size();++i215) {
      i = prev[i215];
      tmp = parse_not212();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev216.push_back(prev[i215]);
      } else {
        if(!(!next_prev216.empty()&&next_prev216.front()==FAIL)) {
          next_prev216.push_front(FAIL);
        }
      }
    }
    prev = next_prev216;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i217=0;i217<(int)prev.size();++i217) {
      if( prev[i217] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i217]<m) {//any character
        tmp.push_back(prev[i217]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i211=0;i211<(int)prev.size();++i211) {
    if( prev[i211] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i211]);
    }
  }
  return memo[key(35,backtracking_ptr_for_packrat35)] = result;
}

inline deque<int> parse_not212() { 
  if(memo.count(key(36,i))) {
    return memo[key(36,i)];
  }
  int backtracking_ptr_for_packrat36=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i214=0;i214<(int)prev.size();++i214) {
    if( prev[i214] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i214]<m&&I[prev[i214]]=='"') {
      tmp.push_back(prev[i214]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i213=0;i213<(int)prev.size();++i213) {
    if( prev[i213] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i213]);
    }
  }
  return memo[key(36,backtracking_ptr_for_packrat36)] = result;
}

deque<int> parse_Content(){
  if(memo.count(key(37,i))) {
    return memo[key(37,i)];
  }
  int backtracking_ptr_for_packrat37=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Prioritized Choice */
  deque<int> next_prev225;
  deque<int> prioritized_choice_final_prev226;
  next_prev225.clear();
  for(int i224=0;i224<(int)prev.size();++i224) {
    i = prev[i224];
    tmp = parse_slash227();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev225.push_back(prev[i224]); }
    for(int i231=0;i231<(int)tmp.size();++i231) {
      if( tmp[i231] != FAIL ) {
        prioritized_choice_final_prev226.push_back(tmp[i231]);
      }
    }
  }
  prev = next_prev225;
  next_prev225.clear();
  for(int i224=0;i224<(int)prev.size();++i224) {
    i = prev[i224];
    tmp = parse_slash232();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev225.push_back(prev[i224]); }
    for(int i236=0;i236<(int)tmp.size();++i236) {
      if( tmp[i236] != FAIL ) {
        prioritized_choice_final_prev226.push_back(tmp[i236]);
      }
    }
  }
  prev = next_prev225;
  next_prev225.clear();
  for(int i224=0;i224<(int)prev.size();++i224) {
    i = prev[i224];
    tmp = parse_slash237();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev225.push_back(prev[i224]); }
    for(int i241=0;i241<(int)tmp.size();++i241) {
      if( tmp[i241] != FAIL ) {
        prioritized_choice_final_prev226.push_back(tmp[i241]);
      }
    }
  }
  prev = next_prev225;
  if(!prev.empty()) {
    if(!(!prioritized_choice_final_prev226.empty() && prioritized_choice_final_prev226.front() == FAIL )) {
      prioritized_choice_final_prev226.push_front(FAIL);
    }
  }
  prev = prioritized_choice_final_prev226;
  for(int i223=0;i223<(int)prev.size();++i223) {
    if( prev[i223] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i223]);
    }
  }
  return memo[key(37,backtracking_ptr_for_packrat37)] = result;
}

inline deque<int> parse_slash227() { 
  if(memo.count(key(38,i))) {
    return memo[key(38,i)];
  }
  int backtracking_ptr_for_packrat38=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (Xml) */
    deque<int> next_prev230;
    for(int i229=0;i229<(int)prev.size();++i229) {
      if( prev[i229] == FAIL ) {
        if(!(!next_prev230.empty() && next_prev230.front() == FAIL )) {
          next_prev230.push_front(FAIL);
        }
        continue;
      }
      i = prev[i229];
      tmp = parse_Xml();
      
      for(int i229=0;i229<(int)tmp.size();++i229) {
        if( tmp[i229] == FAIL ) {
          if(!( !next_prev230.empty() && next_prev230[0] == FAIL )) {
            next_prev230.push_front(FAIL);
          }
        } else {
          next_prev230.push_back(tmp[i229]);
        }
      }
    }
    prev = next_prev230;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i228=0;i228<(int)prev.size();++i228) {
    if( prev[i228] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i228]);
    }
  }
  return memo[key(38,backtracking_ptr_for_packrat38)] = result;
}

inline deque<int> parse_slash232() { 
  if(memo.count(key(39,i))) {
    return memo[key(39,i)];
  }
  int backtracking_ptr_for_packrat39=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (CDataSec) */
    deque<int> next_prev235;
    for(int i234=0;i234<(int)prev.size();++i234) {
      if( prev[i234] == FAIL ) {
        if(!(!next_prev235.empty() && next_prev235.front() == FAIL )) {
          next_prev235.push_front(FAIL);
        }
        continue;
      }
      i = prev[i234];
      tmp = parse_CDataSec();
      
      for(int i234=0;i234<(int)tmp.size();++i234) {
        if( tmp[i234] == FAIL ) {
          if(!( !next_prev235.empty() && next_prev235[0] == FAIL )) {
            next_prev235.push_front(FAIL);
          }
        } else {
          next_prev235.push_back(tmp[i234]);
        }
      }
    }
    prev = next_prev235;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i233=0;i233<(int)prev.size();++i233) {
    if( prev[i233] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i233]);
    }
  }
  return memo[key(39,backtracking_ptr_for_packrat39)] = result;
}

inline deque<int> parse_slash237() { 
  if(memo.count(key(40,i))) {
    return memo[key(40,i)];
  }
  int backtracking_ptr_for_packrat40=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (Text) */
    deque<int> next_prev240;
    for(int i239=0;i239<(int)prev.size();++i239) {
      if( prev[i239] == FAIL ) {
        if(!(!next_prev240.empty() && next_prev240.front() == FAIL )) {
          next_prev240.push_front(FAIL);
        }
        continue;
      }
      i = prev[i239];
      tmp = parse_Text();
      
      for(int i239=0;i239<(int)tmp.size();++i239) {
        if( tmp[i239] == FAIL ) {
          if(!( !next_prev240.empty() && next_prev240[0] == FAIL )) {
            next_prev240.push_front(FAIL);
          }
        } else {
          next_prev240.push_back(tmp[i239]);
        }
      }
    }
    prev = next_prev240;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i238=0;i238<(int)prev.size();++i238) {
    if( prev[i238] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i238]);
    }
  }
  return memo[key(40,backtracking_ptr_for_packrat40)] = result;
}

deque<int> parse_CDataSec(){
  if(memo.count(key(41,i))) {
    return memo[key(41,i)];
  }
  int backtracking_ptr_for_packrat41=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i243=0;i243<(int)prev.size();++i243) {
      if( prev[i243] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i243]<m&&I[prev[i243]]=='<') {
        tmp.push_back(prev[i243]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i244=0;i244<(int)prev.size();++i244) {
      if( prev[i244] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i244]<m&&I[prev[i244]]=='!') {
        tmp.push_back(prev[i244]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i245=0;i245<(int)prev.size();++i245) {
      if( prev[i245] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i245]<m&&I[prev[i245]]=='[') {
        tmp.push_back(prev[i245]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i246=0;i246<(int)prev.size();++i246) {
      if( prev[i246] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i246]<m&&I[prev[i246]]=='C') {
        tmp.push_back(prev[i246]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i247=0;i247<(int)prev.size();++i247) {
      if( prev[i247] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i247]<m&&I[prev[i247]]=='D') {
        tmp.push_back(prev[i247]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i248=0;i248<(int)prev.size();++i248) {
      if( prev[i248] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i248]<m&&I[prev[i248]]=='A') {
        tmp.push_back(prev[i248]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i249=0;i249<(int)prev.size();++i249) {
      if( prev[i249] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i249]<m&&I[prev[i249]]=='T') {
        tmp.push_back(prev[i249]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i250=0;i250<(int)prev.size();++i250) {
      if( prev[i250] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i250]<m&&I[prev[i250]]=='A') {
        tmp.push_back(prev[i250]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i251=0;i251<(int)prev.size();++i251) {
      if( prev[i251] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i251]<m&&I[prev[i251]]=='[') {
        tmp.push_back(prev[i251]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (CDATA) */
    deque<int> next_prev253;
    for(int i252=0;i252<(int)prev.size();++i252) {
      if( prev[i252] == FAIL ) {
        if(!(!next_prev253.empty() && next_prev253.front() == FAIL )) {
          next_prev253.push_front(FAIL);
        }
        continue;
      }
      i = prev[i252];
      tmp = parse_CDATA();
      
      for(int i252=0;i252<(int)tmp.size();++i252) {
        if( tmp[i252] == FAIL ) {
          if(!( !next_prev253.empty() && next_prev253[0] == FAIL )) {
            next_prev253.push_front(FAIL);
          }
        } else {
          next_prev253.push_back(tmp[i252]);
        }
      }
    }
    prev = next_prev253;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i254=0;i254<(int)prev.size();++i254) {
      if( prev[i254] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i254]<m&&I[prev[i254]]==']') {
        tmp.push_back(prev[i254]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i255=0;i255<(int)prev.size();++i255) {
      if( prev[i255] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i255]<m&&I[prev[i255]]==']') {
        tmp.push_back(prev[i255]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i256=0;i256<(int)prev.size();++i256) {
      if( prev[i256] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i256]<m&&I[prev[i256]]=='>') {
        tmp.push_back(prev[i256]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev261;
    deque<int> star_final_prev262;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev261.clear();
      for(int i263=0;i263<(int)prev.size();++i263) {
        i = prev[i263];
        tmp = parse_while257();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev262.push_back(prev[i263]);
        }
        for(int i264=0;i264<(int)tmp.size();++i264) {
          if(tmp[i264]==FAIL) {
            if(!( !next_prev261.empty() && next_prev261.front() == FAIL )) {
              next_prev261.push_front(FAIL);
            }
          } else {
            next_prev261.push_back(tmp[i264]);
          }
        }
      }
      prev = next_prev261;
    }
    prev = star_final_prev262;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i242=0;i242<(int)prev.size();++i242) {
    if( prev[i242] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i242]);
    }
  }
  return memo[key(41,backtracking_ptr_for_packrat41)] = result;
}

inline deque<int> parse_while257() { 
  if(memo.count(key(42,i))) {
    return memo[key(42,i)];
  }
  int backtracking_ptr_for_packrat42=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev260;
  for(int i259=0;i259<(int)prev.size();++i259) {
    if( prev[i259] == FAIL ) {
      if(!(!next_prev260.empty() && next_prev260.front() == FAIL )) {
        next_prev260.push_front(FAIL);
      }
      continue;
    }
    i = prev[i259];
    tmp = parse_S();
    
    for(int i259=0;i259<(int)tmp.size();++i259) {
      if( tmp[i259] == FAIL ) {
        if(!( !next_prev260.empty() && next_prev260[0] == FAIL )) {
          next_prev260.push_front(FAIL);
        }
      } else {
        next_prev260.push_back(tmp[i259]);
      }
    }
  }
  prev = next_prev260;
  for(int i258=0;i258<(int)prev.size();++i258) {
    if( prev[i258] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i258]);
    }
  }
  return memo[key(42,backtracking_ptr_for_packrat42)] = result;
}

deque<int> parse_CDATA(){
  if(memo.count(key(43,i))) {
    return memo[key(43,i)];
  }
  int backtracking_ptr_for_packrat43=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev289;
    deque<int> star_final_prev290;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev289.clear();
      for(int i291=0;i291<(int)prev.size();++i291) {
        i = prev[i291];
        tmp = parse_while266();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev290.push_back(prev[i291]);
        }
        for(int i292=0;i292<(int)tmp.size();++i292) {
          if(tmp[i292]==FAIL) {
            if(!( !next_prev289.empty() && next_prev289.front() == FAIL )) {
              next_prev289.push_front(FAIL);
            }
          } else {
            next_prev289.push_back(tmp[i292]);
          }
        }
      }
      prev = next_prev289;
    }
    prev = star_final_prev290;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Prioritized Choice */
    deque<int> next_prev294;
    deque<int> prioritized_choice_final_prev295;
    next_prev294.clear();
    for(int i293=0;i293<(int)prev.size();++i293) {
      i = prev[i293];
      tmp = parse_slash296();
      if(!tmp.empty()&&tmp[0]==FAIL) { next_prev294.push_back(prev[i293]); }
      for(int i314=0;i314<(int)tmp.size();++i314) {
        if( tmp[i314] != FAIL ) {
          prioritized_choice_final_prev295.push_back(tmp[i314]);
        }
      }
    }
    prev = next_prev294;
    next_prev294.clear();
    for(int i293=0;i293<(int)prev.size();++i293) {
      i = prev[i293];
      tmp = parse_slash315();
      if(!tmp.empty()&&tmp[0]==FAIL) { next_prev294.push_back(prev[i293]); }
      for(int i317=0;i317<(int)tmp.size();++i317) {
        if( tmp[i317] != FAIL ) {
          prioritized_choice_final_prev295.push_back(tmp[i317]);
        }
      }
    }
    prev = next_prev294;
    if(!prev.empty()) {
      if(!(!prioritized_choice_final_prev295.empty() && prioritized_choice_final_prev295.front() == FAIL )) {
        prioritized_choice_final_prev295.push_front(FAIL);
      }
    }
    prev = prioritized_choice_final_prev295;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i265=0;i265<(int)prev.size();++i265) {
    if( prev[i265] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i265]);
    }
  }
  return memo[key(43,backtracking_ptr_for_packrat43)] = result;
}

inline deque<int> parse_while266() { 
  if(memo.count(key(44,i))) {
    return memo[key(44,i)];
  }
  int backtracking_ptr_for_packrat44=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev274;
    for(int i273=0;i273<(int)prev.size();++i273) {
      i = prev[i273];
      tmp = parse_not268();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev274.push_back(prev[i273]);
      } else {
        if(!(!next_prev274.empty()&&next_prev274.front()==FAIL)) {
          next_prev274.push_front(FAIL);
        }
      }
    }
    prev = next_prev274;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev287;
    for(int i286=0;i286<(int)prev.size();++i286) {
      i = prev[i286];
      tmp = parse_not275();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev287.push_back(prev[i286]);
      } else {
        if(!(!next_prev287.empty()&&next_prev287.front()==FAIL)) {
          next_prev287.push_front(FAIL);
        }
      }
    }
    prev = next_prev287;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i288=0;i288<(int)prev.size();++i288) {
      if( prev[i288] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i288]<m) {//any character
        tmp.push_back(prev[i288]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i267=0;i267<(int)prev.size();++i267) {
    if( prev[i267] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i267]);
    }
  }
  return memo[key(44,backtracking_ptr_for_packrat44)] = result;
}

inline deque<int> parse_not268() { 
  if(memo.count(key(45,i))) {
    return memo[key(45,i)];
  }
  int backtracking_ptr_for_packrat45=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i270=0;i270<(int)prev.size();++i270) {
    if( prev[i270] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i270]<m&&I[prev[i270]]==']') {
      tmp.push_back(prev[i270]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i271=0;i271<(int)prev.size();++i271) {
    if( prev[i271] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i271]<m&&I[prev[i271]]==']') {
      tmp.push_back(prev[i271]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i272=0;i272<(int)prev.size();++i272) {
    if( prev[i272] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i272]<m&&I[prev[i272]]=='>') {
      tmp.push_back(prev[i272]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i269=0;i269<(int)prev.size();++i269) {
    if( prev[i269] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i269]);
    }
  }
  return memo[key(45,backtracking_ptr_for_packrat45)] = result;
}

inline deque<int> parse_not275() { 
  if(memo.count(key(46,i))) {
    return memo[key(46,i)];
  }
  int backtracking_ptr_for_packrat46=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i277=0;i277<(int)prev.size();++i277) {
    if( prev[i277] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i277]<m&&I[prev[i277]]=='<') {
      tmp.push_back(prev[i277]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i278=0;i278<(int)prev.size();++i278) {
    if( prev[i278] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i278]<m&&I[prev[i278]]=='!') {
      tmp.push_back(prev[i278]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i279=0;i279<(int)prev.size();++i279) {
    if( prev[i279] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i279]<m&&I[prev[i279]]=='[') {
      tmp.push_back(prev[i279]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i280=0;i280<(int)prev.size();++i280) {
    if( prev[i280] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i280]<m&&I[prev[i280]]=='C') {
      tmp.push_back(prev[i280]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i281=0;i281<(int)prev.size();++i281) {
    if( prev[i281] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i281]<m&&I[prev[i281]]=='D') {
      tmp.push_back(prev[i281]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i282=0;i282<(int)prev.size();++i282) {
    if( prev[i282] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i282]<m&&I[prev[i282]]=='A') {
      tmp.push_back(prev[i282]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i283=0;i283<(int)prev.size();++i283) {
    if( prev[i283] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i283]<m&&I[prev[i283]]=='T') {
      tmp.push_back(prev[i283]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i284=0;i284<(int)prev.size();++i284) {
    if( prev[i284] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i284]<m&&I[prev[i284]]=='A') {
      tmp.push_back(prev[i284]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i285=0;i285<(int)prev.size();++i285) {
    if( prev[i285] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i285]<m&&I[prev[i285]]=='[') {
      tmp.push_back(prev[i285]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i276=0;i276<(int)prev.size();++i276) {
    if( prev[i276] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i276]);
    }
  }
  return memo[key(46,backtracking_ptr_for_packrat46)] = result;
}

inline deque<int> parse_slash296() { 
  if(memo.count(key(47,i))) {
    return memo[key(47,i)];
  }
  int backtracking_ptr_for_packrat47=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i298=0;i298<(int)prev.size();++i298) {
      if( prev[i298] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i298]<m&&I[prev[i298]]=='<') {
        tmp.push_back(prev[i298]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i299=0;i299<(int)prev.size();++i299) {
      if( prev[i299] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i299]<m&&I[prev[i299]]=='!') {
        tmp.push_back(prev[i299]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i300=0;i300<(int)prev.size();++i300) {
      if( prev[i300] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i300]<m&&I[prev[i300]]=='[') {
        tmp.push_back(prev[i300]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i301=0;i301<(int)prev.size();++i301) {
      if( prev[i301] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i301]<m&&I[prev[i301]]=='C') {
        tmp.push_back(prev[i301]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i302=0;i302<(int)prev.size();++i302) {
      if( prev[i302] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i302]<m&&I[prev[i302]]=='D') {
        tmp.push_back(prev[i302]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i303=0;i303<(int)prev.size();++i303) {
      if( prev[i303] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i303]<m&&I[prev[i303]]=='A') {
        tmp.push_back(prev[i303]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i304=0;i304<(int)prev.size();++i304) {
      if( prev[i304] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i304]<m&&I[prev[i304]]=='T') {
        tmp.push_back(prev[i304]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i305=0;i305<(int)prev.size();++i305) {
      if( prev[i305] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i305]<m&&I[prev[i305]]=='A') {
        tmp.push_back(prev[i305]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i306=0;i306<(int)prev.size();++i306) {
      if( prev[i306] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i306]<m&&I[prev[i306]]=='[') {
        tmp.push_back(prev[i306]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (CDATA) */
    deque<int> next_prev308;
    for(int i307=0;i307<(int)prev.size();++i307) {
      if( prev[i307] == FAIL ) {
        if(!(!next_prev308.empty() && next_prev308.front() == FAIL )) {
          next_prev308.push_front(FAIL);
        }
        continue;
      }
      i = prev[i307];
      tmp = parse_CDATA();
      
      for(int i307=0;i307<(int)tmp.size();++i307) {
        if( tmp[i307] == FAIL ) {
          if(!( !next_prev308.empty() && next_prev308[0] == FAIL )) {
            next_prev308.push_front(FAIL);
          }
        } else {
          next_prev308.push_back(tmp[i307]);
        }
      }
    }
    prev = next_prev308;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i309=0;i309<(int)prev.size();++i309) {
      if( prev[i309] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i309]<m&&I[prev[i309]]==']') {
        tmp.push_back(prev[i309]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i310=0;i310<(int)prev.size();++i310) {
      if( prev[i310] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i310]<m&&I[prev[i310]]==']') {
        tmp.push_back(prev[i310]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i311=0;i311<(int)prev.size();++i311) {
      if( prev[i311] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i311]<m&&I[prev[i311]]=='>') {
        tmp.push_back(prev[i311]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (CDATA) */
    deque<int> next_prev313;
    for(int i312=0;i312<(int)prev.size();++i312) {
      if( prev[i312] == FAIL ) {
        if(!(!next_prev313.empty() && next_prev313.front() == FAIL )) {
          next_prev313.push_front(FAIL);
        }
        continue;
      }
      i = prev[i312];
      tmp = parse_CDATA();
      
      for(int i312=0;i312<(int)tmp.size();++i312) {
        if( tmp[i312] == FAIL ) {
          if(!( !next_prev313.empty() && next_prev313[0] == FAIL )) {
            next_prev313.push_front(FAIL);
          }
        } else {
          next_prev313.push_back(tmp[i312]);
        }
      }
    }
    prev = next_prev313;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i297=0;i297<(int)prev.size();++i297) {
    if( prev[i297] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i297]);
    }
  }
  return memo[key(47,backtracking_ptr_for_packrat47)] = result;
}

inline deque<int> parse_slash315() { 
  if(memo.count(key(48,i))) {
    return memo[key(48,i)];
  }
  int backtracking_ptr_for_packrat48=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  for(int i316=0;i316<(int)prev.size();++i316) {
    if( prev[i316] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i316]);
    }
  }
  return memo[key(48,backtracking_ptr_for_packrat48)] = result;
}

deque<int> parse_COMMENT(){
  if(memo.count(key(49,i))) {
    return memo[key(49,i)];
  }
  int backtracking_ptr_for_packrat49=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i319=0;i319<(int)prev.size();++i319) {
      if( prev[i319] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i319]<m&&I[prev[i319]]=='<') {
        tmp.push_back(prev[i319]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i320=0;i320<(int)prev.size();++i320) {
      if( prev[i320] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i320]<m&&I[prev[i320]]=='!') {
        tmp.push_back(prev[i320]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i321=0;i321<(int)prev.size();++i321) {
      if( prev[i321] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i321]<m&&I[prev[i321]]=='-') {
        tmp.push_back(prev[i321]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i322=0;i322<(int)prev.size();++i322) {
      if( prev[i322] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i322]<m&&I[prev[i322]]=='-') {
        tmp.push_back(prev[i322]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev333;
    deque<int> star_final_prev334;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev333.clear();
      for(int i335=0;i335<(int)prev.size();++i335) {
        i = prev[i335];
        tmp = parse_while323();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev334.push_back(prev[i335]);
        }
        for(int i336=0;i336<(int)tmp.size();++i336) {
          if(tmp[i336]==FAIL) {
            if(!( !next_prev333.empty() && next_prev333.front() == FAIL )) {
              next_prev333.push_front(FAIL);
            }
          } else {
            next_prev333.push_back(tmp[i336]);
          }
        }
      }
      prev = next_prev333;
    }
    prev = star_final_prev334;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i337=0;i337<(int)prev.size();++i337) {
      if( prev[i337] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i337]<m&&I[prev[i337]]=='-') {
        tmp.push_back(prev[i337]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i338=0;i338<(int)prev.size();++i338) {
      if( prev[i338] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i338]<m&&I[prev[i338]]=='-') {
        tmp.push_back(prev[i338]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    tmp.clear();
    for(int i339=0;i339<(int)prev.size();++i339) {
      if( prev[i339] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i339]<m&&I[prev[i339]]=='>') {
        tmp.push_back(prev[i339]+1);
      } else {
        if(!( !tmp.empty() && tmp[0] == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev344;
    deque<int> star_final_prev345;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev344.clear();
      for(int i346=0;i346<(int)prev.size();++i346) {
        i = prev[i346];
        tmp = parse_while340();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev345.push_back(prev[i346]);
        }
        for(int i347=0;i347<(int)tmp.size();++i347) {
          if(tmp[i347]==FAIL) {
            if(!( !next_prev344.empty() && next_prev344.front() == FAIL )) {
              next_prev344.push_front(FAIL);
            }
          } else {
            next_prev344.push_back(tmp[i347]);
          }
        }
      }
      prev = next_prev344;
    }
    prev = star_final_prev345;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i318=0;i318<(int)prev.size();++i318) {
    if( prev[i318] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i318]);
    }
  }
  return memo[key(49,backtracking_ptr_for_packrat49)] = result;
}

inline deque<int> parse_while323() { 
  if(memo.count(key(50,i))) {
    return memo[key(50,i)];
  }
  int backtracking_ptr_for_packrat50=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev331;
    for(int i330=0;i330<(int)prev.size();++i330) {
      i = prev[i330];
      tmp = parse_not325();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev331.push_back(prev[i330]);
      } else {
        if(!(!next_prev331.empty()&&next_prev331.front()==FAIL)) {
          next_prev331.push_front(FAIL);
        }
      }
    }
    prev = next_prev331;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i332=0;i332<(int)prev.size();++i332) {
      if( prev[i332] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i332]<m) {//any character
        tmp.push_back(prev[i332]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i324=0;i324<(int)prev.size();++i324) {
    if( prev[i324] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i324]);
    }
  }
  return memo[key(50,backtracking_ptr_for_packrat50)] = result;
}

inline deque<int> parse_not325() { 
  if(memo.count(key(51,i))) {
    return memo[key(51,i)];
  }
  int backtracking_ptr_for_packrat51=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i327=0;i327<(int)prev.size();++i327) {
    if( prev[i327] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i327]<m&&I[prev[i327]]=='-') {
      tmp.push_back(prev[i327]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i328=0;i328<(int)prev.size();++i328) {
    if( prev[i328] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i328]<m&&I[prev[i328]]=='-') {
      tmp.push_back(prev[i328]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  tmp.clear();
  for(int i329=0;i329<(int)prev.size();++i329) {
    if( prev[i329] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i329]<m&&I[prev[i329]]=='>') {
      tmp.push_back(prev[i329]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i326=0;i326<(int)prev.size();++i326) {
    if( prev[i326] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i326]);
    }
  }
  return memo[key(51,backtracking_ptr_for_packrat51)] = result;
}

inline deque<int> parse_while340() { 
  if(memo.count(key(52,i))) {
    return memo[key(52,i)];
  }
  int backtracking_ptr_for_packrat52=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev343;
  for(int i342=0;i342<(int)prev.size();++i342) {
    if( prev[i342] == FAIL ) {
      if(!(!next_prev343.empty() && next_prev343.front() == FAIL )) {
        next_prev343.push_front(FAIL);
      }
      continue;
    }
    i = prev[i342];
    tmp = parse_S();
    
    for(int i342=0;i342<(int)tmp.size();++i342) {
      if( tmp[i342] == FAIL ) {
        if(!( !next_prev343.empty() && next_prev343[0] == FAIL )) {
          next_prev343.push_front(FAIL);
        }
      } else {
        next_prev343.push_back(tmp[i342]);
      }
    }
  }
  prev = next_prev343;
  for(int i341=0;i341<(int)prev.size();++i341) {
    if( prev[i341] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i341]);
    }
  }
  return memo[key(52,backtracking_ptr_for_packrat52)] = result;
}

deque<int> parse_Text(){
  if(memo.count(key(53,i))) {
    return memo[key(53,i)];
  }
  int backtracking_ptr_for_packrat53=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    if(!((int)prev.size()==1&&prev.front()==FAIL)) {
      if(!((int)prev.size()==1&&prev.front()==FAIL)) {
        /* Not */
        deque<int> next_prev353;
        for(int i352=0;i352<(int)prev.size();++i352) {
          i = prev[i352];
          tmp = parse_not349();
          if(!tmp.empty()&&tmp.front()==FAIL) {
            next_prev353.push_back(prev[i352]);
          } else {
            if(!(!next_prev353.empty()&&next_prev353.front()==FAIL)) {
              next_prev353.push_front(FAIL);
            }
          }
        }
        prev = next_prev353;
        sort(prev.begin(),prev.end());
        prev.erase(unique(prev.begin(),prev.end()),prev.end());
      }
      if(!((int)prev.size()==1&&prev.front()==FAIL)) {
        tmp.clear();
        for(int i354=0;i354<(int)prev.size();++i354) {
          if( prev[i354] == FAIL ) {
            if(!(!tmp.empty()&&tmp.front()==FAIL)) {
              tmp.push_front(FAIL);
            }
            continue;
          }
          if(prev[i354]<m) {//any character
            tmp.push_back(prev[i354]+1);
          } else {
            if(!( !tmp.empty() && tmp.front() == FAIL )){
              tmp.push_front(FAIL);
            }
          }
        }
        prev = tmp;
        sort(prev.begin(),prev.end());
        prev.erase(unique(prev.begin(),prev.end()),prev.end());
      }
      sort(prev.begin(),prev.end());
      prev.erase(unique(prev.begin(),prev.end()),prev.end());
    }
    if(!((int)prev.size()==1&&prev.front()==FAIL)) {
      /* Star */
      deque<int> next_prev363;
      deque<int> star_final_prev364;
      while(!((int)prev.size()==1&&prev.front()==FAIL)) {
        next_prev363.clear();
        for(int i365=0;i365<(int)prev.size();++i365) {
          i = prev[i365];
          tmp = parse_while355();
          if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
            star_final_prev364.push_back(prev[i365]);
          }
          for(int i366=0;i366<(int)tmp.size();++i366) {
            if(tmp[i366]==FAIL) {
              if(!( !next_prev363.empty() && next_prev363.front() == FAIL )) {
                next_prev363.push_front(FAIL);
              }
            } else {
              next_prev363.push_back(tmp[i366]);
            }
          }
        }
        prev = next_prev363;
      }
      prev = star_final_prev364;
      sort(prev.begin(),prev.end());
      prev.erase(unique(prev.begin(),prev.end()),prev.end());
    }
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i348=0;i348<(int)prev.size();++i348) {
    if( prev[i348] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i348]);
    }
  }
  return memo[key(53,backtracking_ptr_for_packrat53)] = result;
}

inline deque<int> parse_not349() { 
  if(memo.count(key(54,i))) {
    return memo[key(54,i)];
  }
  int backtracking_ptr_for_packrat54=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i351=0;i351<(int)prev.size();++i351) {
    if( prev[i351] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i351]<m&&I[prev[i351]]=='<') {
      tmp.push_back(prev[i351]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i350=0;i350<(int)prev.size();++i350) {
    if( prev[i350] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i350]);
    }
  }
  return memo[key(54,backtracking_ptr_for_packrat54)] = result;
}

inline deque<int> parse_while355() { 
  if(memo.count(key(55,i))) {
    return memo[key(55,i)];
  }
  int backtracking_ptr_for_packrat55=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev361;
    for(int i360=0;i360<(int)prev.size();++i360) {
      i = prev[i360];
      tmp = parse_not357();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev361.push_back(prev[i360]);
      } else {
        if(!(!next_prev361.empty()&&next_prev361.front()==FAIL)) {
          next_prev361.push_front(FAIL);
        }
      }
    }
    prev = next_prev361;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i362=0;i362<(int)prev.size();++i362) {
      if( prev[i362] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i362]<m) {//any character
        tmp.push_back(prev[i362]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i356=0;i356<(int)prev.size();++i356) {
    if( prev[i356] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i356]);
    }
  }
  return memo[key(55,backtracking_ptr_for_packrat55)] = result;
}

inline deque<int> parse_not357() { 
  if(memo.count(key(56,i))) {
    return memo[key(56,i)];
  }
  int backtracking_ptr_for_packrat56=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i359=0;i359<(int)prev.size();++i359) {
    if( prev[i359] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i359]<m&&I[prev[i359]]=='<') {
      tmp.push_back(prev[i359]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i358=0;i358<(int)prev.size();++i358) {
    if( prev[i358] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i358]);
    }
  }
  return memo[key(56,backtracking_ptr_for_packrat56)] = result;
}

deque<int> parse_S(){
  if(memo.count(key(57,i))) {
    return memo[key(57,i)];
  }
  int backtracking_ptr_for_packrat57=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i368=0;i368<(int)prev.size();++i368) {
      if( prev[i368] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i368]<m&&(I[prev[i368]]==' '||I[prev[i368]]==(char)9||I[prev[i368]]==(char)13||I[prev[i368]]==(char)10)) {
        tmp.push_back(prev[i368]+1);
      } else {
        if(!( !tmp.empty() && tmp.front() == FAIL )){
          tmp.push_front(FAIL);
        }
      }
    }
    prev = tmp;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i367=0;i367<(int)prev.size();++i367) {
    if( prev[i367] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i367]);
    }
  }
  return memo[key(57,backtracking_ptr_for_packrat57)] = result;
}


int main() {
  string tmp;
  while(getline(cin,tmp)) I += (tmp+"\n");
  m = (int)I.size();
  int cnt = 10;
  auto sum = 0;
  long long maxi = -LLONG_MAX;
  long long mini = LLONG_MAX;
  for(int loop=0;loop<cnt;++loop) {
    i=0;
    memo.clear();
    auto st = chrono::system_clock::now();
    deque<int> result = parse_File();
    auto ed = chrono::system_clock::now();
    sort(result.begin(),result.end());
    result.erase(unique(result.begin(),result.end()),result.end());
    if(!( result.size() == 1 && result[0] == FAIL )) {
      puts("success");
      for(int i=0;i<(int)result.size();++i) {
	if(result[i] == -1) continue;
	cout << "consumed :: [" << result[i] << "/" << m << "]" << endl;
      }
    } else {
      puts("fail");
    }
    auto diff = chrono::duration_cast<chrono::milliseconds>(ed-st).count();
    maxi = max(maxi,diff);
    mini = min(mini,diff);
    sum += diff;
    cout << "matching time :: " << diff << "msec" << endl;
    long long memo_s = 0;
    for(auto v : memo) memo_s += (long long)v.second.size();
    cout << "memo :: " << memo_s << endl;
  }
  printf("average :: %10f\n",(sum-maxi-mini)/(double)(cnt-2));
  return 0;
}
