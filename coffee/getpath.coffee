a =
  b:
    c:
      d:
        e: 42
        f: 44
        
paths = ['b', 'b.c', 'b.c.d', 'b.c.d.e', 'b.c.d.f']

        
get = (->
  cache = {}

  get_eval_cache = (obj, path) ->
    cache[path] = eval "obj['#{path.replace /\./g, '\'][\''}']" if not cache[path]?
    cache[path]
  
  get_reduce_cache = (obj, path) ->
    cache[path] = path.split('.').reduce (prev, cur, idx, arr) ->
      if idx == 1 then obj[prev][cur] else prev[cur]
    cache[path]

  get_eval = (obj, path) ->
    eval "obj['#{path.replace /\./g, '\'][\''}']" if not cache[path]?
    
  get_reduce = (obj, path) ->
    path.split('.').reduce (prev, cur, idx, arr) -> if idx == 1 then obj[prev][cur] else prev[cur]
  
  return {
    engines:      ['eval', 'reduce', 'eval_cache', 'reduce_cache']
    eval:         get_eval
    reduce:       get_reduce
    eval_cache:   get_eval_cache
    reduce_cache: get_reduce_cache
  }
)()

for engine in get.engines
  console.time engine
  for path in paths
    #k = "#{engine}-#{path}-#{i}"
    get[engine] a, path for i in [1..100]
  console.timeEnd engine
