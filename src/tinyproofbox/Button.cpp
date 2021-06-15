#include "Button.h"

void ButtonClass::setup() {
	pinMode(TPB_BUTTON_PIN, INPUT_PULLUP);

	attachInterrupt(digitalPinToInterrupt(TPB_BUTTON_PIN),
			buttonPressed, FALLING);
	attachInterrupt(digitalPinToInterrupt(TPB_BUTTON_PIN),
			buttonReleased, RISING);
}

uint8_t ButtonClass::countdown() {
	return _count--;
}

bool ButtonClass::pressed() {
	return _pressed != 0;
}

void ButtonClass::onRelease() {
	_pressed = 0;
}

void ButtonClass::onPress() {
	_pressed = millis();
}

void buttonPressed() {
	Button.onPress();
}

void buttonReleased() {
	Button.onRelease();
}
