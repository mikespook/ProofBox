#include "Relay.h"

RelayClass::RelayClass(int pin) {
	_pin = pin;
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
}

void RelayClass::on() {
	digitalWrite(_pin, LOW);
	Serial.print(_pin);
	Serial.println(" is on");
}

void RelayClass::off() {
	digitalWrite(_pin, HIGH);  
	Serial.print(_pin);
	Serial.println(" is off");
}
