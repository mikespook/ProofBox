#ifndef TPB_PB_H
#define TPB_PB_H

#include <DHT.h>
#include "config.h"
#include "Button.h"
#include "Relay.h"

class ProofBoxClass {
	public:
		ProofBoxClass();
		void loop();
		void next();
	private:
		const static int StarterMin = 21;
		const static int StarterMax = 23;

		const static int Proof1Min = 26;
		const static int Proof1Max = 28;

		const static int Proof2Min = 36;
		const static int Proof2Max = 38;

		const static uint8_t StateOff = 0;
		const static uint8_t StateStarter = 1;
		const static uint8_t StateProof1 = 2;
		const static uint8_t StateProof2 = 3;	

		int _nextHeatOff = 0;
		int _nextFanOff = 0;

		uint8_t _program = StateOff;

		DHT *_dht;

		void _off();
};

static ProofBoxClass ProofBox;
#endif
