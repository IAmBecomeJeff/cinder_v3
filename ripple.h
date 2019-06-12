#ifndef RIPPLE_H
#define RIPPLE_H

int wrap(int step) {
	if (step < 0) return STRIP_LENGTH + step;
	if (step > STRIP_LENGTH - 1) return step - STRIP_LENGTH;
	return step;
}

//void ripple(bool old) {
//	if (old) {
//		if (old_rip_currentBg == old_rip_nextBg) {
//			old_rip_nextBg = random(256);
//		}
//		else if (old_rip_nextBg > old_rip_currentBg) {
//			old_rip_currentBg++;
//		}
//		else {
//			old_rip_currentBg--;
//		}
//
//		for (uint8_t l = 0; l < NUM_LEDS; l++) {
//			old_leds[l] = CHSV(old_rip_currentBg, 255, 50);
//		}
//
//		if (old_rip_step == -1) {
//			old_rip_center = random(STRIP_LENGTH);
//			old_rip_color = random(256);
//			old_rip_step = 0;
//		}
//
//		if (old_rip_step == 0) {
//			ringCHSV(1, old_rip_center, old_rip_color, 255, 255);
//			old_rip_step++;
//		}
//		else {
//			if (old_rip_step < rip_maxSteps) {
//				//Serial.println(pow(fadeRate, step));
//				ringCHSV(1, wrap(old_rip_center + old_rip_step), old_rip_color, 255, pow(old_rip_fadeRate, old_rip_step) * 255);
//				ringCHSV(1, wrap(old_rip_center - old_rip_step), old_rip_color, 255, pow(old_rip_fadeRate, old_rip_step) * 255);
//				if (rip_step > 3) {
//					ringCHSV(1, wrap(old_rip_center + old_rip_step - 3), old_rip_color, 255, pow(old_rip_fadeRate, old_rip_step - 2) * 255);
//					ringCHSV(1, wrap(old_rip_center - old_rip_step + 3), old_rip_color, 255, pow(old_rip_fadeRate, old_rip_step - 2) * 255);
//				}
//				old_rip_step++;
//			}
//			else {
//				old_rip_step = -1;
//			}
//		}
//	}
//	else {
//		if (rip_currentBg == rip_nextBg) {
//			rip_nextBg = random(256);
//		}
//		else if (rip_nextBg > rip_currentBg) {
//			rip_currentBg++;
//		}
//		else {
//			rip_currentBg--;
//		}
//
//		for (uint8_t l = 0; l < NUM_LEDS; l++) {
//			cur_leds[l] = CHSV(rip_currentBg, 255, 50);
//		}
//		if (rip_step < -1) {
//			rip_step++;
//		}
//		if (rip_step == -1) {
//			rip_center = random(STRIP_LENGTH);
//			rip_color = random(256);
//			rip_step = 0;
//		}
//
//		if (rip_step == 0) {
//			ringCHSV(0, rip_center, rip_color, 255, 255);
//			rip_step++;
//		}
//		else {
//			if (rip_step < rip_maxSteps) {
//				//Serial.println(pow(fadeRate, step));
//				ringCHSV(0, wrap(rip_center + rip_step), rip_color, 255, pow(rip_fadeRate, rip_step) * 255);
//				ringCHSV(0, wrap(rip_center - rip_step), rip_color, 255, pow(rip_fadeRate, rip_step) * 255);
//				if (rip_step > 3) {
//					ringCHSV(0, wrap(rip_center + rip_step - 3), rip_color, 255, pow(rip_fadeRate, rip_step - 2) * 255);
//					ringCHSV(0, wrap(rip_center - rip_step + 3), rip_color, 255, pow(rip_fadeRate, rip_step - 2) * 255);
//				}
//				rip_step++;
//			}
//			else {
//				rip_step = rip_delay;
//			}
//		}
//	}
//} // ripple()




void ripple2(bool old) {
	mode_number = 32;
	if (old) {
		fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);                             // 8 bit, 1 = slow, 255 = fast

		switch (old_rip_step) {

		case -1:                                                          // Initialize ripple variables.
			old_rip_center = random(STRIP_LENGTH);
			old_rip_color = random8();
			old_rip_step = 0;
			break;

		case 0:
			old_leds[old_rip_center] = ColorFromPalette(old_palette, old_rip_color, old_rip_fade, current_blending);
			old_rip_step++;
			break;

		case rip_maxSteps:                                                    // At the end of the ripples.
			old_rip_step = -1;
			break;

		default:                                                          // Middle of the ripples.
			ringPaletteAdd(1, (old_rip_center + old_rip_step + STRIP_LENGTH) % STRIP_LENGTH, old_palette, old_rip_color, old_rip_fade / old_rip_step * 2, current_blending);       // Simple wrap from Marc Miller
			ringPaletteAdd(1, (old_rip_center - old_rip_step + STRIP_LENGTH) % STRIP_LENGTH, old_palette, old_rip_color, old_rip_fade / old_rip_step * 2, current_blending);
			old_rip_step++;                                                         // Next step.
			break;
		} // switch step
	}
	else {
		fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);                             // 8 bit, 1 = slow, 255 = fast

		switch (rip_step) {

		case -10:
			rip_pause++;
			if (rip_pause == 0) { rip_step = -1; rip_pause = random8(20) - 20; }
			break;

		case -1:                                                          // Initialize ripple variables.
			rip_center = random(STRIP_LENGTH);
			rip_color = random8();
			rip_step = 0;
			break;

		case 0:
			cur_leds[rip_center] = ColorFromPalette(current_palette, rip_color, ripfade, current_blending);
			rip_step++;
			break;

		case rip_maxSteps:                                                    // At the end of the ripples.
			rip_step = -10;
			break;

		default:                                                          // Middle of the ripples.
			ringPaletteAdd(0, (rip_center + rip_step + STRIP_LENGTH) % STRIP_LENGTH, current_palette, rip_color, rip_fade / rip_step * 2, current_blending);       // Simple wrap from Marc Miller
			ringPaletteAdd(0,(rip_center - rip_step + STRIP_LENGTH) % STRIP_LENGTH, current_palette, rip_color, rip_fade / rip_step * 2, current_blending);
			rip_step++;                                                         // Next step.
			break;
		} // switch step
	}
} // ripple2()

#endif
