#ifndef MATRIX_H
#define MATRIX_H


/* Usage - matrix_pal();
 *  
 *  This is one of the few routines I have with pixel counting.
 *  
 *  
 * current_palette, target_palette
 * this_rot
 * this_index
 * bg_clr
 * bg_bri
 * this_dir
 * this_bright
 */

//void matrix_pal(bool old) {                                           // One line matrix
//	if (old) {
//		if (old_this_rot) old_this_index++;                                   // Increase palette index to change colours on the fly
//
//		if (random8(90) > 80) {
//			if (old_this_dir == 0)
//				old_leds[0] = ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);
//			else
//				old_leds[NUM_LEDS - 1] = ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);
//		}
//		else {
//			if (old_this_dir == 0)
//				old_leds[0] = CHSV(old_bg_clr, old_this_sat, old_bg_bri);
//			else
//				old_leds[NUM_LEDS - 1] = CHSV(old_bg_clr, old_this_sat, old_bg_bri);
//		}
//
//		if (old_this_dir == 0) {
//			for (int i = NUM_LEDS - 1; i > 0; i--) old_leds[i] = old_leds[i - 1];
//		}
//		else {
//			for (int i = 0; i < NUM_LEDS - 1; i++) old_leds[i] = old_leds[i + 1];
//		}
//	}
//	else {
//		if (this_rot) this_index++;                                   // Increase palette index to change colours on the fly
//
//		if (random8(90) > 80) {
//			if (this_dir == 0)
//				cur_leds[0] = ColorFromPalette(current_palette, this_index, this_bright, current_blending);
//			else
//				cur_leds[NUM_LEDS - 1] = ColorFromPalette(current_palette, this_index, this_bright, current_blending);
//		}
//		else {
//			if (this_dir == 0)
//				cur_leds[0] = CHSV(bg_clr, this_sat, bg_bri);
//			else
//				cur_leds[NUM_LEDS - 1] = CHSV(bg_clr, this_sat, bg_bri);
//		}
//
//		if (this_dir == 0) {
//			for (int i = NUM_LEDS - 1; i >0; i--) cur_leds[i] = cur_leds[i - 1];
//		}
//		else {
//			for (int i = 0; i < NUM_LEDS - 1; i++) cur_leds[i] = cur_leds[i + 1];
//		}
//	}
//} // matrix_pal()



void matrix_pal_ring(bool old) {                                           // One line matrix
	mode_number = 21;
	if (old) {
		if (old_this_rot) old_this_index++;                                   // Increase palette index to change colours on the fly

		if (random8(90) > 80) {
			if (old_this_dir == 0)
				ringPalette(1, 0, old_palette, old_this_index, old_this_bright, current_blending);
			else
				ringPalette(1, STRIP_LENGTH - 1, old_palette, old_this_index, old_this_bright, current_blending);
		}
		else {
			if (old_this_dir == 0)
				ringCHSV(1, 0, old_bg_clr, old_this_sat, old_bg_bri);
			else
				ringCHSV(1, STRIP_LENGTH - 1, old_bg_clr, old_this_sat, old_bg_bri);
		}

		if (old_this_dir == 0) {
			for (int i = STRIP_LENGTH - 1; i > 0; i--) {
				for (int j = 0; j < 4; j++) {
					old_leds[ringArray[i][j]] = old_leds[ringArray[i - 1][j]];
				}
			}
		}
		else {
			for (int i = 0; i < STRIP_LENGTH - 1; i++) {
				for (int j = 0; j < 4; j++) {
					old_leds[ringArray[i][j]] = old_leds[ringArray[i + 1][j]];
				}
			}
		}
	}
	else {
		if (this_rot) this_index++;                                   // Increase palette index to change colours on the fly

		if (random8(90) > 80) {
			if (this_dir == 0)
				ringPalette(0, 0, current_palette, this_index, this_bright, current_blending);
			else
				ringPalette(0, STRIP_LENGTH - 1, current_palette, this_index, this_bright, current_blending);
		}
		else {
			if (this_dir == 0)
				ringCHSV(0, 0, bg_clr, this_sat, bg_bri);
			else
				ringCHSV(0, STRIP_LENGTH - 1, bg_clr, this_sat, bg_bri);
		}

		if (this_dir == 0) {
			for (int i = STRIP_LENGTH - 1; i >0; i--) {
				for (int j = 0; j<4; j++) {
					cur_leds[ringArray[i][j]] = cur_leds[ringArray[i - 1][j]];
				}
			}
		}
		else {
			for (int i = 0; i < STRIP_LENGTH - 1; i++) {
				for (int j = 0; j<4; j++) {
					cur_leds[ringArray[i][j]] = cur_leds[ringArray[i + 1][j]];
				}
			}
		}
	}
} // matrix_pal_ring()

void matrix_random_walk(bool old) {                                           // One line matrix
	mode_number = 22;
	if (old) {
		if (old_this_rot) old_this_index++;                                   // Increase palette index to change colours on the fly

		if (random8(90) > 80) {
			if (old_this_dir == 0)
				old_leds[ringArray[random8(4)][0]] = ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);
			else
				old_leds[ringArray[random8(4)][STRIP_LENGTH - 1]] = ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);
		}
		else {
			for (int i = 0; i < 4; i++) {
				if (old_this_dir == 0)
					old_leds[ringArray[0][i]].fadeToBlackBy(old_this_fade);
				else
					old_leds[ringArray[STRIP_LENGTH - 1][i]].fadeToBlackBy(old_this_fade);
			}
		}

		if (old_this_dir == 0) {
			for (int i = STRIP_LENGTH - 1; i > 0; i--) {
				int walk = random8(3);
				for (int r = 0; r < 4; r++) {
					if (walk == 0) {
						old_leds[ringArray[i][r]] = old_leds[ringArray[i - 1][(r + 1) % 4]];
					}
					else if (walk == 1) {
						old_leds[ringArray[i][r]] = old_leds[ringArray[i - 1][((r - 1) + 4) % 4]];
					}
					else {
						old_leds[ringArray[i][r]] = old_leds[ringArray[i - 1][r]];
					}
				}
			}
		}
		else {
			for (int i = 0; i < STRIP_LENGTH - 1; i++) {
				int walk = random8(3);
				for (int r = 0; r < 4; r++) {
					if (walk == 0) {
						old_leds[ringArray[i][r]] = old_leds[ringArray[i + 1][(r + 1) % 4]];
					}
					else if (walk == 1) {
						old_leds[ringArray[i][r]] = old_leds[ringArray[i + 1][((r - 1) + 4) % 4]];
					}
					else {
						old_leds[ringArray[i][r]] = old_leds[ringArray[i + 1][r]];
					}
				}/*cur_leds[i] = cur_leds[i + 1];*/
			}
		}
	}
	else {
		if (this_rot) this_index++;                                   // Increase palette index to change colours on the fly

		if (random8(90) > 80) {
			if (this_dir == 0)
				cur_leds[ringArray[random8(4)][0]] = ColorFromPalette(current_palette, this_index, this_bright, current_blending);
			else
				cur_leds[ringArray[random8(4)][STRIP_LENGTH - 1]] = ColorFromPalette(current_palette, this_index, this_bright, current_blending);
		}
		else {
			for (int i = 0; i < 4; i++){
				if(this_dir == 0){ 
					cur_leds[ringArray[0][i]].fadeToBlackBy(this_fade);
				}
				else {
					cur_leds[ringArray[STRIP_LENGTH - 1][i]].fadeToBlackBy(this_fade);
				}
			}
		if (this_dir == 0) {
			for (int i = STRIP_LENGTH - 1; i > 0; i--) {
				int walk = random8(3);
				for (int r = 0; r < 4; r++) {
					if (walk == 0) {
						cur_leds[ringArray[i][r]] = cur_leds[ringArray[i-1][(r+1)%4]];
					}
					else if (walk == 1) {
						cur_leds[ringArray[i][r]] = cur_leds[ringArray[i - 1][((r - 1)+4) % 4]];
					}
					else {
						cur_leds[ringArray[i][r]] = cur_leds[ringArray[i - 1][r]];
					}
				}
			}
		}
		else {
			for (int i = 0; i < STRIP_LENGTH - 1; i++) {
				int walk = random8(3);
				for (int r = 0; r < 4; r++) {
					if (walk == 0) {
						cur_leds[ringArray[i][r]] = cur_leds[ringArray[i + 1][(r + 1) % 4]];
					}
					else if (walk == 1) {
						cur_leds[ringArray[i][r]] = cur_leds[ringArray[i + 1][((r - 1) + 4) % 4]];
					}
					else {
						cur_leds[ringArray[i][r]] = cur_leds[ringArray[i + 1][r]];
					}
				}/*cur_leds[i] = cur_leds[i + 1];*/
			}
		}
  }
}
}// matrix_random_walk()


#endif
