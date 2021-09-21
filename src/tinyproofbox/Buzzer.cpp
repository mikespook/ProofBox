#include "Buzzer.h"

const uint16_t BuzzerClass::Starter[] = {NoteE, NoteC, NoteE, NoteG};
const uint16_t BuzzerClass::Proof1[] = {NoteC, NoteE, NoteG, NoteG};
const uint16_t BuzzerClass::Proof2[] = {NoteD, NoteF, NoteA, NoteA};
const uint16_t BuzzerClass::On[] = {NoteC, NoteG};
const uint16_t BuzzerClass::Off[] = {NoteG, NoteC};
const uint16_t BuzzerClass::Exceeded[] = {NoteA};
	

void BuzzerClass::begin() {
	pinMode(Pin, OUTPUT);
}

void BuzzerClass::starter() {
	play(Starter);
}

void BuzzerClass::proof1() {
	play(Proof1);
}

void BuzzerClass::proof2() {
	play(Proof2);
}

void BuzzerClass::on() {
	play(On);
}

void BuzzerClass::off() {
	play(Off);
}

void BuzzerClass::exceeded() {
	play(Exceeded);
}
