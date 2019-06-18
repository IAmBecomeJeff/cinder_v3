#ifndef CHECK_DIAL_H
#define CHECK_DIAL_H

void checkDial() {
	debouncer.update();
	if (debouncer.fell()) {
		pinSWstate = 0;
	}
	else {
		pinSWstate = 1;
	}

	if (!pinSWstate) {
		rotary_function += 1;
		if (rotary_function > 3) {
			rotary_function = 0;
		}

		Serial.print("Button Function: ");
		Serial.println(rotary_function);
	}


	aVal = digitalRead(pinA);   // Read pinA
	if ((aVal != pinALast)) {//&&(aVal==LOW)){      // If pinA has changed, update things.   Added the &&
		rotateCount = !rotateCount;   // If at 0, change to 1... if at 1 change to 0 and don't update.
		if (rotateCount) {    // Need to let it change twice
			switch (rotary_function) {

			case 0: // add !transitioning to let the new mode get set up
				old_mode = led_mode;
				if (digitalRead(pinB) != aVal) {   // Means pin A changed first, we're rotating CW
					led_mode++;      // Move to next pattern
				}
				else {            // Means pin B changed first, we're moving CCW
					led_mode--;       // Move to previous pattern
				}
				if (led_mode < 0) {
					led_mode = max_mode;
				}
				if (led_mode > max_mode) {
					led_mode = 0;
				}
				update_old_variables();
				transitioning = 1;
				strobe_mode(led_mode, 1, 0);
				print_mode(mode_number);
				target_delay = this_delay;
				this_delay = old_this_delay;
				break;

			case 1:
				updatePaletteIndex(target_palette);
				if (digitalRead(pinB) != aVal) {
					palette_index++;
				}
				else {
					palette_index--;
				}
				if (palette_index > g_gradient_palette_count - 1) {
					palette_index = 0;
				}
				if (palette_index < 0) {
					palette_index = g_gradient_palette_count - 1;
				}
				target_palette = g_gradient_palettes[palette_index];
				Serial.print("Palette number: ");
				Serial.println(palette_index);
				print_palette(palette_index);
				break;

			case 2:
				if (digitalRead(pinB) != aVal) {
					if (this_delay == 1) {
						this_delay = 1;
					}
					else {
						this_delay--;
					}
				}
				else {
					this_delay++;
				}
				constrain(this_delay, 1, 255);
				Serial.print("Delay: ");
				Serial.println(this_delay);
				break;

			case 3:
				if (digitalRead(pinB) != aVal) {
					max_bright++;
				}
				else {
					max_bright--;
				}
				constrain(max_bright, 0, 128);
				LEDS.setBrightness(max_bright);
				Serial.print("Brightness: ");
				Serial.println(max_bright);
				break;

			}
		}
	}
	pinALast = aVal;
}

#endif