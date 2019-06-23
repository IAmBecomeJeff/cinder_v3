#ifndef FIRE_PAL_H
#define FIRE_PAL_H

void fire_pal()
{
// Array of temperature readings at each simulation cell
  static byte heat[STRIP_LENGTH];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling * 10) / STRIP_LENGTH) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= STRIP_LENGTH - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < sparking ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < STRIP_LENGTH; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      //CRGB color = ColorFromPalette( current_palette, colorindex);
      int pixelnumber;
      if( this_dir ) {
        pixelnumber = (STRIP_LENGTH-1) - j;
      } else {
        pixelnumber = j;
      }
      ringPalette(pixelnumber, current_palette, colorindex);
	  //leds[pixelnumber] = color;
    }
}

#endif