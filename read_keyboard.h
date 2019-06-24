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

				// A spiral_width
			case 65:
				this_arg = Serial.parseInt();
				spiral_width = constrain(this_arg, 0, 255);
				Serial.print("spiral_width: ");
				Serial.println(spiral_width);
				break;

				// B spiral_inc
			case 66:
				this_arg = Serial.parseInt();
				spiral_inc = constrain(this_arg, 0, 255);
				Serial.print("spiral_inc: ");
				Serial.println(spiral_inc);
				break;

				// C - Change Cooling
			case 67:
				this_arg = Serial.parseInt();
				if (this_arg < 256) {
					cooling = constrain(this_arg, 0, 255);
					Serial.print("cooling: ");
					Serial.println(cooling);
				}
				else if (this_arg > 1000 && this_arg < 1256) {
					cooling1 = constrain(this_arg % 1000, 0, 255);
					Serial.print("cooling1: ");
					Serial.println(cooling1);
				}
				else if (this_arg > 2000 && this_arg < 2256) {
					cooling2 = constrain(this_arg % 2000, 0, 255);
					Serial.print("cooling2: ");
					Serial.println(cooling2);
				}
				else if (this_arg > 3000 && this_arg < 3256) {
					cooling3 = constrain(this_arg % 3000, 0, 255);
					Serial.print("cooling3: ");
					Serial.println(cooling3);
				}
				else if (this_arg > 4000 && this_arg < 4256) {
					cooling4 = constrain(this_arg % 4000, 0, 255);
					Serial.print("cooling4: ");
					Serial.println(cooling4);
				}
				else {
					Serial.println("cooling out of range");
				}
				break;

				// D mul1 (0-255)
			case 68:
				this_arg = Serial.parseInt();
				mul1 = constrain(this_arg, 0, 255);
				Serial.print("mul1: ");
				Serial.println(mul1);
				break;

				// E mul2 (0-255)
			case 69:
				this_arg = Serial.parseInt();
				mul2 = constrain(this_arg, 0, 255);
				Serial.print("mul2: ");
				Serial.println(mul2);
				break;

				// F mul3 (0-255)
			case 70:
				this_arg = Serial.parseInt();
				mul3 = constrain(this_arg, 0, 255);
				Serial.print("mul3: ");
				Serial.println(mul3);
				break;

				// G bg_clr (0-255)
			case 71:
				this_arg = Serial.parseInt();
				bg_clr = constrain(this_arg, 0, 255);
				Serial.print("bg_clr: ");
				Serial.println(bg_clr);
				break;

				// H bg_bri (0-255)
			case 72:
				this_arg = Serial.parseInt();
				bg_bri = constrain(this_arg, 0, 255);
				Serial.print("bg_bri: ");
				Serial.println(bg_bri);
				break;

				// I scale 
			case 73:
				this_arg = Serial.parseInt();
				scale = constrain(this_arg, 0, 65535);
				Serial.print("scale: ");
				Serial.println(scale);
				break;

				// J (that_speed) - (0-255)
			case 74:
				this_arg = Serial.parseInt();
				that_speed = constrain(this_arg, 0, 255);
				Serial.print("that_speed: ");
				Serial.println(that_speed);
				break;


				// K (that_rot) - (0-255)
			case 75:
				this_arg = Serial.parseInt();
				that_rot = constrain(this_arg, 0, 255);
				Serial.print("that_rot: ");
				Serial.println(that_rot);
				break;

				// L (thatcutoff) - (0-255)
			case 76:
				this_arg = Serial.parseInt();
				that_cutoff = constrain(this_arg, 0, 255);
				Serial.print("that_cutoff: ");
				Serial.println(that_cutoff);
				break;

				// M - Get mode
			case 77:
				print_mode(mode_number);
				break;

				// N scale2 
			case 78:
				this_arg = Serial.parseInt();
				scale2 = constrain(this_arg, 0, 255);
				Serial.print("scale2: ");
				Serial.println(scale2);
				break;

				// O rip_fade
			case 79:
				this_arg = Serial.parseInt();
				rip_fade = constrain(this_arg, 0, 255);
				Serial.print("rip_fade: ");
				Serial.println(rip_fade);
				break;

				// P - Get Palette
			case 80:
				print_palette(palette_index);
				break;

				// Q - ringBeat
			case 81:
				this_arg = Serial.parseInt();
				if (this_arg < 256) {
					ringBeat[0] = constrain(this_arg, 0, 255);
					Serial.print("ringBeat[0]: ");
					Serial.println(ringBeat[0]);
				}
				else if (this_arg > 1000 && this_arg < 1256) {
					ringBeat[1] = constrain(this_arg, 0, 255);
					Serial.print("ringBeat[1]: ");
					Serial.println(ringBeat[1]);
				}
				else if (this_arg > 2000 && this_arg < 2256) {
					ringBeat[2] = constrain(this_arg, 0, 255);
					Serial.print("ringBeat[2]: ");
					Serial.println(ringBeat[2]);
				}
				else if (this_arg > 3000 && this_arg < 3256) {
					ringBeat[3] = constrain(this_arg, 0, 255);
					Serial.print("ringBeat[3]: ");
					Serial.println(ringBeat[3]);
				}
				else {
					Serial.println("ringBeat outta range");
				}
				break;

				// R - numdots
			case 82:
				this_arg = Serial.parseInt();
				numdots = constrain(this_arg, 0, 255);
				Serial.print("numdots: ");
				Serial.println(numdots);
				break;

				// S - Change sparking
			case 83:
				this_arg = Serial.parseInt();
				if (this_arg < 256) {
					sparking = constrain(this_arg, 0, 255);
					Serial.print("sparking: ");
					Serial.println(sparking);
				}
				else if (this_arg > 1000 && this_arg < 1256) {
					sparking1 = constrain(this_arg % 1000, 0, 255);
					Serial.print("sparking1: ");
					Serial.println(sparking1);
				}
				else if (this_arg > 2000 && this_arg < 2256) {
					sparking2 = constrain(this_arg % 2000, 0, 255);
					Serial.print("sparking2: ");
					Serial.println(sparking2);
				}
				else if (this_arg > 3000 && this_arg < 3256) {
					sparking3 = constrain(this_arg % 3000, 0, 255);
					Serial.print("sparking3: ");
					Serial.println(sparking3);
				}
				else if (this_arg > 4000 && this_arg < 4256) {
					sparking4 = constrain(this_arg % 4000, 0, 255);
					Serial.print("sparking4: ");
					Serial.println(sparking4);
				}
				else {
					Serial.println("Sparking out of range...");
				}
				break;

				// T - jug16_phase
			case 84:
				this_arg = Serial.parseInt();
				jug16_phase = constrain(this_arg, 0, 65535);
				Serial.print("jug16_phase: ");
				Serial.println(jug16_phase);
				break;

				// U - 
			case 85:
				break;

				// V - 
			case 86:
				break;

				// W - 
			case 87:
				break;

				// X - 
			case 88:
				break;

				// Y - 
			case 89:
				break;

				// Z - 
			case 90:
				break;

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
        palette_index = g_current_palette_number;
				print_palette(g_current_palette_number);
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
				Serial.print("this_cutoff: ");
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
        updatePaletteIndex(target_palette);
				//print_mode(mode_number);
				print_variables(mode_number);
				target_delay = this_delay;
				this_delay = old_this_delay;
				break;
				
				// n (this_phase) - (0-255)
			case 110:
				this_arg = Serial.parseInt();
				this_phase = constrain(this_arg, 0, 255);
				Serial.print("this_phase: ");
				Serial.println(this_phase);
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

				// r Change this_diff (0-255)
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

				// u 
			case 117:
				Serial.println("");
				print_variables(mode_number);
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

				// x Change all_freq (0-255)
			case 120:
				this_arg = Serial.parseInt();
				all_freq = constrain(this_arg, 0, 255);
				Serial.print("all_freq: ");
				Serial.println(all_freq);
				break;

				// y - streamer_velocity (0 - 65535)
			case 121:
				this_arg = Serial.parseInt();
				streamer_velocity = constrain(this_arg, 0, 65535);
				Serial.print("streamer_velocity: ");
				Serial.println(streamer_velocity);
				break;

				// z - explosion_velocity (0 - 65535)
			case 122:
				this_arg = Serial.parseInt();
				explosion_velocity = constrain(this_arg, 0, 65535);
				Serial.print("explosion_velocity: ");
				Serial.println(explosion_velocity);
				break;
                
		}
	}
}

#endif
