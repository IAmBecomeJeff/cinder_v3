#ifndef ONE_SIN_H
#define ONE_SIN_H


/* There's lots of values to play with here, as well as selecting your own palettes
 *  
 */


/*
 * Usage - one_sin_pal();
 * 
 * all_freq - What is the frequency
 * bg_bri - The background brightness
 * bg_clr - The background colour
 * start_index  - What foreground colour are we starting with?
 * this_bright - How bright is it?
 * this_cutoff - If the brightness is lower than this_, then brightness=0
 * this_inc - incrementer to change the starting colour after each pass
 * this_index - rotating colours down the strip counter
 * this_phase - the counter used in conjunction with the frequency to move down the strip
 * this_rot - How quickly to rotate those colours down the strip
 * this_speed  - How fast does it whip down the strand
 */


void one_sin_pal(bool old) {
	mode_number 25;
	if (old) {
		old_start_index += old_this_inc;
		old_this_index = old_start_index;
		if (this_dir) {
			old_this_phase += old_this_speed;                                                                     // You can change direction and speed individually.
		}
		else {
			old_this_phase -= old_this_speed;
		}
		for (int k = 0; k < NUM_LEDS; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			int old_this_bright = qsubd(cubicwave8((k * old_all_freq) + old_this_phase), old_this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			old_leds[k] = CHSV(old_bg_clr, 255, old_bg_bri);                                                        // First set a background colour, but fully saturated.
			old_leds[k] += ColorFromPalette(old_palette, old_this_index + k * old_this_inc, old_this_bright, current_blending);
			old_this_index += old_this_rot;
		}
	}
	else {
		start_index += this_inc;
		this_index = start_index;
		if (this_dir) {
			this_phase += this_speed;                                                                     // You can change direction and speed individually.
		}
		else {
			this_phase -= this_speed;                                                                     // You can change direction and speed individually.
		}
		for (int k = 0; k < NUM_LEDS; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			int this_bright = qsubd(cubicwave8((k * all_freq) + this_phase), this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			cur_leds[k] = CHSV(bg_clr, 255, bg_bri);                                                        // First set a background colour, but fully saturated.
			cur_leds[k] += ColorFromPalette(current_palette, this_index + k * this_inc, this_bright, current_blending);
			this_index += this_rot;
		}
	}
} // one_sin()


void one_sin_pal_ring(bool old) {
	mode_number = 26;
	if (old) {
		old_start_index += old_this_inc;
		old_this_index = old_start_index;
   if(this_dir){
    old_this_phase += old_this_speed;  
   }else{
		old_this_phase -= old_this_speed;                                                                     // You can change direction and speed individually.
   }
		for (int k = 0; k < STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			int old_this_bright = qsubd(cubicwave8((k*old_all_freq) + old_this_phase), old_this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			ringCHSV(1,k, old_bg_clr, 155, old_bg_bri);
			ringPaletteAdd(1,k, old_palette, old_this_index + k * old_this_inc, old_this_bright, current_blending);		// First set a background colour, but fully saturated.
			old_this_index += old_this_rot;
		}
	}
	else {
		start_index += this_inc;
		this_index = start_index;
   if(this_dir){
    this_phase += this_speed;  
   }else{
		this_phase -= this_speed;                                                                     // You can change direction and speed individually.
   }
		for (int k = 0; k<STRIP_LENGTH; k++) {                                                            // For each of the LED's in the strand, set a brightness based on a wave as follows:
			int this_bright = qsubd(cubicwave8((k*all_freq) + this_phase), this_cutoff);                    // qsub sets a minimum value called this_cutoff. If < this_cutoff, then bright = 0. Otherwise, bright = 128 (as defined in qsub)..
			ringCHSV(0, k, bg_clr, 155, bg_bri);
			ringPaletteAdd(0, k, current_palette, this_index + k * this_inc, this_bright, current_blending);		// First set a background colour, but fully saturated.
			this_index += this_rot;
		}
	}
} // one_sin_pal_ring()

#endif
