//  copy this in to strobe_mode when ready


void strobe_mode(uint8_t newMode, bool mc, bool old) {
	// void strobe_mode(uint8_t newMode, bool mc){
  // If this_ is a *new* mode, clear out LED array.
	if (mc) {
		fill_solid(cur_leds, NUM_LEDS, CRGB(0, 0, 0));
		Serial.print("Mode: ");
		Serial.println(led_mode);
	}
	switch (newMode) {
	case 0:
		if (mc) { this_delay = 5; this_fade = 1; }
		bouncing_balls(old);
		break;

	case 1:
		if (mc) { this_delay = 10; this_fade = 32; }
		bouncing_balls(old);
		break;
	
	case 2:
		if (mc) { this_delay = 1; this_fade = 0; }
		bouncing_balls(old);
		break;
	
	case 3:
		if (mc) { this_delay = 10; target_palette = Wizzl019_gp;  this_fade = 3; }
		bouncing_balls2(old);
		break;
	
	case 4:
		if (mc) { this_delay = 10; target_palette = cw1_029_gp;  this_fade = 20; }
		bouncing_balls2(old);
		break;
	
	case 5:
		if (mc) { this_delay = 1; target_palette = bhw2_14_gp;  scale = 1000; }
		circnoise_pal_2_ring(old);
		break;

	case 6:
		if (mc) { this_delay = 5; target_palette = Wizzl019_gp;  scale = 500; }
		circnoise_pal_2_ring(old);
		break;

	case 7:
		if (mc) { this_delay = 5; target_palette = b_gp;  scale = 1000; }
		circnoise_pal_3_ring(old);
		break;

	case 8:
		if (mc) { this_delay = 10; target_palette = ofaurora_gp;  scale = 700; }
		circnoise_pal_1_ring(old);
		break;

	case 9:
		if (mc) { this_delay = 15; target_palette = Complementary_01a_gp;  scale = 500; }
		circnoise_pal_4_ring(old);
		break;

	case 10:
		if (mc) { this_delay = 20; target_palette = fire_gp; this_diff = 10; this_inc = 1; this_fade = 8; }
		confetti_pal_ring(old);
		break;

	case 11:
		if (mc) { this_delay = 20; target_palette = ofaurora_gp; this_diff = 8; this_inc = 1; this_fade = 16; }
		confetti_pal_ring(old);
		break;

	case 12:
		if (mc) { this_delay = 30; target_palette = bhw2_49_gp; this_diff = 8; this_inc = 20; this_fade = 28; }
		confetti_pal_ring(old);
		break;

	case 13:
		if (mc) { this_delay = 10; target_palette = GMT_drywet_gp; juggle_index_reset = 0; this_fade = 4; numdots_ring = 2; this_beat = 8; this_diff = 1; }
		juggle_pal_ring(old);
		break;

	case 14:
		if (mc) { this_delay = 10; target_palette = bhw3_21_gp; juggle_index_reset = 0; this_fade = 8; numdots_ring = 3; this_beat = 2; this_diff = 1; }
		juggle_pal_ring(old);
		break;
	
	case 15:
		if (mc) { this_delay = 10; target_palette = slope_gp; juggle_index_reset = 0; this_fade = 8; numdots_ring = 6; this_beat = 2; this_diff = 1; }
		juggle_pal_ring(old);
		break;

	case 16:
		if (mc) { this_delay = 10; target_palette = Wizzl019_gp; juggle_index_reset = 1; this_fade = 64; numdots_ring = 6; this_beat = 6; this_diff = 32; }
		juggle_pal_ring(old);
		break;

	case 17:
		if (mc) { this_delay = 28; target_palette = a_gp; this_rot = 2; bg_clr = 0; bg_bri = 0; this_fade = 32; }
		matrix_pal_ring(old);
		break;

	case 18:
		if (mc) { this_delay = 10; target_palette = apple_green_gp; this_rot = 1; bg_clr = 0; bg_bri = 0; this_fade = 30; }
		matrix_random_walk(old);
		break;

	case 19:
		if (mc) { this_delay = 20; target_palette = bhw4_009_gp; }
		matrix_ray(old);
		break;

	case 20:
		if (mc) { this_delay = 10; target_palette = BlacK_Blue_Magenta_White_gp; scale = 32; }
		noise8_pal(old);
		break;

	case 21:
		if (mc) { this_delay = 5; target_palette = lava_gp; scale = 8; }
		noise8_pal(old);
		break;

	case 22:
		if (mc) { this_delay = 5; target_palette = Ribbon_Colors_gp; scale = 10; }
		noise8_pal(old);
		break;

	case 23:
		if (mc) { this_delay = 5; target_palette = sunlitwave_gp; scale2 = 10; }
		noise8_pal_ring(old);
		break;

	case 24:
		if (mc) { this_delay = 5; target_palette = GMT_seafloor_gp; scale2 = 10; }
		noise8_pal_ring(old);
		break;

	case 25:
		if (mc) { this_delay = 8; target_palette = Tropical_Colors_gp; scale2 = 20; }
		noise8_pal_ring(old);
		break;

	case 26:
		if (mc) { this_delay = 10; target_palette = Sunset_Real_gp; scale = 0; scale2 = 1; }
		inoise_fire(old);
		break;

	case 27:
		if (mc) { this_delay = 20; target_palette = lava_gp; scale = 1; scale2 = 2; }
		inoise_fire(old);
		break;

	case 28:
		if (mc) { this_delay = 1; target_palette = standard_gp; scale = 8; scale2 = 1; }
		inoise_fire(old);
		break;

	case 29:
		if (mc) { this_delay = 4; target_palette = scoutie_gp; this_inc = 1; this_speed = 0; all_freq = 200; this_cutoff = 180; this_rot = 8; bg_clr = 0; bg_bri = 0; }
		one_sin_pal(old);
		break;

	case 30:
		if (mc) { this_delay = 1; target_palette = Blue_Cyan_Yellow_gp; this_inc = 1; this_speed = 64; all_freq = 8; this_cutoff = 180; this_rot = 8; bg_clr = 0; bg_bri = 0; }
		one_sin_pal_ring(old);
		break;

	case 31:
		if (mc) { this_delay = 5; target_palette = sunlitwave_gp; this_inc = 2; this_speed = 5; all_freq = 20; this_cutoff = 224; this_rot = 8; bg_clr = 0; bg_bri = 0; }
		one_sin_pal_ring(old);
		break;

	case 32:
		if (mc) { this_delay = 10; this_rot = 2; this_diff = 8; }
		rainbow_march(old);
		break;

	case 33:
		if (mc) { this_delay = 10; this_rot = 2; this_diff = 8; }
		rainbow_march_ring(old);
		break;

	case 34:
		if (mc) { this_delay = 10; this_rot = 1; this_diff = 2; }
		rainbow_march_ring(old);
		break;

	case 35:
		if (mc) { this_delay = 5; }
		pride(old);
		break;

	case 36:
		if (mc) { this_delay = 20; target_palette = Tropical_Colors_gp; this_fade = 0; myfade = 128; }
		ripple2(old);
		break;

	case 37:
		if (mc) { this_delay = 2; target_palette = Fuschia_7_gp; this_fade = 2; }
		serendipitous_pal(old);
		break;

	case 38:
		if (mc) { this_delay = 20; target_palette = lava_gp; this_fade = 16; }
		serendipitous_pal_ring(old);
		break;

	case 39:
		if (mc) { this_delay = 20; target_palette = apple_green_gp; mul1 = 2; mul2 = 2; mul3 = 3; }
		three_sin_pal(old);
		break;

	case 40:
		if (mc) { this_delay = 15; target_palette = purplefly_gp; mul1 = 8; mul2 = 2; mul3 = 4; }
		three_sin_pal(old);
		break;

	case 41:
		if (mc) { this_delay = 20; target_palette = ofaurora_gp; mul1 = 2; mul2 = 3; mul3 = 1; }
		three_sin_pal_ring(old);
		break;

	case 42:
		if (mc) { this_delay = 18; target_palette = bhw2_22_gp; mul1 = 7; mul2 = 4; mul3 = 1; }
		three_sin_pal_ring(old);
		break;

	case 43:
		if (mc) { this_delay = 20; target_palette = Tropical_Colors_gp; mul1 = 2; mul2 = 2; mul3 = 3; }
		three_sin_pal_ring(old);
		break;

	case 44:
		if (mc) { this_delay = 20; target_palette = scoutie_gp; mul1 = 3; mul2 = 4; mul3 = 5; }
		three_sin_pal_ring(old);
		break;

	case 45:
		if (mc) { this_delay = 10; this_speed = 0; that_speed = 6; this_rot = 1; that_rot = 2; all_freq = 18; this_cutoff = 128; that_cutoff = 160; this_sat = 255;  }
		two_sin(old);
		break;

	case 46:
		if (mc) { this_delay = 12; this_speed = 2; that_speed = 253; this_rot = 1; that_rot = 1; all_freq = 12; this_cutoff = 128; that_cutoff = 128; this_sat = 255; }
		two_sin(old);
		break;

	case 47:
		if (mc) { this_delay = 10; this_speed = 1; that_speed = 2; this_rot = 2; that_rot = 1; all_freq = 4; this_cutoff = 128; that_cutoff = 32; this_sat = 255; }
		two_sin(old);
		break;

	case 48:
		if (mc) { this_delay = 10; this_speed = 2; that_speed = 255; this_rot = 0; that_rot = 1; all_freq = 20; this_cutoff = 64; that_cutoff = 128; this_sat = 255; }
		two_sin(old);
		break;

	case 49:
		if (mc) { this_delay = 10; this_speed = 3; that_speed = 253; this_rot = 1; that_rot = 2; all_freq = 16; this_cutoff = 128; that_cutoff = 64; this_sat = 255; }
		two_sin_ring(old);
		break;

	case 50:
		if (mc) { this_delay = 10; this_speed = 6; that_speed = 8; this_rot = 1; that_rot = 2; all_freq = 16; this_cutoff = 1; that_cutoff = 1; this_sat = 255; }
		two_sin_ring(old);
		break;

	case 51:
		if (mc) { this_delay = 15; target_palette = rainbow_gp; this_speed = 253; that_speed = 2; this_rot = 1; that_rot = 1; all_freq = 20; this_cutoff = 64; that_cutoff = 128; this_sat = 255; }
		two_sin_pal_ring(old);
		break;


	}
