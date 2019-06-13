#ifndef SUPPORT_FUNCTIONS_H
#define SUPPORT_FUNCTIONS_H


void array_init() {
	// Init ring array
	for (uint8_t i = 0; i < 144; i++) {
		ringArray[i][0] = i;
		ringArray[i][1] = 287 - i;
		ringArray[i][2] = 288 + i;
		ringArray[i][3] = 575 - i;
	}

	// Init spiral array

	for (int i = 0; i < STRIP_LENGTH; i += 4 * w) {
		for (int j = 0; j < w; j++) {
			spiralArray[0][i + j] = i + j;
			spiralArray[0][i + j + w] = 287 - w - i - j;
			spiralArray[0][i + j + 2 * w] = 288 + 2 * w + i + j;
			spiralArray[0][i + j + 3 * w] = 575 - 3 * w - i - j;
			spiralArray[1][i + j] = 287 - i - j;
			spiralArray[1][i + j + w] = 288 + w + i + j;
			spiralArray[1][i + j + 2 * w] = 575 - 2 * w - i - j;
			spiralArray[1][i + j + 3 * w] = 3 * w + i + j;
			spiralArray[2][i + j] = 288 + i + j;
			spiralArray[2][i + j + w] = 575 - w - i - j;
			spiralArray[2][i + j + 2 * w] = 2 * w + i + j;
			spiralArray[2][i + j + 3 * w] = 287 - 3 * w - i - j;
			spiralArray[3][i + j] = 575 - i - j;
			spiralArray[3][i + j + w] = w + i + j;
			spiralArray[3][i + j + 2 * w] = 287 - 2 * w - i - j;
			spiralArray[3][i + j + 3 * w] = 288 + 3 * w + i + j;
		}
	}

	for (int i = 0; i < STRIP_LENGTH; i += 4 * w) {
		for (int j = 0; j < w; j++) {
			spiralArrayRev[0][i + j] = i + j;
			spiralArrayRev[0][i + j + w] = 575 - w - i - j;
			spiralArrayRev[0][i + j + 2 * w] = 288 + 2 * w + i + j;
			spiralArrayRev[0][i + j + 3 * w] = 287 - 3 * w - i - j;

			spiralArrayRev[1][i + j] = 287 - i - j;
			spiralArrayRev[1][i + j + w] = w + i + j;
			spiralArrayRev[1][i + j + 2 * w] = 575 - 2 * w - i - j;
			spiralArrayRev[1][i + j + 3 * w] = 288 + 3 * w + i + j;

			spiralArrayRev[2][i + j] = 288 + i + j;
			spiralArrayRev[2][i + j + w] = 287 - w - i - j;
			spiralArrayRev[2][i + j + 2 * w] = 2 * w + i + j;
			spiralArrayRev[2][i + j + 3 * w] = 575 - 3 * w - i - j;

			spiralArrayRev[3][i + j] = 575 - i - j;
			spiralArrayRev[3][i + j + w] = 288 + w + i + j;
			spiralArrayRev[3][i + j + 2 * w] = 287 - 2 * w - i - j;
			spiralArrayRev[3][i + j + 3 * w] = 3 * w + i + j;
		}
	}

	// Set up circ_noise variables
	for (long i = 0; i < NUM_LEDS; i++) {
		uint8_t angle = (i * 256) / NUM_LEDS;
		xd[i] = cos8(angle);
		yd[i] = sin8(angle);
	}

	// Bouncing Ball Variables
	for (int i = 0; i < NUM_BALLS; i++) {    // Initialize variables
		tLast[i] = millis();
		h[i] = h0;
		pos[i] = 0;                              // Balls start on the ground
		vImpact[i] = vImpact0;                   // And "pop" up at vImpact0
		tCycle[i] = 0;
		COR[i] = 0.90 - float(i) / pow(NUM_BALLS, 2);
	}
}

void(* resetFunc)(void) = 0; // reset function.... resetFunc();



void print_mode(uint8_t mn) {
	switch (mn) {
		case 0:
			Serial.println("Undefined");
			break;

		case 1:
			Serial.println("circnoise_pal_2_ring");
			break;
		
		case 2:
			Serial.println("circnoise_pal_3_ring");
			break;

		case 3:
			Serial.println("confetti_pal_ring");
			break;

		case 4:
			Serial.println("fire");
			break;

		case 5:
			Serial.println("fire_pal");
			break;

		case 6:
			Serial.println("fire_mirror");
			break;

		case 7:
			Serial.println("fire_mirror_pal");
			break;

		case 8:
			Serial.println("fire_rings");
			break;

		case 9:
			Serial.println("fire_pal_rings");
			break;

		case 10:
			Serial.println("fire_mirror_rings");
			break;

		case 11:
			Serial.println("fire_mirror_pal_rings");
			break;

		case 12:
			Serial.println("fire_rings_opp");
			break;

		case 13:
			Serial.println("fire_rings_simple");
			break;

		case 14:
			Serial.println("juggle_pal_ring");
			break;

		case 15:
			Serial.println("juggle_pal_ring_onedir");
			break;

		case 16:
			Serial.println("juggle_fire");
			break;

		case 17:
			Serial.println("juggle_pal_individual_ring_all");
			break;

		case 18:
			Serial.println("juggle_pal_individual_ring_onedir_all");
			break;

		case 19:
			Serial.println("juggle_fire_individual");
			break;

		case 20:
			Serial.println("juggle_fire_individual_same_dir");
			break;

		case 21:
			Serial.println("matrix_pal_ring");
			break;

		case 22:
			Serial.println("matrix_random_walk");
			break;

		case 23:
			Serial.println("noise8_pal");
			break;

		case 24:
			Serial.println("noise8_pal_ring");
			break;

		case 25:
			Serial.println("one_sin_pal");
			break;

		case 26:
			Serial.println("one_sin_pal_ring");
			break;

		case 27:
			Serial.println("palette_motion");
			break;

		case 28:
			Serial.println("plasma");
			break;

		case 29:
			Serial.println("pride");
			break;

		case 30:
			Serial.println("rainbow_march");
			break;

		case 31:
			Serial.println("rainbow_march_ring");
			break;

		case 32:
			Serial.println("ripple2");
			break;

		case 33:
			Serial.println("serendipitous_pal");
			break;

		case 34:
			Serial.println("serenditpitous_pal_ring");
			break;

		case 35:
			Serial.println("spiral");
			break;

		case 36:
			Serial.println("spiral_pal");
			break;

		case 37:
			Serial.println("spiral_sin");
			break;

		case 38:
			Serial.println("spiral_sin_sub");
			break;

		case 39:
			Serial.println("one_sin_spiral");
			break;

		case 40:
			Serial.println("helix_spiral");
			break;

		case 41:
			Serial.println("plasma_spiral");
			break;

		case 42:
			Serial.println("plasma_spiral2");
			break;

		case 43:
			Serial.println("spiral_fill_palette");
			break;

		case 44:
			Serial.println("palette_spiral");
			break;

		case 45:
			Serial.println("three_sin_pal");
			break;

		case 46:
			Serial.println("three_sin_pal_ring");
			break;

		case 47:
			Serial.println("twinkle");
			break;

		case 48:
			Serial.println("two_sin");
			break;

		case 49:
			Serial.println("two_sin_ring");
			break;

		case 50:
			Serial.println("two_sin_pal_ring");
			break;

		case 51:
			Serial.println("colorwave");
			break;

		case 52:
			Serial.println("bouncing_balls");
			break;

		case 53:
			Serial.println("bouncing_balls2");
			break;

		case 54:
			Serial.println("matrix_saw");
			break;

		case 55:
			Serial.println("circnoise_pal_1_ring");
			break;

		case 56:
			Serial.println("circnoise_pal_4_ring");
			break;

		case 57:
			Serial.println("cylon");
			break;

		default:
			Serial.println("Undefined");
			break;
	}
}

void print_palette(uint8_t pn) {
	switch (pn) {
	case 0:
		Serial.println("ib_jul01_gp");
		break;

	case 1:
		Serial.println("es_vintage_57_gp");
		break;

	case 2:
		Serial.println("es_vintage_01_gp");
		break;

	case 3:
		Serial.println("es_rivendell_15_gp");
		break;

	case 4:
		Serial.println("rgi_15_gp");
		break;

	case 5:
		Serial.println("retro2_16_gp");
		break;

	case 6:
		Serial.println("Analogous_1_gp");
		break;

	case 7:
		Serial.println("es_pinksplash_08_gp");
		break;

	case 8:
		Serial.println("es_pinksplash_07_gp");
		break;

	case 9:
		Serial.println("Coral_reef_gp");
		break;

	case 10:
		Serial.println("es_ocean_breeze_068_gp");
		break;

	case 11:
		Serial.println("es_ocean_breeze_036_gp");
		break;

	case 12:
		Serial.println("departure_gp");
		break;

	case 13:
		Serial.println("es_landscape_64_gp");
		break;

	case 14:
		Serial.println("es_landscape_33_gp");
		break;

	case 15:
		Serial.println("rainbowsherbet_gp");
		break;

	case 16:
		Serial.println("gr65_hult_gp");
		break;

	case 17:
		Serial.println("gr64_hult_gp");
		break;

	case 18:
		Serial.println("GMT_drywet_gp");
		break;

	case 19:
		Serial.println("ib15_gp");
		break;

	case 20:
		Serial.println("Fuschia_7_gp");
		break;

	case 21:
		Serial.println("es_emerald_dragon_08_gp");
		break;

	case 22:
		Serial.println("lava_gp");
		break;

	case 23:
		Serial.println("fire_gp");
		break;

	case 24:
		Serial.println("Colorfull_gp");
		break;

	case 25:
		Serial.println("Magenta_Evening_gp");
		break;

	case 26:
		Serial.println("Pink_Purple_gp");
		break;

	case 27:
		Serial.println("Sunset_Real_gp");
		break;

	case 28:
		Serial.println("es_autumn_19_gp");
		break;

	case 29:
		Serial.println("BlacK_Blue_Magenta_White_gp");
		break;

	case 30:
		Serial.println("BlacK_Magenta_Red_gp");
		break;

	case 31:
		Serial.println("BlacK_Red_Magenta_Yellow_gp");
		break;

	case 32:
		Serial.println("Blue_Cyan_Yellow_gp");
		break;

	case 33:
		Serial.println("bhw1_greeny_gp");
		break;

	case 34:
		Serial.println("bhw1_26_gp");
		break;

	case 35:
		Serial.println("bhw1_28_gp");
		break;

	case 36:
		Serial.println("bhw2_23_gp");
		break;

	case 37:
		Serial.println("bhw2_22_gp");
		break;

	case 38:
		Serial.println("bhw2_49_gp");
		break;

	case 39:
		Serial.println("bhw2_10_gp");
		break;

	case 40:
		Serial.println("bhw2_14_gp");
		break;

	case 41:
		Serial.println("bhw3_21_gp");
		break;

	case 42:
		Serial.println("bhw3_30_gp");
		break;

	case 43:
		Serial.println("vibrant_gp");
		break;

	case 44:
		Serial.println("cw1_029_gp");
		break;

	case 45:
		Serial.println("alarm_p4_0_2_gp");
		break;

	case 46:
		Serial.println("Ribbon_Colors_gp");
		break;

	case 47:
		Serial.println("Orange_to_Purple_gp");
		break;

	case 48:
		Serial.println("Fire_1_gp");
		break;

	case 49:
		Serial.println("standard_gp");
		break;

	case 50:
		Serial.println("a_gp");
		break;

	case 51:
		Serial.println("b_gp");
		break;

	case 52:
		Serial.println("es_emerald_dragon_01_gp");
		break;

	case 53:
		Serial.println("es_landscape_59_gp");
		break;

	case 54:
		Serial.println("es_seadreams_09_gp");
		break;

	case 55:
		Serial.println("froth316_gp");
		break;

	case 56:
		Serial.println("Skydye11_gp");
		break;

	case 57:
		Serial.println("Wizzl019_gp");
		break;

	case 58:
		Serial.println("Tropical_Colors_gp");
		break;

	case 59:
		Serial.println("slope_gp");
		break;

	case 60:
		Serial.println("ofaurora_gp");
		break;

	case 61:
		Serial.println("hallows_gp");
		break;

	case 62:
		Serial.println("sea_treasure_gp");
		break;

	case 63:
		Serial.println("Secondary_01a_gp");
		break;

	case 64:
		Serial.println("Split_03_gp");
		break;

	case 65:
		Serial.println("GMT_seafloor_gp");
		break;

	case 66:
		Serial.println("rainbow_gp");
		break;

	case 67:
		Serial.println("cloudcolors_gp");
		break;

	case 68:
		Serial.println("cequal_gp");
		break;

	case 69:
		Serial.println("purple_flower_gp");
		break;

	case 70:
		Serial.println("fierce_ice_gp");
		break;

	case 71:
		Serial.println("blueice_gp");
		break;

	case 72:
		Serial.println("twilight_gp");
		break;

	case 73:
		Serial.println("green_gp");
		break;

	case 74:
		Serial.println("ultraviolet_mold_gp");
		break;

	case 75:
		Serial.println("apple_green_gp");
		break;

	case 76:
		Serial.println("faint_rainbow_gp");
		break;

	case 77:
		Serial.println("otis_gp");
		break;

	case 78:
		Serial.println("parrot_gp");
		break;

	case 79:
		Serial.println("scoutie_gp");
		break;

	case 80:
		Serial.println("sunlitwave_gp");
		break;

	case 81:
		Serial.println("GMT_cool_gp");
		break;

	case 82:
		Serial.println("bhw1_sunconure_gp");
		break;

	case 83:
		Serial.println("bhw1_05_gp");
		break;

	case 84:
		Serial.println("bhw2_turq_gp");
		break;

	case 85:
		Serial.println("bhw3_13_gp");
		break;

	case 86:
		Serial.println("bhw3_61_gp");
		break;

	case 87:
		Serial.println("bhw4_009_gp");
		break;

	case 88:
		Serial.println("bhw3_34_gp");
		break;

	case 89:
		Serial.println("es_emerald_dragon_09_gp");
		break;

	case 90:
		Serial.println("xanidu_2_gp");
		break;

	case 91:
		Serial.println("water1_gp");
		break;

	case 92:
		Serial.println("stratosphere_sunset_gp");
		break;

	case 93:
		Serial.println("RedsandCyans_gp");
		break;

	case 94:
		Serial.println("Cyan_Magenta_Blue_gp");
		break;

	case 95:
		Serial.println("Complementary_01a_gp");
		break;

	case 96:
		Serial.println("cyberpunk_neon_gp");
		break;

	default:
		Serial.println("Not a gradient palette");
		break;
	}
}

#endif
