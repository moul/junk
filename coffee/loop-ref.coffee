console.log ''
console.log ''
console.log '================================'

callback = (ret) ->
  console.log'ret', ret

func = (a) ->
  for _d in a
    do ->
      d = _d
        #callback d
        setTimeout (-> callback d), 100

func [1...20]
