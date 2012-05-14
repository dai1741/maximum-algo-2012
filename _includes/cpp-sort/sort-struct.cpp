#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
  int no, kokugo, sugaku;

  // 演算子オーバーロードで比較関数を定義
  bool operator<(const Student& another) const {
    if (kokugo != another.kokugo)
      return kokugo > another.kokugo; // 高い順に並べたいので演算子を逆に
    if (sugaku != another.sugaku)
      return sugaku > another.sugaku; // 同様に比較演算子を反転
    return no < another.no;
  }
};

int main() {
  int n;
  cin >> n;
  vector<Student> vec(n);
  for (int i = 0; i < n; i++)
    cin >> vec[i].no >> vec[i].kokugo >> vec[i].sugaku;

  sort(vec.begin(), vec.end()); // operator< を使ってソートされる

  for (int i = 0; i < vec.size(); i++) cout << vec[i].no << " ";
  cout << endl;

  return 0;
}


