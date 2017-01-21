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
const long long base = 100; // for hash

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

deque<int> parse_D();
deque<int> parse_and1();
deque<int> parse_not5();
deque<int> parse_while12();
deque<int> parse_while21();
deque<int> parse_not29();
deque<int> parse_A();
deque<int> parse_slash38();
deque<int> parse_slash45();
deque<int> parse_B();
deque<int> parse_slash52();
deque<int> parse_slash59();
deque<int> parse_S();

deque<int> parse_D(){
  if(memo.count(key(0,i))) {
    return memo[key(0,i)];
  }
  int backtracking_ptr_for_packrat0=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* And */
    deque<int> next_prev11;
    for(int i10=0;i10<(int)prev.size();++i10) {
      i = prev[i10];
      tmp = parse_and1();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        if(!(!next_prev11.empty()&&next_prev11.front()==FAIL)) {
          next_prev11.push_front(FAIL);
        }
      } else {
        next_prev11.push_back(prev[i10]);
      }
    }
    prev = next_prev11;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev15;
    deque<int> star_final_prev16;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev15.clear();
      for(int i17=0;i17<(int)prev.size();++i17) {
        i = prev[i17];
        tmp = parse_while12();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev16.push_back(prev[i17]);
        }
        for(int i18=0;i18<(int)tmp.size();++i18) {
          if(tmp[i18]==FAIL) {
            if(!( !next_prev15.empty() && next_prev15.front() == FAIL )) {
              next_prev15.push_front(FAIL);
            }
          } else {
            next_prev15.push_back(tmp[i18]);
          }
        }
      }
      prev = next_prev15;
    }
    prev = star_final_prev16;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (B) */
    deque<int> next_prev20;
    for(int i19=0;i19<(int)prev.size();++i19) {
      if( prev[i19] == FAIL ) {
        if(!(!next_prev20.empty() && next_prev20.front() == FAIL )) {
          next_prev20.push_front(FAIL);
        }
        continue;
      }
      i = prev[i19];
      tmp = parse_B();
      
      for(int i19=0;i19<(int)tmp.size();++i19) {
        if( tmp[i19] == FAIL ) {
          if(!( !next_prev20.empty() && next_prev20[0] == FAIL )) {
            next_prev20.push_front(FAIL);
          }
        } else {
          next_prev20.push_back(tmp[i19]);
        }
      }
    }
    prev = next_prev20;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Star */
    deque<int> next_prev25;
    deque<int> star_final_prev26;
    while(!((int)prev.size()==1&&prev.front()==FAIL)) {
      next_prev25.clear();
      for(int i27=0;i27<(int)prev.size();++i27) {
        i = prev[i27];
        tmp = parse_while21();
        if( (int)tmp.size() == 1 && tmp.front() == FAIL ) {
          star_final_prev26.push_back(prev[i27]);
        }
        for(int i28=0;i28<(int)tmp.size();++i28) {
          if(tmp[i28]==FAIL) {
            if(!( !next_prev25.empty() && next_prev25.front() == FAIL )) {
              next_prev25.push_front(FAIL);
            }
          } else {
            next_prev25.push_back(tmp[i28]);
          }
        }
      }
      prev = next_prev25;
    }
    prev = star_final_prev26;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev33;
    for(int i32=0;i32<(int)prev.size();++i32) {
      i = prev[i32];
      tmp = parse_not29();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev33.push_back(prev[i32]);
      } else {
        if(!(!next_prev33.empty()&&next_prev33.front()==FAIL)) {
          next_prev33.push_front(FAIL);
        }
      }
    }
    prev = next_prev33;
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

inline deque<int> parse_and1() { 
  if(memo.count(key(1,i))) {
    return memo[key(1,i)];
  }
  int backtracking_ptr_for_packrat1=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (A) */
    deque<int> next_prev4;
    for(int i3=0;i3<(int)prev.size();++i3) {
      if( prev[i3] == FAIL ) {
        if(!(!next_prev4.empty() && next_prev4.front() == FAIL )) {
          next_prev4.push_front(FAIL);
        }
        continue;
      }
      i = prev[i3];
      tmp = parse_A();
      
      for(int i3=0;i3<(int)tmp.size();++i3) {
        if( tmp[i3] == FAIL ) {
          if(!( !next_prev4.empty() && next_prev4[0] == FAIL )) {
            next_prev4.push_front(FAIL);
          }
        } else {
          next_prev4.push_back(tmp[i3]);
        }
      }
    }
    prev = next_prev4;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Not */
    deque<int> next_prev9;
    for(int i8=0;i8<(int)prev.size();++i8) {
      i = prev[i8];
      tmp = parse_not5();
      if(!tmp.empty()&&tmp.front()==FAIL) {
        next_prev9.push_back(prev[i8]);
      } else {
        if(!(!next_prev9.empty()&&next_prev9.front()==FAIL)) {
          next_prev9.push_front(FAIL);
        }
      }
    }
    prev = next_prev9;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i2=0;i2<(int)prev.size();++i2) {
    if( prev[i2] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i2]);
    }
  }
  return memo[key(1,backtracking_ptr_for_packrat1)] = result;
}

inline deque<int> parse_not5() { 
  if(memo.count(key(2,i))) {
    return memo[key(2,i)];
  }
  int backtracking_ptr_for_packrat2=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i7=0;i7<(int)prev.size();++i7) {
    if( prev[i7] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i7]<m&&I[prev[i7]]=='b') {
      tmp.push_back(prev[i7]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i6=0;i6<(int)prev.size();++i6) {
    if( prev[i6] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i6]);
    }
  }
  return memo[key(2,backtracking_ptr_for_packrat2)] = result;
}

inline deque<int> parse_while12() { 
  if(memo.count(key(3,i))) {
    return memo[key(3,i)];
  }
  int backtracking_ptr_for_packrat3=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i14=0;i14<(int)prev.size();++i14) {
    if( prev[i14] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i14]<m&&I[prev[i14]]=='a') {
      tmp.push_back(prev[i14]+1);
    } else {
      if(!( !tmp.empty() && tmp[0] == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i13=0;i13<(int)prev.size();++i13) {
    if( prev[i13] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i13]);
    }
  }
  return memo[key(3,backtracking_ptr_for_packrat3)] = result;
}

inline deque<int> parse_while21() { 
  if(memo.count(key(4,i))) {
    return memo[key(4,i)];
  }
  int backtracking_ptr_for_packrat4=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Nonterminal (S) */
  deque<int> next_prev24;
  for(int i23=0;i23<(int)prev.size();++i23) {
    if( prev[i23] == FAIL ) {
      if(!(!next_prev24.empty() && next_prev24.front() == FAIL )) {
        next_prev24.push_front(FAIL);
      }
      continue;
    }
    i = prev[i23];
    tmp = parse_S();
    
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
  for(int i22=0;i22<(int)prev.size();++i22) {
    if( prev[i22] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i22]);
    }
  }
  return memo[key(4,backtracking_ptr_for_packrat4)] = result;
}

inline deque<int> parse_not29() { 
  if(memo.count(key(5,i))) {
    return memo[key(5,i)];
  }
  int backtracking_ptr_for_packrat5=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  tmp.clear();
  for(int i31=0;i31<(int)prev.size();++i31) {
    if( prev[i31] == FAIL ) {
      if(!(!tmp.empty()&&tmp.front()==FAIL)) {
        tmp.push_front(FAIL);
      }
      continue;
    }
    if(prev[i31]<m) {//any character
      tmp.push_back(prev[i31]+1);
    } else {
      if(!( !tmp.empty() && tmp.front() == FAIL )){
        tmp.push_front(FAIL);
      }
    }
  }
  prev = tmp;
  for(int i30=0;i30<(int)prev.size();++i30) {
    if( prev[i30] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i30]);
    }
  }
  return memo[key(5,backtracking_ptr_for_packrat5)] = result;
}

deque<int> parse_A(){
  if(memo.count(key(6,i))) {
    return memo[key(6,i)];
  }
  int backtracking_ptr_for_packrat6=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Prioritized Choice */
  deque<int> next_prev36;
  deque<int> prioritized_choice_final_prev37;
  next_prev36.clear();
  for(int i35=0;i35<(int)prev.size();++i35) {
    i = prev[i35];
    tmp = parse_slash38();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev36.push_back(prev[i35]); }
    for(int i44=0;i44<(int)tmp.size();++i44) {
      if( tmp[i44] != FAIL ) {
        prioritized_choice_final_prev37.push_back(tmp[i44]);
      }
    }
  }
  prev = next_prev36;
  next_prev36.clear();
  for(int i35=0;i35<(int)prev.size();++i35) {
    i = prev[i35];
    tmp = parse_slash45();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev36.push_back(prev[i35]); }
    for(int i47=0;i47<(int)tmp.size();++i47) {
      if( tmp[i47] != FAIL ) {
        prioritized_choice_final_prev37.push_back(tmp[i47]);
      }
    }
  }
  prev = next_prev36;
  if(!prev.empty()) {
    if(!(!prioritized_choice_final_prev37.empty() && prioritized_choice_final_prev37.front() == FAIL )) {
      prioritized_choice_final_prev37.push_front(FAIL);
    }
  }
  prev = prioritized_choice_final_prev37;
  for(int i34=0;i34<(int)prev.size();++i34) {
    if( prev[i34] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i34]);
    }
  }
  return memo[key(6,backtracking_ptr_for_packrat6)] = result;
}

inline deque<int> parse_slash38() { 
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
    for(int i40=0;i40<(int)prev.size();++i40) {
      if( prev[i40] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i40]<m&&I[prev[i40]]=='a') {
        tmp.push_back(prev[i40]+1);
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
    /* Nonterminal (A) */
    deque<int> next_prev42;
    for(int i41=0;i41<(int)prev.size();++i41) {
      if( prev[i41] == FAIL ) {
        if(!(!next_prev42.empty() && next_prev42.front() == FAIL )) {
          next_prev42.push_front(FAIL);
        }
        continue;
      }
      i = prev[i41];
      tmp = parse_A();
      
      for(int i41=0;i41<(int)tmp.size();++i41) {
        if( tmp[i41] == FAIL ) {
          if(!( !next_prev42.empty() && next_prev42[0] == FAIL )) {
            next_prev42.push_front(FAIL);
          }
        } else {
          next_prev42.push_back(tmp[i41]);
        }
      }
    }
    prev = next_prev42;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i43=0;i43<(int)prev.size();++i43) {
      if( prev[i43] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i43]<m&&I[prev[i43]]=='b') {
        tmp.push_back(prev[i43]+1);
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
  for(int i39=0;i39<(int)prev.size();++i39) {
    if( prev[i39] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i39]);
    }
  }
  return memo[key(7,backtracking_ptr_for_packrat7)] = result;
}

inline deque<int> parse_slash45() { 
  if(memo.count(key(8,i))) {
    return memo[key(8,i)];
  }
  int backtracking_ptr_for_packrat8=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i46=0;i46<(int)prev.size();++i46) {
    if( prev[i46] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i46]);
    }
  }
  return memo[key(8,backtracking_ptr_for_packrat8)] = result;
}

deque<int> parse_B(){
  if(memo.count(key(9,i))) {
    return memo[key(9,i)];
  }
  int backtracking_ptr_for_packrat9=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Prioritized Choice */
  deque<int> next_prev50;
  deque<int> prioritized_choice_final_prev51;
  next_prev50.clear();
  for(int i49=0;i49<(int)prev.size();++i49) {
    i = prev[i49];
    tmp = parse_slash52();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev50.push_back(prev[i49]); }
    for(int i58=0;i58<(int)tmp.size();++i58) {
      if( tmp[i58] != FAIL ) {
        prioritized_choice_final_prev51.push_back(tmp[i58]);
      }
    }
  }
  prev = next_prev50;
  next_prev50.clear();
  for(int i49=0;i49<(int)prev.size();++i49) {
    i = prev[i49];
    tmp = parse_slash59();
    if(!tmp.empty()&&tmp[0]==FAIL) { next_prev50.push_back(prev[i49]); }
    for(int i61=0;i61<(int)tmp.size();++i61) {
      if( tmp[i61] != FAIL ) {
        prioritized_choice_final_prev51.push_back(tmp[i61]);
      }
    }
  }
  prev = next_prev50;
  if(!prev.empty()) {
    if(!(!prioritized_choice_final_prev51.empty() && prioritized_choice_final_prev51.front() == FAIL )) {
      prioritized_choice_final_prev51.push_front(FAIL);
    }
  }
  prev = prioritized_choice_final_prev51;
  for(int i48=0;i48<(int)prev.size();++i48) {
    if( prev[i48] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i48]);
    }
  }
  return memo[key(9,backtracking_ptr_for_packrat9)] = result;
}

inline deque<int> parse_slash52() { 
  if(memo.count(key(10,i))) {
    return memo[key(10,i)];
  }
  int backtracking_ptr_for_packrat10=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i54=0;i54<(int)prev.size();++i54) {
      if( prev[i54] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i54]<m&&I[prev[i54]]=='b') {
        tmp.push_back(prev[i54]+1);
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
    /* Nonterminal (B) */
    deque<int> next_prev56;
    for(int i55=0;i55<(int)prev.size();++i55) {
      if( prev[i55] == FAIL ) {
        if(!(!next_prev56.empty() && next_prev56.front() == FAIL )) {
          next_prev56.push_front(FAIL);
        }
        continue;
      }
      i = prev[i55];
      tmp = parse_B();
      
      for(int i55=0;i55<(int)tmp.size();++i55) {
        if( tmp[i55] == FAIL ) {
          if(!( !next_prev56.empty() && next_prev56[0] == FAIL )) {
            next_prev56.push_front(FAIL);
          }
        } else {
          next_prev56.push_back(tmp[i55]);
        }
      }
    }
    prev = next_prev56;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i57=0;i57<(int)prev.size();++i57) {
      if( prev[i57] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i57]<m&&I[prev[i57]]=='c') {
        tmp.push_back(prev[i57]+1);
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

inline deque<int> parse_slash59() { 
  if(memo.count(key(11,i))) {
    return memo[key(11,i)];
  }
  int backtracking_ptr_for_packrat11=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
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

deque<int> parse_S(){
  if(memo.count(key(12,i))) {
    return memo[key(12,i)];
  }
  int backtracking_ptr_for_packrat12=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i63=0;i63<(int)prev.size();++i63) {
      if( prev[i63] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i63]<m&&(I[prev[i63]]==' '||I[prev[i63]]==(char)10||I[prev[i63]]==(char)13||I[prev[i63]]==(char)9)) {
        tmp.push_back(prev[i63]+1);
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
  for(int i62=0;i62<(int)prev.size();++i62) {
    if( prev[i62] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i62]);
    }
  }
  return memo[key(12,backtracking_ptr_for_packrat12)] = result;
}


int main() {
  string tmp;
  while(getline(cin,tmp)) I += (tmp+"\n");
  m = (int)I.size();
  auto sum = 0;
  long long maxi = -LLONG_MAX;
  long long mini = LLONG_MAX;
  int cnt = 10;
  for(int loop=0;loop<cnt;++loop) {
    i=0;
    memo.clear();
    auto st = chrono::system_clock::now();
    deque<int> result = parse_D();
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
    cout << "memo ::: " << memo.size() << endl;
  }
  printf("average :: %10f\n",(sum-maxi-mini)/(double)(cnt-2));
  return 0;
}
