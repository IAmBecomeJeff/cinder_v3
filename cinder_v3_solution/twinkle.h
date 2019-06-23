#ifndef TWINKLE_H
#define TWINKLE_H


uint8_t attackDecayWave8(uint8_t i) {
	if (i < 86) {
		return i * 3;
	} else {
		i -= 86;
		return 255 - (i + (i / 2));
	}
}

void coolLikeIncandescent(CRGB& c, uint8_t phase) {
	if (phase < 128) return;
	uint8_t cooling = (phase - 128) >> 4;
	c.g = qsub8 ( c.g, cooling);
	c.b = qsub8 ( c.b, cooling * 2);
}

CRGB computeOneTwinkle(uint32_t ms, uint8_t salt, bool old) {
	uint16_t ticks = ms >> (8 - twinkle_speed);
	uint8_t fastcycle8 = ticks;
	uint16_t slowcycle16 = (ticks >> 8) + salt;
	slowcycle16 += sin8(slowcycle16);
	slowcycle16 = (slowcycle16 * 2053) + 1384;
	uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);

	uint8_t bright = 0;
	if (((slowcycle8 & 0x0E) / 2) < twinkle_density) {
		bright = attackDecayWave8(fastcycle8);
	}
	uint8_t twinkle_hue = slowcycle8 - salt;
	CRGB c;
	if (bright > 0) {
		if (old) {
			c = ColorFromPalette(old_palette, twinkle_hue, bright, NOBLEND);
			if (old_cool_like_incandescent) {
				coolLikeIncandescent(c, fastcycle8);
			}
		}
		else {
			c = ColorFromPalette(current_palette, twinkle_hue, bright, NOBLEND);
			if (cool_like_incandescent) {
				coolLikeIncandescent(c, fastcycle8);
			}
		}
	} else {
		c = CRGB::Black;
	}
	return c;
}


void twinkle(bool old) {
	mode_number = 47;
	if (old) {
		uint16_t PRNG16 = 11337;

		uint32_t clock32 = millis();

		if (old_auto_select_background_color && (old_palette[0] == old_palette[1])) {
			bg = old_palette[0];
			old_bglight = old_bg.getAverageLight();
			if (old_bglight > 64) {
				old_bg.nscale8_video(16);
			}
			else if (old_bglight > 16) {
				old_bg.nscale8_video(64);
			}
			else {
				old_bg.nscale8_video(86);
			}
		}
		else {
			old_bg = old_twinkle_bg;
		}

		old_backgroundBrightness = old_bg.getAverageLight();

		for (CRGB& pixel : old_leds) {
			PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384;
			uint16_t myclockoffset16 = PRNG16;
			PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384;
			uint8_t myspeedmultiplierQ5_3 = ((((PRNG16 & 0xFF) >> 4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
			uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
			uint8_t myunique8 = PRNG16 >> 8;

			CRGB c = computeOneTwinkle(myclock30, myunique8, old);

			uint8_t cbright = c.getAverageLight();
			int16_t deltabright = cbright - old_backgroundBrightness;
			if (deltabright >= 32 || (!old_bg)) {
				pixel = c;
			}
			else if (deltabright > 0) {
				pixel = blend(old_bg, c, deltabright * 8);
			}
			else {
				pixel = old_bg;
			}
		}
	}
	else {
		uint16_t PRNG16 = 11337;

		uint32_t clock32 = millis();

		if (auto_select_background_color && (current_palette[0] == current_palette[1])) {
			bg = current_palette[0];
			bglight = bg.getAverageLight();
			if (bglight > 64) {
				bg.nscale8_video(16);
			}
			else if (bglight > 16) {
				bg.nscale8_video(64);
			}
			else {
				bg.nscale8_video(86);
			}
		}
		else {
			bg = twinkle_bg;
		}

		backgroundBrightness = bg.getAverageLight();

		for (CRGB& pixel : cur_leds) {
			PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384;
			uint16_t myclockoffset16 = PRNG16;
			PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384;
			uint8_t myspeedmultiplierQ5_3 = ((((PRNG16 & 0xFF) >> 4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
			uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
			uint8_t myunique8 = PRNG16 >> 8;

			CRGB c = computeOneTwinkle(myclock30, myunique8, old);

			uint8_t cbright = c.getAverageLight();
			int16_t deltabright = cbright - backgroundBrightness;
			if (deltabright >= 32 || (!bg)) {
				pixel = c;
			}
			else if (deltabright > 0) {
				pixel = blend(bg, c, deltabright * 8);
			}
			else {
				pixel = bg;
			}
		}
	}
} // twinkle()






#endif
