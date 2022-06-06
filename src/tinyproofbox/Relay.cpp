#include "Relay.h"

RelayClass::RelayClass(int pin) {
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	_state = LOW;
}

void RelayClass::on() {
	digitalWrite(_pin, HIGH);
	_state = HIGH;
}

void RelayClass::off() {
	digitalWrite(_pin, LOW);  
	_state = LOW;
}

bool RelayClass::isOn() {
	return _state == HIGH;
}
