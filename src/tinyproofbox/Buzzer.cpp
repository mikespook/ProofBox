#include "Buzzer.h"

const uint16_t BuzzerClass::Starter[] = {NoteC, NoteE, NoteG, NoteG};
const uint16_t BuzzerClass::Proof1[] = {NoteD, NoteF, NoteA, NoteA};
const uint16_t BuzzerClass::Proof2[] = {NoteE, NoteG, NoteB, NoteB};
const uint16_t BuzzerClass::On[] = {NoteC, NoteG};
const uint16_t BuzzerClass::Off[] = {NoteG, NoteC};
const uint16_t BuzzerClass::Exceeded[] = {NoteA};
	

void BuzzerClass::begin() {
	pinMode(Pin, OUTPUT);
}

void BuzzerClass::starter() {
	play(Starter, *(&Starter+1)-Starter);
}

void BuzzerClass::proof1() {
	play(Proof1, *(&Proof1+1)-Proof1);
}

void BuzzerClass::proof2() {
	play(Proof2, *(&Proof2+1)-Proof2);
}

void BuzzerClass::on() {
	play(On, *(&On+1)-On);
}

void BuzzerClass::off() {
	play(Off, *(&Off+1)-Off);
}

void BuzzerClass::exceeded() {
	play(Exceeded, *(&Exceeded+1)-Exceeded);
}
