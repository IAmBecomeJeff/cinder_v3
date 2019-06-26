#ifndef FIRE_H
#define FIRE_H

// Functions:
	// fire()			
		// Moves a fire along the strip, with the rings all the same

	// fire_pal()
		// Moves a fire along the strip with a palette, with the rings all the same

	// fire_mirror()
		// Fire from middle or ends, rings all the same

	// fire_mirror_pal()
		// Fire mirrored, with palette, rings all the same
		
	// fire_rings()
		// Fire with each strip a different flame

	// fire_pal_rings()
		// Fire with each strip a different flame, using palettes

	// fire_mirror_rings()
		// Mirrored fire, with each strip different flame
		
	// fire_mirror_pal_rings()
		// Mirrored fire, with palettes, each strip different
	


void fire(bool old){
	mode_number = 4;
	if (old) {
		// Array of temperature readings at each simulation cell
		static byte old_heat[STRIP_LENGTH];

		// Step 1.  Cool down every cell a little
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling * 10) / STRIP_LENGTH) + 2));
		}

		// Step 2.  Heat from each cell drifts 'up' and diffuses a little
		for (int k = STRIP_LENGTH - 3; k >= 2; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}

		// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
		if (random8() < old_sparking) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}

		// Step 4.  Map from heat cells to LED colors
		for (int j = 0; j < STRIP_LENGTH; j++) {
			CRGB hcolor = HeatColor(old_heat[j]);
			ringCRGB(1, j, hcolor.r, hcolor.g, hcolor.b);
			//  ringCRGB(j, HeatColor(heat[j]).r, HeatColor(heat[j]).g, HeatColor(heat[j]).b);
				//leds[j] = HeatColor( heat[j]);
		}
	}
	else {
		// Array of temperature readings at each simulation cell
		static byte heat[STRIP_LENGTH];

		// Step 1.  Cool down every cell a little
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / STRIP_LENGTH) + 2));
		}

		// Step 2.  Heat from each cell drifts 'up' and diffuses a little
		for (int k = STRIP_LENGTH - 3; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}

		// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
		if (random8() < sparking) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}

		// Step 4.  Map from heat cells to LED colors
		for (int j = 0; j < STRIP_LENGTH; j++) {
			CRGB hcolor = HeatColor(heat[j]);
			ringCRGB(0, j, hcolor.r, hcolor.g, hcolor.b);
			//  ringCRGB(j, HeatColor(heat[j]).r, HeatColor(heat[j]).g, HeatColor(heat[j]).b);
			//leds[j] = HeatColor( heat[j]);
		}
	}
}


// fire with a palette
void fire_pal(bool old){
	mode_number = 5;
	if (old) {
		// Array of temperature readings at each simulation cell
		static byte old_heat[STRIP_LENGTH];

		// Step 1.  Cool down every cell a little
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling * 10) / STRIP_LENGTH) + 2));
		}

		// Step 2.  Heat from each cell drifts 'up' and diffuses a little
		for (int k = STRIP_LENGTH - 1; k >= 2; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}

		// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
		if (random8() < sparking) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}

		// Step 4.  Map from heat cells to LED colors
		for (int j = 0; j < STRIP_LENGTH; j++) {
			// Scale the heat value from 0-255 down to 0-240
			// for best results with color palettes.
			byte colorindex = scale8(old_heat[j], 240);
			//CRGB color = ColorFromPalette( current_palette, colorindex);
			int pixelnumber;
			if (old_this_dir) {
				pixelnumber = (STRIP_LENGTH - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			ringPalette(1, pixelnumber, old_palette, colorindex);
			//leds[pixelnumber] = color;
		}
	}
	else {
		// Array of temperature readings at each simulation cell
		static byte heat[STRIP_LENGTH];

		// Step 1.  Cool down every cell a little
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / STRIP_LENGTH) + 2));
		}

		// Step 2.  Heat from each cell drifts 'up' and diffuses a little
		for (int k = STRIP_LENGTH - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}

		// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
		if (random8() < sparking) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}

		// Step 4.  Map from heat cells to LED colors
		for (int j = 0; j < STRIP_LENGTH; j++) {
			// Scale the heat value from 0-255 down to 0-240
			// for best results with color palettes.
			byte colorindex = scale8(heat[j], 240);
			//CRGB color = ColorFromPalette( current_palette, colorindex);
			int pixelnumber;
			if (this_dir) {
				pixelnumber = (STRIP_LENGTH - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			ringPalette(0, pixelnumber, current_palette, colorindex);
			//leds[pixelnumber] = color;
		}
	}
}



// fire mirrored from ends or center
void fire_mirror(bool old) {
	mode_number = 6;
	if (old) {
		static byte old_heat[STRIP_LENGTH / 2];
		for (int i = 0; i < STRIP_LENGTH / 2; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling * 10) / (STRIP_LENGTH / 2)) + 2));
		}
		for (int k = (STRIP_LENGTH / 2) - 1; k >= 2; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		if (old_this_dir) {
			for (int j = 0; j < STRIP_LENGTH / 2; j++) {
				CRGB hcolor = HeatColor(old_heat[j]);
				ringCRGB(1, j, hcolor.r, hcolor.g, hcolor.b);
				ringCRGB(1, STRIP_LENGTH - 1 - j, hcolor.r, hcolor.g, hcolor.b);
			}
		}
		else {
			for (int j = 0; j < STRIP_LENGTH / 2; j++) {
				CRGB hcolor = HeatColor(old_heat[j]);
				ringCRGB(1, (STRIP_LENGTH / 2) - 1 - j, hcolor.r, hcolor.g, hcolor.b);
				ringCRGB(1, (STRIP_LENGTH / 2) + j, hcolor.r, hcolor.g, hcolor.b);
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH / 2];
		for (int i = 0; i < STRIP_LENGTH / 2; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / (STRIP_LENGTH / 2)) + 2));
		}
		for (int k = (STRIP_LENGTH / 2) - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		if (this_dir) {
			for (int j = 0; j < STRIP_LENGTH / 2; j++) {
				CRGB hcolor = HeatColor(heat[j]);
				ringCRGB(0, j, hcolor.r, hcolor.g, hcolor.b);
				ringCRGB(0, STRIP_LENGTH - 1 - j, hcolor.r, hcolor.g, hcolor.b);
			}
		}
		else {
			for (int j = 0; j < STRIP_LENGTH / 2; j++) {
				CRGB hcolor = HeatColor(heat[j]);
				ringCRGB(0, (STRIP_LENGTH / 2) - 1 - j, hcolor.r, hcolor.g, hcolor.b);
				ringCRGB(0, (STRIP_LENGTH / 2) + j, hcolor.r, hcolor.g, hcolor.b);
			}
		}
	}
  
}//end fire_mirror



// fire mirrored from ends or center using palette
void fire_mirror_pal(bool old) {
	mode_number = 7;
	if (old) {
		static byte old_heat[STRIP_LENGTH / 2];
		for (int i = 0; i < STRIP_LENGTH / 2; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling * 10) / (STRIP_LENGTH / 2)) + 2));
		}
		for (int k = (STRIP_LENGTH / 2) - 1; k >= 2; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(old_heat[j], 240);
			CRGB color = ColorFromPalette(old_palette, colorindex);
			if (old_this_dir) {
				ringPalette(1, j, old_palette, colorindex);
				ringPalette(1, STRIP_LENGTH - 1 - j, old_palette, colorindex);
			}
			else {
				ringPalette(1, (STRIP_LENGTH / 2) - 1 - j, old_palette, colorindex);
				ringPalette(1, (STRIP_LENGTH / 2) + j, old_palette, colorindex);
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH / 2];
		for (int i = 0; i < STRIP_LENGTH / 2; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / (STRIP_LENGTH / 2)) + 2));
		}
		for (int k = (STRIP_LENGTH / 2) - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(heat[j], 240);
			CRGB color = ColorFromPalette(current_palette, colorindex);
			if (this_dir) {
				ringPalette(0, j, current_palette, colorindex);
				ringPalette(0, STRIP_LENGTH - 1 - j, current_palette, colorindex);
			}
			else {
				ringPalette(0, (STRIP_LENGTH / 2) - 1 - j, current_palette, colorindex);
				ringPalette(0, (STRIP_LENGTH / 2) + j, current_palette, colorindex);
			}
		}
	}
} // end fire_mirror_pal()




// fire with each strip doing a seperate flame
void fire_rings1(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking1) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (!old_this_dir) {
				old_leds[ringArray[STRIP_LENGTH - 1 - j][0]] = HeatColor(old_heat[j]);
			}
			else {
				old_leds[ringArray[j][0]] = HeatColor(old_heat[j]);
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking1) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (!this_dir) {
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][0]] = HeatColor(heat[j]);
			}
			else {
				cur_leds[ringArray[j][0]] = HeatColor(heat[j]);
			}
		}
	}
}

void fire_rings2(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling2 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking2) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (!old_this_dir) {
				old_leds[ringArray[STRIP_LENGTH - 1 - j][1]] = HeatColor(old_heat[j]);
			}
			else {
				old_leds[ringArray[j][1]] = HeatColor(old_heat[j]);
			}
		}
	}else{
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling2 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking2) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (!this_dir) {
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][1]] = HeatColor(heat[j]);
			}
			else {
				cur_leds[ringArray[j][1]] = HeatColor(heat[j]);
			}
		}
	}
}

void fire_rings3(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking3) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (!old_this_dir) {
				old_leds[ringArray[STRIP_LENGTH - 1 - j][2]] = HeatColor(old_heat[j]);
			}
			else {
				old_leds[ringArray[j][2]] = HeatColor(old_heat[j]);
			}
		}
	}else{
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking3) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (!this_dir) {
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][2]] = HeatColor(heat[j]);
			}
			else {
				cur_leds[ringArray[j][2]] = HeatColor(heat[j]);
			}
		}
	}
}

void fire_rings4(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking4) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (!old_this_dir) {
				old_leds[ringArray[STRIP_LENGTH - 1 - j][3]] = HeatColor(old_heat[j]);
			}
			else {
				old_leds[ringArray[j][3]] = HeatColor(old_heat[j]);
			}
		}
	}else{
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking4) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (!this_dir) {
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][3]] = HeatColor(heat[j]);
			}
			else {
				cur_leds[ringArray[j][3]] = HeatColor(heat[j]);
			}
		}
	}
}

void fire_rings(bool old){
  if(mode_number != 16){mode_number = 8;}
	fire_rings1(old);
	fire_rings2(old);
	fire_rings3(old);
	fire_rings4(old);
}




// fire rings using current_palette
void fire_pal_rings1(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 1; k >= 2; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking1) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			byte colorindex = scale8(old_heat[j], 240);
			CRGB color = ColorFromPalette(old_palette, colorindex);
			int pixelnumber;
			if (old_this_dir) {
				pixelnumber = (STRIP_LENGTH - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			old_leds[ringArray[pixelnumber][0]] = color;
		}
	}else{
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking1) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			byte colorindex = scale8(heat[j], 240);
			CRGB color = ColorFromPalette(current_palette, colorindex);
			int pixelnumber;
			if (this_dir) {
				pixelnumber = (STRIP_LENGTH - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			cur_leds[ringArray[pixelnumber][0]] = color;
		}
	}
}

void fire_pal_rings2(bool old)
{
  static byte old_heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
		old_heat[i] = qsub8(old_heat[i],  random8(0, ((old_cooling2 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 1; k >= 2; k--) {
		old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2] ) / 3;
    }
    if( random8() < old_sparking2 ) {
      int y = random8(7);
	  old_heat[y] = qadd8(old_heat[y], random8(160,255) );
    }
    for( int j = 0; j < STRIP_LENGTH; j++) {
      byte colorindex = scale8(old_heat[j], 240);
      CRGB color = ColorFromPalette( old_palette, colorindex);
      int pixelnumber;
      if(old_this_dir ) {
        pixelnumber = (STRIP_LENGTH-1) - j;
      } else {
        pixelnumber = j;
      }
      //ringPalette(pixelnumber, current_palette, colorindex);
	  old_leds[ringArray[pixelnumber][1]] = color;
    }
}

void fire_pal_rings3(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 1; k >= 2; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking3) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			byte colorindex = scale8(old_heat[j], 240);
			CRGB color = ColorFromPalette(old_palette, colorindex);
			int pixelnumber;
			if (old_this_dir) {
				pixelnumber = (STRIP_LENGTH - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			//ringPalette(pixelnumber, current_palette, colorindex);
			old_leds[ringArray[pixelnumber][2]] = color;
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking3) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			byte colorindex = scale8(heat[j], 240);
			CRGB color = ColorFromPalette(current_palette, colorindex);
			int pixelnumber;
			if (this_dir) {
				pixelnumber = (STRIP_LENGTH - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			//ringPalette(pixelnumber, current_palette, colorindex);
			cur_leds[ringArray[pixelnumber][2]] = color;
		}
	}
}

void fire_pal_rings4(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 1; k >= 2; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking4) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			byte colorindex = scale8(old_heat[j], 240);
			CRGB color = ColorFromPalette(old_palette, colorindex);
			int pixelnumber;
			if (old_this_dir) {
				pixelnumber = (STRIP_LENGTH - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			//ringPalette(pixelnumber, current_palette, colorindex);
			old_leds[ringArray[pixelnumber][3]] = color;
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 1; k >= 2; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking4) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			byte colorindex = scale8(heat[j], 240);
			CRGB color = ColorFromPalette(current_palette, colorindex);
			int pixelnumber;
			if (this_dir) {
				pixelnumber = (STRIP_LENGTH - 1) - j;
			}
			else {
				pixelnumber = j;
			}
			//ringPalette(pixelnumber, current_palette, colorindex);
			cur_leds[ringArray[pixelnumber][3]] = color;
		}
	}
}

void fire_pal_rings(bool old){
	mode_number = 9;
	fire_pal_rings1(old);
	fire_pal_rings2(old);
	fire_pal_rings3(old);
	fire_pal_rings4(old);
}




// fire mirror using seperate fires for each strip
void fire_mirror_rings1(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking1) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(old_heat[j]);
			if (old_this_dir) {
				old_leds[ringArray[j][0]] = hcolor;
				old_leds[ringArray[STRIP_LENGTH - 1 - j][0]] = hcolor;
			}
			else {
				old_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][0]] = hcolor;
				old_leds[ringArray[(STRIP_LENGTH / 2) + j][0]] = hcolor;
			}
		}
	}else{
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking1) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(heat[j]);
			if (this_dir) {
				cur_leds[ringArray[j][0]] = hcolor;
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][0]] = hcolor;
			}
			else {
				cur_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][0]] = hcolor;
				cur_leds[ringArray[(STRIP_LENGTH / 2) + j][0]] = hcolor;
			}
		}
	}
}	

void fire_mirror_rings2(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling2 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking2) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(old_heat[j]);
			if (old_this_dir) {
				old_leds[ringArray[j][1]] = hcolor;
				old_leds[ringArray[STRIP_LENGTH - 1 - j][1]] = hcolor;
			}
			else {
				old_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][1]] = hcolor;
				old_leds[ringArray[(STRIP_LENGTH / 2) + j][1]] = hcolor;
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling2 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking2) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(heat[j]);
			if (this_dir) {
				cur_leds[ringArray[j][1]] = hcolor;
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][1]] = hcolor;
			}
			else {
				cur_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][1]] = hcolor;
				cur_leds[ringArray[(STRIP_LENGTH / 2) + j][1]] = hcolor;
			}
		}
	}
}	

void fire_mirror_rings3(bool old) {
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < sparking3) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(old_heat[j]);
			if (old_this_dir) {
				old_leds[ringArray[j][2]] = hcolor;
				old_leds[ringArray[STRIP_LENGTH - 1 - j][2]] = hcolor;
			}
			else {
				old_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][2]] = hcolor;
				old_leds[ringArray[(STRIP_LENGTH / 2) + j][2]] = hcolor;
			}
		}
	}
   else{
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking3) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(heat[j]);
			if (this_dir) {
				cur_leds[ringArray[j][2]] = hcolor;
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][2]] = hcolor;
			}
			else {
				cur_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][2]] = hcolor;
				cur_leds[ringArray[(STRIP_LENGTH / 2) + j][2]] = hcolor;
			}
		}
	}
}


void fire_mirror_rings4(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < sparking4) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(old_heat[j]);
			if (old_this_dir) {
				old_leds[ringArray[j][3]] = hcolor;
				old_leds[ringArray[STRIP_LENGTH - 1 - j][3]] = hcolor;
			}
			else {
				old_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][3]] = hcolor;
				old_leds[ringArray[(STRIP_LENGTH / 2) + j][3]] = hcolor;
			}
		}
	}
   else{
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking4) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			CRGB hcolor = HeatColor(heat[j]);
			if (this_dir) {
				cur_leds[ringArray[j][3]] = hcolor;
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][3]] = hcolor;
			}
			else {
				cur_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][3]] = hcolor;
				cur_leds[ringArray[(STRIP_LENGTH / 2) + j][3]] = hcolor;
			}
		}
	}
}	

void fire_mirror_rings(bool old){
	mode_number = 10;
	fire_mirror_rings1(old);
	fire_mirror_rings2(old);
	fire_mirror_rings3(old);
	fire_mirror_rings4(old);
}





// fire mirror rings with palette
void fire_mirror_pal_rings1(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking1) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(old_heat[j], 240);
			CRGB color = ColorFromPalette(old_palette, colorindex);
			if (old_this_dir) {
				old_leds[ringArray[j][0]] = color;
				old_leds[ringArray[STRIP_LENGTH - 1 - j][0]] = color;
			}
			else {
				old_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][0]] = color;
				old_leds[ringArray[(STRIP_LENGTH / 2) + j][0]] = color;
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking1) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(heat[j], 240);
			CRGB color = ColorFromPalette(current_palette, colorindex);
			if (this_dir) {
				cur_leds[ringArray[j][0]] = color;
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][0]] = color;
			}
			else {
				cur_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][0]] = color;
				cur_leds[ringArray[(STRIP_LENGTH / 2) + j][0]] = color;
			}
		}
	}
}	

void fire_mirror_pal_rings2(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling2 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking2) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(old_heat[j], 240);
			CRGB color = ColorFromPalette(old_palette, colorindex);
			if (old_this_dir) {
				old_leds[ringArray[j][1]] = color;
				old_leds[ringArray[STRIP_LENGTH - 1 - j][1]] = color;
			}
			else {
				old_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][1]] = color;
				old_leds[ringArray[(STRIP_LENGTH / 2) + j][1]] = color;
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling2 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking2) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(heat[j], 240);
			CRGB color = ColorFromPalette(current_palette, colorindex);
			if (this_dir) {
				cur_leds[ringArray[j][1]] = color;
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][1]] = color;
			}
			else {
				cur_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][1]] = color;
				cur_leds[ringArray[(STRIP_LENGTH / 2) + j][1]] = color;
			}
		}
	}
}	

void fire_mirror_pal_rings3(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking3) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(old_heat[j], 240);
			CRGB color = ColorFromPalette(old_palette, colorindex);
			if (old_this_dir) {
				old_leds[ringArray[j][2]] = color;
				old_leds[ringArray[STRIP_LENGTH - 1 - j][2]] = color;
			}
			else {
				old_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][2]] = color;
				old_leds[ringArray[(STRIP_LENGTH / 2) + j][2]] = color;
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking3) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(heat[j], 240);
			CRGB color = ColorFromPalette(current_palette, colorindex);
			if (this_dir) {
				cur_leds[ringArray[j][2]] = color;
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][2]] = color;
			}
			else {
				cur_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][2]] = color;
				cur_leds[ringArray[(STRIP_LENGTH / 2) + j][2]] = color;
			}
		}
	}
}	

void fire_mirror_pal_rings4(bool old){
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking4) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(old_heat[j], 240);
			CRGB color = ColorFromPalette(old_palette, colorindex);
			if (old_this_dir) {
				old_leds[ringArray[j][3]] = color;
				old_leds[ringArray[STRIP_LENGTH - 1 - j][3]] = color;
			}
			else {
				old_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][3]] = color;
				old_leds[ringArray[(STRIP_LENGTH / 2) + j][3]] = color;
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking4) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH / 2; j++) {
			byte colorindex = scale8(heat[j], 240);
			CRGB color = ColorFromPalette(current_palette, colorindex);
			if (this_dir) {
				cur_leds[ringArray[j][3]] = color;
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][3]] = color;
			}
			else {
				cur_leds[ringArray[(STRIP_LENGTH / 2) - 1 - j][3]] = color;
				cur_leds[ringArray[(STRIP_LENGTH / 2) + j][3]] = color;
			}
		}
	}
}	

void fire_mirror_pal_rings(bool old){
	mode_number = 11;
	fire_mirror_pal_rings1(old);
	fire_mirror_pal_rings2(old);
	fire_mirror_pal_rings3(old);
	fire_mirror_pal_rings4(old);
}






// fire with each strip doing a seperate flame
void fire_rings1_opp(bool old) {
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking1) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (old_this_dir) {
				old_leds[ringArray[STRIP_LENGTH - 1 - j][0]] = HeatColor(old_heat[j]);
			}
			else {
				old_leds[ringArray[j][0]] = HeatColor(old_heat[j]);
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling1 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking1) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (this_dir) {
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][0]] = HeatColor(heat[j]);
			}
			else {
				cur_leds[ringArray[j][0]] = HeatColor(heat[j]);
			}
		}
	}
}

void fire_rings2_opp(bool old) {
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling2 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking2) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (old_this_dir) {
				old_leds[ringArray[STRIP_LENGTH - 1 - j][1]] = HeatColor(old_heat[j]);
			}
			else {
				old_leds[ringArray[j][1]] = HeatColor(old_heat[j]);
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling2 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking2) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (this_dir) {
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][1]] = HeatColor(heat[j]);
			}
			else {
				cur_leds[ringArray[j][1]] = HeatColor(heat[j]);
			}
		}
	}
}

void fire_rings3_opp(bool old) {
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking3) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (old_this_dir) {
				old_leds[ringArray[STRIP_LENGTH - 1 - j][2]] = HeatColor(old_heat[j]);
			}
			else {
				old_leds[ringArray[j][2]] = HeatColor(old_heat[j]);
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling3 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking3) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (this_dir) {
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][2]] = HeatColor(heat[j]);
			}
			else {
				cur_leds[ringArray[j][2]] = HeatColor(heat[j]);
			}
		}
	}
}

void fire_rings4_opp(bool old) {
	if (old) {
		static byte old_heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
		}
		if (random8() < old_sparking4) {
			int y = random8(7);
			old_heat[y] = qadd8(old_heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (old_this_dir) {
				old_leds[ringArray[STRIP_LENGTH - 1 - j][3]] = HeatColor(old_heat[j]);
			}
			else {
				old_leds[ringArray[j][3]] = HeatColor(old_heat[j]);
			}
		}
	}
	else {
		static byte heat[STRIP_LENGTH];
		for (int i = 0; i < STRIP_LENGTH; i++) {
			heat[i] = qsub8(heat[i], random8(0, ((cooling4 * 10) / STRIP_LENGTH) + 2));
		}
		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
			heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
		}
		if (random8() < sparking4) {
			int y = random8(7);
			heat[y] = qadd8(heat[y], random8(160, 255));
		}
		for (int j = 0; j < STRIP_LENGTH; j++) {
			if (this_dir) {
				cur_leds[ringArray[STRIP_LENGTH - 1 - j][3]] = HeatColor(heat[j]);
			}
			else {
				cur_leds[ringArray[j][3]] = HeatColor(heat[j]);
			}
		}
	}
}

void fire_rings_opp(bool old){
	mode_number = 12;
  fire_rings1_opp(old);
  fire_rings2_opp(old);
  fire_rings3_opp(old);
  fire_rings4_opp(old);
}




//void fire_rings_simple(bool old){
//	mode_number = 13;
//	if (old) {
//		for (int ring = 0; ring < 4; ring++) {
//			static byte old_heat[STRIP_LENGTH];
//			for (int i = 0; i < STRIP_LENGTH; i++) {
//				old_heat[i] = qsub8(old_heat[i], random8(0, ((old_cooling_simple[ring] * 10) / STRIP_LENGTH) + 2));
//			}
//			for (int k = STRIP_LENGTH - 3; k > 0; k--) {
//				old_heat[k] = (old_heat[k - 1] + old_heat[k - 2] + old_heat[k - 2]) / 3;
//			}
//			if (random8() < old_sparking_simple[ring]) {
//				int y = random8(7);
//				old_heat[y] = qadd8(old_heat[y], random8(160, 255));
//			}
//			for (int j = 0; j < STRIP_LENGTH; j++) {
//				if (!old_this_dir) {
//					old_leds[ringArray[STRIP_LENGTH - 1 - j][ring]] = HeatColor(old_heat[j]);
//				}
//				else {
//					old_leds[ringArray[j][ring]] = HeatColor(old_heat[j]);
//				}
//			}
//		}
//	}
//	else {
//		for (int ring = 0; ring < 4; ring++) {
//			static byte heat[STRIP_LENGTH];
//			for (int i = 0; i < STRIP_LENGTH; i++) {
//				heat[i] = qsub8(heat[i], random8(0, ((cooling_simple[ring] * 10) / STRIP_LENGTH) + 2));
//			}
//			for (int k = STRIP_LENGTH - 3; k > 0; k--) {
//				heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
//			}
//			if (random8() < sparking_simple[ring]) {
//				int y = random8(7);
//				heat[y] = qadd8(heat[y], random8(160, 255));
//			}
//			for (int j = 0; j < STRIP_LENGTH; j++) {
//				if (!this_dir) {
//					cur_leds[ringArray[STRIP_LENGTH - 1 - j][ring]] = HeatColor(heat[j]);
//				}
//				else {
//					cur_leds[ringArray[j][ring]] = HeatColor(heat[j]);
//				}
//			}
//		}
//	}
//}

//void addFire() {
//	for (int ring = 0; ring < 4; ring++) {
//		static byte fire_heat[STRIP_LENGTH];
//		for (int i = 0; i < STRIP_LENGTH; i++) {
//			fire_heat[i] = qsub8(fire_heat[i], random8(0, ((cooling_simple[ring] * 10) / STRIP_LENGTH) + 2));
//		}
//		for (int k = STRIP_LENGTH - 3; k > 0; k--) {
//			fire_heat[k] = (fire_heat[k - 1] + fire_heat[k - 2] + fire_heat[k - 2]) / 3;
//		}
//		if (random8() < sparking_simple[ring]) {
//			int y = random8(7);
//			fire_heat[y] = qadd8(fire_heat[y], random8(160, 255));
//		}
//		for (int j = 0; j < STRIP_LENGTH; j++) {
////			if (!this_dir) {
//				fire_leds[ringArray[STRIP_LENGTH - 1 - j][ring]] = HeatColor(fire_heat[j]);
////			}
////			else {
////				fire_leds[ringArray[j][ring]] = HeatColor(fire_heat[j]);
////			}
//		}
//	}
//}


#endif
