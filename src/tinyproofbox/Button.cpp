#include "Button.h"

void ButtonClass::begin() {
	pinMode(Pin, INPUT_PULLUP);
	count = Count;
}

bool ButtonClass::pressed() {
	bool pressed = LOW == digitalRead(Pin);
	end = end && pressed;
	count = pressed ? count : Count;
	return pressed && !end;
}

void ButtonClass::ended() {
	end = true;
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
