#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  // 最初にソート済みの配列を作る
  vector<int> perm(4, 0);
  for (int i = 0; i < perm.size(); i++) perm[i] = i;

  // do {...} while(next_permutation(perm.begin(), perm.end()))
  // とすると、doループ内のperm配列に順列が辞書順で格納されていく
  do {
    cout << "[";
    for (int i = 0; i < perm.size(); i++) cout << " " << perm[i];
    cout << " ]" << endl;
  } while(next_permutation(perm.begin(), perm.end()));

  return 0;
}


