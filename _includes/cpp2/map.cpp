#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
  map<string, int> str_map; // 文字列をキーとして整数値を格納するマップを宣言
  str_map["hoge"] = 5; // 文字列が添え字になる
  str_map["fuga"] = 8;
  cout << str_map["hoge"] << endl; // => 5

  map<int, int> num_map; // 整数をキーとして整数値を格納するマップを宣言
  num_map[2] = 7;
  num_map[-888] = 5000; // 負数や大きな数を添え字にしても無問題
  num_map[100000000] = 3;
  
  // 要素の存在判定にはfind()を使う
  // 要素が見つからないときfind()は終端を示すイテレータを返す
  if (num_map.find(44) == num_map.end()) {
    cout << "44は見つかりません" << endl;
  }

  // 要素の全列挙にはイテレータを使う　とてもややこしい
  // イテレータの中身はpairで、キーと値はそれぞれfirstとsecondで得られる
  for (map<int, int>::iterator it = num_map.begin(); it != num_map.end(); ++it) {
    int key = it->first;
    int value = it->second;
    cout << "key: " << key << ", value: " << value << endl;
  }
  return 0;
}


