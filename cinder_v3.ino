#include "includes.h"
// Modified from Caleb's modified version of seirlight

void setup() {
  // Set up serial connection
  Serial.begin(SERIAL_BAUDRATE);
  Serial.setTimeout(SERIAL_TIMEOUT);

  delay(2000);

  // Set up LEDS
  LEDS.setBrightness(max_bright);

  // -- Single strip of 576 LEDS ------------------------------- //

  LEDS.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS);

  // --------------------------------------------------------------------------------------- //

  set_max_power_in_volts_and_milliamps(5, 1750); // TODO: increase power?

  // Set up variables
  random16_set_seed(4832);
  random16_add_entropy(analogRead(2));

  Serial.println("---SETUP COMPLETE---");

  // Load starting mode and number of leds
  led_mode = EEPROM.read(STARTMODE);

  // Set up palettes
  current_palette  = CRGBPalette16(CRGB::Black);
  target_palette   = RainbowColors_p;
  current_blending = LINEARBLEND;


  // Set up rotary encoder
  pinMode(pinA,INPUT);
  pinMode(pinB,INPUT);
  pinMode(pinSW,INPUT_PULLUP); // or pinMode(pinSW,INPUT); if I use the 10k resistor
  pinALast = digitalRead(pinA);
  debouncer.attach(pinSW);
  debouncer.interval(100);

  // Set up switches
  pinMode(switchA, INPUT_PULLUP);
  pinMode(switchB, INPUT_PULLUP);

  array_init();

  // Keep blank array
  fill_solid(blank_leds, NUM_LEDS, CRGB(0, 0, 0));

  // Init first mode
  strobe_mode(led_mode, 1, 0);
  print_mode(mode_number);
}

void loop() {
	// Reset every 20 minutes
  EVERY_N_MINUTES(1){WRITE_RESTART(0x5FA0004);}

	// Get keyboard input
	readkeyboard();

	// Check rotary dial
	checkDial();

	// Check switchA for direction
	if (digitalRead(switchA)) {
		this_dir = 0;
	}
	else {
		this_dir = 1;
	}

	// Check switchB for demo
	EVERY_N_SECONDS(30) {
		if (!digitalRead(switchB)) {
			if (rotary_function == 1) {// Change palette on rotary 1
				updatePaletteIndex(target_palette);
				//		  palette_index++;
				//		  if (palette_index > g_gradient_palette_count -1){palette_index= 0;}
				palette_index = random8(g_gradient_palette_count + 1);
				target_palette = g_gradient_palettes[palette_index];
				pal_change = 0;
				Serial.print("Palette number: ");
				Serial.println(palette_index);
				print_palette(palette_index);
			}
			else if (rotary_function == 3)
			{
				old_mode = led_mode;
				led_mode = random8(max_mode + 1);;
				update_old_variables();
				transitioning = 1;
				strobe_mode(led_mode, 1, 0);
				print_mode(mode_number);
				target_delay = this_delay;
				this_delay = old_this_delay;
			}
			else {
				old_mode = led_mode;
				led_mode++;
				if (led_mode > max_mode) {
					led_mode = 0;
				}
				update_old_variables();
				transitioning = 1;
				strobe_mode(led_mode, 1, 0);
				print_mode(mode_number);
				target_delay = this_delay;
				this_delay = old_this_delay;
			}
		}
	}

	EVERY_N_SECONDS(15) { // Change palettes and mode a bit more frequently if on second click
		if (!digitalRead(switchB)) {
			if (rotary_function >= 2) {
				if (pal_change) {
					updatePaletteIndex(target_palette);
					//palette_index++;
					palette_index = random8(g_gradient_palette_count + 1);
					//if (palette_index > g_gradient_palette_count - 1) { palette_index = 0; }
					target_palette = g_gradient_palettes[palette_index];
					Serial.print("Palette number: ");
					Serial.println(palette_index);
					print_palette(palette_index);
				}
				pal_change = 1;
			}
		}
	}


	// Palette transitions - always running TODO consider shortening this?
	EVERY_N_MILLISECONDS(50) {
		uint8_t maxChanges = 24;
		nblendPaletteTowardPalette(current_palette, target_palette, maxChanges);
	}

	// Dynamically change delay
	EVERY_N_MILLIS_I(this_timer, this_delay) {
		this_timer.setPeriod(this_delay);
		if (transitioning) {
			strobe_mode(old_mode, 0, 1);
		}
		strobe_mode(led_mode, 0, 0);
	}

	if (transitioning) {
		glitter = 1;
		if (transition_wait) {
			blending_ratio += 1;
		}
		for (int i = 0; i < NUM_LEDS; i++) {
			leds[i] = blend(old_leds[i], cur_leds[i], blending_ratio);
		}
		this_delay = (this_delay + target_delay) / 2;
		if (blending_ratio >= 255) {
			transitioning = 0;
			blending_ratio = 0;
			glitter = 0;
			fill_solid(old_leds, NUM_LEDS, CRGB(0, 0, 0));
			this_delay = target_delay;
		}
		transition_wait = !transition_wait;
	}
	else {
		for (int i = 0; i < NUM_LEDS; i++) {
			leds[i] = cur_leds[i];
		}
	}


	// Optionally add glitter
	if (glitter) addglitter(10);

	//show_at_max_brightness_for_power();
	FastLED.show();
}

/*
 * Sets the mode/routine for the LEDs.
 *
 * @param newMode : the mode to set the leds to
 * @param mc      : signifies if we're changing modes or not
 */
void strobe_mode(uint8_t newMode, bool mc, bool old) {
	// void strobe_mode(uint8_t newMode, bool mc){
  // If this_ is a *new* mode, clear out LED array.
	if (mc) {
		//fill_solid(leds, NUM_LEDS, CRGB( 0, 0, 0)); // comment out for transitioning
		fill_solid(cur_leds, NUM_LEDS, CRGB(0, 0, 0));
		Serial.print("Mode: ");
		Serial.println(led_mode);
	}

	switch (newMode) {

		// 0 - two-sin TODO COMBINE with others or remove
	case  0:
		if (mc) { this_delay = 10; all_freq = 4; this_speed = 1; that_speed = 1; this_hue = 0; that_hue = 128; this_rot = 1; that_rot = 1; this_cutoff = 128; that_cutoff = 192; }
		two_sin(old);
		break;

		// 1 - two-sin TODO combine with others or remove
	case  1:
		if (mc) { this_delay = 10; all_freq = 4; this_speed = -1; that_speed = 0; this_hue = 64; that_hue = 192; this_rot = 0; that_rot = 0; this_cutoff = 64; that_cutoff = 192; }
		two_sin(old);
		break;

		// 2 - two-sin // TODO combine with others or REMOVE
	case  2:
		if (mc) { this_delay = 10; all_freq = 6; this_speed = 2; that_speed = 3; this_hue = 96; that_hue = 224; this_rot = 0; that_rot = 0; this_cutoff = 64; that_cutoff = 64; }
		two_sin(old);
		break;

		// 3 - two-sin TODO combine with other two sins or remove
	case 3:
		if (mc) { this_delay = 20; all_freq = 10; this_speed = 1; that_speed = -2; this_hue = 48; that_hue = 160; this_rot = 1; that_rot = -1; this_cutoff = 128; that_cutoff = 192; }
		two_sin(old);
		break;

		// 4 - two-sin_ring TODO Transition with 52
	case 4:
		if (mc) { this_delay = 20; all_freq = 10; this_speed = 1; that_speed = -2; this_hue = 48; that_hue = 160; this_rot = 1; that_rot = -1; this_cutoff = 128; that_cutoff = 192; }
		two_sin_ring(old);
		break;

		// 5 - two-sin TODO this looks really cool... nice rotating trade-off... find out why
	case 5:
		if (mc) { this_delay = 10; all_freq = 20; this_speed = 2; that_speed = -1; this_hue = 24; that_hue = 180; this_rot = 0; that_rot = 1; this_cutoff = 64; that_cutoff = 128; }
		two_sin(old);
		break;

		// 6 - two-sin_ring TODO tranisition with 48 and 52, maybe some back and forths
	case 6:
		if (mc) { this_delay = 10; all_freq = 20; this_speed = 2; that_speed = -1; this_hue = 24; that_hue = 180; this_rot = 0; that_rot = 1; this_cutoff = 64; that_cutoff = 128; }
		two_sin_ring(old);
		break;

		// 7 - two-sin ring, transition with other two-sins, 44, 48, 52, especially 52
	case 7:
		if (mc) { this_delay = 10; all_freq = 6; this_speed = 2; that_speed = 3; this_hue = 96; that_hue = 224; this_rot = 0; that_rot = 0; this_cutoff = 64; that_cutoff = 64; }
		two_sin_ring(old);
		break;

		// 8 - two-sin ring, TODO mix with other twosins or m2
	case 8:
		if (mc) { this_delay = 10; all_freq = 16; this_speed = 4; that_speed = 1; this_hue = 0; that_hue = 128; this_rot = 1; that_rot = 1; this_cutoff = 128; that_cutoff = 192; }
		two_sin_ring(old);
		break;

		// 9 - two-sin_ring GOOD AS IS, transition with 48
	case 9:
		if (mc) { this_delay = 10; this_speed = 2; that_speed = 3; this_hue = 96; that_hue = 224; this_rot = 1; that_rot = 2; this_cutoff = 128; that_cutoff = 64; }
		two_sin_ring(old);
		break;

		// 10 - two-sin TODO REMOVE or combine in transitions
	case 10:
		if (mc) { this_delay = 10; all_freq = 16; this_speed = 2; that_speed = 3; this_hue = 96; that_hue = 224; this_rot = 1; that_rot = 2; this_cutoff = 128; that_cutoff = 64; }
		two_sin(old);
		break;

		// 11 - three-sin with palette kinda weird/redundant
	case 11:
		if (mc) { this_delay = 20; mul1 = 5; mul2 = 8; mul3 = 2; }
		three_sin_pal_ring(old);
		break;

		// 12 - three-sin with palette
	case 12:
		if (mc) { this_delay = 20; mul1 = 6; mul2 = 9; mul3 = 11; target_palette = bhw2_14_gp; }
		three_sin_pal_ring(old);
		break;

		// 13 - three-sin with palette // looks cool with ofaurora_gp palette TODO find more palettes
	case 13:
		if (mc) { this_delay = 20; mul1 = 3; mul2 = 4; mul3 = 5; target_palette = cequal_gp; }
		three_sin_pal_ring(old);
		break;

		// 14 - one-sin with rainbow palette // TODO find something good to transition with, or REMOVE
	case 14:
		if (mc) { this_delay = 6; target_palette = RainbowColors_p; all_freq = 20; bg_clr = 0; bg_bri = 0; this_bright = 255; start_index = 64; this_inc = 2; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 6; wave_brightness = 255; }
		one_sin_pal(old);
		break;

		// 15 - one-sin with rainbow palette_ring //TODO find palette... f2 is kinda cool
	case 15:
		if (mc) { this_delay = 5; target_palette = ib_jul01_gp; all_freq = 8; bg_clr = 0; bg_bri = 0; this_bright = 255; start_index = 64; this_inc = 1; this_phase = 0; this_cutoff = 200; this_rot = 8; this_speed = 128; wave_brightness = 255; }
		one_sin_pal_ring(old);
		break;

		// 16 - one-sin with rainbow palette_ring TODO find palette, check one_sin_tests TODO remove either 15 or 16
	case 16:
		if (mc) { this_delay = 5; target_palette = Sunset_Real_gp; all_freq = 20; bg_clr = 0; bg_bri = 0; this_bright = 255; start_index = 64; this_inc = 2; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 6; wave_brightness = 255; }
		one_sin_pal_ring(old);
		break;

		// 17 - serendipitous with palette TODO combine with twinkle or confetti
	case 17:
		if (mc) { this_delay = 5; target_palette = ForestColors_p; }
		serendipitous_pal(old);
		break;

		// 18 - noise8 with palette_ring TODO maybe find palette, or remove
	case 18:
		if (mc) { this_delay = 10; target_palette = OceanColors_p; palette_change = 1; }
		noise8_pal_ring(old);
		break;

		// 19 - circular noise with party palette_ring TODO if keep, maybe let palettes change, or find the right palette
	case 19:
		if (mc) { this_delay = 10; target_palette = PartyColors_p; }
		circnoise_pal_2_ring(old);
		break;

		// 20 - confetti with party palette_ring TODO KEEP ONE CONFETTI
	case 20:
		if (mc) { this_delay = 20; target_palette = PartyColors_p; this_inc = 1; this_hue = 192; this_sat = 255; this_fade = 2; this_diff = 32; this_bright = 255; }
		confetti_pal_ring(old);
		break;

		// 21 - noise8 with lava palette TODO find palette or remove kinda weird
	case 21:
		if (mc) { this_delay = 10; target_palette = LavaColors_p; palette_change = 0; }
		noise8_pal(old);
		break;

		// 22 - circular noise with party palette_ring TODO Find Palette
	case 22:
		if (mc) { this_delay = 10; target_palette = PartyColors_p; }
		circnoise_pal_3_ring(old);
		break;

		// 23 - confetti with forest palette_ring
	case 23:
		if (mc) { this_delay = 15; target_palette = ForestColors_p; this_inc = 1; this_hue = random8(255); this_fade = 1; this_bright = 255; }
		confetti_pal_ring(old);
		break;

		// 24 - noise8 with lava palette_ring 
	case 24:
		if (mc) { this_delay = 10; target_palette = LavaColors_p; palette_change = 0; scale = 500; }
		noise8_pal_ring(old);
		break;

		// 25 - rainbow march with narrow waves TODO combine with other rainbows or remove
	case 25:
		if (mc) { this_delay = 10; this_rot = 2; this_diff = 10; }
		rainbow_march(old);
		break;

		// 26 - pride rainbows
	case 26:
		if (mc) { this_delay = 10; }  // maybe update delay?
		pride(old);
		break;

		// 27 - rainbow march with slow, long waves
	case 27:
		if (mc) { this_delay = 25; this_rot = 1; this_diff = 1; }
		rainbow_march(old);
		break;

		// 28 - rainbow march with wide waves
	case 28:
		if (mc) { this_delay = 10; this_rot = 1; this_diff = 1; }
		rainbow_march_ring(old);
		break;

		// 29 - rainbow march with narrow waves
	case 29:
		if (mc) { this_delay = 10; this_rot = 2; this_diff = 10; }
		rainbow_march_ring(old);
		break;

		// 30 - ripple2
	case 30:
		if (mc) { this_delay = 25; this_fade = 255; rip_fade = 128; }
		ripple2(old);
		break;

		// 31 - matrix with forest palette_ring TODO Find better GREEN palette
	case 31:
		if (mc) { this_delay = 10; target_palette = ForestColors_p; this_index = 192; this_rot = 1; this_bright = 255; bg_clr = 50; bg_bri = 0; }
		matrix_pal_ring(old);
		break;

		// 32 - juggle mode with ocean palette_ring
	case 32:
		if (mc) { this_delay = 10; numdots_ring = 4; target_palette = OceanColors_p; this_fade = 32; this_beat = 12; this_bright = 255; this_diff = 20; juggle_index_reset = 1; }
		juggle_pal_ring(old);
		break;

		// 33 - juggle mode one direction
	case 33:
		if (mc) { this_delay = 5; numdots_ring = 5; target_palette = LavaColors_p; this_fade = 16; this_beat = 6; this_bright = 255; this_diff = 50; juggle_index_reset = 1; }
		juggle_pal_ring_onedir(old);
		break;

		// 34 - juggle mode ring TODO find positino and palette
	case 34:
		if (mc) { this_delay = 10; numdots_ring = 4; target_palette = bhw2_23_gp; this_fade = 32; this_beat = 6; this_bright = 255; this_diff = 32; juggle_index_reset = 1; }
		juggle_pal_ring(old);
		break;

		// 35 - juggle mode one direction TODO find best palette, this_diff, this_beat
	case 35:
		if (mc) { this_delay = 5; numdots_ring = 5; target_palette = purple_flower_gp; this_fade = 16; this_beat = 6; this_bright = 255; this_diff = 50; juggle_index_reset = 1; }
		juggle_pal_ring_onedir(old);
		break;

		// 36 - spiral sin 1 TODO find good palette
	case 36:
		if (mc) { this_delay = 5; start_index = 0; this_inc = 1; this_rot = 4; all_freq = 20; this_phase = 0; this_speed = 127; }
		spiral_sin(old);
		break;

		// 37 - one sin spiral TODO find good palette
	case 37:
		if (mc) { this_delay = 4; target_palette = RainbowColors_p; all_freq = 20; bg_clr = 0; bg_bri = 0; this_bright = 255; start_index = 64; this_inc = 1; this_phase = 0; this_cutoff = 224; this_rot = 0; this_speed = 3; wave_brightness = 255; }
		one_sin_spiral(old);
		break;

		// 38 - twinkle TODO find best palette
	case 38:
		if (mc) { this_delay = 15; twinkle_speed = 4; twinkle_density = 2; twinkle_bg = CRGB::Black; auto_select_background_color = 0; cool_like_incandescent = 1; }
		twinkle(old);
		break;

		// 39 - fire rings
	case 39:
		if (mc) { this_delay = 10; cooling1 = 80; sparking1 = 90; cooling2 = 55; sparking2 = 70; cooling3 = 70; sparking3 = 70; cooling4 = 55; sparking4 = 90; }
		fire_rings(old);
		break;

		// 40 - fire mirror with rings
	case 40:
		if (mc) { this_delay = 10; cooling1 = 80; sparking1 = 90; cooling2 = 55; sparking2 = 70; cooling3 = 70; sparking3 = 70; cooling4 = 55; sparking4 = 90; }
		fire_mirror_rings(old);
		break;

		// 41 - juggle fire rings
	case 41:
		if (mc) { this_delay = 7; target_palette = es_emerald_dragon_01_gp; numdots_ring = 3; jug_fade = 32; this_beat = 10; this_diff = 80; cooling1 = 80; sparking1 = 40; cooling2 = 80; sparking2 = 30; cooling3 = 80; sparking3 = 35; cooling4 = 75; sparking4 = 45; juggle_index_reset = 0; }
		juggle_fire(old);
		break;

		// 42 - juggle individual rings one dir fire
	case 42:
		if (mc) { this_delay = 7; target_palette = hallows_gp; numdots_ring = 4; ringBeat[0] = 12; ringBeat[1] = 5; ringBeat[2] = 10; ringBeat[3] = 6; this_diff = 32; this_fade = 16; cooling1 = 80; sparking1 = 40; cooling2 = 80; sparking2 = 30; cooling3 = 80; sparking3 = 35; cooling4 = 75; sparking4 = 45; juggle_index_reset = 1; }
		juggle_fire_individual(old);
		break;

		// 43 - juggle individual rings one dir
	case 43:
		if (mc) { this_delay = 7; target_palette = hallows_gp; numdots_ring_arr[0] = 4; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = random8(5); numdots_ring_arr[3] = 3; ringBeat[0] = 12; ringBeat[1] = 5; ringBeat[2] = 12; ringBeat[3] = 6; this_diff = 32; this_fade = 16; juggle_index_reset = 0; }
		juggle_pal_individual_ring_onedir_all(old);
		break;

		// 44 - juggle individual rings one dir fire same dir
	case 44:
		if (mc) { this_delay = 7; target_palette = hallows_gp;  numdots_ring = 4; ringBeat[0] = 12; ringBeat[1] = 5; ringBeat[2] = 12; ringBeat[3] = 6; this_diff = 32; this_fade = 16; cooling1 = 80; sparking1 = 20; cooling2 = 90; sparking2 = 15; cooling3 = 85; sparking3 = 20; cooling4 = 80; sparking4 = 25; juggle_index_reset = 0; }
		juggle_fire_individual_same_dir(old);
		break;

		// 45 - colorwave
	case 45:
		if (mc) { this_delay = 10; target_palette = Skydye11_gp; }
		colorwave(old);
		break;

		// 46 - bouncing balls
	case 46:
		if (mc) { this_delay = 5; this_fade = 64; }
		bouncing_balls(old);
		break;

		// 47 -bouncing balls where the colors change
	case 47:
		if (mc) { this_delay = 5; this_fade = 32; }
		bouncing_balls2(old);
		break;

		// 48 - matrix_saw
	case 48:
		if (mc) { this_delay = 10; this_fade = 64; target_palette = bhw2_22_gp; }
		matrix_saw(old);
		break;

		// 49 - plasma
	case 49:
		if (mc) { this_delay = 10; target_palette = ib15_gp; }
		plasma(old);
		break;

		// 50 - fire
	case 50:
		if (mc) { this_delay = 10; cooling = 80; sparking = 60; }
		fire(old);
		break;

		// 51 - fire_pal
	case 51:
		if (mc) { this_delay = 10; cooling = 50; sparking = 90; target_palette = blue_fire_gp; }
		fire_pal(old);
		break;

		// 52 - two_sin_pal_ring
	case 52:
		if (mc) { this_delay = 10; all_freq = 16; this_speed = 4; that_speed = 1; this_hue = 0; that_hue = 128; this_rot = 1; that_rot = 1; this_cutoff = 128; that_cutoff = 192; }
		two_sin_pal_ring(old);
		break;

		// 53 - three_sin_pal
	case 53:
		if (mc) { this_delay = 20; mul1 = 10; mul2 = 2; mul3 = 11; target_palette = bhw2_14_gp; }
		three_sin_pal(old);
		break;

		// 54 - serenditpitous_pal_ring
	case 54:
		if(mc) {this_delay = 10; target_palette = lava_gp; this_fade = 64;}
		serendipitous_pal_ring(old);
		break;

		// 55 - matrix_random_walk
	case 55:
		if (mc) { this_delay = 10; this_rot = 4; target_palette = slope_gp; this_fade = 32; }
		matrix_random_walk(old);
		break;

		// 56 - juggle_pal_individual_ring_all
	case 56:
		if (mc) { this_delay = 7; target_palette = hallows_gp; numdots_ring_arr[0] = 4; numdots_ring_arr[1] = 3; numdots_ring_arr[2] = random8(5); numdots_ring_arr[3] = 3; ringBeat[0] = 12; ringBeat[1] = 5; ringBeat[2] = 12; ringBeat[3] = 6; this_diff = 32; this_fade = 16; juggle_index_reset = 0; }
		juggle_pal_individual_ring_all(old);
		break;

		// 57 - spiral - broken
	case 57:
		led_mode = 60;
		//if (mc) { this_delay = 10; spiral_width = 3; spiral_inc = 2; this_hue = 200; }
		//spiral(old);
		break;

		// 58 - spiral_pal - broken
	case 58:
		led_mode = 60;
		//if (mc) { this_delay = 8; target_palette = bhw2_14_gp; spiral_width = 6; spiral_inc = 3; this_hue = 32; this_inc = 10; }
		//spiral_pal(old);
		break;

		// 59 - spiral_sin_sub
	case 59:

		if (mc) { this_delay = 10; target_palette = slope_gp; this_inc = 4; this_speed = 2; this_rot = 1; all_freq = 2; }
		spiral_sin_sub(old);
		break;

		// 60 - helix_spiral
	case 60:
		if (mc) { this_delay = 10; target_palette = bhw2_23_gp; this_inc = 2; this_speed = 1; this_rot = 10; all_freq = 8; that_speed = 2; bg_clr = 30; bg_bri = 16; }
		helix_spiral(old);
		break;

		// 61 - plasma_spiral
	case 61:
		if (mc) { this_delay = 10; target_palette = cw1_029_gp; }
		plasma_spiral(old);
		break;

		// 62 - plasma_spiral2
	case 62: 
		if (mc) { this_delay = 15; target_palette = vibrant_gp; }
		plasma_spiral2(old);
		break;

		// 63 -palette_spiral
	case 63:
		if (mc) { this_delay = 12; this_speed = 1; this_inc = 2; target_palette = es_landscape_59_gp; }
		palette_spiral(old);
		break;

		// 64 - fire
	case 64:
		if (mc) { this_delay = 10; cooling = 35; sparking = 35; }
		fire(old);
		break;

		// 65 - fire_pal
	case 65:
		if (mc) { this_delay = 15; cooling = 80; sparking = 80; target_palette = lava_gp; }
		fire_pal(old);
		break;

		// 66 - fire_mirror
	case 66:
		if (mc) { this_delay = 10; cooling = 40; sparking = 80; }
		fire_mirror(old);
		break;

		// 67 - fire_mirror_pal
	case 67:
		if (mc) { this_delay = 10; cooling = 80; sparking = 60; target_palette = Sunset_Real_gp; }
		fire_mirror_pal(old);
		break;

		// 68 - fire_pal_rings
	case 68:
		if (mc) { this_delay = 10; target_palette = parrot_gp; cooling1 = 30; cooling2 = 40; cooling3 = 50; cooling4 = 60; sparking1 = 80; sparking2 = 70; sparking3 = 60; sparking4 = 50; }
		fire_pal_rings(old);
		break;

		// 69 (nice) - fire_mirror_pal_rings
	case 69: //nice
		if(mc){ this_delay = 10; target_palette = cyberpunk_neon_gp; cooling1 = 60; cooling2 = 40; cooling3 = 90; cooling4 = 60; sparking1 = 80; sparking2 = 110; sparking3 = 160; sparking4 = 50; }
		fire_mirror_pal_rings(old);
		break;

		// 70 - circnoise_pal_1_ring
	case 70: 
		if (mc) { this_delay = 10; target_palette = bhw1_sunconure_gp; scale = 500; }
		circnoise_pal_1_ring(old);
		break;

		// 71 - circnoise_pal_4_ring
	case 71:
		if (mc) { this_delay = 15; target_palette = xanidu_2_gp; scale = 3000; }
		circnoise_pal_4_ring(old);
		break;

		// 72 - cylon
	case 72:
		led_mode = 71;
		//if (mc) { this_delay = 10; target_palette = apple_green_gp; }
		//cylon(old);
		break;

		// 73 - fade
	case 73:
		led_mode = 71;
		//if (mc) { this_delay = 20; this_hue = 69; }
		//fade(old);
		break;

		// 74 - fade_rainbow
	case 74:
		led_mode = 71;
		//if (mc) { this_delay = 30; }
		//fade_rainbow(old);
		break;

		// 75 - matrix_ray
	case 75:
		if (mc) { this_delay = 15; target_palette = blueice_gp; }
		matrix_ray(old);
		break;

		// 76 - juggle_pal_individual_ring_onedir_phase
	case 76:
		if (mc) { this_delay = 10; target_palette = Secondary_01a_gp; juggle_index_reset = 0; this_fade = 64; numdots = 4; this_beat = 8; this_diff = 4; jug16_phase = 8192; }
		juggle_pal_individual_ring_onedir_phase(old);
		break;

		// 77 - inoise_mover
	case 77:
		if (mc) { this_delay = 15; target_palette = a_gp; scale = 30; scale2 = 30; dist = 12345; }
		inoise_mover(old);
		break;

		// 78 - inoise_fire
	case 78:
		if (mc) { this_delay = 12; target_palette = lava_gp; scale = 20; scale2 = 3; this_index = 0; }
		inoise_fire(old);
		break;

		// 79 - movingdot - doesn't work
	case 79:
		led_mode = 78;
		//if (mc) { this_delay = 10; this_fade = 32; this_index = 1; blue_angle = 20; blue_low = 180; blue_high = 255; green_angle = 2; green_low = 100; green_high = 180; red_angle = 3; red_low = 0; red_high = 255; }
		//movingdot(old);
		break;


		// if more modes added, must update max_modes in variables
	}
}
