#ifndef FADE_H
#define FADE_H

void fadein(bool old) {
	mode_number = 55;
	if (old) {
		random16_set_seed(535);
		for (uint16_t i = 0; i < NUM_LEDS; i++) {
			fader = sin8(millis() / random8(10, 20));
			old_leds[i] = ColorFromPalette(old_palette, i * 20, fader, current_blending);
		}
		random16_set_seed(millis());
	}
	else {
		random16_set_seed(535);
		for (uint16_t i = 0; i < NUM_LEDS; i++) {
			fader = sin8(millis() / random8(10, 20));
			cur_leds[i] = ColorFromPalette(current_palette, i * 20, fader, current_blending);
		}
		random16_set_seed(millis());
	}
}

#endif
