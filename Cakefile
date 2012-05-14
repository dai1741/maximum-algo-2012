fs = require 'fs'
util = require 'util'
exec = (require 'child_process').exec

filename = 'js/maximum-algo'
sourceDir = 'coffee'
files = [
  'coffee/maximum-algo.coffee'
]

logger = (err, stdout, stderr) ->
  throw err if err
  console.log stdout+stderr if stdout or stderr

compiling = no

task 'compile', 'コンパイルします', ->
  return if compiling
  compiling = yes
  
  exec "coffee -cj #{filename}.js #{files.join ' '}", () ->
    logger.apply this, arguments
    exec "uglifyjs #{filename}.js > #{filename}.min.js", () ->
      logger.apply this, arguments
      compiling = no

task 'watch', 'ファイルに変更があったらコンパイルします', ->
  fs.watch sourceDir, (event, filename) ->
    path = "#{sourceDir}/#{filename}"
    if files.some((f) -> path is f)
      util.log "Changed in #{path}, start compiling"
      invoke 'compile'
    else
      util.log "Change in #{path} ignored"