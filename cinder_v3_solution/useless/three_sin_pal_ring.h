#ifndef THREE_SIN_PAL_RING_H
#define THREE_SIN_PAL_RING_H



// three_sin_pal_ring variables ---------------------------------------------------------------------

int wave1r;
int wave2r;
int wave3r;
uint8_t mul1r;
uint8_t mul2r;
uint8_t mul3r;


void three_sin_pal_ring() {
  wave1r += beatsin8(10,-4,4);
  wave2r += beatsin8(15,-2,2);
  wave3r += beatsin8(12,-3, 3);

  for (int k=0; k<144; k++) {
    uint8_t tmp = sin8(mul1r*k + wave1r) + sin8(mul1r*k + wave2r) + sin8(mul1r*k + wave3r);
    ringPalette(k, current_palette, tmp, 255);
  }
} // three_sin_pal_ring()


#endif
