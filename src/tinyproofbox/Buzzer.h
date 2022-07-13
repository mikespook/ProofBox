#ifndef TPB_BUZZER_H
#define TPB_BUZZER_H

#include <avr/wdt.h>
#include <Arduino.h>

class BuzzerClass {
	const static uint8_t Pin = 3;
	const static uint16_t Tick = 200;

	const static uint16_t NoteC = 262;
	const static uint16_t NoteD = 294;
	const static uint16_t NoteE = 330;
	const static uint16_t NoteF = 349;
	const static uint16_t NoteG = 392;
	const static uint16_t NoteA = 440;
	const static uint16_t NoteB = 494;

	const static uint16_t Starter[];
	const static uint16_t Proof1[];
	const static uint16_t Proof2[];
	const static uint16_t On[];
	const static uint16_t Off[];
	const static uint16_t Exceeded[];
	
	void play(uint16_t seq[], size_t l) {
		for(int i = 0; i < l; i++) {
			wdt_reset();
			tone(Pin, seq[i], Tick);
			delay(Tick);
		}
	}

	public:
		void begin();
		void starter();
		void proof1();
		void proof2();
		void on();
		void off();
		void exceeded();
};

static BuzzerClass Buzzer;
#endif
