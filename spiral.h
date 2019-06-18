#ifndef SPIRAL_H
#define SPIRAL_H




// spiral_sin()
// start_index = 0
// this_inc = 1
// freq = 6
// this_rot = 1

void spiral_sin(bool old) {
	mode_number = 37;
	if (old) {
		fill_solid(old_leds, NUM_LEDS, CRGB(0, 0, 0));
		old_start_index += old_this_inc;
		old_this_index = old_start_index;
		old_this_phase += old_this_speed;
		for (int k = 0; k < STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			for (int r = 0; r < 4; r++) {
				int old_spiral_bri = qsuba(scale8(cubicwave8((k*old_all_freq) + r * 64 + old_this_phase), 120), 85);
				old_leds[ringArray[k][r]] = ColorFromPalette(old_palette, old_this_index + k * old_this_inc, old_spiral_bri, current_blending);
			}
			old_this_index += old_this_rot;
		}
	}
	else {
		fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
		start_index += this_inc;
		this_index = start_index;
		this_phase += this_speed;
		for (int k = 0; k < STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			for (int r = 0; r < 4; r++) {
				int spiral_bri = qsuba(scale8(cubicwave8((k*all_freq) + r * 64 + this_phase), 120), 85);
				cur_leds[ringArray[k][r]] = ColorFromPalette(current_palette, this_index + k * this_inc, spiral_bri, current_blending);
			}
			this_index += this_rot;
		}
	}
}

void spiral_sin_sub(bool old) {
	mode_number = 38;
	if (old) {
		fill_solid(old_leds, NUM_LEDS, CRGB(0, 0, 0));
		old_start_index += old_this_inc;
		old_this_index = old_start_index;
		old_this_phase += old_this_speed;
		for (int k = 0; k < STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			for (int r = 0; r < 4; r++) {
				int old_spiral_bri = qsuba(cubicwave8((k*old_all_freq) + r * 64 + old_this_phase) - 192, 0);
				old_leds[ringArray[k][r]] = ColorFromPalette(old_palette, old_this_index + k * old_this_inc, old_spiral_bri, current_blending);
			}
			old_this_index += old_this_rot;
		}
	}else{
		fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
		start_index += this_inc;
		this_index = start_index;
		this_phase += this_speed;
		for (int k = 0; k < STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			for (int r = 0; r < 4; r++) {
				int spiral_bri = qsuba(cubicwave8((k*all_freq) + r * 64 + this_phase) - 192, 0);
				cur_leds[ringArray[k][r]] = ColorFromPalette(current_palette, this_index + k * this_inc, spiral_bri, current_blending);
			}
			this_index += this_rot;
		}
	}
}


void one_sin_spiral(bool old) {
	mode_number = 39;
	if (old) {
		old_start_index += old_this_inc;
		old_this_index = old_start_index;
		if (old_this_dir) {
			old_this_phase += old_this_speed;                                                                     // You can change direction and speed individually.
		}
		else { old_this_phase -= old_this_speed; }
  		for (int k = 0; k < STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
  			int old_this_bright = qsubd(cubicwave8((k*old_all_freq) + old_this_phase), old_this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
  			old_leds[spiralArray[0][k]] = CHSV(old_bg_clr, 255, old_bg_bri);                                                        // First set a background colour, but fully saturated.
  			old_leds[spiralArray[0][k]] += ColorFromPalette(old_palette, old_this_index + k * old_this_inc, old_this_bright, current_blending);
  			old_this_index += old_this_rot;
  		}
	}else{
		start_index += this_inc;
		this_index = start_index;
		if (this_dir) {
			this_phase += this_speed;                                                                     // You can change direction and speed individually.
		}
		else { this_phase -= this_speed; }
		  for (int k = 0; k<STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
  			int this_bright = qsubd(cubicwave8((k*all_freq) + this_phase), this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
  			cur_leds[spiralArray[0][k]] = CHSV(bg_clr, 255, bg_bri);                                                        // First set a background colour, but fully saturated.
  			cur_leds[spiralArray[0][k]] += ColorFromPalette(current_palette, this_index + k * this_inc, this_bright, current_blending);
  			this_index += this_rot;
  		}
    
	}
} // one_sin_spiral()

void helix_spiral(bool old) {
	mode_number = 40;
	if (old) {
		old_start_index += old_this_inc;
		old_this_index = old_start_index;

		if (old_this_dir) {
			old_this_phase += old_this_speed; // You can change direction and speed individually.
			old_that_phase -= old_that_speed;
		}
		else {
			old_this_phase -= old_this_speed;
			old_that_phase += old_that_speed;
		}

		//  for (int k = 0; k<STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
		//    int this_bright = qsubd(cubicwave8((k*all_freq) + this_phase), this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
		//    leds[spiralArray[0][k]] = CHSV(bg_clr, 255, bg_bri);                                                        // First set a background colour, but fully saturated.
		//    leds[spiralArray[0][k]] += ColorFromPalette(current_palette, this_index + k * this_inc, this_bright, current_blending);
		//    this_index += this_rot;
		//  }

		for (int k = 0; k < STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			int old_that_bright = qsubd(cubicwave8((k*old_all_freq) + old_that_phase), old_this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			old_leds[spiralArrayRev[2][k]] = CHSV(old_bg_clr, 255, old_bg_bri);                                                        // First set a background colour, but fully saturated.
			old_leds[spiralArrayRev[2][k]] += ColorFromPalette(old_palette, old_this_index + 64 + k * old_this_inc, old_that_bright, current_blending);
			old_this_index += old_this_rot;
		}
	}
	else {
		start_index += this_inc;
		this_index = start_index;

		if (this_dir) {
			this_phase += this_speed; // You can change direction and speed individually.
			that_phase -= that_speed;
		}
		else {
			this_phase -= this_speed;
			that_phase += that_speed;
		}

		//  for (int k = 0; k<STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
		//    int this_bright = qsubd(cubicwave8((k*all_freq) + this_phase), this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
		//    leds[spiralArray[0][k]] = CHSV(bg_clr, 255, bg_bri);                                                        // First set a background colour, but fully saturated.
		//    leds[spiralArray[0][k]] += ColorFromPalette(current_palette, this_index + k * this_inc, this_bright, current_blending);
		//    this_index += this_rot;
		//  }

		for (int k = 0; k<STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			int that_bright = qsubd(cubicwave8((k*all_freq) + that_phase), this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			cur_leds[spiralArrayRev[2][k]] = CHSV(bg_clr, 255, bg_bri);                                                        // First set a background colour, but fully saturated.
			cur_leds[spiralArrayRev[2][k]] += ColorFromPalette(current_palette, this_index + 64 + k * this_inc, that_bright, current_blending);
			this_index += this_rot;
		}
	}
} // helix_spiral()



void plasma_spiral(bool old) {
	mode_number = 41;
	if (old) {
		old_plasma_phase1 = beatsin8(6, -64, 64);
		old_plasma_phase2 = beatsin8(7, -64, 64);

		for (int k = 0; k < STRIP_LENGTH; k++) {
			old_plasmaIndex = cubicwave8((k * 23) + old_plasma_phase1) / 2 + cos8((k * 15) + old_plasma_phase2) / 2;
			old_plasmaBright = qsuba(old_plasmaIndex, beatsin8(7, 0, 96));

			old_leds[spiralArray[0][k]] = ColorFromPalette(old_palette, old_plasmaIndex, old_plasmaBright, current_blending);
		}
	}else{
		plasma_phase1 = beatsin8(6, -64, 64);
		plasma_phase2 = beatsin8(7, -64, 64);

		for (int k = 0; k < STRIP_LENGTH; k++) {
			plasmaIndex = cubicwave8((k * 23) + plasma_phase1) / 2 + cos8((k * 15) + plasma_phase2) / 2;
			plasmaBright = qsuba(plasmaIndex, beatsin8(7, 0, 96));

			cur_leds[spiralArray[0][k]] = ColorFromPalette(current_palette, plasmaIndex, plasmaBright, current_blending);
		}
	}
} // plasma_spiral()


void plasma_spiral2(bool old) {
	mode_number = 42;
	if (old) {
		old_plasma_phase1 = beatsin8(6, -64, 64);
		old_plasma_phase2 = beatsin8(7, -64, 64);

		for (int k = 0; k < STRIP_LENGTH; k++) {
			old_plasmaIndex = cubicwave8((k * 23) + old_plasma_phase1) / 2 + cos8((k * 15) + old_plasma_phase2) / 2;
			old_plasmaBright = qsuba(old_plasmaIndex, beatsin8(7, 0, 96));

			old_leds[spiralArray[0][k]] = ColorFromPalette(old_palette, old_plasmaIndex, old_plasmaBright, current_blending);
			//leds[spiralArray[1][k]] = ColorFromPalette(current_palette, plasmaIndex, plasmaBright, current_blending);
			old_leds[spiralArray[2][k]] = ColorFromPalette(LavaColors_p, old_plasmaIndex, old_plasmaBright, current_blending);
			//leds[spiralArray[3][k]] = ColorFromPalette(current_palette, plasmaIndex, plasmaBright, current_blending);
		}
	}
	else {
		plasma_phase1 = beatsin8(6, -64, 64);
		plasma_phase2 = beatsin8(7, -64, 64);

		for (int k = 0; k < STRIP_LENGTH; k++) {
			plasmaIndex = cubicwave8((k * 23) + plasma_phase1) / 2 + cos8((k * 15) + plasma_phase2) / 2;
			plasmaBright = qsuba(plasmaIndex, beatsin8(7, 0, 96));

			cur_leds[spiralArray[0][k]] = ColorFromPalette(current_palette, plasmaIndex, plasmaBright, current_blending);
			//leds[spiralArray[1][k]] = ColorFromPalette(current_palette, plasmaIndex, plasmaBright, current_blending);
			cur_leds[spiralArray[2][k]] = ColorFromPalette(LavaColors_p, plasmaIndex, plasmaBright, current_blending);
			//leds[spiralArray[3][k]] = ColorFromPalette(current_palette, plasmaIndex, plasmaBright, current_blending);
		}
	}
} // plasma_spiral()

void spiral_fill_palette(bool old, uint8_t spine, uint8_t startIndex, uint8_t incIndex, CRGBPalette16 pal=current_palette, uint8_t bri = this_bright, TBlendType blending=current_blending){
	mode_number = 43;
	if (old) {
		uint8_t colorIndex = startIndex;
		for (uint16_t i = 0; i < STRIP_LENGTH; i++) {
			old_leds[spiralArray[spine][i]] = ColorFromPalette(pal, colorIndex, bri, blending);
			colorIndex += incIndex;
		}
	}
	else {
		uint8_t colorIndex = startIndex;
		for (uint16_t i = 0; i < STRIP_LENGTH; i++) {
			cur_leds[spiralArray[spine][i]] = ColorFromPalette(pal, colorIndex, bri, blending);
			colorIndex += incIndex;
		}
	}
 }


void palette_spiral(bool old){
	mode_number = 44;
	if (old) {
		if (old_this_dir) {
			old_this_index += old_this_speed;
		}
		else { old_this_index -= old_this_speed; }

		spiral_fill_palette(0, 0, old_this_index, old_this_inc, old_palette, old_this_bright, current_blending);
		spiral_fill_palette(0, 1, old_this_index + 64, old_this_inc, old_palette, old_this_bright, current_blending);
		spiral_fill_palette(0, 2, old_this_index + 128, old_this_inc, old_palette, old_this_bright, current_blending);
		spiral_fill_palette(0, 3, old_this_index + 192, old_this_inc, old_palette, old_this_bright, current_blending);
	}
	else {
		if (this_dir) {
			this_index += this_speed;
		}
		else { this_index -= this_speed; }

		spiral_fill_palette(1, 0, this_index, this_inc, current_palette, this_bright, current_blending);
		spiral_fill_palette(1, 1, this_index + 64, this_inc, current_palette, this_bright, current_blending);
		spiral_fill_palette(1, 2, this_index + 128, this_inc, current_palette, this_bright, current_blending);
		spiral_fill_palette(1, 3, this_index + 192, this_inc, current_palette, this_bright, current_blending);
	}
}



// spiral()
// spiral_start = 0
// spiral_inc = 4
// spiral_width = 1
// this_hue

//void spiral(bool old) {
//	mode_number = 35;
//	if (old) {
//		fill_solid(old_leds, NUM_LEDS, CRGB(0, 0, 0));
//		for (int r_index = 0; r_index < 4; r_index++) {
//			for (int i = old_spiral_start + r_index * old_spiral_width; i < STRIP_LENGTH; i += old_spiral_inc * old_spiral_width) {
//				for (int w = i; w < i + old_spiral_width; w++) {
//					old_leds[ringArray[w % STRIP_LENGTH][r_index]] = CHSV(old_this_hue, old_this_sat, old_this_bright);
//				}
//			}
//		}
//		old_spiral_start += old_spiral_width;
//		if (old_spiral_start > 3 * old_spiral_width) {
//			old_spiral_start = 0;
//		}
//	}
//	else {
//		fill_solid(cur_leds, NUM_LEDS, CRGB(0, 0, 0));
//		for (int r_index = 0; r_index < 4; r_index++) {
//			for (int i = spiral_start + r_index * spiral_width; i < STRIP_LENGTH; i += spiral_inc * spiral_width) {
//				for (int w = i; w < i + spiral_width; w++) {
//					cur_leds[ringArray[w % STRIP_LENGTH][r_index]] = CHSV(this_hue, this_sat, this_bright);
//				}
//			}
//		}
//		spiral_start += spiral_width;
//		if (spiral_start > 3 * spiral_width) {
//			spiral_start = 0;
//		}
//	}
//}
//
//// spiral_pal()
//// spiral_start = 0
//// spiral_inc = 4
//// spiral_width = 1
//// this_inc
//// start_index = 0
//
//void spiral_pal(bool old) {
//	mode_number = 36;
//	if (old) {
//		fill_solid(old_leds, NUM_LEDS, CRGB(0, 0, 0));
//		old_start_index += old_this_inc;
//		old_this_index = old_start_index;
//		for (int r_index = 0; r_index < 4; r_index++) {
//			for (int i = old_spiral_start + r_index * old_spiral_width; i < STRIP_LENGTH; i += old_spiral_inc * old_spiral_width) {
//				for (int w = i; w < i + old_spiral_width; w++) {
//					old_leds[ringArray[w % STRIP_LENGTH][r_index]] = ColorFromPalette(old_palette, old_this_index + w * old_this_inc, old_this_bright, current_blending);
//				}
//			}
//		}
//		old_spiral_start += old_spiral_width;
//		if (old_spiral_start > 3 * old_spiral_width) {
//			old_spiral_start = 0;
//		}
//	}
//	else {
//		fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
//		start_index += this_inc;
//		this_index = start_index;
//		for (int r_index = 0; r_index < 4; r_index++) {
//			for (int i = spiral_start + r_index * spiral_width; i < STRIP_LENGTH; i += spiral_inc * spiral_width) {
//				for (int w = i; w < i + spiral_width; w++) {
//					cur_leds[ringArray[w % STRIP_LENGTH][r_index]] = ColorFromPalette(current_palette, this_index + w * this_inc, this_bright, current_blending);
//				}
//			}
//		}
//		spiral_start += spiral_width;
//		if (spiral_start > 3 * spiral_width) {
//			spiral_start = 0;
//		}
//	}
//}

#endif
