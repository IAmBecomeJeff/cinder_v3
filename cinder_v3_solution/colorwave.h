#ifndef COLORWAVE_H
#define COLORWAVE_H

// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
//
//	colorwave()
//
//	Variables
//		led.target_palette

void colorwave(bool old) {
	mode_number = 51;
	if (old) {
		//uint8_t sat8 = beatsin88(87, 220, 250);
		old_brightdepth = beatsin88(341, 96, 224);
		old_brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
		old_msmultiplier = beatsin88(147, 23, 60);

		old_hue16 = old_sHue16;//gHue * 256;
		old_hueinc16 = beatsin88(113, 300, 1500);

		old_ms = millis();
		old_deltams = old_ms - sLastMillis;
		old_sLastMillis = old_ms;
		old_sPseudotime += old_deltams * old_msmultiplier;
		old_sHue16 += old_deltams * beatsin88(400, 5, 9);
		old_brightnesstheta16 = old_sPseudotime;

		for (uint16_t i = 0; i < STRIP_LENGTH; i++) {
			for (byte c = 0; c < 4; c++) {
				old_hue16 += old_hueinc16;
				old_hue8 = old_hue16 / 256;
				old_h16_128 = old_hue16 >> 7;
				if (old_h16_128 & 0x100) {
					old_hue8 = 255 - (old_h16_128 >> 1);
				}
				else {
					old_hue8 = old_h16_128 >> 1;
				}

				old_brightnesstheta16 += old_brightnessthetainc16;
				old_b16 = sin16(old_brightnesstheta16) + 32768;

				old_bri16 = (uint32_t)((uint32_t)old_b16 * (uint32_t)old_b16) / 65536;
				old_bri8 = (uint32_t)(((uint32_t)old_bri16) * old_brightdepth) / 65536;
				old_bri8 += (255 - old_brightdepth);

				old_cwave_index = old_hue8;
				//index = triwave8( index);
				old_cwave_index = scale8(old_cwave_index, 240);

				CRGB old_newcolor = ColorFromPalette(old_palette, old_cwave_index, old_bri8);

				old_pixelnumber = i;
				old_pixelnumber = (STRIP_LENGTH - 1) - old_pixelnumber;

				nblend(old_leds[ringArray[old_pixelnumber][c]], old_newcolor, 128);
			}
		}
	}
	else {
		//uint8_t sat8 = beatsin88(87, 220, 250);
		brightdepth = beatsin88(341, 96, 224);
		brightnessthetainc16 = beatsin88(203, (25 * 256), (40 * 256));
		msmultiplier = beatsin88(147, 23, 60);

		hue16 = sHue16;//gHue * 256;
		hueinc16 = beatsin88(113, 300, 1500);

		ms = millis();
		deltams = ms - sLastMillis;
		sLastMillis = ms;
		sPseudotime += deltams * msmultiplier;
		sHue16 += deltams * beatsin88(400, 5, 9);
		brightnesstheta16 = sPseudotime;

		for (uint16_t i = 0; i < STRIP_LENGTH; i++) {
			for (byte c = 0; c < 4; c++) {
				hue16 += hueinc16;
				hue8 = hue16 / 256;
				h16_128 = hue16 >> 7;
				if (h16_128 & 0x100) {
					hue8 = 255 - (h16_128 >> 1);
				}
				else {
					hue8 = h16_128 >> 1;
				}

				brightnesstheta16 += brightnessthetainc16;
				b16 = sin16(brightnesstheta16) + 32768;

				bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
				bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
				bri8 += (255 - brightdepth);

				cwave_index = hue8;
				//index = triwave8( index);
				cwave_index = scale8(cwave_index, 240);

				CRGB newcolor = ColorFromPalette(current_palette, cwave_index, bri8);

				pixelnumber = i;
				pixelnumber = (STRIP_LENGTH - 1) - pixelnumber;

				nblend(cur_leds[ringArray[pixelnumber][c]], newcolor, 128);
			}
		}
	}
}

#endif