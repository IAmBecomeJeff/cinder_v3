#ifndef SERENDIPITOUS_PAL_RING_H
#define SERENDIPITOUS_PAL_RING_H

/*  This is from Serendipitous Circles from the August 1977 and April 1978 issues of Byte Magazine. I didn't do a very good job of it, but am at least getting some animation and the routine is very short.
*/


/*  Usage - serendipitous_pal_ring();
 *  
 */

uint16_t Xorig2 = 0x013;
uint16_t Yorig2 = 0x021;
uint16_t X2=Xorig2;
uint16_t Y2=Yorig2;
uint16_t Xn2;
uint16_t Yn2;


void serendipitous_pal_ring() {

  EVERY_N_SECONDS(5) {
    X2 = Xorig2;
	  Y2 = Yorig2;
  }

  Xn2 = X2-(Y2/2); Yn2 = Y2+(Xn2/2);
//  Xn = X-Y/2;   Yn = Y+Xn/2;
//  Xn = X-(Y/2); Yn = Y+(X/2.1);
//  Xn = X-(Y/3); Yn = Y+(X/1.5);
//  Xn = X-(2*Y); Yn = Y+(X/1.1);
  
  X2 = Xn2;
  Y2 = Yn2;
  this_index = (sin8(X2)+cos8(Y2))/2;
  ringPalette(X2%143, current_palette, this_index, 255, LINEARBLEND);
  fadeToBlackBy(leds, NUM_LEDS, 16);                     // 8 bit, 1 = slow, 255 = fast
  
} // serendipitous_pal_ring()

#endif
