#include "ProofBox.h"
#include "Button.h"
#include "Buzzer.h"
#include "LCD.h"

#define SERIAL_SPEED 115200

void setup() {
	Serial.begin(SERIAL_SPEED);
	while(!Serial) {}
	Serial.println(SERIAL_SPEED);
	Button.begin();
	Buzzer.begin();
	Buzzer.on();
	LCD.begin();
	LCD.clear();
	LCD.backlight();
	delay(500);
	ProofBox.begin();
	switch(ProofBox.current()) {
		case 0:
			Serial.println("Off");
			Buzzer.off();
			break;
		case 1:
			Serial.println("Starter");	
			Buzzer.starter();
			break;
		case 2:
			Serial.println("Proof1");	
			Buzzer.proof1();
			break;
		case 3:
			Serial.println("Proof2");
			Buzzer.proof2();	
			break;
	}
}


float t, h;

void loop() {
	char step[17];
	if (Button.pressed()) {
		// turn on LCD
		LCD.backlight();
		uint8_t c = Button.countdown();
		Serial.println(c);
		LCD.output(c);
		if (0 == c) {
			uint8_t n = ProofBox.next();
			switch(n) {
				case 0:
					sprintf(step, "Off    520.co.nz");
					Serial.println("Off");
					Buzzer.off();
					break;
				case 1:
					sprintf(step, "Starter %d-%d%cC", ProofBoxClass::StarterMin, ProofBoxClass::StarterMax, 0xDF);	
					Serial.println("Starter");	
					Buzzer.starter();
					break;
				case 2:
					sprintf(step, "Proof1 %d-%d%cC", ProofBoxClass::Proof1Min, ProofBoxClass::Proof1Max, 0xDF);	
					Serial.println("Proof1");	
					Buzzer.proof1();
					break;
				case 3:
					sprintf(step, "Proof2 %d-%d%cC", ProofBoxClass::Proof2Min, ProofBoxClass::Proof2Max, 0xDF);
					Serial.println("Proof2");
					Buzzer.proof2();	
					break;
			}
		}
		return;
	}
	ProofBox.loop(&t, &h);
	LCD.output(step, t, h);
}
