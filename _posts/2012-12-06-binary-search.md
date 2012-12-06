---
layout: post
category: docs
title: 二分探索
---


二分探索
========

二分探索は、ソートされた配列や関数から値を効率よく検索するためのアルゴリズムです。
アルゴリズムの詳細については、[Wikipedia](http://ja.wikipedia.org/wiki/二分探索)などを参照してください。


配列に対する二分探索
--------------------

ソースコードは次の通り。

{% highlight cpp %}
{% include binary-search/bs-array.cpp %}
{% endhighlight %}

上記コードでも記載していますが、配列（というよりイテレータ）に対する二分探索にはC++のalgorithmヘッダにある[lower_bound関数](http://www.cplusplus.com/reference/algorithm/lower_bound/)や[upper_bound関数](http://www.cplusplus.com/reference/algorithm/upper_bound/)も使えます。

二分探索は考え方は理解しやすいものの、値の範囲の狭め方などコーディングの際にバグを仕込む要因が非常に多いです。
そのため、C++の標準ライブラリを使えるようにするといいでしょう。

配列以外に対する二分探索
------------------------

プログラムにおいては、二分探索は配列に対して行う場合が多いです。
しかし、二分探索は単調非減少な関数、つまり戻り値がソートされているような関数にも適用することができます。
このような二分探索を、数値解析の分野では二分法と言います。

ソースコードは次の通り。

{% highlight cpp %}
{% include binary-search/bs-func.cpp %}
{% endhighlight %}

このことは意外にも幅広く応用することができます。
問題をうまく単調増加な関数の形に変換することで、愚直に解くと時間がかかりすぎる問題でもうまく解けることがあります。
詳しくはプログラミングコンテストチャレンジブックの「値の検索だけじゃない！"二分探索"」や[最強最速アルゴリズマー養成講座：トップクラスだけが知る「このアルゴリズムがすごい」――「探索」基礎最速マスター (3/4)](http://www.itmedia.co.jp/enterprise/articles/1002/06/news001_3.html)を見てください。

問題
----

- [AIZU ONLINE JUDGE 0181 Persistence](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0181)
