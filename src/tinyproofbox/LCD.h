#ifndef TPB_LCD_H
#define TPB_LCD_H

#include <Arduino.h>
#include <LCD_I2C.h>

// A4 SDA
// A5 SCL

class LCDClass : public LCD_I2C {
	const static uint16_t MaxBacklightOn = 10 * 1000; // 10s

	uint64_t lastBacklightOn = millis();

	public:
		LCDClass();
		void autoBacklight(void);
		void backlight(void);
};

static LCDClass LCD;

#endif
