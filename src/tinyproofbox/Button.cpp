#include "Button.h"

void ButtonClass::begin() {
	pinMode(Pin, INPUT_PULLUP);
	count = Count;
}

bool ButtonClass::pressed() {
	bool pressed = LOW == digitalRead(Pin);
	count = pressed ? count : Count;
	return pressed;
}

uint8_t ButtonClass::countdown() {
	delay(Tick);
	count--;
	if (0 == count) {
		count = Count;
		return 0;
	}
	return count;
}
