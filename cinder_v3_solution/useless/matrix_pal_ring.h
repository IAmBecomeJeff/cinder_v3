#ifndef MATRIX_PAL_RING_H
#define MATRIX_PAL_RING_H


/* Usage - matrix_pal_ring();
 *  
 *  This is one of the few routines I have with pixel counting.
 *  
 *  
 * current_palette, target_palette
 * this_rot
 * this_index
 * bg_clr
 * bg_bri
 * this_dir
 * this_bright
 */

void matrix_pal_ring() {                                           // One line matrix

  if (this_rot) this_index++;                                   // Increase palette index to change colours on the fly
  
  if (random8(90) > 80) {
    if (this_dir == 0)
	  ringPalette(0, current_palette, this_index, this_bright, current_blending);
    else
	  ringPalette(STRIP_LENGTH-1, current_palette, this_index, this_bright, current_blending);
  } else {
    if (this_dir == 0)
	  ringCHSV(0, bg_clr, this_sat, bg_bri);
    else
	  ringCHSV(STRIP_LENGTH-1, bg_clr, this_sat, bg_bri);
  }

  if (this_dir == 0) {
    for (int i = STRIP_LENGTH-1; i >0 ; i-- ) {
		for (int j=0; j<4; j++){
			leds[ringArray[i][j]] = leds[ringArray[i-1][j]];
		}
  }
  }  else {
    for (int i = 0; i < STRIP_LENGTH-1 ; i++ ) {
		for (int j=0;j<4;j++){
			leds[ringArray[i][j]] = leds[ringArray[i+1][j]];
		}
  }
  }
} // matrix_pal_ring()


#endif
