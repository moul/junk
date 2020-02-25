package main

import (
	"fmt"
	"sync"
	"time"
)

func main() {
	// write should never block
	// could have 0 or infinity readers
	// reader order should be preserved (implies writer order should be preserved too)
	// reader should not have "skipped" entries

	// ideas
	// - rotating buffer
	// - inspiration from streaming server

	m := manager{
		in:       make(chan int, 0),
		subs:     make([]chan int, 0),
		finished: make(chan bool, 0),
	}
	go m.start()

	for i := 0; i < 10; i++ {
		m.in <- i
	}

	m.addSub(coolSub("bob"))

	for i := 10; i < 20; i++ {
		m.in <- i
	}

	m.addSub(slowSub("alice"))

	for i := 20; i < 30; i++ {
		m.in <- i
	}

	close(m.in)
	<-m.finished
}

type manager struct {
	in       chan int
	subs     []chan int
	finished chan bool
}

func (m *manager) addSub(ch chan int) {
	m.subs = append(m.subs, ch)
}

func (m *manager) start() {
	for entry := range m.in {
		fmt.Println()
		fmt.Println("manager", entry)
		var wg sync.WaitGroup
		wg.Add(len(m.subs))
		for _, sub := range m.subs {
			go func(sub chan int) {
				defer wg.Done()
				select {
				case sub <- entry:
				case <-time.After(500 * time.Millisecond):
					fmt.Println("too slow unsub")
				}
			}(sub)
		}
		wg.Wait()
	}
	m.finished <- true
}

func coolSub(name string) chan int {
	ch := make(chan int, 0)
	go func() {
		for entry := range ch {
			fmt.Println(name, entry)
		}
	}()
	return ch
}

func slowSub(name string) chan int {
	ch := make(chan int, 0)
	go func() {
		for entry := range ch {
			fmt.Println(name, entry)
			time.Sleep(1000 * time.Millisecond)
		}
	}()
	return ch
}
