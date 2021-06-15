package main

import "context"

// The HandlerFunc type is an adapter to allow the use of
// ordinary functions as Goduino Loop handlers.
type HandlerFunc func(context.Context) (context.Context, error)

// The Goduino struct is a framework to enable semi-adruino style code with context
type Goduino struct {
	// keep ctx to pass to the next handling function
	ctx  context.Context
	init HandlerFunc
	loop HandlerFunc
}

// NewGoduino makes Goduino instance
func NewGoduino(init HandlerFunc, loop HandlerFunc) *Goduino {
	return &Goduino{
		init: init,
		loop: loop,
	}
}

// Init calls InitFunc
func (g *Goduino) Init() (err error) {
	if g.ctx != nil {
		panic("Init() should be called only once")
	}
	g.ctx, err = g.init(context.Background())
	if err != nil {
		return err
	}
	return nil
}

// Loop sync calls LoopFunc
func (g *Goduino) Loop() (err error) {
	for {
		g.ctx, err = g.loop(g.ctx)
		if err != nil {
			break
		}
	}
	return err
}
