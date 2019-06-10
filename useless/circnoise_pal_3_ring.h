#ifndef CIRCNOISE_PAL_3_RING_H
#define CIRCNOISE_PAL_3_RING_H

/* This is adapted from a routine created by Stefan Petrick */

/*  Usage - circnoise_pal_3_ring();
 *  
 */


// no x/y shifting but scrolling along z
void circnoise_pal_3_ring() {

  int scale = 1000;                               // the "zoom factor" for the noise

  for (uint16_t i = 0; i < STRIP_LENGTH; i++) {

    uint16_t shift_x = 0;                             // no movement along x and y
    uint16_t shift_y = 0;


    uint32_t real_x = (xd[i] + shift_x) * scale;       // calculate the coordinates within the noise field
    uint32_t real_y = (yd[i] + shift_y) * scale;       // based on the precalculated positions
    
    uint32_t real_z = millis() * 20;                  // increment z linear

    uint8_t noise = inoise16(real_x, real_y, real_z) >> 8;           // get the noise data and scale it down

    uint8_t index = noise * 3;                        // map led color based on noise data
    uint8_t bri   = noise;

	ringPalette(i,current_palette,index,bri,LINEARBLEND);
     // With that value, look up the 8 bit colour palette value and assign it to the current LED.

  }
} // circnoise_pal_3_ring()



#endif
