#ifndef JUGGLE_H
#define JUGGLE_H

/* This is adapted from a routine created by Mark Kriegsman */

/*  Usage - juggle_pal();
 *  
 *  this_hue
 *  this_fade
 *  numdots
 *  this_beat
 *  this_bright
 *  this_diff
 */
// use beatsin16_halfup and beatsin16_halfdown to make it go one way

//void juggle_pal(bool old) {                                            // Several colored dots, weaving in and out of sync with each other
//	if (old) {
//		old_this_index = 0;                                           // Reset the hue values.
//		fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
//		for (int i = 0; i < old_numdots; i++) {
//			old_leds[beatsin16(old_this_beat + i + old_numdots, 0, NUM_LEDS)] += ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);    // Munge the values and pick a colour from the palette
//			old_this_index += old_this_diff;
//		}
//	}
//	else {
//		this_index = 0;                                           // Reset the hue values.
//		fadeToBlackBy(leds, NUM_LEDS, this_fade);
//		for (int i = 0; i < numdots; i++) {
//			cur_leds[beatsin16(this_beat + i + numdots, 0, NUM_LEDS)] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);    // Munge the values and pick a colour from the palette
//			this_index += this_diff;
//		}
//	}
//} // juggle_pal()

void juggle_pal_ring(bool old) {                                            // Several colored dots, weaving in and out of sync with each other
	mode_number = 14;
	if (old) {
		if (old_juggle_index_reset) { old_this_index = 0; }          // Reset the hue values.
		fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
		for (int i = 0; i < old_numdots_ring; i++) {
			ringPaletteAdd(1, beatsin16(old_this_beat + i + old_numdots_ring, 0, STRIP_LENGTH - 1), old_palette, old_this_index, old_this_bright, current_blending);
			// Munge the values and pick a colour from the palette
			old_this_index += old_this_diff;
		}
	}
	else {
		if (juggle_index_reset) { this_index = 0; }                      // Reset the hue values.
		fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);
		for (int i = 0; i < numdots_ring; i++) {
			ringPaletteAdd(0, beatsin16(this_beat + i + numdots_ring, 0, STRIP_LENGTH - 1), current_palette, this_index, this_bright, current_blending);
			// Munge the values and pick a colour from the palette
			this_index += this_diff;
		}
	}
} // juggle_pal_ring()

void juggle_pal_ring_onedir(bool old) {                                            // Several colored dots, weaving in and out of sync with each other
	mode_number = 15;
	if (old) {
		if (old_juggle_index_reset) { old_this_index = 0; }                                           // Reset the hue values.
		fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
		for (int i = 0; i < old_numdots_ring; i++) {
			if (!old_this_dir) {
				ringPaletteAdd(1, beatsin16_halfdown(old_this_beat + i + old_numdots_ring, 0, STRIP_LENGTH - 1), old_palette, old_this_index, old_this_bright, current_blending);
			}
			else {
				ringPaletteAdd(1, beatsin16_halfup(old_this_beat + i + old_numdots_ring, 0, STRIP_LENGTH - 1), old_palette, old_this_index, old_this_bright, current_blending);
			}
			// Munge the values and pick a colour from the palette
			old_this_index += old_this_diff;
		}
	}
	else {
		if (juggle_index_reset) { this_index = 0; }                                          // Reset the hue values.
		fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);
		for (int i = 0; i < numdots_ring; i++) {
			if (!this_dir) {
				ringPaletteAdd(0, beatsin16_halfdown(this_beat + 2 * i + numdots_ring, 0, STRIP_LENGTH - 1), current_palette, this_index, this_bright, current_blending);
			}
			else {
				ringPaletteAdd(0, beatsin16_halfup(this_beat + i + numdots_ring, 0, STRIP_LENGTH - 1), current_palette, this_index, this_bright, current_blending);
			}
			this_index += this_diff;
		}
	}
} // juggle_pal_ring()


void juggle_fire(bool old) {
	mode_number = 16;
	if (old_juggle_index_reset) { old_this_index = 0; }
	if (juggle_index_reset) { this_index = 0; }
	fadeToBlackBy(jug_leds, NUM_LEDS, this_fade);
	for (int i = 0; i < numdots_ring; i++) {
		if (this_dir) {
			ring_juggle(beatsin16_halfdown(this_beat + 3 * i + numdots_ring, 0, STRIP_LENGTH - 1), current_palette, this_index, this_bright, current_blending);
		}
		else {
			ring_juggle(beatsin16_halfup(this_beat + 3 * i + numdots_ring, 0, STRIP_LENGTH - 1), current_palette, this_index, this_bright, current_blending);
		}
		this_index += this_diff;
	}
	fire_rings(old);
	for (int i = 0; i < NUM_LEDS; i++) {
		if (old) {
			old_leds[i] += jug_leds[i];
		}
		else {
			cur_leds[i] += jug_leds[i];
		}
	}
}



  void juggle_pal_individual_ring(bool old, int ring) {                                            // Several colored dots, weaving in and out of sync with each other
	  if (old) {
		  if (old_juggle_index_reset) { old_this_index = 0; }                                            // Reset the hue values.
		  for (int i = 0; i < old_numdots_ring_arr[ring]; i++) {
			  old_leds[ringArray[beatsin16(old_ringBeat[ring] + i + old_numdots_ring_arr[ring], 0, STRIP_LENGTH-1)][ring]] += ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);    // Munge the values and pick a colour from the palette
			  old_this_index += old_this_diff;
		  }
	  }
	  else {
		  if (juggle_index_reset) { this_index = 0; }                                           // Reset the hue values.
		  for (int i = 0; i < numdots_ring_arr[ring]; i++) {
			  cur_leds[ringArray[beatsin16(ringBeat[ring] + i + numdots_ring_arr[ring], 0, STRIP_LENGTH-1)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);    // Munge the values and pick a colour from the palette
			  this_index += this_diff;
		  }
	  }
  } // juggle_pal()

  void juggle_pal_individual_ring_all(bool old) {
	  mode_number = 17;
    if(old){ fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade); }
    else{ fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);}
	  juggle_pal_individual_ring(old, 0);
	  juggle_pal_individual_ring(old, 1);
	  juggle_pal_individual_ring(old, 2);
	  juggle_pal_individual_ring(old, 3);
  }

  void juggle_pal_individual_ring_onedir(bool old, int ring) {                                            // Several colored dots, weaving in and out of sync with each other
	  if (old) {
		  if (old_juggle_index_reset) { old_this_index = 0; }                                            // Reset the hue values.
		  for (int i = 0; i < old_numdots_ring_arr[ring]; i++) {
			  if (old_this_dir) {
				  old_leds[ringArray[beatsin16_halfdown(old_ringBeat[ring] + i + old_numdots_ring_arr[ring], 0, STRIP_LENGTH - 1)][ring]] += ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);
			  }
			  else {
				  old_leds[ringArray[beatsin16_halfup(old_ringBeat[ring] + i + old_numdots_ring_arr[ring], 0, STRIP_LENGTH - 1)][ring]] += ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);
			  }
			  // Munge the values and pick a colour from the palette
			  old_this_index += old_this_diff;
		  }
	  }
	  else {
		  if (juggle_index_reset) { this_index = 0; }                                            // Reset the hue values.
		  for (int i = 0; i < numdots_ring_arr[ring]; i++) {
			  if (this_dir) {
				  cur_leds[ringArray[beatsin16_halfdown(ringBeat[ring] + i + numdots_ring_arr[ring], 0, STRIP_LENGTH - 1)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
			  }
			  else {
				  cur_leds[ringArray[beatsin16_halfup(ringBeat[ring] + i + numdots_ring_arr[ring], 0, STRIP_LENGTH - 1)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
			  }
			  this_index += this_diff;
		  }
	  }
  } 


  void juggle_pal_individual_ring_onedir_all(bool old) {
	  mode_number = 18;
    if(old){ fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade); }
    else{ fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);}
	  juggle_pal_individual_ring_onedir(old, 0);
	  juggle_pal_individual_ring_onedir(old, 1);
	  juggle_pal_individual_ring_onedir(old, 2);
	  juggle_pal_individual_ring_onedir(old, 3);
}

  void juggle_fire_individual(bool old) {
	  mode_number = 19;
	  if (old_juggle_index_reset) { old_this_index = 0; }
	  fadeToBlackBy(jug_leds, NUM_LEDS, this_fade);
		for (int ring = 0; ring < 4; ring++) {
      for (int i = 0; i < numdots_ring_arr[ring]; i++) {
			  if (this_dir) {
				  jug_leds[ringArray[beatsin16_halfdown(ringBeat[ring] + i + numdots_ring_arr[ring], 0, STRIP_LENGTH - 1)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
			  }
			  else {
				  jug_leds[ringArray[beatsin16_halfup(ringBeat[ring] + i + numdots_ring_arr[ring], 0, STRIP_LENGTH - 1)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
			  }
        this_index += this_diff;
		  }
	  }
	  fire_rings1(old);
	  fire_rings2(old);
	  fire_rings3(old);
	  fire_rings4(old);
	  for (int i = 0; i < NUM_LEDS; i++) {
		  if (old) {
			  old_leds[i] += jug_leds[i];
		  }
		  else {
			  cur_leds[i] += jug_leds[i];
		  }
	  }
  }

  
void juggle_fire_individual_same_dir(bool old) {
	mode_number = 20;
	if (old_juggle_index_reset) { old_this_index = 0; }
	fadeToBlackBy(jug_leds, NUM_LEDS, this_fade);
	for (int ring = 0; ring < 4; ring++) {
    for (int i = 0; i < numdots_ring_arr[ring]; i++) {
			if (this_dir) {
				jug_leds[ringArray[beatsin16_halfdown(ringBeat[ring] + i + numdots_ring_arr[ring], 0, STRIP_LENGTH - 1)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
			}
			else {
				jug_leds[ringArray[beatsin16_halfup(ringBeat[ring] + i + numdots_ring_arr[ring], 0, STRIP_LENGTH - 1)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
			}
      this_index += this_diff;
		}
	}
	fire_rings1_opp(old);
	fire_rings2_opp(old);
	fire_rings3_opp(old);
	fire_rings4_opp(old);
	for (int i = 0; i < NUM_LEDS; i++) {
		if (old) {
			old_leds[i] += jug_leds[i];
		}
		else {
			cur_leds[i] += jug_leds[i];
		}
	}
}



void juggle_pal_individual_ring_onedir_phase(bool old) {                                            // Several colored dots, weaving in and out of sync with each other
	mode_number = 61;
	if (old) {
		if (old_juggle_index_reset) { old_this_index = 0; }                                            // Reset the hue values.
		fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
		for (uint8_t ring = 0; ring < 4; ring++) {
			for (int i = 0; i < old_numdots; i++) {
				if (old_this_dir) {
					old_leds[ringArray[beatsin16_halfdown(old_this_beat + i + old_numdots, 0, STRIP_LENGTH - 1, 0, old_jug16_phase * ring)][ring]] += ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);
				}
				else {
					old_leds[ringArray[beatsin16_halfup(old_this_beat + i + old_numdots, 0, STRIP_LENGTH - 1, 0, old_jug16_phase * ring)][ring]] += ColorFromPalette(old_palette, old_this_index, old_this_bright, current_blending);
				}
				// Munge the values and pick a colour from the palette
				old_this_index += old_this_diff;
			}
		}
	}
	else {
		if (juggle_index_reset) { this_index = 0; }                                            // Reset the hue values.
		fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);
		for (uint8_t ring = 0; ring < 4; ring++) {
			for (int i = 0; i < numdots; i++) {
				if (this_dir) {
					cur_leds[ringArray[beatsin16_halfdown(this_beat + i + numdots, 0, STRIP_LENGTH - 1, 0, jug16_phase * ring)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
				}
				else {
					cur_leds[ringArray[beatsin16_halfup(this_beat + i + numdots, 0, STRIP_LENGTH - 1, 0, jug16_phase * ring)][ring]] += ColorFromPalette(current_palette, this_index, this_bright, current_blending);
				}
				this_index += this_diff;
			}
		}
	}
}

	//
////add juggle
//void add_juggle_down() {
//	fadeToBlackBy(jug_leds, NUM_LEDS, jug_fade);
//	int pos1 = beatsin16_halfdown(30, 0, STRIP_LENGTH-1);
//	//int pos2 = beatsin16_halfdown(70, 0, STRIP_LENGTH);
//  jug_index++;
//  if (jug_index > 250){jug_index = 0;}
//	ring_juggle(pos1, current_palette, jug_index);	
//}
//

#endif
