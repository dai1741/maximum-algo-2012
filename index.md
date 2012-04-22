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

{% for post in site.posts reversed %}
- [{{ post.title }}]({{site.baseurl}}{{ post.url }})
{% endfor %}
