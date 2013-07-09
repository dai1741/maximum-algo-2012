#include <iostream>
#include <map>  // pairはutilityヘッダにあり、mapヘッダから読み込まれる
#include <vector>
using namespace std;

typedef pair<int, int> PII;  // typedefしておくと型の記述量が減って便利

int main() {
  pair<int, double> p = make_pair(2, 3.2);  // 整数と実数のペアを宣言
  cout << p.first << ", " << p.second << endl;  // firstとsecondで要素にアクセス。  => 2, 3.2
  p.second += 10;  // ペアの各値は変更可能
  cout << p.second << endl;  // => 13.2

  // pairは比較可能。1つ目の要素の大小関係が優先される
  cout << (p < make_pair(1, 3.2))   << endl;  // => 0
  cout << (p < make_pair(1, 100.0)) << endl;  // => 0
  cout << (p < make_pair(2, 0.1))   << endl;  // => 0
  cout << (p < make_pair(2, 100.0)) << endl;  // => 1
  cout << (p < make_pair(3, 1.5))   << endl;  // => 1

  // vectorやmapにも入れられる
  // まとめてソートするときにも便利
  vector<pair<int, char> > pair_vec;
  pair_vec.push_back(make_pair(5, 'a'));
  cout << pair_vec[0].second << endl; // => a
  
  // typedefしておくと型の記述量が減って便利
  PII pii = PII(3,7);
  cout << pii.second << endl;  // => 7
  pii = PII(-4,9);  // `PII(-4,9)`は`pair<int,int>(-4,9)`と等価で、この場合`make_pair(-4,9)`とも等価
  cout << pii.first  << endl;  // => -4

  return 0;
}

