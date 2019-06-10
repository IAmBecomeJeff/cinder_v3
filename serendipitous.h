#ifndef SERENDIPITOUS_H
#define SERENDIPITOUS_H


void serendipitous_pal(bool old) {
	mode_number = 33;
	if (old) {
		EVERY_N_SECONDS(5) {
			old_X = old_Xorig;
			old_Y = old_Yorig;
		}

		old_Xn = old_X - (old_Y / 2); old_Yn = old_Y + (old_Xn / 2);
		//  Xn = X-Y/2;   Yn = Y+Xn/2;
		//  Xn = X-(Y/2); Yn = Y+(X/2.1);
		//  Xn = X-(Y/3); Yn = Y+(X/1.5);
		//  Xn = X-(2*Y); Yn = Y+(X/1.1);

		old_X = old_Xn;
		old_Y = old_Yn;
		old_this_index = (sin8(old_X) + cos8(old_Y)) / 2;
		old_leds[old_X % (NUM_LEDS - 1)] = ColorFromPalette(old_palette, old_this_index, 255, LINEARBLEND);
		fadeToBlackBy(old_leds, NUM_LEDS, 16);                     // 8 bit, 1 = slow, 255 = fast
	}
	else {
		EVERY_N_SECONDS(5) {
			X = Xorig;
			Y = Yorig;
		}

		Xn = X - (Y / 2); Yn = Y + (Xn / 2);

		X = Xn;
		Y = Yn;
		this_index = (sin8(X) + cos8(Y)) / 2;
		cur_leds[X % (NUM_LEDS - 1)] = ColorFromPalette(current_palette, this_index, 255, LINEARBLEND);
		fadeToBlackBy(cur_leds, NUM_LEDS, 16);
	}
} // serendipitous_pal()


void serendipitous_pal_ring(bool old) {
	mode_number = 34;
	if (old) {
		EVERY_N_SECONDS(5) {
			old_X2 = old_Xorig2;
			old_Y2 = old_Yorig2;
		}

		old_Xn2 = old_X2 - (old_Y2 / 2); old_Yn2 = old_Y2 + (old_Xn2 / 2);

		old_X2 = old_Xn2;
		old_Y2 = old_Yn2;
		old_this_index = (sin8(old_X2) + cos8(old_Y2)) / 2;
		ringPalette(1, old_X2 % 143, old_palette, old_this_index, 255, LINEARBLEND);
		fadeToBlackBy(old_leds, NUM_LEDS, 16);                     // 8 bit, 1 = slow, 255 = fast
	}
	else {
		EVERY_N_SECONDS(5) {
			X2 = Xorig2;
			Y2 = Yorig2;
		}

		Xn2 = X2 - (Y2 / 2); Yn2 = Y2 + (Xn2 / 2);

		X2 = Xn2;
		Y2 = Yn2;
		this_index = (sin8(X2) + cos8(Y2)) / 2;
		ringPalette(0, X2 % 143, current_palette, this_index, 255, LINEARBLEND);
		fadeToBlackBy(cur_leds, NUM_LEDS, 16);
	}
} // serendipitous_pal_ring()

#endif
