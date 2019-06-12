#ifndef TWO_SIN_H
#define TWO_SIN_H

/* Usage - two_sin();
 *
 * Loads of variables to play with
 * 
 */




void two_sin(bool old) {                                                              // This is the heart of this_ program. Sure is short.
	mode_number = 48;
	if (old) {
		if (old_this_dir == 0) { old_this_phase += old_this_speed; old_that_phase += old_that_speed; }
		else { old_this_phase -= old_this_speed; old_that_phase -= old_that_speed; }

		old_this_hue = old_this_hue + old_this_rot;                                                // Hue rotation is fun for this_wave.
		old_that_hue = old_that_hue + old_that_rot;                                                // It's also fun for that_wave.

		for (int k = 0; k < NUM_LEDS - 1; k++) {
			int old_this_bright = qsuba(cubicwave8((k*old_all_freq) + old_this_phase), old_this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int old_that_bright = qsuba(cubicwave8((k*old_all_freq) + 128 + old_that_phase), old_that_cutoff); // This wave is 180 degrees out of phase (with the value of 128).

			old_leds[k] = CHSV(old_this_hue, old_this_sat, old_this_bright);                              // Assigning hues and brightness to the led array.
			old_leds[k] += CHSV(old_that_hue, old_this_sat, old_that_bright);

		}
	}
	else {
		if (this_dir == 0) { this_phase += this_speed; that_phase += that_speed; }
		else { this_phase -= this_speed; that_phase -= that_speed; }

		this_hue = this_hue + this_rot;                                                // Hue rotation is fun for this_wave.
		that_hue = that_hue + that_rot;                                                // It's also fun for that_wave.

		for (int k = 0; k<NUM_LEDS - 1; k++) {
			int this_bright = qsuba(cubicwave8((k*all_freq) + this_phase), this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int that_bright = qsuba(cubicwave8((k*all_freq) + 128 + that_phase), that_cutoff); // This wave is 180 degrees out of phase (with the value of 128).

			cur_leds[k] = CHSV(this_hue, this_sat, this_bright);                              // Assigning hues and brightness to the led array.
			cur_leds[k] += CHSV(that_hue, this_sat, that_bright);

		}
	}
} // two_sin()


void two_sin_ring(bool old) {                                                              // This is the heart of this_ program. Sure is short.
	mode_number = 49;
	if (old) {
		if (old_this_dir == 0) { old_this_phase += old_this_speed; old_that_phase += old_that_speed; }
		else { old_this_phase -= old_this_speed; old_that_phase -= old_that_speed; }

		old_this_hue = old_this_hue + old_this_rot;                                                // Hue rotation is fun for this_wave.
		old_that_hue = old_that_hue + old_that_rot;                                                // It's also fun for that_wave.

		for (int k = 0; k < STRIP_LENGTH - 1; k++) {
			int old_this_bright = qsuba(cubicwave8((k*old_all_freq) + old_this_phase), old_this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int old_that_bright = qsuba(cubicwave8((k*old_all_freq) + 128 + old_that_phase), old_that_cutoff); // This wave is 180 degrees out of phase (with the value of 128).

			ringCHSV(old, k, old_this_hue, old_this_sat, old_this_bright);
			ringCHSVAdd(old, k, old_that_hue, old_this_sat, old_that_bright);

		}
	}
	else {
		if (this_dir == 0) { this_phase += this_speed; that_phase += that_speed; }
		else { this_phase -= this_speed; that_phase -= that_speed; }

		this_hue = this_hue + this_rot;                                                // Hue rotation is fun for this_wave.
		that_hue = that_hue + that_rot;                                                // It's also fun for that_wave.

		for (int k = 0; k < STRIP_LENGTH - 1; k++) {
			int this_bright = qsuba(cubicwave8((k*all_freq) + this_phase), this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int that_bright = qsuba(cubicwave8((k*all_freq) + 128 + that_phase), that_cutoff); // This wave is 180 degrees out of phase (with the value of 128).

			ringCHSV(old, k, this_hue, this_sat, this_bright);
			ringCHSVAdd(old, k, that_hue, this_sat, that_bright);

		}
	}
} // two_sin_ring()

void two_sin_pal_ring(bool old) {                                                              // This is the heart of this_ program. Sure is short.
	mode_number = 50;
	if (old) {
		if (old_this_dir == 0) { old_this_phase += old_this_speed; old_that_phase += old_that_speed; }
		else { old_this_phase -= old_this_speed; old_that_phase -= old_that_speed; }

		old_this_hue = old_this_hue + old_this_rot;                                                // Hue rotation is fun for this_wave.
		old_that_hue = old_that_hue + old_that_rot;                                                // It's also fun for that_wave.

		for (int k = 0; k < STRIP_LENGTH - 1; k++) {
			int old_this_bright = qsuba(cubicwave8((k * old_all_freq) + old_this_phase), old_this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int old_that_bright = qsuba(cubicwave8((k * old_all_freq) + 128 + old_that_phase), old_that_cutoff); // This wave is 180 degrees out of phase (with the value of 128).

			ringCHSV(old, k, old_this_hue, old_this_sat, old_this_bright);
			ringPaletteAdd(1, k, old_palette, old_that_hue, old_that_bright, current_blending);
			//ringCHSVAdd(old, k, old_that_hue, old_this_sat, old_that_bright);

		}
	}
	else {
		if (this_dir == 0) { this_phase += this_speed; that_phase += that_speed; }
		else { this_phase -= this_speed; that_phase -= that_speed; }

		this_hue = this_hue + this_rot;                                                // Hue rotation is fun for this_wave.
		that_hue = that_hue + that_rot;                                                // It's also fun for that_wave.

		for (int k = 0; k < STRIP_LENGTH - 1; k++) {
			int this_bright = qsuba(cubicwave8((k * all_freq) + this_phase), this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int that_bright = qsuba(cubicwave8((k * all_freq) + 128 + that_phase), that_cutoff); // This wave is 180 degrees out of phase (with the value of 128).

			ringCHSV(old, k, this_hue, this_sat, this_bright);
			ringPaletteAdd(0, k, current_palette, that_hue, that_bright, current_blending);
			//ringCHSVAdd(old, k, that_hue, this_sat, that_bright);

		}
	}
} // two_sin_pal_ring()
#endif
