#include<iostream>

using namespace std;

const int size = 100000;

int main() {
  cout << string(size,'a') << string(size,'b') << string(size,'c') << endl;
  return 0;
}
