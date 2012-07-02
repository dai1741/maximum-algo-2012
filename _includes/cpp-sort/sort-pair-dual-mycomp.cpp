#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, pair<int, int> > S; // 番号、国語の点、数学の点

// lhs < rhs ならtrueを返す
bool comp(S lhs, S rhs) {
  if (lhs.second.first != rhs.second.first)
    return lhs.second.first > rhs.second.first;
  if (lhs.second.second != rhs.second.second)
    return lhs.second.second > rhs.second.second;
  return lhs.first < rhs.first;
}

int main() {
  int n;
  cin >> n;
  vector<S> vec(n);
  for (int i = 0; i < n; i++) {
    int no, kokugo, sugaku;
    cin >> no >> kokugo >> sugaku;
    vec[i] = S(no, make_pair(kokugo, sugaku));
  }

  sort(vec.begin(), vec.end(), comp);

  for (int i = 0; i < vec.size(); i++)
    // 番号は1番目に入れたのでfirstでアクセスする
    cout << vec[i].first << " ";
  cout << endl;

  return 0;
}

