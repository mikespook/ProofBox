#include "Button.h"

void ButtonClass::setup() {
	button = this;
	pinMode(Pin, INPUT_PULLUP);

	attachInterrupt(digitalPinToInterrupt(Pin),	ButtonOnChange, CHANGE);
	
	_pressed = millis(); 
	_count = Count;
}

void ButtonClass::onChange() {
	_pressed = LOW == digitalRead(Pin);
	if (!_pressed) {
		_count = Count;
	}	
}

bool ButtonClass::pressed() {
	return _pressed;
}

uint8_t ButtonClass::countdown() {
	delay(Tick);
	_count--;
	if (0 == _count) {
		_count = Count;
		return 0;
	}
	return _count;
}

void ButtonOnChange() {
	button->onChange();
}
