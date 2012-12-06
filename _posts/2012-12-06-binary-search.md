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

上記コードでも記載していますが、配列（というより[イテレータ](../cpp2/#イテレータ)）に対する二分探索にはSTLの
[algorithmヘッダ](../cpp2/#algorithm)にある[lower_bound関数](http://www.cplusplus.com/reference/algorithm/lower_bound/)や
[upper_bound関数](http://www.cplusplus.com/reference/algorithm/upper_bound/)も使えます。

二分探索は考え方は理解しやすいものの、値の範囲の狭め方などコーディングの際にバグを仕込む要因が非常に多いです。
そのため、C++の標準ライブラリの関数を使えるようにするといいでしょう。

配列以外に対する二分探索
------------------------

プログラムにおいては、二分探索は配列に対して行う場合が多いです。
それに加えて、二分探索は[単調な関数](http://ja.wikipedia.org/wiki/単調関数)、つまり戻り値が引数の値について常に非減少（非増加）である関数にも適用することができます。
蛇足ですが、数値解析の分野では関数に対する二分探索を[二分法](http://ja.wikipedia.org/wiki/二分法)と言います。

ソースコードは次の通りです。

{% highlight cpp %}
{% include binary-search/bs-func.cpp %}
{% endhighlight %}

意外なことに、関数に対する二分探索は幅広く応用することができます。
問題をうまく単調関数の形に変換することで、素直に解くと時間がかかりすぎる問題でも効率よく解けることがあります。

具体的な二分探索の適用方法については、プログラミングコンテストチャレンジブックの「値の検索だけじゃない！"二分探索"」や
[最強最速アルゴリズマー養成講座：トップクラスだけが知る「このアルゴリズムがすごい」――「探索」基礎最速マスター (3/4)](http://www.itmedia.co.jp/enterprise/articles/1002/06/news001_3.html)を見てください。

問題
----

- [AIZU ONLINE JUDGE 0181 Persistence](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0181)
  - f(w) を「幅wの本棚に本が入りきるなら1、入らないなら0」という関数とすると、f(w)は単調非減少な関数となります。
    この関数に対して二分探索を適用できます。
