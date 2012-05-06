#include <iostream>
using namespace std;

struct SomeClass {
  int i;
  int j;
  double d;

  double get_sum() {
    return i + j + d;
  }

  // コンストラクタ（初期化子リストを使用）
  SomeClass(int i, int j, double d) : i(i), j(j), d(d) {}

  // 演算子オーバーロード
  bool operator<(const SomeClass& another) const {
    return i < another.i; // iの大小だけで比較
  }
};

int main() {
  SomeClass s(1,2,3);
  cout << s.get_sum() << endl; // => 6

  s = SomeClass(3,-88,5.5);
  cout << s.get_sum() << endl; // => -79.5

  s.i = 3;
  s.j = 2;
  s.d += 10.2;
  cout << s.get_sum() << endl; // => 20.7

  SomeClass s2(1,5,5);
  cout << (s < s2) << endl; // => 0
  s2.i = 10;
  cout << (s < s2) << endl; // => 1

  return 0;
}


