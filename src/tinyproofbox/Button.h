#ifndef TPB_BUTTON_H
#define TPB_BUTTON_H

#include "config.h"

class ButtonClass {
	public:
		void setup();
		uint8_t countdown();
		bool pressed();
		void onPress();
		void onRelease();
	private:
		uint8_t _count = 0;
		uint64_t _pressed = 0; 
};

static ButtonClass Button;
void buttonPressed();
void buttonReleased();
#endif
