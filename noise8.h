#ifndef NOISE8_H
#define NOISE8_H


void noise8_pal(bool old) {
	mode_number = 23;
	if (old) {
		for (int i = 0; i < NUM_LEDS; i++) {                                      // Just ONE loop to fill up the LED array as all of the pixels change.
			uint8_t old_index = inoise8(i*old_scale, old_dist + i * old_scale) % 255;                  // Get a value from the noise function. I'm using both x and y axis.
			old_leds[i] = ColorFromPalette(old_palette, old_index, 255, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
		}
		old_dist += beatsin8(10, 1, 4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
	}
	else {
		for (int i = 0; i < NUM_LEDS; i++) {                                      // Just ONE loop to fill up the LED array as all of the pixels change.
			uint8_t index = inoise8(i*scale, dist + i * scale) % 255;                  // Get a value from the noise function. I'm using both x and y axis.
			cur_leds[i] = ColorFromPalette(current_palette, index, 255, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
		}
		dist += beatsin8(10, 1, 4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
	}// In some sketches, I've used millis() instead of an incremented counter. Works a treat.
} // noise8_pal()


void noise8_pal_ring(bool old) {
	mode_number = 24;
	if (old) {
		for (int i = 0; i < STRIP_LENGTH; i++) {
			uint8_t old_index = inoise8(i*old_scale2, old_dist2 + i * old_scale2) % 255;
			ringPalette(1, i, old_palette, old_index, 255, LINEARBLEND);
		}
		old_dist2 += beatsin8(10, 1, 4);
	}
	else {
		for (int i = 0; i < STRIP_LENGTH; i++) {
			uint8_t index = inoise8(i*scale2, dist2 + i * scale2) % 255;
			ringPalette(0, i, current_palette, index, 255, LINEARBLEND);
		}
		dist2 += beatsin8(10, 1, 4);
	}
} // noise8_pal_ring()

#endif
