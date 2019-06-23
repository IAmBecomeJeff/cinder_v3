#ifndef FIRE_MIRROR_RINGS_H
#define FIRE_MIRRORRINGS_H

// Call with a call to fire1(), fire2(), fire3(), fire4()

void fire1_mirror_rings_pal()
{
  static byte heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling1 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 3; k > 0; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < sparking1 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
	for ( int j = 0; j < STRIP_LENGTH/2; j++) {
		byte colorindex = scale8( heat[j], 240);
		CRGB color = ColorFromPalette( current_palette, colorindex);
		if(this_dir){
			leds[ringArray[j][0]] = color;
			leds[ringArray[STRIP_LENGTH-1-j][0]] = color;
		} else {
			leds[ringArray[(STRIP_LENGTH/2) - 1- j][0]] = color;
			leds[ringArray[(STRIP_LENGTH/2) + j][0]] = color;
		}
	}
}	

void fire2_mirror()
{
  static byte heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling2 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 3; k > 0; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < sparking2 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
	for ( int j = 0; j < STRIP_LENGTH/2; j++) {
		CRGB hcolor = HeatColor(heat[j]);	
		if(this_dir){
			leds[ringArray[j][1]] = hcolor;
			leds[ringArray[STRIP_LENGTH-1-j][1]] = hcolor;
		} else {
			leds[ringArray[(STRIP_LENGTH/2) - 1- j][1]] = hcolor;
			leds[ringArray[(STRIP_LENGTH/2) + j][1]] = hcolor;
		}
	}
}	

void fire3_mirror()
{
  static byte heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling3 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 3; k > 0; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < sparking3 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
	for ( int j = 0; j < STRIP_LENGTH/2; j++) {
		CRGB hcolor = HeatColor(heat[j]);	
		if(this_dir){
			leds[ringArray[j][2]] = hcolor;
			leds[ringArray[STRIP_LENGTH-1-j][2]] = hcolor;
		} else {
			leds[ringArray[(STRIP_LENGTH/2) - 1- j][2]] = hcolor;
			leds[ringArray[(STRIP_LENGTH/2) + j][2]] = hcolor;
		}
	}
}	

void fire4_mirror()
{
  static byte heat[STRIP_LENGTH];
    for( int i = 0; i < STRIP_LENGTH; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((cooling4 * 10) / STRIP_LENGTH) + 2));
    }
    for( int k= STRIP_LENGTH - 3; k > 0; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < sparking4 ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
	for ( int j = 0; j < STRIP_LENGTH/2; j++) {
		CRGB hcolor = HeatColor(heat[j]);	
		if(this_dir){
			leds[ringArray[j][3]] = hcolor;
			leds[ringArray[STRIP_LENGTH-1-j][3]] = hcolor;
		} else {
			leds[ringArray[(STRIP_LENGTH/2) - 1- j][3]] = hcolor;
			leds[ringArray[(STRIP_LENGTH/2) + j][3]] = hcolor;
		}
	}
}	
#endif
