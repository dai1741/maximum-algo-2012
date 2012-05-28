---
layout: index
title: 目次
---

講習会資料
==========

[GitHub Pages](http://pages.github.com/)と[jekyll](http://jekyllrb.com/)で資料を作ってみた。
今後もこの形式で資料を用意するかは未定。今後資料を作るのかも未定。

目次
----

完全な目次は[サークルWikiのページ](http://maximum.vc/wiki.cgi?page=%A5%A2%A5%EB%A5%B4%A5%EA%A5%BA%A5%E0%B9%D6%BD%AC%B2%F12012)にあります。

{% for post in site.posts reversed %}
- [{{ post.title }}]({{site.baseurl}}{{ post.url }})
{% endfor %}
