#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> vec(5,0); // 要素数5、初期値0の配列を宣言
  for (int i = 0; i < vec.size(); i++) {
    vec[i] = i*2;
  }
  // vec = [0, 2, 4, 6, 8]

  vec[2] = 100;
  vec.push_back(999); // 末尾に追加
  // vec = [0, 2, 100, 6, 8, 999]

  vec.insert(vec.begin() + 3, 5555); // 4番目の要素（vec[3]）の直前に追加
  vec.erase(vec.begin() + 1); // 2番目の要素（vec[1]）を消す
  
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl; // "0 100 5555 6 8 999 " と表示される
  return 0;
}


