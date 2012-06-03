#include <iostream>
#include <vector>
using namespace std;

const int INF = 100000000; // 無限

int n, m; // 頂点数, 辺数

typedef vector<vector<int> > AdjMatrix; // 隣接行列の型
AdjMatrix graph; // 隣接行列を表すグローバル変数

void input_graph_adj_matrix() {
  // 隣接行列を生成
  graph = AdjMatrix(n, vector<int>(n, INF));
  // 場合によっては自己ループ辺の重みを0にする
  // for (int i = 0; i < n; i++) graph[i][i] = 0;
  
  for (int i = 0; i < m; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;
    // cost = 1; // 重みなしグラフならコスト1

    graph[from][to] = cost;
    // 入力が無向グラフなら逆辺も張る
    // graph[to][from] = cost;
  }
}

// 隣接リストで使う辺を表す型
struct Edge {
  int to; // 辺の接続先頂点
  int cost; // 辺の重み

  Edge(int to, int cost) : to(to), cost(cost) {} // コンストラクタ
  // 余談だが、コンストラクタを使うと、
  //     Edge e; e.to=to; e.cost=cost; vec.push_back(e);
  // と書くような処理を
  //     vec.push_back(Edge(to, cost));
  // と書けるようになり、若干楽。
};

typedef vector<vector<Edge> > AdjList; // 隣接リストの型
// typedef vector<vector<int> > AdjList; // 辺に重みがなければ中身はintでもいい
AdjList edges; // 隣接リストを表すグローバル変数

void input_graph_adj_list() {
  // 隣接リストを生成
  edges = AdjList(n);

  for (int i = 0; i < m; i++) {
    int from, to, cost;
    cin >> from >> to >> cost;

    edges[from].push_back(Edge(to, cost));
    // 入力が無向グラフなら逆辺も張る
    // edges[to].push_back(Edge(from, cost));
  }
}

int main() {
  cin >> n >> m; // 頂点数, 辺数

  if (true) { // 隣接行列を使う場合
    input_graph_adj_matrix();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (graph[i][j] != INF)
          cout << i << "から" << j << "への辺のコスト: " << graph[i][j] << endl;
      }
    }
  }
  else { // 隣接リストを使う場合
    input_graph_adj_list();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < edges[i].size(); j++) {
          cout << i << "から" << edges[i][j].to << "への辺のコスト: "
              << edges[i][j].cost << endl;
      }
    }
  }
  return 0;
}

