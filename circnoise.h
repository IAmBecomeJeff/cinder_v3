#ifndef CIRCNOISE_H
#define CIRCNOISE_H
//
//void circnoise_pal_1(bool old) {
//	if (old) {
//		int old_scale = 1000;                               // the "zoom factor" for the noise
//
//		for (uint16_t i = 0; i < NUM_LEDS; i++) {
//
//			uint16_t old_shift_x = beatsin8(17);                  // the x position of the noise field swings @ 17 bpm
//			uint16_t old_shift_y = millis() / 100;                // the y position becomes slowly incremented
//
//			uint32_t old_real_x = (old_xd[i] + old_shift_x) * old_scale;       // calculate the coordinates within the noise field
//			uint32_t old_real_y = (old_yd[i] + old_shift_y) * old_scale;       // based on the precalculated positions
//
//			uint8_t old_noise = inoise16(old_real_x, old_real_y, 4223) >> 8;           // get the noise data and scale it down
//
//			uint8_t old_index = old_noise * 3;                        // map led color based on noise data
//			uint8_t old_bri = old_noise;
//
//			old_leds[i] = ColorFromPalette(old_palette, old_index, old_bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//		}
//	}
//	else {
//		int scale = 1000;                               // the "zoom factor" for the noise
//
//		for (uint16_t i = 0; i < NUM_LEDS; i++) {
//
//			uint16_t shift_x = beatsin8(17);                  // the x position of the noise field swings @ 17 bpm
//			uint16_t shift_y = millis() / 100;                // the y position becomes slowly incremented
//
//			uint32_t real_x = (xd[i] + shift_x) * scale;       // calculate the coordinates within the noise field
//			uint32_t real_y = (yd[i] + shift_y) * scale;       // based on the precalculated positions
//
//			uint8_t noise = inoise16(real_x, real_y, 4223) >> 8;           // get the noise data and scale it down
//
//			uint8_t index = noise * 3;                        // map led color based on noise data
//			uint8_t bri = noise;
//
//			cur_leds[i] = ColorFromPalette(current_palette, index, bri, LINEARBLEND);
//		}
//	}
//} // circnoise_pal_1()
//
//
//
//void circnoise_pal_2(bool old) {
//	if (old) {
//		int old_scale = 1000;                               // the "zoom factor" for the noise
//
//		for (uint16_t i = 0; i < NUM_LEDS; i++) {
//
//			uint16_t old_shift_x = millis() / 10;                 // x as a function of time
//			uint16_t old_shift_y = 0;
//
//			uint32_t old_real_x = (old_xd[i] + old_shift_x) * old_scale;       // calculate the coordinates within the noise field
//			uint32_t old_real_y = (old_yd[i] + old_shift_y) * old_scale;       // based on the precalculated positions
//
//			uint8_t old_noise = inoise16(old_real_x, old_real_y, 4223) >> 8;           // get the noise data and scale it down
//
//			uint8_t old_index = old_noise * 3;                        // map led color based on noise data
//			uint8_t old_bri = old_noise;
//
//			old_leds[i] = ColorFromPalette(old_palette, old_index, old_bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//
//		}
//	}
//	else {
//		int scale = 1000;                               // the "zoom factor" for the noise
//
//		for (uint16_t i = 0; i < NUM_LEDS; i++) {
//
//			uint16_t shift_x = millis() / 10;                 // x as a function of time
//			uint16_t shift_y = 0;
//
//			uint32_t real_x = (xd[i] + shift_x) * scale;       // calculate the coordinates within the noise field
//			uint32_t real_y = (yd[i] + shift_y) * scale;       // based on the precalculated positions
//
//			uint8_t noise = inoise16(real_x, real_y, 4223) >> 8;           // get the noise data and scale it down
//
//			uint8_t index = noise * 3;                        // map led color based on noise data
//			uint8_t bri = noise;
//
//			cur_leds[i] = ColorFromPalette(current_palette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//
//		}
//	}
//} // circnoise_pal_2()
//
//
//
//void circnoise_pal_3(bool old) {
//	if (old) {
//		int old_scale = 1000;                               // the "zoom factor" for the noise
//
//		for (uint16_t i = 0; i < NUM_LEDS; i++) {
//
//			uint16_t old_shift_x = 0;                             // no movement along x and y
//			uint16_t old_shift_y = 0;
//
//
//			uint32_t old_real_x = (old_xd[i] + old_shift_x) * old_scale;       // calculate the coordinates within the noise field
//			uint32_t old_real_y = (old_yd[i] + old_shift_y) * old_scale;       // based on the precalculated positions
//
//			uint32_t old_real_z = millis() * 20;                  // increment z linear
//
//			uint8_t old_noise = inoise16(old_real_x, old_real_y, old_real_z) >> 8;           // get the noise data and scale it down
//
//			uint8_t old_index = old_noise * 3;                        // map led color based on noise data
//			uint8_t old_bri = old_noise;
//
//			old_leds[i] = ColorFromPalette(old_palette, old_index, old_bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//
//		}
//	}
//	else {
//		int scale = 1000;                               // the "zoom factor" for the noise
//
//		for (uint16_t i = 0; i < NUM_LEDS; i++) {
//
//			uint16_t shift_x = 0;                             // no movement along x and y
//			uint16_t shift_y = 0;
//
//
//			uint32_t real_x = (xd[i] + shift_x) * scale;       // calculate the coordinates within the noise field
//			uint32_t real_y = (yd[i] + shift_y) * scale;       // based on the precalculated positions
//
//			uint32_t real_z = millis() * 20;                  // increment z linear
//
//			uint8_t noise = inoise16(real_x, real_y, real_z) >> 8;           // get the noise data and scale it down
//
//			uint8_t index = noise * 3;                        // map led color based on noise data
//			uint8_t bri = noise;
//
//			cur_leds[i] = ColorFromPalette(current_palette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//
//		}
//	}
//} // circnoise_pal_3()
//
//
//
//void circnoise_pal_4(bool old) {
//	if (old) {
//		int old_scale = 1000;                               // the "zoom factor" for the noise
//
//		for (uint16_t i = 0; i < NUM_LEDS; i++) {
//
//			uint16_t old_shift_x = beatsin8(15);                          // x as a function of time
//			uint16_t old_shift_y = beatsin8(17);                          // y as a function of time
//			uint32_t old_real_z = millis() / 11;                          // z is also a function of time
//
//
//			uint32_t old_real_x = (cos8(i) + beatsin8(5, 0, 32) + old_shift_x) * old_scale;             // calculate the coordinates within the noise field
//			uint32_t old_real_y = (sin8(i) + beatsin8(3, 0, 32) + old_shift_y) * old_scale;             // based on the precalculated positions
//
//
//			uint8_t old_noise = inoise16(old_real_x, old_real_y, old_real_z) >> 8;           // get the noise data and scale it down
//
//			uint8_t old_index = old_noise * 3;                        // map led color based on noise data
//			uint8_t old_bri = old_noise;
//
//			old_leds[i] = ColorFromPalette(old_palette, old_index, old_bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//
//		}
//	}else{
//		int scale = 1000;                               // the "zoom factor" for the noise
//
//		for (uint16_t i = 0; i < NUM_LEDS; i++) {
//
//			uint16_t shift_x = beatsin8(15);                          // x as a function of time
//			uint16_t shift_y = beatsin8(17);                          // y as a function of time
//			uint32_t real_z = millis() / 11;                          // z is also a function of time
//
//
//			uint32_t real_x = (cos8(i) + beatsin8(5, 0, 32) + shift_x) * scale;             // calculate the coordinates within the noise field
//			uint32_t real_y = (sin8(i) + beatsin8(3, 0, 32) + shift_y) * scale;             // based on the precalculated positions
//
//
//			uint8_t noise = inoise16(real_x, real_y, real_z) >> 8;           // get the noise data and scale it down
//
//			uint8_t index = noise * 3;                        // map led color based on noise data
//			uint8_t bri = noise;
//
//			cur_leds[i] = ColorFromPalette(current_palette, index, bri, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
//
//		}
//	}
//} // circnoise_pal_4()
//
//
//
//
//
//
//// *************************RINGS*******************************//
//
void circnoise_pal_1_ring(bool old) {
	mode_number = 55;
	if (old) {
		//int old_scale = 1000;                               // the "zoom factor" for the noise

		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {

			old_shift_x = beatsin8(17);                  // the x position of the noise field swings @ 17 bpm
			old_shift_y = millis() / 100;                // the y position becomes slowly incremented

			old_real_x = (old_xd[i] + old_shift_x) * old_scale;       // calculate the coordinates within the noise field
			old_real_y = (old_yd[i] + old_shift_y) * old_scale;       // based on the precalculated positions

			old_noise = inoise16(old_real_x, old_real_y, 4223) >> 8;           // get the noise data and scale it down

			old_circ_index = old_noise * 3;                        // map led color based on noise data
			old_circ_bri = old_noise;

			ringPalette(1, i, old_palette, old_circ_index, old_circ_bri, LINEARBLEND);
		}
	}else{
		//int scale = 1000;                               // the "zoom factor" for the noise

		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {

			shift_x = beatsin8(17);                  // the x position of the noise field swings @ 17 bpm
			shift_y = millis() / 100;                // the y position becomes slowly incremented

			real_x = (xd[i] + shift_x) * scale;       // calculate the coordinates within the noise field
			real_y = (yd[i] + shift_y) * scale;       // based on the precalculated positions

			noise = inoise16(real_x, real_y, 4223) >> 8;           // get the noise data and scale it down

			circ_index = noise * 3;                        // map led color based on noise data
			circ_bri = noise;

			ringPalette(0, i, current_palette, circ_index, circ_bri, LINEARBLEND);
		}
	}
}//circnoise_pal_1_ring()

void circnoise_pal_2_ring(bool old) {
	mode_number = 1;
	if (old) {
		//old_scale = 1000;                               // the "zoom factor" for the noise

		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {

			old_shift_x = millis() / 10;                 // x as a function of time
			old_shift_y = 0;

			old_real_x = (old_xd[i] + old_shift_x) * old_scale;       // calculate the coordinates within the noise field
			old_real_y = (old_yd[i] + old_shift_y) * old_scale;       // based on the precalculated positions

			old_noise = inoise16(old_real_x, old_real_y, 4223) >> 8;           // get the noise data and scale it down

			old_circ_index = old_noise * 3;                        // map led color based on noise data
			old_circ_bri = old_noise;

			ringPalette(1, i, old_palette, old_circ_index, old_circ_bri, LINEARBLEND);				// With that value, look up the 8 bit colour palette value and assign it to the current LED.

		}
	}else{
		//scale = 1000;                               // the "zoom factor" for the noise

		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {

			shift_x = millis() / 10;                 // x as a function of time
			 shift_y = 0;

			real_x = (xd[i] + shift_x) * scale;       // calculate the coordinates within the noise field
			real_y = (yd[i] + shift_y) * scale;       // based on the precalculated positions

			noise = inoise16(real_x, real_y, 4223) >> 8;           // get the noise data and scale it down

			circ_index = noise * 3;                        // map led color based on noise data
			circ_bri = noise;

			ringPalette(0, i, current_palette, circ_index, circ_bri, LINEARBLEND);				// With that value, look up the 8 bit colour palette value and assign it to the current LED.

		}
	}
}//circnoise_pal_2_ring()

void circnoise_pal_3_ring(bool old) {
	mode_number = 2;
	if (old) {
		//old_scale = 1000;                               // the "zoom factor" for the noise

		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {

			old_shift_x = 0;                             // no movement along x and y
			old_shift_y = 0;


			old_real_x = (old_xd[i] + old_shift_x) * old_scale;       // calculate the coordinates within the noise field
			old_real_y = (old_yd[i] + old_shift_y) * old_scale;       // based on the precalculated positions

			old_real_z = millis() * 20;                  // increment z linear

			old_noise = inoise16(old_real_x, old_real_y, old_real_z) >> 8;           // get the noise data and scale it down

			old_circ_index = old_noise * 3;                        // map led color based on noise data
			old_circ_bri = old_noise;

			ringPalette(1, i, old_palette, old_circ_index, old_circ_bri, LINEARBLEND);
			// With that value, look up the 8 bit colour palette value and assign it to the current LED.

		}
	}
	else {
		//scale = 1000;                               // the "zoom factor" for the noise

		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {

			shift_x = 0;                             // no movement along x and y
			shift_y = 0;


			real_x = (xd[i] + shift_x) * scale;       // calculate the coordinates within the noise field
			real_y = (yd[i] + shift_y) * scale;       // based on the precalculated positions

			real_z = millis() * 20;                  // increment z linear

			noise = inoise16(real_x, real_y, real_z) >> 8;           // get the noise data and scale it down

			circ_index = noise * 3;                        // map led color based on noise data
			circ_bri = noise;

			ringPalette(0, i, current_palette, circ_index, circ_bri, LINEARBLEND);
			// With that value, look up the 8 bit colour palette value and assign it to the current LED.

		}
	}
} // circnoise_pal_3_ring()

void circnoise_pal_4_ring(bool old) {
	mode_number = 56;
	if (old) {
		//old_scale = 1000;                               // the "zoom factor" for the noise

		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {

			old_shift_x = beatsin8(15);                          // x as a function of time
			old_shift_y = beatsin8(17);                          // y as a function of time
			old_real_z = millis() / 11;                          // z is also a function of time


			old_real_x = (cos8(i) + beatsin8(5, 0, 32) + old_shift_x) * old_scale;             // calculate the coordinates within the noise field
			old_real_y = (sin8(i) + beatsin8(3, 0, 32) + old_shift_y) * old_scale;             // based on the precalculated positions


			old_noise = inoise16(old_real_x, old_real_y, old_real_z) >> 8;           // get the noise data and scale it down

			old_circ_index = old_noise * 3;                        // map led color based on noise data
			old_circ_bri = old_noise;

			ringPalette(1, i, old_palette, old_circ_index, old_circ_bri, LINEARBLEND);
			// With that value, look up the 8 bit colour palette value and assign it to the current LED.

		}
	}
	else {
		//scale = 1000;                               // the "zoom factor" for the noise

		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {

			shift_x = beatsin8(15);                          // x as a function of time
			shift_y = beatsin8(17);                          // y as a function of time
			real_z = millis() / 11;                          // z is also a function of time


			real_x = (cos8(i) + beatsin8(5, 0, 32) + shift_x) * scale;             // calculate the coordinates within the noise field
			real_y = (sin8(i) + beatsin8(3, 0, 32) + shift_y) * scale;             // based on the precalculated positions


			noise = inoise16(real_x, real_y, real_z) >> 8;           // get the noise data and scale it down

			circ_index = noise * 3;                        // map led color based on noise data
			circ_bri = noise;

			ringPalette(0, i, current_palette, circ_index, circ_bri, LINEARBLEND);
			// With that value, look up the 8 bit colour palette value and assign it to the current LED.

		}
	}
} // circnoise_pal_4_ring()

#endif
