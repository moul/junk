package main

import "github.com/deanishe/awgo"

func main() {
     wf := aw.New()
     wf.Run(func() {
         wf.NewItem("First result!")
	 wf.SendFeedback()
     })
}