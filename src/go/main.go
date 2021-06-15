package main

import (
	"context"
	"machine"
	"time"
)

func main() {
	g := NewGoduino(goduinoInit, goduinoLoop)
	if err := g.Init(); err != nil {
		print(err.Error())
	}
	if err := g.Loop(); err != nil {
		print(err.Error())
	}
}

var led machine.Pin

func goduinoInit(parent context.Context) (ctx context.Context, err error) {
	ctx = context.Background()
	led = machine.LED
	led.Configure(machine.PinConfig{Mode: machine.PinOutput})
	return
}

func goduinoLoop(parent context.Context) (ctx context.Context, err error) {
	led.Low()
	time.Sleep(time.Millisecond * 500)

	led.High()
	time.Sleep(time.Millisecond * 500)

	return
}
