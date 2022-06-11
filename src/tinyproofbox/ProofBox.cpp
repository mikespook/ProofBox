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
	}
	lastNow = now;

	if (Heater.isOn()) {
		nextFanOff = now + FanTick;
		Heater.off();
	}

	*t = dht->readTemperature();
	*h = dht->readHumidity();
	if (isnan(*h) || isnan(*t)) {
		// failure from sensor
		this->debug("Faulty sensor", *t, *h);
		Heater.off();
		return false;
	}

	if ((*t) > DeathMax) {
		this->debug("Death temperature", *t, *h);
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
	} else if (Fan.isOn()){
		this->debug("Fan off", *t, *h);
		Fan.off();
	}
	if ((*t) < min) {
		this->debug("Heater on", *t, *h);	
		Heater.on();
		delay(HeatOnTick);
		Heater.off();
		delay(HeatOffTick);
		this->debug("Heater off", *t, *h);
	} else {
		Heater.off();
		this->debug("Target reached", *t, *h);
	}
	if ((*t) >= max) {
		Heater.off();
		this->debug("Over heating", *t, *h);
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

void ProofBoxClass::debug(const char* msg, float t, float h) {
	if (strcmp(msg, lastMsg) == 0 && (t - lastT) < 0.001 &&
			(h - lastH) < 0.001) {
		return;
	}
	lastT = t;
	lastH = h;
	lastMsg = msg;

	char buf[11];
	sprintf(buf, "%010lu", lastNow);
	Serial.print(buf);
	Serial.print("\tHeader on at: ");
	sprintf(buf, "%010lu", nextHeatOn);
	Serial.print(buf);
	Serial.print("\tFan off at: ");
	sprintf(buf, "%010lu", nextFanOff);	
	Serial.print(buf);
	Serial.print("\tT: ");
	Serial.print(t);
	Serial.print("°C\tH: ");
	Serial.print(h);
	Serial.print("%\t");
	Serial.println(msg);
}
