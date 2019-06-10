#ifndef CHECK_DIAL_H
#define CHECK_DIAL_H

//void checkDial() {
//	int reading = digitalRead(pinSW);		// check button
//	if (reading != lastPinSWstate){			// is it different from before?
//		lastDebounceTime = millis();		// set time
//	}
//	if ((millis() - lastDebounceTime) > debounceDelay) {	// is current time 50ms since the button was pressed?
//		if (reading != pinSWstate){			// if the button state has changed
//			pinSWstate = reading;
//			if (!pinSWstate){
//				rotary_function +=1;
//				if (rotary_function > 2){
//					rotary_function = 0;
//				}
//			}
//		}
//	}
//	lastPinSWstate = reading;
//	
//	if (!(digitalRead(pinSW))){
//		rotary_function += 1;
//		if (rotary_function > 3){
//			rotary_function = 0;
//		}
//		
//    Serial.print("Button Function: ");
//    Serial.println(rotary_function);
//	}
//	aVal = digitalRead(pinA);		// Read pinA
//	if (aVal != pinALast){			// If pinA has changed, update things
//		rotateCount = !rotateCount;   // If at 0, change to 1... if at 1 change to 0 and don't update.
//		if (rotateCount){    // Need to let it change twice
//			switch (rotary_function) {
//        
//				case 0:
//					if (digitalRead(pinB) != aVal){		// Means pin A changed first, we're rotating CW
//						led_mode ++;			// Move to next pattern
//					} else {						// Means pin B changed first, we're moving CCW
//						led_mode--;				// Move to previous pattern
//					}
//				    if (led_mode < 0){
//						led_mode = max_mode;
//				    }
//				    if (led_mode > max_mode){
//						led_mode = 0;
//				    }
//				    strobe_mode(led_mode, 1);
//				  break;
//					
//				case 1:
//					updatePaletteIndex(target_palette);
//					if (digitalRead(pinB) != aVal){
//						palette_index++;
//					} else {
//						palette_index--;
//					}
//					if (palette_index > g_gradient_palette_count-1){
//						palette_index = 0;
//					}
//					if (palette_index < 0){
//						palette_index = g_gradient_palette_count-1;
//					}
//					target_palette = g_gradient_palettes[palette_index];
//					Serial.print("Palette number: ");
//					Serial.println(palette_index);
//					break;
//					
//				case 2:
//					if (digitalRead(pinB) != aVal){
//						this_delay ++;
//					} else {
//						this_delay --;
//					}
//					constrain(this_delay, 0, 255);
//					Serial.print("Delay: ");
//					Serial.println(this_delay);
//					break;
//					
//				case 3:
//					if (digitalRead(pinB) != aVal){
//						this_bright ++;
//					} else {
//						this_bright --;
//					}
//					constrain(this_bright,0,max_bright);
//					LEDS.setBrightness(this_bright);
//					Serial.print("Brightness: ");
//					Serial.println(this_bright);
//					break;
//					
//			}
//		}
//		pinALast = aVal;		
//	}
//}
#endif
