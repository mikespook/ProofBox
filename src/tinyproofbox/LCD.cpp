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
