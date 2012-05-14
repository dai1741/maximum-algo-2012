#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// 表示用関数
void disp(vector<int>& vec) {
  cout << "[";
  for (int i = 0; i < vec.size(); i++) cout << " " << vec[i];
  cout << " ]" << endl;
}

// 自作のソート関数
// 5で割った余りの大小で比較
bool less_mod5(int lhs, int rhs) {
  if ((lhs - rhs) % 5 != 0)
    return lhs % 5 < rhs % 5;
  else // 5で割った余りが等しいなら普通に大小比較する
    return lhs < rhs;
}

int main() {
  vector<int> vec(10);
  for (int i = 0; i < vec.size(); i++) vec[i] = 9 - i;

  sort(vec.begin(), vec.end());
  disp(vec); // => [ 0 1 2 3 4 5 6 7 8 9 ]

  sort(vec.begin(), vec.end(), greater<int>()); // 降順（大きい順）でソート
  disp(vec); // => [ 9 8 7 6 5 4 3 2 1 0 ]
  
  sort(vec.begin(), vec.end(), less_mod5); // 自作関数でソート
  disp(vec); // => [ 0 5 1 6 2 7 3 8 4 9 ]
  return 0;
}


