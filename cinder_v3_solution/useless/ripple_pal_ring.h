#ifndef RIPPLE_PAL_RING_H
#define RIPPLE_PAL_RING_H

/* ripple_pal
*/


int center = 0;                                                // Center of the current ripple.
int step = -1;                                                 // -1 is the initializing step.
uint8_t colour;                   		 	       // Ripple colour
uint8_t myfade          = 255;    			       // Starting ripple brightness
#define maxsteps 16               			       // Ripple case statement won't allow a variable

void ripple_pal_ring() {

  fadeToBlackBy(leds, NUM_LEDS, this_fade);                             // 8 bit, 1 = slow, 255 = fast
  
  switch (step) {

    case -1:                                                          // Initialize ripple variables.
      center = random(144);
      colour = random8();
      step = 0;
      break;

    case 0:
	  ringPalette(center, current_palette, colour, myfade, current_blending);      
      step ++;
      break;

    case maxsteps:                                                    // At the end of the ripples.
      step = -1;
      break;

    default:                                                          // Middle of the ripples.
      ringPaletteAdd((center + step + 144) % 144, current_palette, colour, myfade/step*2, current_blending);
      ringPaletteAdd((center - step + 144) % 144, current_palette, colour, myfade/step*2, current_blending);
      step ++;                                                         // Next step.
      break;  
  } // switch step
  
} // ripple_pal_ring()
