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

	if (now < lastNow) {
		nextHeatOn = 0;
		nextHeatOff = 0;
	}
	lastNow = now;

	if (Heater.isOn()) {
		nextFanOff = now + FanTick;
	}
	// fan is controlled separatly
	if (now < nextFanOff) {
		Fan.on();
	} else if (Fan.isOn()){
		this->debug("Fan off", *t, *h);
		Fan.off();
		Heater.off();
	}

	*t = dht->readTemperature();
	*h = dht->readHumidity();
	if (isnan(*h) || isnan(*t)) {
		// failure from sensor
		this->debug("Faulty sensor", *t, *h);
		Heater.off();
		nextFanOff = now + FanTick * 10;
		nextHeatOn = now + FanTick * 30;
		nextHeatOff = now + FanTick *10;	
		return false;
	}

	if (DeathMax < (*t)) {
		this->debug("Death temperature", *t, *h);
		Heater.off();
		nextFanOff = now + FanTick * 10;
		nextHeatOn = now + FanTick * 30;
		nextHeatOff = now + FanTick *10;
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

	if (max <= (*t)) { // too high
		Heater.off();
		this->debug("Over heating", *t, *h);
		nextFanOff = now + FanTick;
		return true;
	}
	if ((min <= (*t)) && ((*t) < max)) {
		Heater.off();
		this->debug("Target reached", *t, *h);
		return true;
	}

	// off period
	if ((*t) < min && nextHeatOff <= now && Heater.isOn()) {
		Heater.off();
		this->debug("Heater off", *t, *h);
		nextHeatOn = now + offTick(*t, min);
		nextHeatOff = nextHeatOn + onTick(*t, min);
		return true;
	}

	// on period
	if ((*t) < min && nextHeatOn <= now && !Heater.isOn()) {
		Fan.on();
		delay(100);
		Heater.on();
		nextHeatOff = now + onTick(*t, min);
		nextHeatOn = nextHeatOff + offTick(*t, min);
		this->debug("Heater & fan on", *t, *h);
		return true;
	}
	return true;
}

uint32_t ProofBoxClass::onTick(float current, float target) {
	float t = target - current;
	t = t < 0 ? 0 : t;
	return round(pow(HeatOnTickBase, t / 10) * HeatOnTickAdjust);
}

uint32_t ProofBoxClass::offTick(float current, float target) {
	float t = target - current;
	t = t < 0 ? 0 : t; 
	return round(pow(HeatOffTickBase, -t / 10) * HeatOffTickAdjust);
}

uint8_t ProofBoxClass::next() {
	program ++;
	if (program > StateProof2) program = StateOff;
	EEPROM.write(0, program);
	return program;
}

void ProofBoxClass::debug(const char* msg, float t, float h) {
	debug(msg, t, h, true);
}

void ProofBoxClass::debug(const char* msg, float t, float h, bool cached) {
	if (cached) {
		if ((strcmp(msg, lastMsg) == 0) && ((t - lastT) < 0.00001) &&
				((h - lastH) < 0.00001)) {
			return;
		}
		lastT = t;
		lastH = h;
		lastMsg = msg;
	}

	char buf[16];
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
