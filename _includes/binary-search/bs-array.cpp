#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// vec から値が val である要素の位置を返す。
// 値が複数あるときは、最も小さな位置を返す。
// 値がなければ、値が val 超である最も小さな位置を返す。
int binsearch_lower_bound(vector<int>& vec, int val) {
  int low = 0; // 範囲の下限
  int high = vec.size(); // 範囲の上限。解はあれば [low, high] の中に存在する
  while (low < high) {
    int mid = (low + high) / 2;  // 中心点（この実装ではオーバーフローしうるので注意）
    int midval = vec[mid];  // 中心での値
    
    // 解の範囲を狭める
    if (midval < val) low = mid + 1;
    else high = mid;
  }
  return low;
}
// 上記の関数のSTLを使った実装。戻り値は全く同じになる
int stl_binsearch_lower_bound(vector<int>& vec, int val) {
  return lower_bound(vec.begin(), vec.end(), val) - vec.begin();
}

// vec から値が val 超である最も小さな要素の位置を返す。
int binsearch_upper_bound(vector<int>& vec, int val) {
  int low = 0; // 範囲の下限
  int high = vec.size(); // 範囲の上限
  while (low < high) {
    int mid = (low + high) / 2;  // 中心点
    int midval = vec[mid];  // 中心での値
    
    // 解の範囲を狭める（binsearch_lower_bound関数との違いはここだけ）
    if (midval <= val) low = mid + 1;
    else high = mid;
  }
  return low;
}
// 上記の関数のSTLを使った実装。戻り値は全く同じになる
int stl_binsearch_upper_bound(vector<int>& vec, int val) {
  return upper_bound(vec.begin(), vec.end(), val) - vec.begin();
}

int main() {
  int n = 100;
  vector<int> vec(n);
  for (int i = 0; i < n; i++) vec[i] = i * 2;

  cout << binsearch_lower_bound(vec, 50) << endl;    // => 25
  cout << stl_binsearch_lower_bound(vec, 50) << endl; // => 25
  cout << binsearch_upper_bound(vec, 50) << endl;    // => 26
  cout << stl_binsearch_upper_bound(vec, 50) << endl; // => 26
  
  cout << binsearch_lower_bound(vec, 76) << endl;    // => 38
  cout << binsearch_lower_bound(vec, 51) << endl;    // => 26
  cout << binsearch_upper_bound(vec, 51) << endl;    // => 26
  cout << binsearch_lower_bound(vec, 0) << endl;     // => 0
  cout << binsearch_lower_bound(vec, -1) << endl;    // => 0
  cout << binsearch_lower_bound(vec, 10000) << endl; // => 100

  return 0;
}

