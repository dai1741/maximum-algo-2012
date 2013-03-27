package jp.dai1741.competitive.util;

import jp.dai1741.competitive.util.Graphs.Edge;
import jp.dai1741.competitive.util.Graphs.ListsGraph;

import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.TreeSet;

public class Geometries2D {

    static final double EPS = 1e-9;

    static boolean approxEquals(double a, double b) {
        return Math.abs(a - b) < EPS;
    }

    static class Point extends Point2D.Double implements Comparable<Point> {

        public Point() {
        }

        public Point(double x, double y) {
            super(x, y);
            // xとyはfinalではないが、このライブラリ関数の一部は変更されないことを前提としているので注意。
        }

        /** dot(v1,v2)=|v1||v2|cosθ */
        double dot(Point p) {
            return x * p.x + y * p.y;
        }

        /** cross(v1,v2)=|v1||v2|sinθ  */
        double cross(Point p) {
            return x * p.y - y * p.x;
        }

        double distanceSqr() {
            return x * x + y * y;
        }

        double distance() {
            return Math.hypot(x, y);
        }

        Point add(Point p) {
            return new Point(x + p.x, y + p.y);
        }

        Point multiply(double k) {
            return new Point(k * x, k * y);
        }

        Point multiply(Point p) {  // complex mul: (x+yi)*(p.x+p.yi)
            return new Point(x * p.x - y * p.y, x * p.y + p.x * y);
        }

        Point subtract(Point begin) {
            return new Point(x - begin.x, y - begin.y);
        }

        @Override
        public boolean equals(Object obj) {  // この関数はEclipseで生成して座標の比較だけ書き換えればいい
            if (this == obj) return true;
            if (obj == null) return false;
            if (getClass() != obj.getClass()) return false;
            Point other = (Point) obj;
            if (!approxEquals(x, other.x)) return false;
            if (!approxEquals(y, other.y)) return false;
            return true;
        }

        @Override
        public int compareTo(Point o) {
            if (!approxEquals(x, o.x)) return (int) Math.signum(x - o.x);
            if (!approxEquals(y, o.y)) return (int) Math.signum(y - o.y);
            return 0;
        }

        @Override
        public String toString() {
            return "(" + x + "," + y + ")";
        }

    }

    /**
     * @return ベクトル a->b から見てベクトル b->c が左向きなら1、右向きなら-1
     * @see http://www.prefield.com/algorithm/geometry/ccw.html
     */
    static int ccw(Point a, Point b, Point c) {
        b = b.subtract(a);
        c = c.subtract(a);
        if (b.cross(c) > EPS) return +1;                  // counter clockwise
        if (b.cross(c) + EPS < 0) return -1;              // clockwise
        if (b.dot(c) + EPS < 0) return +2;                // c--a--b on line and a!=c
        if (b.distanceSqr() < c.distanceSqr()) return -2; // a--b--c on line or a==b　※基本的にa==bとなるべきでない　
        return 0;                                         // a--c--b on line or b==c
    }

    /*
     * 交差判定
     * @see http://www.prefield.com/algorithm/geometry/intersection.html
     */

    /** @return 直線aと直線bが交差しているならtrue */
    static boolean intersectsLL(Point a1, Point a2, Point b1, Point b2) {
        Point a = a2.subtract(a1);
        Point b = b2.subtract(b1);
        return !intersectsLP(a, b, new Point()) || intersectsLP(a1, b1, b2);
    }

    /** @return 直線aと線分bが交差しているならtrue */
    static boolean intersectsLS(Point a1, Point a2, Point b1, Point b2) {
        // a1を原点に移動
        Point a = a2.subtract(a1);
        b1 = b1.subtract(a1);
        b2 = b2.subtract(a1);
        return a.cross(b1) * a.cross(b2) < EPS;  // 線分bが直線aをまたぐならtrue
    }

    /** @return 直線aと点bが交差しているならtrue */
    static boolean intersectsLP(Point a1, Point a2, Point b) {
        int ccw = ccw(a1, a2, b);
        return ccw != 1 && ccw != -1;
    }

    static boolean intersectsSS(Point a1, Point a2, Point b1, Point b2) {
        // 互いの端点が自身の左右に分かれているならtrue
        return ccw(a1, a2, b1) * ccw(a1, a2, b2) <= 0
                && ccw(b1, b2, a1) * ccw(b1, b2, a2) <= 0;
    }

    static boolean intersectsSP(Point a1, Point a2, Point b) {
        return ccw(a1, a2, b) == 0;
    }

    /*
     * 距離
     * @see http://www.prefield.com/algorithm/geometry/distance.html
     */

    /** @return 直線aに点pを投影したときの位置 */
    static Point projection(Point a1, Point a2, Point p) {
        Point a = a2.subtract(a1);
        p = p.subtract(a1);
        double t = a.dot(p) / a.distanceSqr();
        // |a||p|cosθ=t|a|^2, a,tが固定でθが動くとき、点pの軌跡は直線
        return a1.add(a.multiply(t));
    }

    static Point reflection(Point a1, Point a2, Point p) {
        Point dir = projection(a1, a2, p).subtract(p);
        return p.add(dir.multiply(2));
    }

    static double distanceLP(Point a1, Point a2, Point p) {
        return projection(a1, a2, p).distance(p);
    }

    static double distanceLL(Point a1, Point a2, Point b1, Point b2) {
        if (intersectsLL(a1, a2, b1, b2)) return 0;
        return distanceLP(a1, a2, b1);
    }

    static double distanceLS(Point a1, Point a2, Point b1, Point b2) {
        if (intersectsLS(a1, a2, b1, b2)) return 0;
        return Math.min(distanceLP(a1, a2, b1), distanceLP(a1, a2, b2));
    }

    static double distanceSP(Point a1, Point a2, Point b) {
        Point r = projection(a1, a2, b);
        // 投影した点が線分上にあるなら、点pからその点への距離を返せばいい
        if (intersectsSP(a1, a2, r)) return r.distance(b);
        return Math.min(b.distance(a1), b.distance(a2));
    }

    static double distanceSS(Point a1, Point a2, Point b1, Point b2) {
        if (intersectsSS(a1, a2, b1, b2)) return 0;
        return Math.min(Math.min(b1.distance(a1), b1.distance(a2)), Math.min(b2
                .distance(a1), b2.distance(a2)));
    }

    /** @see http://www.deqnotes.net/acmicpc/2d_geometry/lines#intersection_of_lines */
    static Point crosspointLL(Point a1, Point a2, Point b1, Point b2) {
        // ベクトルaの長さをd1/d2倍すると直線bに接するようにd1,d2を設定
        Point a = a2.subtract(a1);
        Point b = b2.subtract(b1);
        double d1 = b.cross(b1.subtract(a1));
        double d2 = b.cross(a);
        if (Math.abs(d1) < EPS && Math.abs(d2) < EPS) return a1;  // same line
        if (Math.abs(d2) < EPS) throw new IllegalArgumentException(
                "PRECONDITION NOT SATISFIED");
        return a1.add(a.multiply(d1 / d2));
    }

    /*
     * 円の交差判定と距離判定
     * サークルの先輩が作った資料を参考にして書いた（があまり原形をとどめていない）
     */

    /** @return 直線aと円bの距離 */
    static double distanceLC(Point a1, Point a2, Point b, double r) {
        return Math.max(distanceLP(a1, a2, b) - r, 0);
    }

    static double distanceSC(Point a1, Point a2, Point b, double r) {
        double dSqr1 = b.subtract(a1).distanceSqr();
        double dSqr2 = b.subtract(a2).distanceSqr();
        boolean a1InCircle = dSqr1 < r * r;
        boolean a2InCircle = dSqr2 < r * r;
        if (a1InCircle && a2InCircle) {  // 線分の両端が円の中
            return r - Math.sqrt(Math.max(dSqr1, dSqr2));
        }
        if (a1InCircle ^ a2InCircle) return 0;  // 端点が円の中と外なら明らかに一点で交わる
        // 線分の端点が完全に円の外ならば点との距離判定でよい
        return Math.max(distanceSP(a1, a2, b) - r, 0);
    }

    /**
     * @return 交差点の組。ret.length は交差点の個数となる。
     * @see http://homepage1.nifty.com/gfk/circle-line.htm
     */
    static Point[] crosspointLC(Point a1, Point a2, Point b, double r) {
        // 直線aに円の中心から垂線の足をたらし、直線方向のベクトルを得て、
        // 三平方の定理で足から交点への距離を求める
        Point foot = projection(a1, a2, b);
        double footLenSqr = foot.distanceSq(b);
        Point dir = a2.subtract(a1);
        if (approxEquals(r * r, footLenSqr)) {  // 一点で接する場合（誤差死回避のため分岐）
            return new Point[] { foot };
        }
        if (r * r < footLenSqr) return new Point[0];

        double len = Math.sqrt(r * r - footLenSqr) / dir.distance();
        dir = dir.multiply(len);
        return new Point[] { foot.add(dir), foot.subtract(dir), };
    }

    /** @return 2円の関係を表す数値。値は適当。この関数いらないのでは。 */
    static int intersectionCC(Point a, double ar, Point b, double br) {
        double dSqr = a.distanceSq(b);
        if (approxEquals(dSqr, (ar + br) * (ar + br))) return 2;  // 外接する
        if (approxEquals(dSqr, (ar - br) * (ar - br))) return 3;  // 内接する
        if (dSqr < (ar - br) * (ar - br)) return -1;  // 片方の円はもう片方の内部
        if ((ar + br) * (ar + br) < dSqr) return -2;  // 片方の円はもう片方と全然関係がない
        return 1;  // 2点で交わる
    }

    static double distanceCC(Point a, double ar, Point b, double br) {
        double dSqr = a.distanceSq(b);
        // 片方の円はもう片方の内部
        if (dSqr + EPS < (ar - br) * (ar - br)) return Math.abs(ar - br)
                - Math.sqrt(dSqr);
        // 片方の円はもう片方と離れている
        if ((ar + br) * (ar + br) + EPS < dSqr) return Math.sqrt(dSqr) - ar - br;
        return 0;  // 接するか交わっている
    }

    /**
     * @return 2円の交差点の配列。配列の要素数は交差点の個数となる。
     */
    static Point[] crosspointCC(Point a, double ar, Point b, double br) {
        Point ab = b.subtract(a);
        double d = ab.distance();

        // 余弦定理で円の中心から2円の交点を結ぶ直線への距離を求め、
        // 三平方の定理で2円の交点を結ぶ直線の長さを求める
        double lenToCross = (ab.distanceSqr() + ar * ar - br * br) / (2 * d);
        double lenRef = Math.sqrt(ar * ar - lenToCross * lenToCross);
        if (d < EPS || ar < lenToCross) return new Point[0];  // 交点なし（か無限個存在）

        // 長さから交点の位置を求める
        Point abN = ab.multiply(new Point(0, 1)).multiply(lenRef / d);
        Point crosspoint = a.add(ab.multiply(lenToCross / d));
        Point[] ret = new Point[] { crosspoint.add(abN), crosspoint.subtract(abN) };
        return ret[0].equals(ret[1]) ? new Point[] { ret[0] } : ret;  // 交点が1つのときを処理（不要なら消す）
    }

    /**
     * @param b 円の外部の点
     * @return 接点2つ。交点が1つのとき（bが円周上）のときも2要素の配列を返す。
     */
    static Point[] tangent(Point a, double ar, Point b) {
        Point ba = a.subtract(b);
        double baLen = ba.distance();
        if (baLen < ar) return new Point[0];  // 接線なし

        double cos = Math.sqrt(ba.distanceSqr() - ar * ar) / baLen;
        double sin = ar / baLen;
        Point dir = ba.multiply(new Point(cos, sin));
        Point dir2 = ba.multiply(new Point(cos, -sin));
        return new Point[] { b.add(dir.multiply(cos)), b.add(dir2.multiply(cos)) };
        
//        Point ab = b.subtract(a);
//        double len = ab.distance();
//        if (len < ar) return new Point[0];  // 接線なし
//        double theta = Math.PI/2 - Math.asin(ar / len);
//        double cos = Math.cos(theta);
//        double sin = Math.sin(theta);
//        Point rot = new Point(cos, -sin);
//        return new Point[] { a.add(ab.multiply(rot.multiply(ar/len))), a.add(ab.multiply(new Point(cos, sin).multiply(ar/len))) };
    }

    /** 2円に対する接線の交点を返す。この関数いらないのでは。NaN返すとか極悪。 */
    static Point[] bitangentPoints(Point a, double ar, Point b, double br) {
        int type = intersectionCC(a, ar, b, br);
        Point ab = b.subtract(a);
        Point inner = null;
        Point outer = null;
        if (type != 3 && type != -1) inner = a.add(ab.multiply(ar / (ar + br)));
        if (type != 2 && type != -1) outer = ar != br ? a
                .add(ab.multiply(ar / (ar - br))) : new Point(Double.NaN, Double.NaN);
        return new Point[] { outer, inner };
    }

    /**
     * @return 2円の共通接線の組。ret[0]に共通外接線、ret[1]に共通内接線。
     *         対応する接線がない（or接線が無数にある）場合、ret[i]はnull。
     *         ret[i][j]に各接線が格納される。ret[i][j][0]に円aの接点、ret[i][j][1]に円bの接点。
     *         ret[i][0][0]は線分ABから見て左側に、ret[i][1][0]は線分ABから見て右側にある。
     *         接線が重なる場合、ret[i][1]はnull。外接線と内接線が一致する場合は重複して列挙する。
     * @see https://github.com/infnty/acm/blob/master/lib/geometry/CircleTangents.java
     */
    static Point[][][] tangentLines(Point a, double ar, Point b, double br) {
        Point[][][] ret = new Point[2][][];
        double d = a.distance(b);
        Point v = b.subtract(a).multiply(1 / d);  // aからbへの単位ベクトル

        for (int sign = +1, i = 0; sign >= -1; sign -= 2, i++) {  // 外接線 -> 内接線
            double sin = (ar - sign * br) / d;  // ベクトルabが斜辺、半径の和/差は正弦（符号付き）
            if (sin * sin > 1 + EPS || sin != sin) break;  // 距離よりも半径の和/差の方が大きい＝可能な接線を調べつくした

            ret[i] = new Point[2][];
            double cos = Math.sqrt(Math.max(1 - sin * sin, 0));

            for (int j = 0; j < 2; j++) {  // 2つの接線を求める
                // 接線の単位法線ベクトルを得る。(1-j*2)は符号
                Point n = v.multiply(new Point(sin, cos * (1 - j * 2)));
                ret[i][j] = new Point[] {
                        a.add(n.multiply(ar)), b.add(n.multiply(sign * br)) };  // 内接線は片方逆側になる
                // 接線が重なるときはret[i][j]は線分にならないので以下のように方向成分を足しておくと便利かもしれない 
                // if (cos < EPS) ret[i][j][1] = ret[i][j][1].add(n.multiply(new Point(0,1)));
                if (cos < EPS) break;  // 接線が重なっている（重複を区別しないならこの行を削除）
            }
            // i++; // 内接線と外接線を区別しないならiのインクリメント位置をここに変える
        }
        return ret;  // 内接線と外接線を区別せずret.lengthで接線の組の数を得るには
                    // return Arrays.copyOf(ret, i); とする（要Java6）
    }

    static Point circumcenter(Point a, Point b, Point c) {
        // 2本の垂直二等分線の交点を求める
        a = a.subtract(c).multiply(0.5);
        Point an = a.multiply(new Point(0, 1));
        b = b.subtract(c).multiply(0.5);
        Point bn = b.multiply(new Point(0, 1));
        return crosspointLL(a, a.add(an), b, b.add(bn)).add(c);
    }

    /**
     * psは多角形でなくてよい。O(n)？
     * 
     * @return 最小包含円の中心
     * @see http://www.ipsj.or.jp/07editj/promenade/4309.pdf
     */
    static Point minEnclosingCircle(Point[] ps) {
        int n = ps.length;
        Point c = new Point();
        double move = 0.5;
        for (int i = 0; i < 39; i++) {  // 2^(-39-1) \approx 0.9e-12
            for (int t = 0; t < 50; t++) {
                double max = 0;
                int k = 0;
                for (int j = 0; j < n; j++) {
                    if (max < ps[j].distanceSq(c)) {
                        max = ps[j].distanceSq(c);
                        k = j;
                    }
                }
                c = c.add(ps[k].subtract(c).multiply(move));
            }
            move /= 2;
        }
        return c;
    }

    /*
     * 凸多角形
     */

    /**
     * Andrew's Monotone Chain。引数の配列はソートされる。
     * 
     * @return ccwな凸包
     * @see http://www.prefield.com/algorithm/geometry/convex_hull.html
     * @see http://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
     */
    static ArrayList<Point> convexHull(Point[] ps) {
        Arrays.sort(ps);
        int n = ps.length;
        ArrayList<Point> hull = new ArrayList<Point>(n);
        // 下側凸包
        hull.add(ps[0]);
        hull.add(ps[1]);
        int k = 2; // k == hull.size()
        for (int i = 2; i < n; i++, k++) {
            while (k >= 2) {
                if (ccw(hull.get(k - 2), hull.get(k - 1), ps[i]) == -1) {  // 同一直線上の点を含まないなら <= 0 に
                    // 最後のベクトルから見て候補点が右側にあるなら、最後の点をはずす
                    hull.remove(--k);
                }
                else break;
            }
            hull.add(ps[i]);
        }
        // 下側凸包の後に上側を加える
        int lowerEnd = k++;
        hull.add(ps[n - 2]);
        for (int i = n - 3; i >= 0; i--, k++) {
            while (k > lowerEnd) {
                if (ccw(hull.get(k - 2), hull.get(k - 1), ps[i]) == -1) {  // 同一直線上の点を含まないなら <= 0 に
                    hull.remove(--k);
                }
                else break;
            }
            hull.add(ps[i]);
        }
        hull.remove(--k);  // 最後は重複しているので消す
        return hull;
    }

    /**
     * O(n)。
     * 
     * @return 多角形が左回りの凸（縮退可）ならtrue
     * @see http://www.prefield.com/algorithm/geometry/isconvex.html
     */
    static boolean isCcwConvex(Point[] polygon) {
        int n = polygon.length;
        for (int i = 0; i < n; i++) {
            Point cur = polygon[i];
            Point next = polygon[(i + 1) % n];
            Point next2 = polygon[(i + 2) % n];
            if (ccw(cur, next, next2) == -1) return false;
            // ↑縮退を認めないなら != 1 とする
        }
        return true;
    }

    /**
     * O(n)。凸形の向きはどちらでもいい
     */
    static boolean isConvex(Point[] polygon) {
        int n = polygon.length;
        boolean isClockwise = true;
        boolean isCounterClockwise = true;
        for (int i = 0; i < n; i++) {
            Point cur = polygon[i];
            Point next = polygon[(i + 1) % n];
            Point next2 = polygon[(i + 2) % n];
            int ccw = ccw(cur, next, next2);
            if (ccw == 1) {
                if (!isCounterClockwise) return false;
                isClockwise = false;
            }
            else if (ccw == -1) {
                if (!isClockwise) return false;
                isCounterClockwise = false;
            }
        }
        return true;
    }

    /**
     * O(n)
     * 
     * @return 内部に存在するなら1、線分上なら2、外部なら0
     */
    static int isInConvex(Point p, Point[] polygon) {
        int n = polygon.length;
        int dir = ccw(polygon[0], polygon[1], p);
        for (int i = 0; i < n; i++) {
            Point cur = polygon[i];
            Point next = polygon[(i + 1) % n];
            int ccw = ccw(cur, next, p);
            if (ccw == 0) return 2;  // 線分上に存在
            if (ccw != dir) return 0;
        }
        return 1;
    }

    /**
     * O(log n)
     * 多角形は縮退していないこと
     * 
     * @return 内部に存在するなら1、線分上なら2、外部なら0
     * @see http://www.prefield.com/algorithm/geometry/convex_contains.html
     * @see http://stackoverflow.com/a/5224119/897061
     */
    static int isInCcwConvex(Point p, Point[] polygon) {
        int n = polygon.length;
        // 凸形の内点を任意に選ぶ
        Point g = polygon[0].add(polygon[n / 3]).add(polygon[n * 2 / 3])
                .multiply(1.0 / 3);
        if (g.equals(p)) return 1;
        Point gp = p.subtract(g);

        int l = 0;
        int r = n;
        while (l + 1 < r) {  // 点gにより領域をセクタに分割し、二分探索で点pのあるセクタを探す
            int mid = (l + r) / 2;
            Point gl = polygon[l].subtract(g);
            Point gm = polygon[mid].subtract(g);
            if (gl.cross(gm) > 0) { // glからgmへのセクタが鋭角である
                // glからgmの範囲に点pがあるか調べる
                if (gl.cross(gp) >= 0 && gm.cross(gp) <= 0) r = mid;
                else l = mid;
            }
            else {
                // 鋭角側に点があるか調べる
                if (gm.cross(gp) >= 0 && gl.cross(gp) <= 0) l = mid;
                else r = mid;
            }
        }
        r %= n;
        double cross = polygon[l].subtract(p).cross(polygon[r].subtract(p));
        return approxEquals(cross, 0) ? 2 : cross < 0 ? 0 : 1;
    }

    /**
     * O(n)。
     * JavaならPolygonかPath2Dで図を作ってArea#contains()使ったほうが楽。どれくらい誤差があるか知らないけど。
     * 
     * @return 内部に存在するなら1、線分上なら2、外部なら0
     * @see http://www.prefield.com/algorithm/geometry/contains.html
     */
    static int isInPolygon(Point p, Point[] polygon) {
        int n = polygon.length;
        boolean in = false;
        for (int i = 0; i < n; i++) {
            Point a = polygon[i].subtract(p);
            Point b = polygon[(i + 1) % n].subtract(p);
            if (approxEquals(a.cross(b), 0) && a.dot(b) < EPS) return 2;
            if (a.y > b.y) {  // 点との位置関係を求めるためベクトルabを上向きにする
                Point temp = a;
                a = b;
                b = temp;
            }
            // 線分が直線と完全に交差しているか、線分の端点が
            // 直線の上側にあるなら直線と交差するとみなす
            if (a.y * b.y < 0 || (a.y * b.y < EPS && b.y > EPS)) {
                if (a.cross(b) < EPS) in = !in;  // 外積が負なら半直線とも交差する
            }
        }
        return in ? 1 : 0;
    }

    /**
     * O(nlogm + mlogn)。酷く冗長な実装。
     * JavaならPolygonかPath2Dで図を作ってArea#intersect(Area)を使ったほうが楽な上に
     * 凸じゃない図形にも使えるが、結構派手に摂動するので面積求めるとき以外は誤差がきつそう。
     * 
     * @return pとqの共通部分
     * @see http://www.prefield.com/algorithm/geometry/convex_intersect.html
     * @see http://web.archive.org/web/20110317231822/http://cgm.cs.mcgill.ca/~godfried/teaching/cg-projects/97/Plante/
     *      CompGeomProject-EPlante/algorithm.html
     */
    static ArrayList<Point> convexIntersection(Point[] p, Point[] q) {
        int n = p.length;
        int m = q.length;
        Point minP = Collections.min(Arrays.asList(p));
        Point minQ = Collections.min(Arrays.asList(q));
        int argminP = Arrays.asList(p).indexOf(minP);
        int argminQ = Arrays.asList(q).indexOf(minQ);
        int comp = minP.compareTo(minQ);
        int i = argminP;
        int j = argminQ;
        if (comp == 0) {
            // 最小の要素が一致するなら、2つの凸多角形を同時に進んでいく
            // 最初に見つかった相違点が交差部分である
            do {
                i = (i + 1) % n;
                j = (j + 1) % m;
            } while (i != argminP && p[i].equals(q[j]));
            if (i == argminP) return new ArrayList<Point>(Arrays.asList(p));  // pとqは等しい
            return convexIntersectionPhase3(p, q, (i + n - 1) % n, (j + m - 1) % m);
        }
        if (comp > 0) {  // pがqより右(あるいは上)にある
            return convexIntersection(q, p);  // 怠惰にswap
        }

        // pがqより左にあるならキャリパーする
        int count = 0;
        do {
            Point pVec = p[next(i, n)].subtract(p[i]);
            Point qVec = q[next(j, m)].subtract(q[j]);
            double cross = pVec.cross(qVec);
            Point dir = cross > 0 ? pVec : qVec;
            if (dir.cross(q[j].subtract(p[i])) < EPS) {
                // pのキャリパーから見てqのキャリパーは右側か一直線上にある。ここがpokect lid
                return convexIntersectionPhase2(p, q, i, j);
            }

            if (cross > -EPS) i = next(i, n);
            if (cross < EPS) j = next(j, m);
        } while (count++ < n + m);

        // 一周以上してもキャリパーの位置関係が変わらなかったのでqはpの内部にある
        return new ArrayList<Point>(Arrays.asList(q));
    }

    private static int next(int i, int n) {
        return (i + 1) % n;
    }

    private static ArrayList<Point> convexIntersectionPhase2(Point[] p, Point[] q, int i,
            int j) {
        int n = p.length;
        int m = q.length;
        // System.out.println("convexIntersectionREVENGEPhase2()" + i + ", " + j);
        // pocket lidの中に交差部分があるはずなので探す
        // 今は耳の中にいる
        // 前提条件よりp[0]は共通部分外なので、pはインデックスを進めるごとに耳の奥に行き、
        // qはインデックスを戻すごとに奥へ行く
        boolean updated;
        int count = 0;
        do {
            updated = false;
            while (count < n + m
                    && p[next(i, n)].subtract(p[i]).cross(
                            q[(j + m - 1) % m].subtract(p[i])) < -EPS) {
                j = (j + m - 1) % m;
                updated = true;
                count++;
            }
            while (count < n + m
                    && q[(j + m - 1) % m].subtract(q[j]).cross(
                            p[next(i, n)].subtract(q[j])) > EPS) {
                i = next(i, n);
                updated = true;
                count++;
            }
        } while (updated);
        if (count >= n + m) {  // 共通部分などなかった
            return new ArrayList<Point>();
        }
        j = (j + m - 1) % m;  // qを時計回りに考えていたので戻す
        return convexIntersectionPhase3(p, q, i, j);
    }

    private static ArrayList<Point> convexIntersectionPhase3(Point[] p, Point[] q, int i,
            int j) {
        // 具体的な共通部分が見つかったので、あとは交互弧をトレースしていけばいい…はず
        int n = p.length;
        int m = q.length;
        assert intersectsSS(p[i], p[next(i, n)], q[j], q[next(j, m)]);
        // System.out.println("convexIntersectionREVENGEPhase3()" + i + ", " + j);
        // System.out.println(intersectsSS(p[i], p[next(i, n)], q[j], q[next(j, m)]));
        // System.out.println(isInCcwConvex(p[next(i, n)], q));

        ArrayList<Point> intersection = new ArrayList<Point>();
        Point crossP = crosspointLL(p[i], p[next(i, n)], q[j], q[next(j, m)]);
        intersection.add(crossP);
        boolean pIsInQ = p[next(i, n)].subtract(p[i]).cross(q[next(j, m)].subtract(q[j])) <= 0;
        if (pIsInQ && !p[next(i, n)].equals(q[j])) j = next(j, m);
        else i = next(i, n);
        // System.out.println("pisinq" + pIsInQ + ", " + Arrays.toString(p));
        // System.out.println(i + ", " + j);

        // ここまでO(n+m)だったがここからO(nlogm + mlogn)になります（設計ミス）
        // キャリパーで事前に交差点列挙すればO(n+m)も可能。
        // Spaghetti Sourceのコードは事前列挙してないけどO(n+m)達成してて何やってるのか謎。
        do {
            Point nextP = p[next(i, n)];
            Point nextQ = q[next(j, m)];
            if (pIsInQ) {
                int inState = isInCcwConvex(nextP, q);
                if (inState == 1
                        || (inState == 2 && nextP.subtract(p[i]).cross(
                                nextQ.subtract(q[j])) < EPS)) {
                    intersection.add(nextP);
                }
                else {
                    // 交差する辺が見つかるまでqの辺を進める
                    while (!intersectsSS(p[i], nextP, q[j], q[next(j, m)])
                            || p[i].equals(q[j]))
                        j = (j + 1) % m;
                    nextQ = q[next(j, m)];
                    Point c = crosspointLL(p[i], nextP, q[j], nextQ);
                    if (approxEquals(nextP.subtract(p[i]).cross(nextQ.subtract(q[j])), 0)) {  // 2ベクトルが同一直線上
                        // qにとって最も進んだ場所へ行くべき
                        if (intersectsSP(p[i], nextP, nextQ)) c = nextQ;
                        else c = nextQ.subtract(nextP).distanceSqr() > nextQ.subtract(
                                p[i]).distanceSqr() ? p[i] : nextP;
                    }
                    intersection.add(c);
                    pIsInQ = false;
                }
                i = (i + 1) % n;
            }
            else {
                int inState = isInCcwConvex(nextQ, p);
                if (inState == 1
                        || (inState == 2 && nextQ.subtract(q[j]).cross(
                                nextP.subtract(p[i])) < EPS)) {
                    intersection.add(nextQ);
                }
                else {
                    while (!intersectsSS(p[i], p[next(i, n)], q[j], nextQ)
                            || p[i].equals(q[j]))
                        i = (i + 1) % n;
                    nextP = p[next(i, n)];
                    Point c = crosspointLL(p[i], nextP, q[j], nextQ);
                    if (approxEquals(nextP.subtract(p[i]).cross(nextQ.subtract(q[j])), 0)) {  // 2ベクトルが同一直線上
                        // pにとって最も進んだ場所へ行くべき
                        if (intersectsSP(q[j], nextQ, nextP)) c = nextP;
                        else c = nextP.subtract(nextQ).distanceSqr() > nextP.subtract(
                                q[j]).distanceSqr() ? q[j] : nextQ;
                    }
                    intersection.add(c);
                    pIsInQ = true;
                }
                j = (j + 1) % m;
            }
        } while (intersection.size() <= (n + m) * 2
                && !intersection.get(0).equals(intersection.get(intersection.size() - 1)));
        if (intersection.size() > (n + m) * 2) throw new IllegalStateException("A BUG");

        // 無駄な辺を消す
        ArrayList<Point> intersection2 = new ArrayList<Point>();
        for (int k = 0; k < intersection.size(); k++) {
            if (intersection2.size() < 2
                    || ccw(intersection2.get(intersection2.size() - 2), intersection2
                            .get(intersection2.size() - 1), intersection.get(k)) == 1) {
                intersection2.add(intersection.get(k));
            }
        }
        if (intersection2.size() > 1
                && intersection2.get(0).equals(
                        intersection2.get(intersection2.size() - 1))) intersection2
                .remove(intersection2.size() - 1);
        return intersection2;
    }

    /**
     * 凸多角形の直線の右側にある部分を切り捨てる
     * 
     * @param ps
     * @param a1
     * @param a2
     * @return
     * @see http://www.prefield.com/algorithm/geometry/convex_cut.html
     */
    static ArrayList<Point> convexCut(Point[] ps, Point a1, Point a2) {
        int n = ps.length;
        ArrayList<Point> ret = new ArrayList<Point>(n + 1);
        for (int i = 0; i < n; i++) {
            int ccw = ccw(a1, a2, ps[i]);
            if (ccw != -1) ret.add(ps[i]);
            int ccwn = ccw(a1, a2, ps[(i + 1) % n]);
            if (ccw * ccwn == -1) {  // ???????
                ret.add(crosspointLL(a1, a2, ps[i], ps[(i + 1) % n]));
            }
        }
        return ret;
    }

    /**
     * O(n)
     * 
     * @return 凸多角形の直径となる2点の組
     * @see http://www.prefield.com/algorithm/geometry/convex_diameter.html
     */
    static int[] convexDiameter(Point[] ps) {
        int n = ps.length;
        int initI = 0, initJ = 0;
        for (int i = 1; i < n; i++) {
            if (ps[i].x < ps[initI].x) initI = i;
            if (ps[i].x > ps[initJ].x) initJ = i;
        }
        int i = initI, j = initJ;
        int maxI = i, maxJ = j;
        double maxDSqr = 0;
        int count = 0;
        do {
            if (maxDSqr < ps[i].distanceSq(ps[j])) {
                maxDSqr = ps[i].distanceSq(ps[j]);
                maxI = i;
                maxJ = j;
            }
            int ni = (i + 1) % n;
            int nj = (j + 1) % n;
            // i側の逆向きのベクトルから見てj側のベクトルが右向きならjを進める
            if (ps[i].subtract(ps[ni]).cross(ps[nj].subtract(ps[j])) <= 0) j = nj;
            else i = ni;
        } while (count++ <= 2 * n);
        // Spaghetti Sourceに倣うとループ条件は(i != initI || j != initJ)とすべきだが、
        // 縮退した多角形に対し無限ループしうるのでロバストな実装にした
        return new int[] { maxI, maxJ };
    }

    /**
     * @see http://www.prefield.com/algorithm/geometry/area2.html
     */
    static double area(Point[] polygon) {
        double a = 0;
        for (int i = 0; i < polygon.length; i++) {
            a += polygon[i].cross(polygon[(i + 1) % polygon.length]);
        }
        return a / 2;
    }
    
    /**
     * @return 多角形の幾何学的重心
     * @see http://izumi-math.jp/F_Nakamura/heso/heso3.htm
     */
    static Point centroid(Point[] ps) {
        int n = ps.length;
        double areaSum = 0;
        Point centroid = new Point();
        for (int i = 0; i < n; i++) {
            double area = ps[i].cross(ps[(i + 1) % n]);
            areaSum += area;
            Point center3 = ps[i].add(ps[(i + 1) % n]);
            centroid = centroid.add(center3.multiply(area));
        }
        return centroid.multiply(1 / (areaSum * 3));
    }


    /**
     * @param segs 線分のリスト
     * @param ps グラフと座標の対応が入る出力変数
     * @return 線分アレンジメントのグラフ。推移的な辺は省略している。
     * @see http://www.prefield.com/algorithm/geometry/segment_arrangement.html
     */
    static ListsGraph segmentArrangement(Point[][] segs, List<Point> ps) {  // ListsGraphはGraphs.javaにある
        int n = segs.length;
        TreeSet<Point> set = new TreeSet<Point>();  // JavaのリストにはC++のuniqueがないので…
        for (int i = 0; i < n; i++) {
            set.add(segs[i][0]);
            set.add(segs[i][1]);
            for (int j = i + 1; j < n; j++) {
                if (intersectsSS(segs[i][0], segs[i][1], segs[j][0], segs[j][1])) {
                    // assert !intersectsSS(segs[i][0], segs[j][0], segs[i][1], segs[i][1]);
                    set.add(crosspointLL(segs[i][0], segs[i][1], segs[j][0], segs[j][1]));
                }
            }
        }
        ps.addAll(set);
        ListsGraph g = new ListsGraph(ps.size());

        class CP implements Comparable<CP> {  // JAVAにpairはない!!!
            final int i;
            final double d;

            CP(int i, double d) {
                this.i = i;
                this.d = d;
            }

            @Override
            public int compareTo(CP o) {
                return (int) Math.signum(d - o.d);
            }
        }
        ArrayList<CP> list = new ArrayList<CP>(ps.size());
        for (int i = 0; i < n; i++) {
            list.clear();
            for (int j = 0; j < ps.size(); j++) {
                if (intersectsSP(segs[i][0], segs[i][1], ps.get(j))) list.add(new CP(j,
                        segs[i][0].distanceSq(ps.get(j))));
            }
            Collections.sort(list);
            for (int j = 0; j + 1 < list.size(); j++) {
                int a = list.get(j).i;
                int b = list.get(j + 1).i;
                g.addEdge(new Edge(a, b, (int) ps.get(a).distance(ps.get(b))));
                // 横着してEdgeクラスの仕様に合わせてintにキャストしているが実際はキャストしない
            }
        }
        return g;
    }
}
