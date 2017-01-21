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

deque<int> parse_S();
deque<int> parse_T();
deque<int> parse_alternation8();
deque<int> parse_alternation13();
deque<int> parse_alternation18();
deque<int> parse_alternation28();

deque<int> parse_S(){
  if(memo.count(key(0,i))) {
    return memo[key(0,i)];
  }
  int backtracking_ptr_for_packrat0=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    tmp.clear();
    for(int i1=0;i1<(int)prev.size();++i1) {
      if( prev[i1] == FAIL ) {
        if(!(!tmp.empty()&&tmp.front()==FAIL)) {
          tmp.push_front(FAIL);
        }
        continue;
      }
      if(prev[i1]<m&&I[prev[i1]]=='b') {
        tmp.push_back(prev[i1]+1);
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
    /* Nonterminal (T) */
    deque<int> next_prev3;
    for(int i2=0;i2<(int)prev.size();++i2) {
      if( prev[i2] == FAIL ) {
        if(!(!next_prev3.empty() && next_prev3.front() == FAIL )) {
          next_prev3.push_front(FAIL);
        }
        continue;
      }
      i = prev[i2];
      tmp = parse_T();
      
      for(int i2=0;i2<(int)tmp.size();++i2) {
        if( tmp[i2] == FAIL ) {
          if(!( !next_prev3.empty() && next_prev3[0] == FAIL )) {
            next_prev3.push_front(FAIL);
          }
        } else {
          next_prev3.push_back(tmp[i2]);
        }
      }
    }
    prev = next_prev3;
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

deque<int> parse_T(){
  if(memo.count(key(1,i))) {
    return memo[key(1,i)];
  }
  int backtracking_ptr_for_packrat1=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  /* Alternation */
  deque<int> next_prev5;
  deque<int> tmp6;
  for(int i7=0;i7<(int)prev.size();++i7) {
    i = prev[i7];
    tmp6=parse_alternation8();
    for(int i27=0;i27<(int)tmp6.size();++i27) {
      if( tmp6[i27] == FAIL ) {
        if(!(!next_prev5.empty()&&next_prev5.front()==FAIL)) {
          next_prev5.push_front(FAIL);
        }
      } else {
        next_prev5.push_back(tmp6[i27]);
      }
    }
    i = prev[i7];
    tmp6=parse_alternation28();
    for(int i30=0;i30<(int)tmp6.size();++i30) {
      if( tmp6[i30] == FAIL ) {
        if(!(!next_prev5.empty()&&next_prev5.front()==FAIL)) {
          next_prev5.push_front(FAIL);
        }
      } else {
        next_prev5.push_back(tmp6[i30]);
      }
    }
  }
  prev = next_prev5;
  for(int i4=0;i4<(int)prev.size();++i4) {
    if( prev[i4] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i4]);
    }
  }
  return memo[key(1,backtracking_ptr_for_packrat1)] = result;
}

inline deque<int> parse_alternation8() { 
  if(memo.count(key(2,i))) {
    return memo[key(2,i)];
  }
  int backtracking_ptr_for_packrat2=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Alternation */
    deque<int> next_prev10;
    deque<int> tmp11;
    for(int i12=0;i12<(int)prev.size();++i12) {
      i = prev[i12];
      tmp11=parse_alternation13();
      for(int i17=0;i17<(int)tmp11.size();++i17) {
        if( tmp11[i17] == FAIL ) {
          if(!(!next_prev10.empty()&&next_prev10.front()==FAIL)) {
            next_prev10.push_front(FAIL);
          }
        } else {
          next_prev10.push_back(tmp11[i17]);
        }
      }
      i = prev[i12];
      tmp11=parse_alternation18();
      for(int i24=0;i24<(int)tmp11.size();++i24) {
        if( tmp11[i24] == FAIL ) {
          if(!(!next_prev10.empty()&&next_prev10.front()==FAIL)) {
            next_prev10.push_front(FAIL);
          }
        } else {
          next_prev10.push_back(tmp11[i24]);
        }
      }
    }
    prev = next_prev10;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (T) */
    deque<int> next_prev26;
    for(int i25=0;i25<(int)prev.size();++i25) {
      if( prev[i25] == FAIL ) {
        if(!(!next_prev26.empty() && next_prev26.front() == FAIL )) {
          next_prev26.push_front(FAIL);
        }
        continue;
      }
      i = prev[i25];
      tmp = parse_T();
      
      for(int i25=0;i25<(int)tmp.size();++i25) {
        if( tmp[i25] == FAIL ) {
          if(!( !next_prev26.empty() && next_prev26[0] == FAIL )) {
            next_prev26.push_front(FAIL);
          }
        } else {
          next_prev26.push_back(tmp[i25]);
        }
      }
    }
    prev = next_prev26;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i9=0;i9<(int)prev.size();++i9) {
    if( prev[i9] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i9]);
    }
  }
  return memo[key(2,backtracking_ptr_for_packrat2)] = result;
}

inline deque<int> parse_alternation13() { 
  if(memo.count(key(3,i))) {
    return memo[key(3,i)];
  }
  int backtracking_ptr_for_packrat3=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (S) */
    deque<int> next_prev16;
    for(int i15=0;i15<(int)prev.size();++i15) {
      if( prev[i15] == FAIL ) {
        if(!(!next_prev16.empty() && next_prev16.front() == FAIL )) {
          next_prev16.push_front(FAIL);
        }
        continue;
      }
      i = prev[i15];
      tmp = parse_S();
      
      for(int i15=0;i15<(int)tmp.size();++i15) {
        if( tmp[i15] == FAIL ) {
          if(!( !next_prev16.empty() && next_prev16[0] == FAIL )) {
            next_prev16.push_front(FAIL);
          }
        } else {
          next_prev16.push_back(tmp[i15]);
        }
      }
    }
    prev = next_prev16;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i14=0;i14<(int)prev.size();++i14) {
    if( prev[i14] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i14]);
    }
  }
  return memo[key(3,backtracking_ptr_for_packrat3)] = result;
}

inline deque<int> parse_alternation18() { 
  if(memo.count(key(4,i))) {
    return memo[key(4,i)];
  }
  int backtracking_ptr_for_packrat4=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (S) */
    deque<int> next_prev21;
    for(int i20=0;i20<(int)prev.size();++i20) {
      if( prev[i20] == FAIL ) {
        if(!(!next_prev21.empty() && next_prev21.front() == FAIL )) {
          next_prev21.push_front(FAIL);
        }
        continue;
      }
      i = prev[i20];
      tmp = parse_S();
      
      for(int i20=0;i20<(int)tmp.size();++i20) {
        if( tmp[i20] == FAIL ) {
          if(!( !next_prev21.empty() && next_prev21[0] == FAIL )) {
            next_prev21.push_front(FAIL);
          }
        } else {
          next_prev21.push_back(tmp[i20]);
        }
      }
    }
    prev = next_prev21;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    /* Nonterminal (S) */
    deque<int> next_prev23;
    for(int i22=0;i22<(int)prev.size();++i22) {
      if( prev[i22] == FAIL ) {
        if(!(!next_prev23.empty() && next_prev23.front() == FAIL )) {
          next_prev23.push_front(FAIL);
        }
        continue;
      }
      i = prev[i22];
      tmp = parse_S();
      
      for(int i22=0;i22<(int)tmp.size();++i22) {
        if( tmp[i22] == FAIL ) {
          if(!( !next_prev23.empty() && next_prev23[0] == FAIL )) {
            next_prev23.push_front(FAIL);
          }
        } else {
          next_prev23.push_back(tmp[i22]);
        }
      }
    }
    prev = next_prev23;
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i19=0;i19<(int)prev.size();++i19) {
    if( prev[i19] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i19]);
    }
  }
  return memo[key(4,backtracking_ptr_for_packrat4)] = result;
}

inline deque<int> parse_alternation28() { 
  if(memo.count(key(5,i))) {
    return memo[key(5,i)];
  }
  int backtracking_ptr_for_packrat5=i;
  deque<int> result; // we use -1 to denote failure
  deque<int> tmp;
  deque<int> prev; //ちょうど今失敗せずに残っているポインタ
  prev.push_back(i);
  if(!((int)prev.size()==1&&prev.front()==FAIL)) {
    sort(prev.begin(),prev.end());
    prev.erase(unique(prev.begin(),prev.end()),prev.end());
  }
  for(int i29=0;i29<(int)prev.size();++i29) {
    if( prev[i29] == FAIL ) {
      if(!( !result.empty() && result[0] == FAIL )) {
        result.push_front(FAIL);
      }
    } else {
      result.push_back(prev[i29]);
    }
  }
  return memo[key(5,backtracking_ptr_for_packrat5)] = result;
}


int main() {
  string tmp;
  while(getline(cin,tmp)) I += (tmp+"\n");
  m = (int)I.size();
  int cnt = 10;
  long long maxi = -LLONG_MAX;
  long long mini = LLONG_MAX;
  auto sum = 0;
  for(int loop=0;loop<cnt;++loop) {
    i=0;
    memo.clear();
    auto st = chrono::system_clock::now();
    deque<int> result = parse_S();
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
    cout << "matching time :: " << diff << "msec" << endl;
    cout << "the number of elements in memo :: " << memo.size() << endl;
    sum += diff;
    maxi = max(maxi,diff);
    mini = min(mini,diff);
  }
  printf("average :: %10f\n",(sum-maxi-mini)/(double)(cnt-2));
  return 0;
}
