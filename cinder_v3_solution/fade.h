#ifndef FADE_H
#define FADE_H

void fade(bool old) {
	mode_number = 58;
	if (old) {
		old_this_bright = cubicwave8(old_this_index);
		for (uint16_t i = 0; i < NUM_LEDS; i++) {
			old_leds[i] = CHSV(old_this_hue, old_this_sat, old_this_bright);
		}
		old_this_index++;
	}
	else {
		this_bright = cubicwave8(this_index);
		for (uint16_t i = 0; i < NUM_LEDS; i++) {
			cur_leds[i] = CHSV(this_hue, this_sat, this_bright);
		}
		this_index++;
	}
}


void fade_rainbow(bool old) {
	mode_number = 59;
	if (old) {
		old_this_bright = sin8(old_this_index);
		for (uint16_t i = 0; i < NUM_LEDS; i++) {
			old_leds[i] = CHSV(old_this_hue, old_this_sat, old_this_bright);
		}
		old_this_index++;
		old_this_hue++;
	}
	else {
		this_bright = sin8(this_index);
		for (uint16_t i = 0; i < NUM_LEDS; i++) {
			cur_leds[i] = CHSV(this_hue, this_sat, this_bright);
		}
		this_index++;
		this_hue += this_inc;
	}
}
#endif
