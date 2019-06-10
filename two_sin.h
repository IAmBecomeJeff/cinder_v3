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
		if (old_this_dir == 0) { old_this_phase += old_this_speed; old_thatphase += old_thatspeed; }
		else { old_this_phase -= old_this_speed; old_thatphase -= old_thatspeed; }

		old_this_hue = old_this_hue + old_this_rot;                                                // Hue rotation is fun for this_wave.
		old_thathue = old_thathue + old_thatrot;                                                // It's also fun for thatwave.

		for (int k = 0; k < NUM_LEDS - 1; k++) {
			int old_this_bright = qsuba(cubicwave8((k*old_all_freq) + old_this_phase), old_this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int old_thatbright = qsuba(cubicwave8((k*old_all_freq) + 128 + old_thatphase), old_thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).

			old_leds[k] = CHSV(old_this_hue, old_this_sat, old_this_bright);                              // Assigning hues and brightness to the led array.
			old_leds[k] += CHSV(old_thathue, old_this_sat, old_thatbright);

		}
	}
	else {
		if (this_dir == 0) { this_phase += this_speed; thatphase += thatspeed; }
		else { this_phase -= this_speed; thatphase -= thatspeed; }

		this_hue = this_hue + this_rot;                                                // Hue rotation is fun for this_wave.
		thathue = thathue + thatrot;                                                // It's also fun for thatwave.

		for (int k = 0; k<NUM_LEDS - 1; k++) {
			int this_bright = qsuba(cubicwave8((k*all_freq) + this_phase), this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int thatbright = qsuba(cubicwave8((k*all_freq) + 128 + thatphase), thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).

			cur_leds[k] = CHSV(this_hue, this_sat, this_bright);                              // Assigning hues and brightness to the led array.
			cur_leds[k] += CHSV(thathue, this_sat, thatbright);

		}
	}
} // two_sin()


void two_sin_ring(bool old) {                                                              // This is the heart of this_ program. Sure is short.
	mode_number = 49;
	if (old) {
		if (old_this_dir == 0) { old_this_phase += old_this_speed; old_thatphase += old_thatspeed; }
		else { old_this_phase -= old_this_speed; old_thatphase -= old_thatspeed; }

		old_this_hue = old_this_hue + old_this_rot;                                                // Hue rotation is fun for this_wave.
		old_thathue = old_thathue + old_thatrot;                                                // It's also fun for thatwave.

		for (int k = 0; k < STRIP_LENGTH - 1; k++) {
			int old_this_bright = qsuba(cubicwave8((k*old_all_freq) + old_this_phase), old_this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int old_thatbright = qsuba(cubicwave8((k*old_all_freq) + 128 + old_thatphase), old_thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).

			ringCHSV(old, k, old_this_hue, old_this_sat, old_this_bright);
			ringCHSVAdd(old, k, old_thathue, old_this_sat, old_thatbright);

		}
	}
	else {
		if (this_dir == 0) { this_phase += this_speed; thatphase += thatspeed; }
		else { this_phase -= this_speed; thatphase -= thatspeed; }

		this_hue = this_hue + this_rot;                                                // Hue rotation is fun for this_wave.
		thathue = thathue + thatrot;                                                // It's also fun for thatwave.

		for (int k = 0; k < STRIP_LENGTH - 1; k++) {
			int this_bright = qsuba(cubicwave8((k*all_freq) + this_phase), this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int thatbright = qsuba(cubicwave8((k*all_freq) + 128 + thatphase), thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).

			ringCHSV(old, k, this_hue, this_sat, this_bright);
			ringCHSVAdd(old, k, thathue, this_sat, thatbright);

		}
	}
} // two_sin_ring()

void two_sin_pal_ring(bool old) {                                                              // This is the heart of this_ program. Sure is short.
	mode_number = 50;
	if (old) {
		if (old_this_dir == 0) { old_this_phase += old_this_speed; old_thatphase += old_thatspeed; }
		else { old_this_phase -= old_this_speed; old_thatphase -= old_thatspeed; }

		old_this_hue = old_this_hue + old_this_rot;                                                // Hue rotation is fun for this_wave.
		old_thathue = old_thathue + old_thatrot;                                                // It's also fun for thatwave.

		for (int k = 0; k < STRIP_LENGTH - 1; k++) {
			int old_this_bright = qsuba(cubicwave8((k * old_all_freq) + old_this_phase), old_this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int old_thatbright = qsuba(cubicwave8((k * old_all_freq) + 128 + old_thatphase), old_thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).

			ringCHSV(old, k, old_this_hue, old_this_sat, old_this_bright);
			ringPaletteAdd(1, k, old_palette, old_thathue, old_thatbright, current_blending);
			//ringCHSVAdd(old, k, old_thathue, old_this_sat, old_thatbright);

		}
	}
	else {
		if (this_dir == 0) { this_phase += this_speed; thatphase += thatspeed; }
		else { this_phase -= this_speed; thatphase -= thatspeed; }

		this_hue = this_hue + this_rot;                                                // Hue rotation is fun for this_wave.
		thathue = thathue + thatrot;                                                // It's also fun for thatwave.

		for (int k = 0; k < STRIP_LENGTH - 1; k++) {
			int this_bright = qsuba(cubicwave8((k * all_freq) + this_phase), this_cutoff);     // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			int thatbright = qsuba(cubicwave8((k * all_freq) + 128 + thatphase), thatcutoff); // This wave is 180 degrees out of phase (with the value of 128).

			ringCHSV(old, k, this_hue, this_sat, this_bright);
			ringPaletteAdd(0, k, current_palette, thathue, thatbright, current_blending);
			//ringCHSVAdd(old, k, thathue, this_sat, thatbright);

		}
	}
} // two_sin_pal_ring()
#endif
