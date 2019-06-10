#ifndef READ_KEYBOARD_H
#define READ_KEYBOARD_H

/*
 * Takes in keyboard input and executes commands.
 *
 * Serial timeout value here is important.
 * We should make sure it's set high enough
 * to type the entire command within the timeout.
 */
void readkeyboard() {
	while (Serial.available() > 0) {

		in_byte = Serial.read();

		// Don't print carriage return
		if (in_byte != 10) {
			Serial.print("# ");
			Serial.print(char(in_byte));
			Serial.print(" ");
		}

		switch (in_byte) {

				// a {hue} - set entire strip to {hue} (0-255)
			case 97:
				led_mode = 0;
				this_arg = Serial.parseInt();
				this_arg = constrain(this_arg, 0, 255);
				Serial.print("Entire Strip Hue: ");
				Serial.println(this_arg);
				fill_solid(leds, NUM_LEDS, CHSV(this_arg, 255, 255));
				break;

				// b {brightness} - set entire strip to {brightness} (0-255)
			case 98:
				max_bright = Serial.parseInt();
				max_bright = constrain(max_bright, 0, 255);
				Serial.print("Brightness: ");
				Serial.println(max_bright);
				LEDS.setBrightness(max_bright);
				break;

				// c - swtich blending: 0 = NOBLEND, 1 = LINEARBLEND
			case 99:
				this_arg = Serial.parseInt();
				Serial.print("Blending: ");
				if (this_arg) { current_blending = LINEARBLEND; Serial.println("LINEARBLEND"); }
				else { current_blending = NOBLEND; Serial.println("NOBLEND"); }
				break;

				// d {delay} - set the delay amount to {delay} (0-255)
			case 100:
				this_arg = Serial.parseInt();
				this_delay = constrain(this_arg, 0, 255);
				Serial.print("Delay: ");
				Serial.println(this_delay);
				break;

				// f {palette_number} - set the current palette
			case 102:
				demo_run = 0;
				palette_change = 0;
				this_arg = Serial.parseInt();
				g_current_palette_number = this_arg % g_gradient_palette_count;
				target_palette = g_gradient_palettes[g_current_palette_number];
				Serial.print("Palette: ");
				Serial.println(g_current_palette_number);
				break;

				// g - toggle glitter
			case 103:
				glitter = !glitter;
				Serial.println("Glittering... ");
				break;

				// h {hue} - set hue variable to {hue} (0-255)
			case 104:
				this_arg = Serial.parseInt();
				this_hue = constrain(this_arg, 0, 255);
				Serial.print("This_hue: ");
				Serial.println(this_hue);
				break;

				// i (this_inc) - set this_inc (0-255)
			case 105:
				this_arg = Serial.parseInt();
				this_inc = constrain(this_arg, 0, 255);
				Serial.print("this_inc: ");
				Serial.println(this_inc);
				break;

				// j (this_speed) - (0-255)
			case 106:
				this_arg = Serial.parseInt();
				this_speed = constrain(this_arg, 0, 255);
				Serial.print("this_speed: ");
				Serial.println(this_speed);
				break;

				// k (this_rot) - (0-255)
			case 107:
				this_arg = Serial.parseInt();
				this_rot = constrain(this_arg, 0, 255);
				Serial.print("this_rot: ");
				Serial.println(this_rot);
				break;

				// l (this_cutoff) - (0-255)
			case 108:
				this_arg = Serial.parseInt();
				this_cutoff = constrain(this_arg, 0, 255);
				Serial.print("this_cutoff");
				Serial.println(this_cutoff);
				break;

				// m {mode} - select mode {mode} (0-255)
			case 109:
				old_mode = led_mode;
				led_mode = Serial.parseInt();
				led_mode = constrain(led_mode, 0, max_mode);
				Serial.print("Mode: ");
				Serial.println(led_mode);
				update_old_variables();
				transitioning = 1;
				strobe_mode(led_mode, 1, 0); // strobe the updated mode, mc = 1, old = 0 (so cur_leds)
				print_mode(mode_number);
				target_delay = this_delay;
				this_delay = old_this_delay;
				break;
				
				// n (all_freq) - (0-255)
			case 110:
				this_arg = Serial.parseInt();
				all_freq = constrain(this_arg, 0, 255);
				Serial.print("all_freq: ");
				Serial.println(all_freq);
				break;

				// o Change this_fade (0-255)
			case 111:
				this_arg = Serial.parseInt();
				this_fade = constrain(this_arg, 0, 255);
				Serial.print("this_fade: ");
				Serial.println(this_fade);
				break;

				// p Change numdots_ring (0-255)
			case 112:
				this_arg = Serial.parseInt();
				numdots_ring = constrain(this_arg, 0, 255);
				Serial.print("numdots_ring: ");
				Serial.println(numdots_ring);
				break;

				// q Change this_beat (0-255)
			case 113:
				this_arg = Serial.parseInt();
				this_beat = constrain(this_arg, 0, 255);
				Serial.print("this_beat: ");
				Serial.println(this_beat);
				break;

				// r Change all_freq (0-255)
			case 114:
				this_arg = Serial.parseInt();
				this_diff = constrain(this_arg, 0, 255);
				Serial.print("this_diff: ");
				Serial.println(this_diff);
				break;

				// s {saturation} - set saturation to {saturation} (0-255)
			case 115:
				this_arg = Serial.parseInt();
				this_sat = constrain(this_arg, 0, 255);
				Serial.print("Saturation: ");
				Serial.println(this_sat);
				break;

				// t {0/1} - juggle_index_reset
			case 116:
				this_arg = Serial.parseInt();
				if (this_arg) { juggle_index_reset = 1; }
				else { juggle_index_reset = 0; }
				Serial.print("Juggle_index_reset: ");
				Serial.println(juggle_index_reset);
				break;

				// u Change this_bright (0-255)
			case 117:
				this_arg = Serial.parseInt();
				this_bright = constrain(this_arg, 0, 255);
				Serial.print("this_bright: ");
				Serial.println(this_bright);
				break;

				// v Change numdots (0-255)
			case 118:
				this_arg = Serial.parseInt();
				numdots = constrain(this_arg, 0, 255);
				Serial.print("numdots: ");
				Serial.println(numdots);
				break;

				// w - write current mode to EEPROM
			case 119:
				EEPROM.write(STARTMODE, led_mode);
				Serial.print("Writing keyboard: ");
				Serial.println(led_mode);
				break;

				// C - Change Cooling
			case 67:
				this_arg = Serial.parseInt();
				cooling = constrain(this_arg, 0, 255);
				Serial.print("Cooling: ");
				Serial.println(cooling);
				break;

				// S - Change sparking
			case 83:
				this_arg = Serial.parseInt();
				sparking = constrain(this_arg, 0, 255);
				Serial.print("Sparking: ");
				Serial.println(sparking);
				break;

				// M - Get mode
			case 77:
				print_mode(mode_number);
				break;

				// P - Get Palette
			case 80:
				print_palette(palette_index);
				break;
		}
	}
}

#endif
