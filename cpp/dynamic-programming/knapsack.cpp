#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

const int MAX_N = 1000; // nの最大値
const int MAX_W = 5000; // Wの最大値

// 入力
int n, W;
int w[MAX_N], v[MAX_N];

// i番目以降の品物から重さの和がj以下なるように選んだときの、
// 取りうる価値の総和の最大値を返す関数
int rec(int i, int j) {
  int res;
  if (i == n) {
    // 品物がもう残っていないときは、価値の和の最大値は0で確定
    res = 0;
  } else if (j < w[i]) {
    // 残りの容量が足りず品物iを入れられないので、入れないパターンだけ処理
    // i+1 以降の品物で判定したときの最大値をそのままこの場合の最大値にする
    res = rec(i + 1, j);
  } else {
    // 品物iを入れるか入れないか選べるので、両方試して価値の和が大きい方を選ぶ
    res = max(
        rec(i + 1, j),
        rec(i + 1, j - w[i]) + v[i]
    );
  }
  return res;
}

// 単純な再帰を用いた解法
void solve() {
  // 0番目以降で容量W以下の場合の結果を表示する
  cout << rec(0, W) << endl;
}

// メモ化テーブル
// dp[i][j]はi番目以降の品物から重さの和がj以下なるように選んだときの価値の和の最大値を表す。
// -1なら値が未決定であることを表す
int dp[MAX_N + 1][MAX_W + 1]; 

// i番目以降の品物から重さの和がj以下なるように選んだときの、
// 取りうる価値の総和の最大値を返す関数。メモ配列で計算結果を再利用する
int rec_dp(int i, int j) {
  if (dp[i][j] != -1) {
    // すでに調べたことがあるならその結果を再利用
    return dp[i][j];
  }
  int res;
  if (i == n) {
    // 品物がもう残っていないときは、価値の和の最大値は0で確定
    res = 0;
  } else if (j < w[i]) {
    // 残りの容量が足りず品物iを入れられないので、入れないパターンだけ処理
    res = rec_dp(i + 1, j);
  } else {
    // 品物iを入れるか入れないか選べるので、両方試して価値の和が大きい方を選ぶ
    res = max(
        rec_dp(i + 1, j),
        rec_dp(i + 1, j - w[i]) + v[i]
    );
  }
  // 結果をテーブルに記憶する
  return dp[i][j] = res;
}

// メモ化再帰を用いた解法
void solve_dp() {
  memset(dp, -1, sizeof(dp)); // メモ化テーブルを-1で初期化　以下のforループと等価
//  for (int i = 0; i < MAX_N + 1; i++)
//    for (int j = 0; j < MAX_W + 1; j++)
//      dp[i][j] = -1;
  
  // 0番目以降で容量W以下の場合の結果を表示する
  cout << rec_dp(0, W) << endl;
}

// DPテーブル。
// dp2[i][j]はi番目以降の品物から重さの和がj以下なるように選んだときの価値の和の最大値を表す。
int dp2[MAX_N + 1][MAX_W + 1];

// 漸化式を用いた解法
void solve_dp2() {
  for (int j = 0; j <= W; j++) dp2[n][j] = 0;
  
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= W; j++) {
      if (j < w[i])
        dp2[i][j] = dp2[i + 1][j];
      else
        dp2[i][j] = max(dp2[i + 1][j], dp2[i + 1][j - w[i]] + v[i]);
    }
  }
  cout << dp2[0][W] << endl;
}


int main() {
  cin >> n >> W;
  for (int i = 0; i < n; i++) {
    cin >> w[i] >> v[i];
  }

  solve();  // 再帰
  solve_dp(); // メモ化再帰によるDP
  solve_dp2(); // 漸化式ループによるDP

  return 0;
}

/*
 入力の形式：
    n W
    w_1 v_1
    w_2 v_2
    ...
    w_n v_n

 入力例：
    6 15
    11 15
    2 3
    3 1
    5 8
    1 2
    4 4
 
 出力例：
    20
	20
	20
*/
