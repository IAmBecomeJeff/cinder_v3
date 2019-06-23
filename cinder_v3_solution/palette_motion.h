#ifndef PALETTE_MOTION_H
#define PALETTE_MOTION_H

// uint8_t color_index  -  the index within the palette.  involves a sin function.  leave it out?
// uint8_t color_speed  -  how quickly we move the palette
// uint8_t color_inc  -  how quickly we go from the beginning to end of palette

//void fillFromPalette(){
//	color_index += color_speed;
//	for( int i = 0; i < STRIP_LENGTH; i++){
//		ringPalette(i, current_palette, color_index + sin8(8*i), this_bright, current_blending);
//		color_index += color_inc;
//	}
//}

void palette_motion(bool old){
	mode_number = 27;
	if (old) {
		if (old_this_dir) {
			old_color_index += old_color_speed;
		}
		else { old_color_index -= old_color_speed; }
		ring_fill_palette(1, old_color_index, old_color_inc, old_palette, old_this_bright, current_blending);
	}
	else {
		if (this_dir) {
			color_index += color_speed;
		}
		else { color_index -= color_speed; }
		ring_fill_palette(0, color_index, color_inc, current_palette, this_bright, current_blending);
	}
}


#endif
