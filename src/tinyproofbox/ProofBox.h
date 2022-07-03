#ifndef TPB_PB_H
#define TPB_PB_H

#include <DHT.h>
#include <EEPROM.h>
#include "Relay.h"

class ProofBoxClass {
	public:
		const static uint8_t StateOff = 0;
		const static uint8_t StateStarter = 1;
		const static uint8_t StateProof1 = 2;
		const static uint8_t StateProof2 = 3;

		const static uint8_t StarterMin = 21;
		const static uint8_t StarterMax = 23;

		const static uint8_t Proof1Min = 26;
		const static uint8_t Proof1Max = 28;

		const static uint8_t Proof2Min = 36;
		const static uint8_t Proof2Max = 38;

		const static uint8_t DeathMax = 40;

		ProofBoxClass() {};

		bool loop(float *t, float *h);
		void begin();
		uint8_t next();
		uint8_t current() {
			return program;
		};
	private:
		const static uint8_t PinDHT = 4;

		const static float HeatOnTickBase = 1.5;	
		const static uint16_t HeatOnTickAdjust = 3000;
		const static float HeatOffTickBase = 5;		
		const static uint16_t HeatOffTickAdjust = 3000;
		const static uint16_t FanTick = 60000;

		uint64_t lastRead;

		//
		uint32_t nextHeatOn = 0;
		uint32_t nextHeatOff = 0;
		//
		uint32_t nextFanOff = 0;
		//
		uint32_t lastNow = 0;

		uint8_t program = StateOff;

		DHT *dht;

		float lastT;
		float lastH;
		char * lastMsg;

		uint32_t offTick(float current, float target);
		uint32_t onTick(float current, float target);

		void debug(const char*, float t, float h);
		void debug(const char*, float t, float h, bool cached);
};

static ProofBoxClass ProofBox;
#endif
