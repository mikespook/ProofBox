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

		const static int StarterMin = 21;
		const static int StarterMax = 23;

		const static int Proof1Min = 26;
		const static int Proof1Max = 28;

		const static int Proof2Min = 36;
		const static int Proof2Max = 38;

		ProofBoxClass() {};

		bool loop(float *t, float *h);
		void begin();
		uint8_t next();
		uint8_t current() {
			return program;
		};
	private:
		const static uint8_t PinDHT = 4;

		const static uint16_t HeatTick = 1000;
		const static uint16_t FanTick = 3000;

		const static uint16_t ReadGap = 2000;

		uint64_t lastRead;

		int nextHeatOff = 0;
		int nextFanOff = 0;

		uint8_t program = StateOff;

		DHT *dht;

		void off();
};

static ProofBoxClass ProofBox;
#endif
