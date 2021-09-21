#include "LCD.h"

LCDClass::LCDClass():LCD_I2C(0x27) {}

void LCDClass::backlight(void) {
	lastBacklightOn = millis();
	LCD_I2C::backlight();
}
	

void LCDClass::autoBacklight(void) {
	if (lastBacklightOn != 0 && (MaxBacklightOn < (millis() - lastBacklightOn))) {
		noBacklight();
		lastBacklightOn = 0;
	}
}

void LCDClass::output(char* text, float t, float h) {
	// turn off LCD if over LCD::MaxBacklightOn sec
	autoBacklight();
	if ((lastOutput != 0 && (OutputTick < (millis() - lastOutput))) ||
			(lastT - t) != 0 || (lastH - h) != 0) {
		clear();
		setCursor(0,0);
		print(text);
		setCursor(0,1);
		if (isnan(t)) {
			print("--.--");
		} else {
			print(t);
		}
		print((char)0xDF);
		print("C/");
		if (isnan(h)) {
			print("--.--");
		} else {
			print(h);
		}
		print("%");
		lastOutput = millis();
		lastT = t;
		lastH = h;
	}
}

void LCDClass::output(uint8_t c) {
	if ((Columns - 1) == c) clear();
	setCursor(0, 0);
	print("Holding...");
	setCursor(Columns - c - 1, 1);
	print((char)0x3E);
}
