#ifndef TPB_BUTTON_H
#define TPB_BUTTON_H

#include <Arduino.h>

class ButtonClass {
	const static uint8_t Pin = 3;
	const static uint16_t Tick = 100;
	const static uint8_t Count = 12;

	public:
		void setup();
		void onChange();
		bool pressed();
		uint8_t countdown();
	private:
		uint8_t _count = Count;
		uint64_t _pressed = 0; 
};

static ButtonClass *button;
static ButtonClass Button;

static void ButtonOnChange();
#endif
