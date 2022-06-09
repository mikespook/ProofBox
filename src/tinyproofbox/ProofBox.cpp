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

	if (lastNow > now) {
		nextHeatOn = 0;
		nextHeatOff = 0;
	}

	lastNow = now;

	if (Heater.isOn()) {
		nextFanOff = now + FanTick;
	}

	*t = dht->readTemperature();
	*h = dht->readHumidity();
	if (isnan(*h) || isnan(*t)) {
		// failure from sensor
		if (Heater.isOn()) {
			this->debug("Heater off: faulty sensor");
		}
		Heater.off();
		return false;
	}

	if ((*t) > DeathMax) {
		this->debug("Heater off: death temperature");
		Heater.off();
		nextFanOff = now + FanTick * 10;
		return true;
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
			this->debug("Fan off");
		}
		Fan.off();
	}
	if ((*t) < min) {
		if (Heater.isOn()) {
			if (nextHeatOff <= now) {
				Heater.off();
				nextHeatOn = now + HeatOffTick;
				this->debug("Heater off: heating loop");
			}
		} else if (nextHeatOn <= now) {
			Heater.on();
			Fan.on();
			nextHeatOff = now + HeatOnTick;
			this->debug("Heater & fan on: heating loop");
		}
	} else {
		if (Heater.isOn()) {
			Heater.off();
			this->debug("Heater off: target hit");
		}
	}
	if ((*t) >= max) {
		if (Heater.isOn()) {
			Heater.off();
			this->debug("Heater off: over heating");
		}
		nextFanOff = now + FanTick;
	}
	return true;
}

uint8_t ProofBoxClass::next() {
	program ++;
	if (program > StateProof2) program = StateOff;
	EEPROM.write(0, program);
	return program;
}

void ProofBoxClass::debug(const char* msg) {
	char buf[11];
	sprintf(buf, "%010lu", lastNow);
	Serial.print(buf);
	Serial.print("\t\tHeader: [");
	sprintf(buf, "%010lu", nextHeatOn);
	Serial.print(buf);
	Serial.print("-");	
	sprintf(buf, "%010lu", nextHeatOff);
	Serial.print(buf);
	Serial.print("]\t\tFan: ");
	sprintf(buf, "%010lu", nextFanOff);	
	Serial.print(buf);
	Serial.print("\t\t");
	Serial.println(msg);
}
