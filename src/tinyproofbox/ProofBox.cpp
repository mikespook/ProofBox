#include "ProofBox.h"

void ProofBoxClass::begin() {
	int now = millis();
	dht = new DHT(PinDHT, DHT11);
	dht->begin();
	program = EEPROM.read(0);
	dht->readTemperature();
	dht->readHumidity();
}

bool ProofBoxClass::loop(float *t, float *h) {
	uint32_t now = millis();

	if (Heater.isOn()) {
		nextFanOff = now + FanTick;
	}

	*t = dht->readTemperature();
	*h = dht->readHumidity();
	if (isnan(*h) || isnan(*t)) {
		// failure from sensor
		if (Heater.isOn()) {
			Serial.println("Heater off: faulty sensor");
		}
		Heater.off();
		return false;
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
			Heater.off();
			return true;
	}
	// fan is controlled separatly
	if (nextFanOff > now) {
		Fan.on();
	} else {
		if (Fan.isOn()) {
			Serial.println("Fan off");
		}
		Fan.off();
	}
	if ((*t) < min) {
		if (Heater.isOn()) {
			if (nextHeatOff <= now) {
				Heater.off();
				nextHeatOn = now + HeatOffTick;
				Serial.println("Heater off: heating loop");
			}		
		} else if (nextHeatOn <= now) {
			Heater.on();
			Fan.on();
			nextHeatOff = now + HeatOnTick;
			Serial.println("Heater & fan on: heating loop");
		}
	} else {
		if (Heater.isOn()) {
			Heater.off();
			Serial.println("Heater off: target hit");
		}
	}
	if (*t >= max) {
		if (Heater.isOn()) {
			Heater.off();
			Serial.println("Heater off: over heating");
		}
		nextFanOff += FanTick;
	}
	return true;
}

uint8_t ProofBoxClass::next() {
	program ++;
	if (program > StateProof2) program = StateOff;
	EEPROM.write(0, program);
	return program;
}
