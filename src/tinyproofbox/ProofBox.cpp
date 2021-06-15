#include "ProofBox.h"

ProofBoxClass::ProofBoxClass() {
	_dht = new DHT(TPB_DHT_PIN, DHT11);
}

void ProofBoxClass::loop() {
	int now = millis();
	if (_nextHeatOff < now) {
		Heater.off();
	}
	if (_nextFanOff < now) {
		Fan.off();
	}
	float min, max;
	switch(_program) {
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
			_off();
			return;
	}
	float t = _dht->readTemperature();
	if (t < min) {
		Fan.on();
		Heater.on();
		_nextHeatOff = now + TPB_HEAT_TIME;
		_nextFanOff = _nextHeatOff + TPB_FAN_TIME;
		return;
	}
	Heater.off();
	if (t > max) {
		_nextFanOff += TPB_FAN_TIME;
	}
}

void ProofBoxClass::_off() {
	_nextHeatOff = millis() - TPB_HEAT_TIME;
	Heater.off();
	_nextFanOff += TPB_FAN_TIME; 
}

void ProofBoxClass::next() {
	if (_program > 4) _program = StateOff;
	_program ++;
}
