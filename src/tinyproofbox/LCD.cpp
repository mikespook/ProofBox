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

void LCDClass::output(float t, float h) {
	char tmp[17];
	char tstr[6];
	char hstr[6];
	dtostrf(t, 4, 2, tstr);
	dtostrf(h, 4, 2, hstr);	
	setCursor(0,1);
	sprintf(tmp, "%s%cC / %s%%", tstr, 0xDF, hstr);
	print(tmp);
}

void LCDClass::output(const char* text) {
	setCursor(0,0);
	print(text);
}

void LCDClass::error() {
	setCursor(0,1);
	print("--.--");
	print((char)0xDF);
	print("C / ");
	print("--.--%");	
}

void LCDClass::holding(uint8_t c) {
	if ((Columns - 1) == c) clear();
	setCursor(0, 0);
	print("Holding...");
	setCursor(Columns - c - 1, 1);
	print((char)0x3E);
}
