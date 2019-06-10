#ifndef METEORRAIN_H
#define METEORRAIN_H

void meteorRain() {
		if (meteor_index < STRIP_LENGTH + STRIP_LENGTH) {
			for (int j = 0; j < NUM_LEDS; j++) {
				if (meteorRandomDecay) {
					leds[j].fadeToBlackBy(meteorTrailDecay);
				}
			}

			for (int j = 0; j < meteorSize; j++) {
				if ((meteor_index - j < STRIP_LENGTH) && (meteor_index - j >= 0)) {
					ringCRGB(meteor_index - j, meteor_r, meteor_g, meteor_b);
				}
			}
			meteor_index++;
		}
		else {
			meteor_index = 0;
		}
}


#endif
