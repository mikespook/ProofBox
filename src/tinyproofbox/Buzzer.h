#ifndef TPB_BUZZER_H
#define TPB_BUZZER_H

#include <Arduino.h>

class BuzzerClass {
	const static uint8_t Pin = 10;
	const static uint16_t Tick = 200;

	const static uint16_t NoteC = 262;
	const static uint16_t NoteD = 294;
	const static uint16_t NoteE = 330;
	const static uint16_t NoteF = 349;
	const static uint16_t NoteG = 392;
	const static uint16_t NoteA = 440;
	const static uint16_t NoteB = 494;
	
	public:
		void setup();
		void starter();
		void proof1();
		void proof2();
		void on();
		void off();
		void exceeded();
};

static BuzzerClass Buzzer;
#endif
