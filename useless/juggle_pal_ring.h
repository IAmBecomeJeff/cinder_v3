#ifndef JUGGLE_PAL_RING_H
#define JUGGLE_PAL_RING_H

/* This is adapted from a routine created by Mark Kriegsman */

/*  Usage - juggle_pal_ring();
 *  
 *  this_hue
 *  this_fade
 *  numdots
 *  this_beat
 *  this_bright
 *  this_diff
 */

//uint8_t numdots_ring;

void juggle_pal_ring() {                                            // Several colored dots, weaving in and out of sync with each other
  this_index = 0;                                           // Reset the hue values.
  fadeToBlackBy(leds, NUM_LEDS, this_fade);
  for( int i = 0; i < numdots_ring; i++) {
    ringPaletteAdd(beatsin16(this_beat+i+numdots_ring,0,STRIP_LENGTH-1), current_palette, this_index, this_bright, current_blending);
	// Munge the values and pick a colour from the palette
    this_index += this_diff;
  }
} // juggle_pal_ring()

#endif
