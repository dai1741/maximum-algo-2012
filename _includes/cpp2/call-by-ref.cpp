#include <iostream>
#include <vector>
using namespace std;

// 値渡し（普通の引数定義）
void func_val(int a, vector<int> v) {
  a += 1; // コピーされたint変数を書き換え（呼び出し元の変数の値は変化しない）
  v.push_back(1); // コピーされたvectorを書き換え
}

// 参照渡し
void func_ref(int& a, vector<int>& v) {
  a += 1; // 参照先にあるint変数を書き換え（呼び出し元の変数の値も変化する）
  v.push_back(1); // 参照先にあるvectorを書き換え
}

// ポインタ使用（参照渡しとほぼ同じ）
void func_pt(int* a, vector<int>* v) {
  *a += 1;
  v->push_back(1);
}

int main() {
  int a = 0;
  vector<int> v(10000);
  cout << a << ","  << v.size() << endl; // => 0,10000
  func_val(a, v);
  cout << a << ","  << v.size() << endl; // => 0,10000
  func_ref(a, v);
  cout << a << ","  << v.size() << endl; // => 1,10001
  func_pt(&a, &v);
  cout << a << ","  << v.size() << endl; // => 2,10002
  return 0;
}


