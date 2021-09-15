#include "Buzzer.h"

void BuzzerClass::setup() {
	pinMode(Pin, OUTPUT);
}

void BuzzerClass::starter() {
  tone(Pin, NoteE, Tick);
  delay(Tick);  
  tone(Pin, NoteC, Tick);
  delay(Tick);  
  tone(Pin, NoteE, Tick);  
  delay(Tick);  
  tone(Pin, NoteG, Tick); 
}

void BuzzerClass::proof1() {
  tone(Pin, NoteC, Tick);
  delay(Tick);  
  tone(Pin, NoteE, Tick);
  delay(Tick);  
  tone(Pin, NoteG, Tick);  
}

void BuzzerClass::proof2() {
  tone(Pin, NoteD, Tick);
  delay(Tick);  
  tone(Pin, NoteF, Tick);
  delay(Tick);  
  tone(Pin, NoteA, Tick);  
}

void BuzzerClass::on() {
  tone(Pin, NoteC, Tick);
  delay(Tick);  
  tone(Pin, NoteG, Tick);
}

void BuzzerClass::off() {
  tone(Pin, NoteG, Tick);
  delay(Tick);  
  tone(Pin, NoteC, Tick);
}

void BuzzerClass::exceeded() {
  tone(Pin, NoteA, Tick); 
  delay(Tick);
}
