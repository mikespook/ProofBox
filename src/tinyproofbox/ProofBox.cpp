#include "ProofBox.h"

void ProofBoxClass::begin() {
	dht = new DHT(PinDHT, DHT11);
	dht->begin();
	program = EEPROM.read(0);
	dht->readTemperature();
	dht->readHumidity();
}

bool ProofBoxClass::loop(float *t, float *h) {
	int now = millis();
	*t = dht->readTemperature();
	*h = dht->readHumidity();
	if (isnan(*h) || isnan(*t)) {
		Heater.off();
		Fan.off();
    	return false;
	}	
	if (nextHeatOff < now) {
		Heater.off();
	}
	if (nextFanOff < now) {
		Fan.off();
	}
	float min, max;
	switch(program) {
		case StateStarter:
			min = StarterMin;
			max = StarterMax;
			break;
		case StateProof1:
			min = Proof1Min;
			max = Proof1Max;
			break;
		case StateProof2:
			min = Proof2Min;
			max = Proof2Max;
			break;
		default:
			off();
			return true;
	}
	if (*t < min) {
		Fan.on();
		Heater.on();
		nextHeatOff = now + HeatTick;
		nextFanOff = nextHeatOff + FanTick;
		return true;
	}
	Heater.off();
	if (*t > max) {
		nextFanOff += FanTick;
	}
	return true;
}

void ProofBoxClass::off() {
	nextHeatOff = millis() - HeatTick;
	Heater.off();
	nextFanOff += FanTick; 
}

uint8_t ProofBoxClass::next() {
	program ++;
	if (program > StateProof2) program = StateOff;
	EEPROM.write(0, program);
	return program;
}
