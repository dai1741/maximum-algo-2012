#include <iostream>
using namespace std;

// クラス定義。C++ではクラスと構造体はほぼ同等
struct SomeClass {
  int i;
  int j;
  double d;

  // 何か関数
  double get_sum() {
    return i + j + d;  // クラスのメンバ変数を参照できる
  }

  // コンストラクタ（初期化子リストを使用）
  SomeClass(int i, int j, double d) : i(i), j(j), d(d) {}

  // `<`演算子のオーバーロード
  bool operator<(const SomeClass& another) const {
    return i < another.i; // iの大小だけで比較
  }
};

int main() {
  SomeClass s(1,2,3);  // 変数宣言と初期化
  // SomeClass s = SomeClass(1,2,3);  // コピーコンストラクタ経由で初期化（上とほぼ等価）
  // SomeClass s = {1,2,3};  // 変数宣言時の初期化構文を使った方法（コンストラクタがない場合 / 上とほぼ等価）
  cout << s.get_sum() << endl; // => 6

  s = SomeClass(3,-88,5.5);  // コンストラクタを呼び出して再代入
  // s = (SomeClass){3,-88,5.5};  // C99風のCompound Literalを使った書き方（g++拡張 / コンストラクタ不要）
  // s = SomeClass({3,-88,5.5});  // C++0xの初期化子リストを使った書き方（コンストラクタ不要）
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


