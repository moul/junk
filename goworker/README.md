# goworker

```console
$ redis-cli -r 100000 RPUSH resque:queue:hello '{"class":"Hello","args":["hi","there"]}'
```

```console
$ ./goworker -queues=hello
```
