#ifndef CIRCNOISE_PAL_1_RING_H
#define CIRCNOISE_PAL_1_RING_H

/* This is adapted from a routine created by Stefan Petrick */

/*  Usage - circnoise_pal_1_ring();
 *  
 */


// moves a noise up and down while slowly shifting to the side
void circnoise_pal_1_ring() {

  int scale = 1000;                               // the "zoom factor" for the noise

  for (uint16_t i = 0; i < STRIP_LENGTH; i++) {

    uint16_t shift_x = beatsin8(17);                  // the x position of the noise field swings @ 17 bpm
    uint16_t shift_y = millis() / 100;                // the y position becomes slowly incremented

    uint32_t real_x = (xd[i] + shift_x) * scale;       // calculate the coordinates within the noise field
    uint32_t real_y = (yd[i] + shift_y) * scale;       // based on the precalculated positions

    uint8_t noise = inoise16(real_x, real_y, 4223) >> 8;           // get the noise data and scale it down

    uint8_t index = noise * 3;                        // map led color based on noise data
    uint8_t bri   = noise;
    
    ringPalette(i, current_palette, index, bri, LINEARBLEND);
  }
}//circnoise_pal_1_ring()


#endif
