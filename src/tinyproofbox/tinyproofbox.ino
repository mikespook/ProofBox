#include <avr/wdt.h>

#include "ProofBox.h"
#include "Button.h"
#include "Buzzer.h"
#include "LCD.h"

#define SERIAL_SPEED 115200

float t, h;

void setup() {
	Serial.begin(SERIAL_SPEED);
	while(!Serial) {}
	Serial.println();
	Serial.print("Serial speed: ");
	Serial.println(SERIAL_SPEED);
	Button.begin();
	Buzzer.begin();
	Buzzer.on();
	LCD.begin();
	LCD.clear();
	LCD.backlight();
	delay(100);
	ProofBox.begin();
	state(ProofBox.current());
	delay(2000);
	wdt_enable(WDTO_500MS);
}

void state(int n) {
	char text[17];
	switch(n) {
		case 0:
			sprintf(text, "Off  [520.co.nz]");
			break;
		case 1:
			sprintf(text, "Starter[%d-%d%cC]", ProofBoxClass::StarterMin, ProofBoxClass::StarterMax, 0xDF);	
			break;
		case 2:
			sprintf(text, "Proof1 [%d-%d%cC]", ProofBoxClass::Proof1Min, ProofBoxClass::Proof1Max, 0xDF);	
			break;
		case 3:
			sprintf(text, "Proof2 [%d-%d%cC]", ProofBoxClass::Proof2Min, ProofBoxClass::Proof2Max, 0xDF);
			break;
	}
	LCD.output(text);
}

void loop() {
	LCD.autoBacklight();
	while (Button.pressed()) {
		// turn on LCD
		LCD.backlight();
		uint8_t c = Button.countdown();
		if (0 == c) {
			switch(ProofBox.next()) {
				case 0:
					Buzzer.off();
					break;
				case 1:
					Buzzer.starter();
					break;
				case 2:
					Buzzer.proof1();
					break;
				case 3:
					Buzzer.proof2();
					break;
			}
			Button.ended();
			break;
		}
		LCD.holding(c);
		wdt_reset();
	}
	state(ProofBox.current());
	if (ProofBox.loop(&t, &h)) {
		LCD.output(t, h);
	} else {
		LCD.error();
	}
	wdt_reset();
}
