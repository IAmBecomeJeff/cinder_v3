#ifndef NOISE8_PAL_RING_H
#define NOISE8_PAL_RING_H

/* This is adapted from a routine created by Mark Kriegsman */

/*  Usage - noise8_ring();
 *  
 */

uint16_t dist2 = 12345;         // A random number for our noise generator.
uint16_t scale2 = 30;          // Wouldn't recommend changing this_ on the fly, or the animation will be really blocky.

void noise8_pal_ring() {
 
  for(int i = 0; i < STRIP_LENGTH; i++) {                                      // Just ONE loop to fill up the LED array as all of the pixels change.
    uint8_t index = inoise8(i*scale2, dist2+i*scale2) % 255;                  // Get a value from the noise function. I'm using both x and y axis.
    ringPalette(i, current_palette, index, 255, LINEARBLEND);		 // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  dist2 += beatsin8(10,1,4);                                                // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
                                                                           // In some sketches, I've used millis() instead of an incremented counter. Works a treat.
} // noise8_pal_ring()

#endif
