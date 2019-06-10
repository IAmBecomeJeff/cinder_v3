#ifndef RAINBOW_MARCH_H
#define RAINBOW_MARCH_H

/* Usage - rainbow_march();
 *  
 * this_index
 * this_diff
 * this_rot
 * this_dir
 */


void rainbow_march(bool old) {                                           // The fill_rainbow call doesn't support brightness levels
	mode_number = 30;
	if (old) {
		if (old_this_dir == 0) old_this_index += old_this_rot; else old_this_index -= old_this_rot;  // I could use signed math, but 'this_dir' works with other routines.
		fill_rainbow(old_leds, NUM_LEDS, old_this_index, old_this_diff);               // I don't change deltahue on the fly as it's too fast near the end of the strip.
	}
	else {
		if (this_dir == 0) this_index += this_rot; else this_index -= this_rot;  // I could use signed math, but 'this_dir' works with other routines.
		fill_rainbow(cur_leds, NUM_LEDS, this_index, this_diff);               // I don't change deltahue on the fly as it's too fast near the end of the strip.
	}
} // rainbow_march()

void rainbow_march_ring(bool old) {                                           // The fill_rainbow call doesn't support brightness levels
	mode_number = 31;
	if (old) {
		if (old_this_dir == 0) old_this_index += old_this_rot; else old_this_index -= old_this_rot;  // I could use signed math, but 'this_dir' works with other routines.
		ring_fill_rainbow(1, old_this_index, old_this_diff);               // I don't change deltahue on the fly as it's too fast near the end of the strip.
	}
	else {
		if (this_dir == 0) this_index += this_rot; else this_index -= this_rot;  // I could use signed math, but 'this_dir' works with other routines.
		ring_fill_rainbow(0, this_index, this_diff);               // I don't change deltahue on the fly as it's too fast near the end of the strip.
	}
} // rainbow_march_ring()

#endif
