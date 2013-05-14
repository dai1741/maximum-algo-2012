#include <iostream>
using namespace std;

// 何か単調な関数
double func(double x) {
  return 0.003*x*x*x + 5.5*x - 100; // 0.003x^3 + 5.5x - 100
}

// func(x)=val となるx（の近似値）を[low, high]の範囲内で返す
double binsearch_func(double val, double low, double high) {
  for (int i = 0; i < 100; i++) {   // 100回ループ。これで十分精度がある
    double mid = (low + high) / 2;  // 中心点
    double midval = func(mid);      // 中心での値
    
    // 解の範囲を狭める
    if (midval < val) low = mid;
    else high = mid;
  }
  return low;
}

int main() {
  double low = -10000000;
  double high = 10000000;
  
  cout << binsearch_func(0,         low, high) << endl;  // => 15.9631
  cout << binsearch_func(100,       low, high) << endl;  // => 26.3661
  cout << binsearch_func(100000000, low, high) << endl;  // => 3218.11
  cout << binsearch_func(-10000,    low, high) << endl;  // => -144.777

  return 0;
}

