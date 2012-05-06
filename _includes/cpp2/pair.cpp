#include <iostream>
#include <map> // pairはmapヘッダにある
#include <vector>
using namespace std;

int main() {
  pair<int, double> p = make_pair(2, 3.2);  // 整数と実数のペアを宣言
  cout << p.first << ", " << p.second << endl; // firstとsecondで要素にアクセス

  // pairは比較可能。1つ目の要素の大小関係が優先される
  cout << (p < make_pair(1, 3.2)) << endl;   // => 0
  cout << (p < make_pair(1, 100.0)) << endl; // => 0
  cout << (p < make_pair(2, 0.1)) << endl;   // => 0
  cout << (p < make_pair(2, 100.0)) << endl; // => 1
  cout << (p < make_pair(3, 1.5)) << endl;   // => 1

  // vectorやmapにも入れられる
  // まとめてソートするときにも便利
  vector<pair<int, char> > pair_vec;
  pair_vec.push_back(make_pair(5, 'a'));
  cout << pair_vec[0].second << endl; // => a

  return 0;
}

