#ifndef TPB_LCD_H
#define TPB_LCD_H

#include <Arduino.h>
#include <LCD_I2C.h>

// A4 SDA
// A5 SCL

class LCDClass : public LCD_I2C {
	const static uint8_t Rows = 2;
	const static uint8_t Columns = 16;
	const static uint16_t MaxBacklightOn = 10 * 1000; // 10s
	const static uint16_t OutputTick = 500;

	uint64_t lastBacklightOn = millis();
	uint64_t lastOutput = millis();
	float lastT;
	float lastH;

	public:
		LCDClass();
		void autoBacklight(void);
		void backlight(void);
		void output(char* text, float t, float h);
		void output(uint8_t c);
};

static LCDClass LCD;

#endif
