#ifndef TPB_RELAY_H
#define TPB_RELAY_H

#include <Arduino.h>
#include "config.h"

class RelayClass {
	public:
		RelayClass(int pin);
		void off();		
		void on();
		
	private:
		int _pin;
};

static RelayClass Heater(TPB_HEATER_PIN);
static RelayClass Fan(TPB_FAN_PIN);

#endif
