#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
  int no, kokugo, sugaku;
};

// a < b ならtrueを返す
bool comp(const Student& a, const Student& b) {
  if (a.kokugo != b.kokugo)
    return a.kokugo > b.kokugo; // 高い順に並べたいので演算子を逆に
  if (a.sugaku != b.sugaku)
    return a.sugaku > b.sugaku; // 同様に比較演算子を反転
  return a.no < b.no;
}

int main() {
  int n;
  cin >> n;
  vector<Student> vec(n);
  for (int i = 0; i < n; i++)
    cin >> vec[i].no >> vec[i].kokugo >> vec[i].sugaku;

  sort(vec.begin(), vec.end(), comp);

  for (int i = 0; i < vec.size(); i++) cout << vec[i].no << " ";
  cout << endl;

  return 0;
}
