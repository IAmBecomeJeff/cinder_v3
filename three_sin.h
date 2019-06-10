#ifndef THREE_SIN_H
#define THREE_SIN_H

void three_sin_pal(bool old) {
	mode_number = 45;
	if (old) {
		old_wave1 += beatsin8(10, -4, 4);
		old_wave2 += beatsin8(15, -2, 2);
		old_wave3 += beatsin8(12, -3, 3);

		for (int k = 0; k < NUM_LEDS; k++) {
			uint8_t old_tmp = sin8(old_mul1*k + old_wave1) + sin8(old_mul2*k + old_wave2) + sin8(old_mul3*k + old_wave3);
			old_leds[k] = ColorFromPalette(old_palette, old_tmp, 255);
		}
	}
	else {
		wave1 += beatsin8(10, -4, 4);
		wave2 += beatsin8(15, -2, 2);
		wave3 += beatsin8(12, -3, 3);

		for (int k = 0; k<NUM_LEDS; k++) {
			uint8_t tmp = sin8(mul1*k + wave1) + sin8(mul2*k + wave2) + sin8(mul3*k + wave3);
			cur_leds[k] = ColorFromPalette(current_palette, tmp, 255);
		}
	}
} // three_sin_pal()


void three_sin_pal_ring(bool old) {
	mode_number = 46;
	if (old) {
		old_wave1r += beatsin8(10, -4, 4);
		old_wave2r += beatsin8(15, -2, 2);
		old_wave3r += beatsin8(12, -3, 3);

		for (int k = 0; k < 144; k++) {
			uint8_t old_tmp = sin8(old_mul1r*k + old_wave1r) + sin8(old_mul2r*k + old_wave2r) + sin8(old_mul3r*k + old_wave3r);
			ringPalette(1, k, old_palette, old_tmp, 255);
		}
	}else{
		wave1r += beatsin8(10, -4, 4);
		wave2r += beatsin8(15, -2, 2);
		wave3r += beatsin8(12, -3, 3);

		for (int k = 0; k<144; k++) {
			uint8_t tmp = sin8(mul1r*k + wave1r) + sin8(mul2r*k + wave2r) + sin8(mul3r*k + wave3r);
			ringPalette(0, k, current_palette, tmp, 255);
		}
	}
} // three_sin_pal_ring()


#endif
