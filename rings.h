#ifndef RINGS_H
#define RINGS_H

// Use CHSV
void ringCHSV(bool old, uint8_t pos, uint8_t hue, uint8_t sat = this_sat, uint8_t bri = this_bright) {
	if (old) {
		for (byte j = 0; j < 4; j++) {
			old_leds[ringArray[pos][j]] = CHSV(hue, sat, bri);
		}
	}
	else {
		for (byte j = 0; j<4; j++) {
			cur_leds[ringArray[pos][j]] = CHSV(hue, sat, bri);
		}
	}
}

// Add CHSV
void ringCHSVAdd(bool old, uint8_t pos, uint8_t hue, uint8_t sat = this_sat, uint8_t bri = this_bright) {
	if (old) {
		for (byte j = 0; j < 4; j++) {
			old_leds[ringArray[pos][j]] += CHSV(hue, sat, bri);
		}
	}
	else {
		for (byte j = 0; j<4; j++) {
			cur_leds[ringArray[pos][j]] += CHSV(hue, sat, bri);
		}
	}
}

// Use CRGB
void ringCRGB(bool old, uint8_t pos, uint8_t r, uint8_t g, uint8_t b){
	if (old) {
		for (byte j = 0; j < 4; j++) {
			old_leds[ringArray[pos][j]] = CRGB(r, g, b);
		}
	}
	else {
		for (byte j = 0; j<4; j++) {
			cur_leds[ringArray[pos][j]] = CRGB(r, g, b);
		}
	}
}

// Add CRGB
void ringCRGBAdd(bool old, uint8_t pos, uint8_t r, uint8_t g, uint8_t b){
	if (old) {
		for (byte j = 0; j < 4; j++) {
			old_leds[ringArray[pos][j]] += CRGB(r, g, b);
		}
	}
	else {
		for (byte j = 0; j<4; j++) {
			cur_leds[ringArray[pos][j]] += CRGB(r, g, b);
		}
	}
}

// Use ColorFromPalette
void ringPalette(bool old, uint8_t pos, CRGBPalette16 pal, uint8_t index, uint8_t bri = this_bright, TBlendType blending = current_blending){
	if (old) {
		for (byte j = 0; j < 4; j++) {
			old_leds[ringArray[pos][j]] = ColorFromPalette(pal, index, bri, blending);
		}
	}
	else {
		for (byte j = 0; j<4; j++) {
			cur_leds[ringArray[pos][j]] = ColorFromPalette(pal, index, bri, blending);
		}
	}
}

// Use ColorFromPalette
void ringPaletteAdd(bool old, uint8_t pos, CRGBPalette16 pal, uint8_t index, uint8_t bri = this_bright, TBlendType blending = current_blending){
	if (old) {
		for (byte j = 0; j < 4; j++) {
			old_leds[ringArray[pos][j]] += ColorFromPalette(pal, index, bri, blending);
		}
	}
	else {
		for (byte j = 0; j<4; j++) {
			cur_leds[ringArray[pos][j]] += ColorFromPalette(pal, index, bri, blending);
		}
	}
}

// Use nblend
void ring_nblend(bool old, uint16_t pix, CRGB new_color, fract8 blend_amount){
	if (old) {
		for (byte j = 0; j < 4; j++) {
			nblend(old_leds[ringArray[pix][j]], new_color, blend_amount);
		}
	}
	else {
		for (byte j = 0; j<4; j++) {
			nblend(cur_leds[ringArray[pix][j]], new_color, blend_amount);
		}
	}
}

// Ring version of fill_palette
 void ring_fill_palette(bool old, uint8_t startIndex, uint8_t incIndex, CRGBPalette16 pal=current_palette, uint8_t bri = this_bright, TBlendType blending=current_blending){
	 if (old) {
		 uint8_t colorIndex = startIndex;
		 for (uint16_t i = 0; i < STRIP_LENGTH; i++) {
			 ringPalette(1, i, pal, colorIndex, bri, blending);
			 colorIndex += incIndex;
		 }
	 }
	 else {
		 uint8_t colorIndex = startIndex;
		 for (uint16_t i = 0; i < STRIP_LENGTH; i++) {
			 ringPalette(0, i, pal, colorIndex, bri, blending);
			 colorIndex += incIndex;
		 }
	 }
 }

 // Ring version of fill_rainbow
 void ring_fill_rainbow(bool old, uint8_t initialhue, uint8_t deltahue){
	 if (old) {
		 byte hsv_hue;
		 hsv_hue = initialhue;
		 for (int i = 0; i < STRIP_LENGTH; i++) {
			 ringCHSV(1, i, hsv_hue, 255, 240);
			 hsv_hue += deltahue;
		 }
	 }
	 else {
		 byte hsv_hue;
		 hsv_hue = initialhue;
		 for (int i = 0; i < STRIP_LENGTH; i++) {
			 ringCHSV(0, i, hsv_hue, 255, 240); 
			 hsv_hue += deltahue;
		 }
	 }
 }

void ring_fill_static_palette(bool old, CRGBPalette16 pal=current_palette, uint8_t bri = this_bright, TBlendType blending=current_blending){
	if (old) {
		for (uint8_t i = 0; i < STRIP_LENGTH; i++) {
			ringPalette(1, i, pal, i * 255 / STRIP_LENGTH, bri, blending);
		}
	}
	else {
		for (uint8_t i = 0; i< STRIP_LENGTH; i++) {
			ringPalette(0, i, pal, i * 255 / STRIP_LENGTH, bri, blending);
		}
	}
} 

void ring_juggle(int pos, CRGBPalette16 pal, uint8_t index, uint8_t bri= this_bright, TBlendType blending = current_blending){
	for (byte j = 0; j<4; j++) {
		jug_leds[ringArray[pos][j]] = ColorFromPalette(pal, index, bri, blending);
	}
}
#endif
