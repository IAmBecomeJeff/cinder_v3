#ifndef FIRE_RINGS_H
#define FIRE_RINGS_H

// Call with a call to fire1(), fire2(), fire3(), fire4()

void fire_pal_rings1()
{
  static byte heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling1 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < sparking1 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < STRIP_LENGTH; j++) {
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( current_palette, colorindex);
      int pixelnumber;
      if( this_dir ) {
        pixelnumber = (STRIP_LENGTH-1) - j;
      } else {
        pixelnumber = j;
      }
	  leds[ringPalette[pixelnumber][0]] = color;
    }
}


void fire_pal_rings2()
{
  static byte heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling2 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < sparking2 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < STRIP_LENGTH; j++) {
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( current_palette, colorindex);
      int pixelnumber;
      if( this_dir ) {
        pixelnumber = (STRIP_LENGTH-1) - j;
      } else {
        pixelnumber = j;
      }
      //ringPalette(pixelnumber, current_palette, colorindex);
	  leds[ringPalette[pixelnumber][1]] = color;
    }
}


void fire_pal_rings3()
{
  static byte heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling3 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < sparking3 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < STRIP_LENGTH; j++) {
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( current_palette, colorindex);
      int pixelnumber;
      if( this_dir ) {
        pixelnumber = (STRIP_LENGTH-1) - j;
      } else {
        pixelnumber = j;
      }
      //ringPalette(pixelnumber, current_palette, colorindex);
	  leds[ringPalette[pixelnumber][2]] = color;
    }
}


void fire_pal_rings4()
{
  static byte heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling4 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < sparking4 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < STRIP_LENGTH; j++) {
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( current_palette, colorindex);
      int pixelnumber;
      if( this_dir ) {
        pixelnumber = (STRIP_LENGTH-1) - j;
      } else {
        pixelnumber = j;
      }
      //ringPalette(pixelnumber, current_palette, colorindex);
	  leds[ringPalette[pixelnumber][3]] = color;
    }
}

void fire_pal_rings_all(){
	fire_pal_rings1();
	fire_pal_rings2();
	fire_pal_rings3();
	fire_pal_rings4();
}

#endif

