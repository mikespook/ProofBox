#ifndef TPB_BUTTON_H
#define TPB_BUTTON_H

#include <Arduino.h>

class ButtonClass {
	const static uint8_t Pin = 2;
	const static uint16_t Tick = 50;

	public:
		const static uint8_t Count = 16;

		void begin();
		void onChange();
		bool pressed();
		uint8_t countdown();
	private:
		uint8_t count = Count;
};

static ButtonClass Button;
#endif
