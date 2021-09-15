#include "ProofBox.h"

ProofBoxClass::ProofBoxClass() {
	_dht = new DHT(PinDHT, DHT11);
}

void ProofBoxClass::loop(float *t, float *h) {
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
	*t = _dht->readTemperature();
	if (*t < min) {
		Fan.on();
		Heater.on();
		_nextHeatOff = now + HeatTick;
		_nextFanOff = _nextHeatOff + FanTick;
		return;
	}
	Heater.off();
	if (*t > max) {
		_nextFanOff += FanTick;
	}
}

void ProofBoxClass::_off() {
	_nextHeatOff = millis() - HeatTick;
	Heater.off();
	_nextFanOff += FanTick; 
}

uint8_t ProofBoxClass::next() {
	_program ++;
	if (_program > StateProof2) _program = StateOff;
	return _program;
}
