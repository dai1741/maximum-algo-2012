MAX_HEAD_LENGTH = 20
MIN_HEAD_COUNT = 4

$ ->
  makeList = (->
    indexList = $('<ul/>').appendTo $('.contents-menu')
    prevRank = 1
    (elm, anchorName) ->
      m = elm.tagName.match /h(\d)/i
      return unless m?
      rank = +m[1]
      if prevRank < rank
        for i in [prevRank...rank]
          lastLi = indexList.children 'li:last'
          lastLi = $('<li/>').appendTo(indexList) if lastLi.size() is 0
          indexList = $('<ul/>').appendTo lastLi
      else if rank < prevRank
        indexList = indexList.parent().parent() for i in [rank...prevRank]
      prevRank = rank
      
      text = $(elm).text()
      if text.length > MAX_HEAD_LENGTH + 2
        text = text.slice(0, MAX_HEAD_LENGTH) + '...'
      indexList.append $('<li/>').append($('<a/>').attr(
        href: "##{anchorName}"
      ).text(text))
  )()

  dejavu = {}
  hashString = location.hash.slice 1

  heads = $('h1,h2,h3,h4,h5').each ->
    elm = $ @
    anchorName = elm.text().replace(/\s+/, '-').replace /\?/, ''
    anchorName += "'" while dejavu[anchorName]
    dejavu[anchorName] = yes

    makeList @, anchorName
    
    $('<a/>').addClass('anchor').attr(
      name: anchorName
      id: anchorName  # for IE7
      href: "##{anchorName}"
    ).text('¶').prependTo elm

    if anchorName is hashString
      setTimeout(( -> $('html, body').scrollTop elm.offset().top), 1)

  if heads.size() < MIN_HEAD_COUNT
    $('.contents-menu').remove()

