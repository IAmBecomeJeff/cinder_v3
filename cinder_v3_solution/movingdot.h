#ifndef MOVING_DOT_H
#define MOVING_DOT_H



void movingdot(bool old) {
	mode_number = 64;
	if (old) {
		old_lead_led.b = beatsin8(old_blue_angle, old_blue_low, old_blue_high);
		old_lead_led.g = beatsin8(old_green_angle, old_green_low, old_green_high);
		old_lead_led.r = beatsin8(old_red_angle, old_red_low, old_red_high);
		ringCRGB(1, old_this_index, old_lead_led.r, old_lead_led.g, old_lead_led.b);
		fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
		if (old_this_dir) {
			if (old_this_index++ >= STRIP_LENGTH) {}
			old_this_index = 0;
		}
		else {
			if (old_this_index-- == 0) {
				old_this_index = STRIP_LENGTH - 1;
			}
		}
	}
	else {
		lead_led.b = beatsin8(blue_angle, blue_low, blue_high);
		lead_led.g = beatsin8(green_angle, green_low, green_high);
		lead_led.r = beatsin8(red_angle, red_low, red_high);
		ringCRGB(0, this_index, lead_led.r, lead_led.g, lead_led.b);
		fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);
		if (this_dir) {
			if (this_index++ >= STRIP_LENGTH){}
				this_index = 0;
		}
		else {
			if (this_index-- == 0) {
				this_index = STRIP_LENGTH - 1;
			}
		}
	}
}



#endif
