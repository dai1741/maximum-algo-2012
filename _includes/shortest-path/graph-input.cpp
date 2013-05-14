#include <iostream>
#include <vector>
using namespace std;

const int INF = 100000000;  // 無限

int n, m;  // 頂点数, 辺数

typedef vector<vector<int> > AdjMatrix;  // 隣接行列の型
AdjMatrix mat_graph;  // 隣接行列表現のグラフを表すグローバル変数

void input_graph_adj_matrix() {
  // 隣接行列を生成。INFで辺がないことを表す
  mat_graph = AdjMatrix(n, vector<int>(n, INF));
  // 場合によっては次のように自己ループ辺の重みを0にする（ワーシャルフロイド法で必要）
  // for (int i = 0; i < n; i++) mat_graph[i][i] = 0;
  
  for (int i = 0; i < m; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    // cost = 1; // 重みなしグラフならコスト1

    mat_graph[from][to] = cost;
    // 入力が無向グラフなら次のように逆辺も張る
    // mat_graph[to][from] = cost;
  }
}

// 隣接リストで使う辺を表す型
struct Edge {
  int to, cost;  // 辺の接続先頂点, 辺の重み

  Edge(int to, int cost) : to(to), cost(cost) {}  // コンストラクタ
  // 余談だが、コンストラクタを使うと、
  //     Edge e; e.to=to; e.cost=cost; vec.push_back(e);
  // と書くような処理を
  //     vec.push_back(Edge(to, cost));
  // と書けるようになり、若干楽。
};

typedef vector<vector<Edge> > AdjList;  // 隣接リストの型
AdjList list_graph;  // 隣接リスト表現のグラフを表すグローバル変数

void input_graph_adj_list() {
  // 隣接リストを生成
  list_graph = AdjList(n);

  for (int i = 0; i < m; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;

    list_graph[from].push_back(Edge(to, cost));
    // 入力が無向グラフなら逆辺も張る
    // list_graph[to].push_back(Edge(from, cost));
  }
}

int main() {
  cin >> n >> m; // 頂点数, 辺数

  if (true) {  // 隣接行列を使う場合
    input_graph_adj_matrix();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (mat_graph[i][j] != INF)
          cout << i << "から" << j << "への辺のコスト: " << mat_graph[i][j] << endl;lkjj
      }
    }
  }
  else {  // 隣接リストを使う場合
    input_graph_adj_list();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < list_graph[i].size(); j++) {
          cout << i << "から" << list_graph[i][j].to << "への辺のコスト: "
              << list_graph[i][j].cost << endl;
      }
    }
  }
  return 0;
}

