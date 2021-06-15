#include "Relay.h"

RelayClass::RelayClass(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void RelayClass::on() {
  digitalWrite(_pin, HIGH);  
}

void RelayClass::off() {
  digitalWrite(_pin, LOW);  
}
