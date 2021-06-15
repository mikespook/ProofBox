#include "ProofBox.h"
#include "Button.h"

void setup() {
	Button.setup();
}

void loop() {
	if (Button.pressed()) {
		uint8_t countdown = Button.countdown();
		if (countdown == 0) {
			ProofBox.next();
		}
		delay(10);
		return;
	}
	ProofBox.loop();
}
