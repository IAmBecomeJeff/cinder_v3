#ifndef CONFETTI_H
#define CONFETTI_H

/* This is adapted from the confetti routine created by Mark Kriegsman */

/*  Usage - confetti_pal();
 *   
 *  this_fade
 *  this_delay
 *  current_palette and target_palette
 *  this_diff
 *  this_index
 *  this_inc
 *  this_bright
 */


//void confetti_pal(bool old) {                                                                                               // random colored speckles that blink in and fade smoothly
//	if (old) {
//		fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
//		int pos = random8(NUM_LEDS);                                                                                      // Pick an LED at random.
//		old_leds[pos] = ColorFromPalette(old_palette, old_this_index + random8(old_this_diff) / 4, old_this_bright, current_blending);      // Munge the values and pick a colour from the palette
//		old_this_index = old_this_index + old_this_inc;
//	}else{
//		fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);
//		int pos = random8(NUM_LEDS);                                                                                      // Pick an LED at random.
//		cur_leds[pos] = ColorFromPalette(current_palette, this_index + random8(this_diff) / 4, this_bright, current_blending);      // Munge the values and pick a colour from the palette
//		this_index = this_index + this_inc;                                                                   // base palette counter increments here.
//} // confetti_pal()
//}


void confetti_pal_ring(bool old) {                                                                                               // random colored speckles that blink in and fade smoothly
	mode_number = 3;
	if (old) {
		fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
		int pos = random8(STRIP_LENGTH);                                                                                      // Pick an LED at random.
		ringPalette(1, pos, old_palette, old_this_index + random8(old_this_diff) / 4, old_this_bright, current_blending);
		// Munge the values and pick a colour from the palette
		old_this_index = old_this_index + old_this_inc;                                                                                  // base palette counter increments here.
	}
	else {
		fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);
		int pos = random8(STRIP_LENGTH);                                                                                      // Pick an LED at random.
		ringPalette(0, pos, current_palette, this_index + random8(this_diff) / 4, this_bright, current_blending);
		// Munge the values and pick a colour from the palette
		this_index = this_index + this_inc;
	}
} // confetti_pal_ring()

#endif
