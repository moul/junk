package main

import (
	"fmt"

	"github.com/benmanns/goworker"
)

var total int

func init() {
	goworker.Register("Hello", helloWorker)
	total = 0
}

func helloWorker(queue string, args ...interface{}) error {
	fmt.Printf("Hello, world! from %s, %v (%d)\n", queue, args, total)
	total++
	return nil
}
