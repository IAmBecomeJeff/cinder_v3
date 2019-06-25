void strobe_mode(uint8_t newMode, bool mc, bool old) {
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
		if (mc) { this_delay = 10; this_speed = 0; that_speed = 6; this_rot = 1; that_rot = 2; all_freq = 18; this_cutoff = 128; that_cutoff = 160; this_sat = 255; }
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

	case 52:
		if (mc) { this_delay = 8; target_palette = ofaurora_gp; }
		colorwave(old);
		break;

	case 53:
		if (mc) { this_delay = 8; target_palette = cequal_gp; }
		colorwave(old);
		break;

	case 54:
		if (mc) { this_delay = 8; target_palette = rainbow2_gp; }
		colorwave(old);
		break;

	case 55:
		if (mc) { this_delay = 10; sparking = 120; cooling = 94; }
		fire(old);
		break;

	case 56:
		if (mc) { this_delay = 15; target_palette = blue_fire_gp;  sparking = 100; cooling = 90; }
		fire_pal(old);
		break;

	case 57:
		if (mc) { this_delay = 15; target_palette = lava_gp;  sparking = 100; cooling = 90; }
		fire_pal(old);
		break;

	case 58:
		if (mc) { this_delay = 15; sparking = 70; cooling = 90; }
		fire_mirror(old);
		break;

	case 59:
		if (mc) { this_delay = 15; target_palette = purple_flower_gp;  sparking = 45; cooling = 75; }
		fire_mirror_pal(old);
		break;

	case 60:
		if (mc) { this_delay = 15; target_palette = lava_gp;  sparking = 55; cooling = 75; }
		fire_mirror_pal(old);
		break;

	case 61:
		if (mc) { this_delay = 10; cooling1 = 80; cooling2 = 55; cooling3 = 70;	cooling4 = 55; sparking1 = 90; sparking2 = 70; sparking3 = 70; sparking4 = 90; }
		fire_rings(old);
		break;

	case 62:
		if (mc) { this_delay = 10; target_palette = blue_fire_gp; cooling1 = 80; cooling2 = 100; cooling3 = 90;	cooling4 = 73; sparking1 = 90; sparking2 = 70; sparking3 = 70; sparking4 = 90; }
		fire_pal_rings(old);
		break;

	case 63:
		if (mc) { this_delay = 10; target_palette = es_emerald_dragon_01_gp;  cooling1 = 101; cooling2 = 100; cooling3 = 115; cooling4 = 110; sparking1 = 65; sparking2 = 60; sparking3 = 30; sparking4 = 50; }
		fire_pal_rings(old);
		break;

	case 64:
		if (mc) { this_delay = 10; target_palette = ultraviolet_mold_gp;  cooling1 = 80; cooling2 = 75; cooling3 = 85; cooling4 = 65; sparking1 = 70; sparking2 = 75; sparking3 = 55; sparking4 = 60; }
		fire_pal_rings(old);
		break;

	case 65:
		if (mc) { this_delay = 10; target_palette = b_gp;  cooling1 = 69; cooling2 = 69; cooling3 = 69; cooling4 = 69; sparking1 = 69; sparking2 = 69; sparking3 = 69; sparking4 = 69; }
		fire_pal_rings(old);
		break;

	case 66:
		if (mc) { this_delay = 10; cooling1 = 100; cooling2 = 95; cooling3 = 105; cooling4 = 100; sparking1 = 90; sparking2 = 85; sparking3 = 69; sparking4 = 100; }
		fire_mirror_rings(old);
		break;

	case 67:
		if (mc) { this_delay = 13; cooling1 = 120; cooling2 = 110; cooling3 = 115; cooling4 = 130; sparking1 = 60; sparking2 = 85; sparking3 = 69; sparking4 = 70; }
		fire_mirror_rings(old);
		break;

	case 68:
		if (mc) { this_delay = 13; target_palette = cequal_gp; cooling1 = 80; cooling2 = 80; cooling3 = 90; cooling4 = 60; sparking1 = 80; sparking2 = 70; sparking3 = 60; sparking4 = 50; }
		fire_mirror_pal_rings(old);
		break;

	case 69:  //nice
		if (mc) { this_delay = 15; target_palette = b_gp; cooling1 = 100; cooling2 = 110; cooling3 = 90; cooling4 = 115; sparking1 = 80; sparking2 = 70; sparking3 = 60; sparking4 = 50; }
		fire_mirror_pal_rings(old);
		break;

	case 70:
		if (mc) { this_delay = 15; target_palette = green_gp; cooling1 = 69; cooling2 = 80; cooling3 = 90; cooling4 = 55; sparking1 = 80; sparking2 = 70; sparking3 = 60; sparking4 = 50; }
		fire_mirror_pal_rings(old);
		break;

	case 71:
		if (mc) { this_delay = 10; target_palette = Cyan_Magenta_Blue_gp; juggle_index_reset = 0; this_fade = 16; numdots_ring = 4; this_beat = 5; this_diff = 1; }
		juggle_pal_ring_onedir(old);
		break;

	case 72:
		if (mc) { this_delay = 10; target_palette = ofaurora_gp; juggle_index_reset = 1; this_fade = 40; numdots_ring = 10; this_beat = 0; this_diff = 80; }
		juggle_pal_ring_onedir(old);
		break;

	case 73:
		if (mc) { this_delay = 13; target_palette = Secondary_01a_gp; juggle_index_reset = 0; this_fade = 32; numdots_ring = 2; this_beat = 8; this_diff = 1; }
		juggle_pal_ring_onedir(old);
		break;

	case 74:
		if (mc) { this_delay = 7; target_palette = Coral_reef_gp; juggle_index_reset = 0; this_fade = 32; numdots_ring = 3; this_beat = 10; this_diff = 1; cooling = 100; sparking = 64; }
		juggle_fire(old);
		break;

	case 75:
		if (mc) { this_delay = 12; target_palette = bhw1_sunconure_gp; juggle_index_reset = 0; this_fade = 32; numdots_ring = 3; this_beat = 3; this_diff = 1; cooling = 95; sparking = 87; }
		juggle_fire(old);
		break;

	case 76:
		if (mc) { this_delay = 15; target_palette = cyberpunk_neon_gp; juggle_index_reset = 0; this_fade = 16; numdots_ring_arr[0] = 2; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = 1; numdots_ring_arr[3] = 2; ringBeat[0] = 8; ringBeat[1] = 7; ringBeat[2] = 2; ringBeat[3] = 4; this_diff = 1; }
		juggle_pal_individual_ring_all(old);
		break;

	case 77:
		if (mc) { this_delay = 16; target_palette = alarm_p4_0_2_gp; juggle_index_reset = 0; this_fade = 16; numdots_ring_arr[0] = 2; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = 2; numdots_ring_arr[3] = 1; ringBeat[0] = 20; ringBeat[1] = 5; ringBeat[2] = 18; ringBeat[3] = 15; this_diff = 1; }
		juggle_pal_individual_ring_onedir_all(old);
		break;

	case 78:
		if (mc) { this_delay = 16; target_palette = alarm_p4_0_2_gp; juggle_index_reset = 0; this_fade = 16; numdots_ring_arr[0] = 2; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = 2; numdots_ring_arr[3] = 1; ringBeat[0] = 20; ringBeat[1] = 5; ringBeat[2] = 18; ringBeat[3] = 15; this_diff = 1; cooling1 = 110; cooling2 = 99; cooling3 = 104; cooling4 = 111; sparking1 = 68; sparking2 = 74; sparking3 = 64; sparking4 = 90; }
		juggle_fire_individual(old);
		break;

	case 79:
		if (mc) { this_delay = 10; target_palette = Fire_1_gp; juggle_index_reset = 0; this_fade = 32; numdots_ring_arr[0] = 2; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = 2; numdots_ring_arr[3] = 4; ringBeat[0] = 12; ringBeat[1] = 5; ringBeat[2] = 6; ringBeat[3] = 3; this_diff = 128; }
		juggle_pal_individual_ring_onedir_all(old);
		break;

	case 80:
		if (mc) { this_delay = 10; target_palette = Fire_1_gp; juggle_index_reset = 0; this_fade = 32; numdots_ring_arr[0] = 2; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = 2; numdots_ring_arr[3] = 4; ringBeat[0] = 12; ringBeat[1] = 5; ringBeat[2] = 6; ringBeat[3] = 3; this_diff = 128; cooling1 = 100; cooling2 = 90; cooling3 = 85; cooling4 = 103; sparking1 = 55; sparking2 = 63; sparking3 = 64; sparking4 = 57; }
		juggle_fire_individual(old);
		break;

	case 81:
		if (mc) { this_delay = 18; target_palette = Fire_1_gp; juggle_index_reset = 0; this_fade = 40; numdots_ring_arr[0] = 2; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = 2; numdots_ring_arr[3] = 3; ringBeat[0] = 10; ringBeat[1] = 4; ringBeat[2] = 6; ringBeat[3] = 7; this_diff = 80; }
		juggle_pal_individual_ring_onedir_all(old);
		break;

	case 82:
		if (mc) { this_delay = 18; target_palette = Fire_1_gp; juggle_index_reset = 0; this_fade = 40; numdots_ring_arr[0] = 2; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = 2; numdots_ring_arr[3] = 3; ringBeat[0] = 10; ringBeat[1] = 4; ringBeat[2] = 6; ringBeat[3] = 7; this_diff = 80; cooling1 = 100; cooling2 = 90; cooling3 = 85; cooling4 = 103; sparking1 = 55; sparking2 = 63; sparking3 = 64; sparking4 = 57; }
		juggle_fire_individual(old);
		break;

	case 83:
		if (mc) { this_delay = 10; target_palette = hallows_gp; juggle_index_reset = 1; this_fade = 8; numdots_ring_arr[0] = 2; numdots_ring_arr[1] = 1; numdots_ring_arr[2] = 2; numdots_ring_arr[3] = 1; ringBeat[0] = 12; ringBeat[1] = 5; ringBeat[2] = 10; ringBeat[3] = 8; this_diff = 32; cooling1 = 99; cooling2 = 95; cooling3 = 85; cooling4 = 75; sparking1 = 40; sparking2 = 30; sparking3 = 35; sparking4 = 45; }
		juggle_fire_individual(old);
		break;

	case 84:
		if (mc) { this_delay = 12; target_palette = rainbow2_gp; juggle_index_reset = 0; this_fade = 1; numdots_ring_arr[0] = 1; numdots_ring_arr[1] = 1; numdots_ring_arr[2] = 1; numdots_ring_arr[3] = 1; ringBeat[0] = 10; ringBeat[1] = 4; ringBeat[2] = 5; ringBeat[3] = 7; this_diff = 1; cooling1 = 99; cooling2 = 95; cooling3 = 85; cooling4 = 75; sparking1 = 40; sparking2 = 30; sparking3 = 35; sparking4 = 45; }
		juggle_fire_individual(old);
		break;

	case 85:
		if (mc) { this_delay = 12; target_palette = bhw2_22_gp; juggle_index_reset = 0; this_fade = 4; numdots_ring_arr[0] = 1; numdots_ring_arr[1] = 2; numdots_ring_arr[2] = 1; numdots_ring_arr[3] = 1; ringBeat[0] = 10; ringBeat[1] = 9; ringBeat[2] = 6; ringBeat[3] = 7; this_diff = 1; cooling1 = 108; cooling2 = 115; cooling3 = 103; cooling4 = 109; sparking1 = 40; sparking2 = 30; sparking3 = 35; sparking4 = 45; }
		juggle_fire_individual(old);
		break;

	case 86:
		if (mc) { this_delay = 10; target_palette = hallows_gp; juggle_index_reset = 1; this_fade = 20; numdots_ring_arr[0] = 1; numdots_ring_arr[1] = 1; numdots_ring_arr[2] = 1; numdots_ring_arr[3] = 1; ringBeat[0] = 12; ringBeat[1] = 5; ringBeat[2] = 10; ringBeat[3] = 8; this_diff = 48; cooling1 = 99; cooling2 = 95; cooling3 = 85; cooling4 = 75; sparking1 = 40; sparking2 = 30; sparking3 = 35; sparking4 = 45; }
		juggle_fire_individual(old);
		break;

	case 87:
		if (mc) { this_delay = 4; target_palette = Cyan_Magenta_Blue_gp; this_inc = 1; this_speed = 12; this_rot = 7; all_freq = 10; this_cutoff = 64; bg_clr = 0; bg_bri = 0; }
		one_sin_spiral(old);
		break;

	case 88:
		if (mc) { this_delay = 4; target_palette = bhw2_turq_gp; this_inc = 1; this_speed = 3; this_rot = 1; all_freq = 24; this_cutoff = 224; bg_clr = 0; bg_bri = 0; }
		one_sin_spiral(old);
		break;

	case 89:
		if (mc) { this_delay = 10; target_palette = bhw2_23_gp; this_inc = 4; this_speed = 1; this_rot = 20; all_freq = 80; this_cutoff = 0;  that_speed = 1;  bg_clr = 0; bg_bri = 0; }
		helix_spiral(old);
		break;

	case 90:
		if (mc) { this_delay = 10; target_palette = Sunset_Real_gp; this_inc = 4; this_speed = 1; this_rot = 20; all_freq = 120; this_cutoff = 0;  that_speed = 1;  bg_clr = 0; bg_bri = 0; }
		helix_spiral(old);
		break;

	case 91:
		if (mc) { this_delay = 1; target_palette = rainbow2_gp; }
		plasma_spiral(old);
		break;

	case 92:
		if (mc) { this_delay = 1; target_palette = hallows_gp; }
		plasma_spiral2(old);
		break;


	}
}