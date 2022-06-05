#ifndef TPB_RELAY_H
#define TPB_RELAY_H

#include <Arduino.h>

class RelayClass {
	public:
		const static uint8_t PinHeater = 7;
		const static uint8_t PinFan = 8;

		RelayClass(int pin);
		void off();		
		void on();
		bool isOn();
		
	private:
		int _pin;
		int _state;
};

static RelayClass Heater(RelayClass::PinHeater);
static RelayClass Fan(RelayClass::PinFan);

#endif
