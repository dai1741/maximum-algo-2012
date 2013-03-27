#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include <complex>
using namespace std;
#define rep(i,n) for (int i=0; i < (n); i++)

// 主に以下の資料を参考に作成した。
// - http://www.prefield.com/algorithm
// - http://www.deqnotes.net/acmicpc/2d_geometry/
// - https://github.com/infnty/acm/tree/master/lib/geometry
// - サークルの先輩が作ったライブラリ

// 以下のコードは全て動作チェックしていないので注意

/* 基本要素 */

typedef double D;
typedef complex<D> P;
typedef pair<P, P> L;
typedef vector<P> VP;
const D EPS = 1e-9;
#define X real()
#define Y imag()
#define LE(n,m) ((n) < (m) + EPS)
#define GE(n,m) ((n) + EPS > (m))
#define EQ(n,m) (abs((n)-(m)) < EPS)

// 内積　dot(a,b) = |a||b|cosθ
D dot(P a, P b) {
  return (conj(a)*b).X;
}
// 外積　cross(a,b) = |a||b|sinθ
D cross(P a, P b) {
  return (conj(a)*b).Y;
}

// 点の進行方向
int ccw(P a, P b, P c) {
  b -= a;
  c -= a;
  if (cross(b,c) >  EPS) return +1;  // counter clockwise
  if (cross(b,c) < -EPS) return -1;  // clockwise
  if (dot(b,c)   < -EPS) return +2;  // c--a--b on line
  if (norm(b) < norm(c)) return -2;  // a--b--c on line or a==b
  return 0;                          // a--c--b on line or a==c or b==c
}

/* 交差判定　直線・線分は縮退してはならない。接する場合は交差するとみなす。 */

// 直線と点
bool intersectsLP(P a1, P a2, P b) {
  return abs(ccw(a1, a2, b)) != 1;
}

// 直線と直線
bool intersectsLL(P a1, P a2, P b1, P b2) {
  return !intersectsLP(a2-a1, b2-b1, 0) || intersectsLP(a1, b1, b2);
}

// 直線と線分
bool intersectsLS(P a1, P a2, P b1, P b2) {
  P a = a2 - a1;
  b1 -= a1;
  b2 -= a1;
  return cross(a, b1) * cross(a,b2) < EPS;
}

// 線分と線分
bool intersectsSS(P a1, P a2, P b1, P b2) {
  return ccw(a1, a2, b1)*ccw(a1, a2, b2) < EPS  &&  ccw(b1, b2, a1)*ccw(b1, b2, a2) < EPS;
}

// 線分と点
bool intersectsSP(P a1, P a2, P b) {
  return !ccw(a1, a2, b);
}


/* 距離　各直線・線分は縮退してはならない */

// 点pの直線aへの射影点を返す
P projection(P a1, P a2, P p) {
  a2 -= a1;
  p -= a1;
  D t = dot(a2,p) / norm(a2);
  return a1 + t*a2;
}

// 点pの直線aへの反射点を返す
P reflection(P a1, P a2, P p) {
  return 2.0*projection(a1, a2, p) - p;
}

D distanceLP(P a1, P a2, P p) {
  return abs(projection(a1, a2, p) - p);
}

D distanceLL(P a1, P a2, P b1, P b2) {
  return intersectsLL(a1, a2, b1, b2) ? 0 : distanceLP(a1, a2, b1);
}

D distanceLS(P a1, P a2, P b1, P b2) {
  return intersectsLS(a1, a2, b1, b2) ? 0 : min(distanceLP(a1, a2, b1), distanceLP(a1, a2, b2));
}

D distanceSP(P a1, P a2, P b) {
  P r = projection(a1, a2, b);
  if (intersectsSP(a1, a2, r)) return abs(r-b);
  return min(abs(a1-b), abs(a2-b));
}

D distanceSS(P a1, P a2, P b1, P b2) {
  if (intersectsSS(a1, a2, b1, b2)) return 0;
  return min(min(abs(b1-a1), abs(b1-a2)), min(abs(b2-a1), abs(b2-a2)));
}

// 2直線の交点
P crosspointLL(P a1, P a2, P b1, P b2) {
  a2 -= a1;
  b2 -= b1;
  D d1 = cross(b2, b1-a1);
  D d2 = cross(b2, a2);
  if (EQ(d1, 0) && EQ(d2, 0)) return a1;  // same line
  if (EQ(d2, 0)) throw "kouten ga nai";  // 交点がない
  return a1 + d1/d2 * a2;
}


/* 円 */

D distanceLC(P a1, P a2, P p, D r) {
  return max(distanceLP(a1, a2, p) - r, 0.0);
}

D distanceSC(P a1, P a2, P b, D r) {
  D dSqr1 = norm(b-a1);
  D dSqr2 = norm(b-a2);
  if (dSqr1 < r*r ^  dSqr2 < r*r) return 0;  // 線分が円の中にあるとき距離0とするなら、ここをORに変える
  if (dSqr1 < r*r && dSqr2 < r*r) return r - sqrt(max(dSqr1, dSqr2));
  return max(distanceSP(a1, a2, b) - r, 0.0);
}

VP crosspointLC(P a1, P a2, P b, D r) {
  VP ret;
  P ft = projection(a1, a2, b);
  D ftLSqr = norm(ft-b);
  P dir = a2-a1;
  if (EQ(r*r, ftLSqr)) ret.push_back(ft);
  if (LE(r*r, ftLSqr) || ft != ft) return ret;

  dir *= sqrt(r*r - ftLSqr) / abs(dir);
  ret.push_back(ft + dir);
  ret.push_back(ft - dir);
  return ret;
}

D distanceCC(P a, D ar, P b, D br) {
  D dSqr = norm(a-b);
  if (dSqr + EPS < (ar-br) * (ar-br)) return abs(ar-br) - sqrt(dSqr);
  if ((ar+br) * (ar+br) + EPS < dSqr) return sqrt(dSqr) - ar - br;
  return 0;
}

// 2円の交点
VP crosspointsCC(P a, D ar, P b, D br) {
  VP ret;
  P ab = b-a;
  D d = abs(ab);
  D crossL = (norm(ab) + ar*ar - br*br) / (2*d);
  if (EQ(d, 0) || ar < crossL) return ret;

  P abN = ab * P(0, sqrt(ar*ar - crossL*crossL) / d);
  P cp = a + crossL/d * ab;
  ret.push_back(cp + abN);
  if (!EQ(norm(abN), 0)) ret.push_back(cp - abN);
  return ret;
}

// 点bから円aへの接線の接点
VP tangentPoints(P a, D ar, P b) {
  VP ret;
  double sin = ar / abs(b-a);
  if (!LE(sin, 1)) return ret;  // ここでNaNも弾かれる
  double t = M_PI_2 - asin(min(sin, 1.0));
  ret.push_back(a + (b-a)*polar(sin, t));
  if (!EQ(sin, 1)) ret.push_back(a + (b-a)*polar(sin, -t));
  return ret;
}

// 2円の共通接線。返される各直線に含まれる頂点は円との接点となる
vector<L> tangentLines(P a, D ar, P b, D br) {
  vector<L> ret;
  D d = abs(b-a);
  rep (i,2) {
    D sin = (ar - (1-i*2)*br) / d;
    if (!LE(sin*sin, 1)) break;
    D cos = sqrt(max(1 - sin*sin, 0.0));
    rep (j,2) {
      P n = (b-a) * P(sin, cos * (1-j*2)) / d;
      ret.push_back(L(a + ar*n, b + (1-i*2)*br*n));
      if (cos < EPS) break;  // 重複する接線を無視（重複していいならこの行不要）
    }
  }
  return ret;
}

// 三角形の外心
P circumcenter(P a, P b, P c) {
  a = (a-c)*0.5;
  b = (b-c)*0.5;
  return c + crosspointLL(a, a*P(1,1), b, b*P(1,1));
}

// 点集合を含む最小の円
P minEnclosingCircle(const VP& ps) {
  P c;
  double move = 0.5;
  rep(i,39) {  // 2^(-39-1) \approx 0.9e-12
    rep(t,50) {
      D max = 0;
      int k = 0;
      rep (j, ps.size()) {
        if (max < norm(ps[j]-c)) {
          max = norm(ps[j]-c);
          k = j;
        }
      }
      c += (ps[k]-c) * move;
    }
    move /= 2;
  }
  return c;
}


/* 多角形 */

// 頂点の順序（sortやmax_elementに必要）
namespace std {
  bool operator<(const P a, const P b) {
    return a.X != b.X ? a.X < b.X : a.Y < b.Y;
  }
}

// 凸包。引数の点集合はソートされる
VP convexHull(VP& ps) {
  int n = ps.size(), k = 0;
  sort(ps.begin(), ps.end());
  VP ch(2*n);
  for (int i = 0; i < n; ch[k++] = ps[i++]) // lower-hull
    while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;  // 同一直線上の点を含むなら == -1 とする
  for (int i = n-2, t = k+1; i >= 0; ch[k++] = ps[i--]) // upper-hull
    while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) --k;
  ch.resize(k-1);
  return ch;
}

// 凸判定
bool isCcwConvex(const VP& ps) {
  int n = ps.size();
  rep (i, n) {
    if (ccw(ps[i], ps[(i + 1) % n], ps[(i + 2) % n]) == -1) return false;  // 縮退を認めないなら != 1 とする
  }
  return true;
}

// 凸多角形の内部判定　O(n)
// 点が領域内部なら1、境界上なら2、外部なら0を返す
int inConvex(P p, const VP& ps) {
  int n = ps.size();
  int dir = ccw(ps[0], ps[1], p);
  rep (i, n) {
    int ccwc = ccw(ps[i], ps[(i + 1) % n], p);
    if (ccwc == 0) return 2;  // 線分上に存在
    if (ccwc != dir) return 0;
  }
  return 1;
}

// 凸多角形の内部判定　O(logn)
// 点が領域内部なら1、境界上なら2、外部なら0を返す
int inCcwConvex(const VP& ps, P p) {
  int n = ps.size();
  P g = (ps[0] + ps[n / 3] + ps[n*2 / 3]) / 3.0;
  if (g == p) return 1;
  P gp = p - g;

  int l = 0, r = n;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    P gl = ps[l] - g;
    P gm = ps[mid] - g;
    if (cross(gl, gm) > 0) {
      if (cross(gl, gp) >= 0 && cross(gm, gp) <= 0) r = mid;
      else l = mid;
    }
    else {
      if (cross(gm, gp) >= 0 && cross(gl, gp) <= 0) l = mid;
      else r = mid;
    }
  }
  r %= n;
  D cr = cross(ps[l] - p, ps[r] - p);
  return EQ(cr, 0) ? 2 : cr < 0 ? 0 : 1;
}

// 多角形の内部判定
// 点が領域内部なら1、境界上なら2、外部なら0を返す
int inPolygon(const VP& ps, P p) {
  int n = ps.size();
  bool in = false;
  rep (i, n) {
    P a = ps[i] - p;
    P b = ps[(i + 1) % n] - p;
    if (EQ(cross(a,b), 0) && LE(dot(a,b), 0)) return 2;
    if (a.Y > b.Y) swap(a,b);
    if ((a.Y*b.Y < 0 || (a.Y*b.Y < EPS && b.Y > EPS)) && LE(cross(a, b), 0)) in = !in;
  }
  return in;
}

// 凸多角形クリッピング
VP convexCut(const VP& ps, P a1, P a2) {
  int n = ps.size();
  VP ret;
  rep(i,n) {
    int ccwc = ccw(a1, a2, ps[i]);
    if (ccwc != -1) ret.push_back(ps[i]);
    int ccwn = ccw(a1, a2, ps[(i + 1) % n]);
    if (ccwc * ccwn == -1) ret.push_back(crosspointLL(a1, a2, ps[i], ps[(i + 1) % n]));
  }
  return ret;
}

// 凸多角形の直径（最遠点対）
pair<int, int> convexDiameter(const VP& ps) {
  int n = ps.size();
  int i = min_element(ps.begin(), ps.end()) - ps.begin();
  int j = max_element(ps.begin(), ps.end()) - ps.begin();
  int maxI, maxJ;
  D maxD = 0;
  rep(_, 2*n) {
    if (maxD < norm(ps[i]-ps[j])) {
      maxD = norm(ps[i]-ps[j]);
      maxI = i;
      maxJ = j;
    }
    int ni = (i + 1) % n;
    int nj = (j + 1) % n;
    if (cross(ps[i]-ps[ni], ps[nj]-ps[j]) <= 0) j = nj;
    else i = ni;
  }
  return make_pair(maxI, maxJ);
}

// 多角形の符号付面積
D area(const VP& ps) {
  int n = ps.size();
  D a = 0;
  rep (i, n) a += cross(ps[i], ps[(i + 1) % n]);
  return a / 2;
}

// 多角形の幾何学的重心
P centroid(const VP& ps) {
  int n = ps.size();
  D aSum = 0;
  P ret;
  rep (i, n) {
    D a = cross(ps[i], ps[(i + 1) % n]);
    aSum += a;
    ret += (ps[i] + ps[(i + 1) % n]) * a;
  }
  return 1 / aSum / 3 * ret;
}

// 幾何グラフ

struct Edge {
  int from, to;
  D cost;
  Edge(int from, int to, D cost) : from(from), to(to), cost(cost) {}
};
struct Graph {
  int n;
  vector<vector<Edge> > edges;
  Graph(int n) : n(n), edges(n) {}
  void addEdge(Edge e) {
    edges[e.from].push_back(e);
    edges[e.to].push_back(Edge(e.to, e.from, e.cost));
  }
};

// 線分アレンジメント（線分の位置関係からグラフを作成）
Graph segmentArrangement(const vector<L>& segs, VP& ps) {
  int n = segs.size();
  rep (i, n) {
    ps.push_back(segs[i].first);
    ps.push_back(segs[i].second);
    rep (j, i) {
      if (intersectsSS(segs[i].first, segs[i].second, segs[j].first, segs[j].second))
        ps.push_back(crosspointLL(segs[i].first, segs[i].second, segs[j].first, segs[j].second));
    }
  }
  sort(ps.begin(), ps.end());
  ps.erase(unique(ps.begin(), ps.end()), ps.end());

  int m = ps.size();
  Graph g(m);
  vector<pair<D, int> > list;
  rep (i, n) {
    list.clear();
    rep (j, m) {
      if (intersectsSP(segs[i].first, segs[i].second, ps[j]))
        list.push_back(make_pair(norm(segs[i].first-ps[j]), j));
    }
    sort(list.begin(), list.end());
    rep (j, list.size() - 1) {
      int a = list[j].second;
      int b = list[j+1].second;
      g.addEdge(Edge(a, b, abs(ps[a]-ps[b])));
    }
  }
  return g;
}


// この辺にコードを載せるほどでもないが重要な定理とか図とか書いておくとよい気がします


int main() {

  return 0;
}
