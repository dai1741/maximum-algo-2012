#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define all(c) (c).begin(), (c).end()

int main() {
  vector<int> vec(10); // 要素数10個の配列宣言
  for (int i = 0; i < vec.size(); i++)
    vec[i] = (10*i + 3) % 14; // 適当に初期化


  cout << "ソート前：";
  for (int i = 0; i < vec.size(); i++) cout << " " << vec[i];
  cout << endl; // => ソート前： 3 13 9 5 1 11 7 3 13 9

  sort(vec.begin(), vec.end());

  cout << "ソート後：";
  for (int i = 0; i < vec.size(); i++) cout << " " << vec[i];
  cout << endl; // => ソート後： 1 3 3 5 7 9 9 11 13 13

  cout << *lower_bound(vec.begin(), vec.end(), 3) << endl; // => 3
  // vec.begin()で戻り値のイテレータを引けば配列の何番目かがわかる
  cout << (upper_bound(vec.begin(), vec.end(), 11) - vec.begin()) << endl; // => 8

  // all というマクロを用意しておくとbeginとendを毎回書く必要がなく便利
  cout << "3の個数: " << count(all(vec), 9) << endl; // => 3の個数: 2

  return 0;
}


