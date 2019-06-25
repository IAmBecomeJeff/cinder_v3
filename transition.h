#ifndef TRANSITION_H
#define TRANSITION_H


void update_old_variables() {
	for (int i = 0; i < NUM_LEDS; i++) {
		old_leds[i] = cur_leds[i];
	}
	old_all_freq = all_freq;
	old_bg_clr = bg_clr;
	old_bg_bri = bg_bri;
	old_start_index = start_index;
	old_this_beat = this_beat;
	old_this_bright = this_bright;
	old_that_bright = that_bright;
	old_this_cutoff = this_cutoff;
	old_this_delay = this_delay;
	old_this_diff = this_diff;
	old_this_dir = this_dir;
	old_this_fade = this_fade;
	old_this_hue = this_hue;
	old_this_index = this_index;
	old_this_inc = this_inc;
	old_this_phase = this_phase;
	old_that_phase = that_phase;
	old_this_rot = this_rot;
	old_this_sat = this_sat;
	old_this_speed = this_speed;
	old_that_speed = that_speed;
//	old_wave_brightness = wave_brightness;
	old_plasma_phase1 = plasma_phase1;
	old_plasma_phase2 = plasma_phase2;
	old_plasmaIndex = plasmaIndex;
	old_plasmaBright = plasmaBright;
	old_rip_color = rip_color;
	old_rip_center = rip_center;
	old_rip_step = rip_step;
	if (old_rip_step < 0) {
		old_rip_step = -1;
	}
	//old_rip_fadeRate = rip_fadeRate;
	//old_rip_currentBg = rip_currentBg;
	//old_rip_nextBg = rip_nextBg;
	//old_myfade = myfade;
	//old_fadeval = fadeval;
	//old_twinkle_speed = twinkle_speed;
	//old_twinkle_density = twinkle_density;
	//old_twinkle_bg = twinkle_bg;
	//old_auto_select_background_color = auto_select_background_color;
	//old_cool_like_incandescent = cool_like_incandescent;
	//old_bglight = bglight;
	//old_backgroundBrightness = backgroundBrightness;
	//old_bg = bg;
	//old_numdots = numdots;
	old_numdots_ring = numdots_ring;
	old_cooling = cooling;
	old_cooling1 = cooling1;
	old_cooling2 = cooling2;
	old_cooling3 = cooling3;
	old_cooling4 = cooling4;
	old_sparking = sparking;
	old_sparking1 = sparking1;
	old_sparking2 = sparking2;
	old_sparking3 = sparking3;
	old_sparking4 = sparking4;
	//old_zooming_beats_per_minute = zooming_beats_per_minute;
	//old_color_index = color_index;
	//old_color_speed = color_speed;
	//old_color_inc = color_inc;
	old_dist = dist;
	old_scale = scale;
	old_dist2 = dist2;
	old_scale2 = scale2;
	old_Xorig = Xorig;
	old_Yorig = Yorig;
	old_X = X;
	old_Y = Y;
	old_Xn = Xn;
	old_Yn = Yn;
	//old_Xorig2 = Xorig2;
	//old_Yorig2 = Yorig2;
	//old_X2 = X2;
	//old_Y2 = Y2;
	//old_Xn2 = Xn2;
	//old_Yn2 = Yn2;
	old_wave1 = wave1;
	old_wave2 = wave2;
	old_wave3 = wave3;
	old_mul1 = mul1;
	old_mul2 = mul2;
	old_mul3 = mul3;
	old_that_hue = that_hue;
	old_that_rot = that_rot;
	old_that_speed = that_speed;
	old_that_phase = that_phase;
	old_that_cutoff = that_cutoff;
	for (int i = 0; i < NUM_LEDS; i++) {
		old_xd[i] = xd[i];
		old_yd[i] = yd[i];
	}
	old_palette = current_palette;
	for (int i = 0; i < 4; i++) {
		old_ringBeat[i] = ringBeat[i];
	}
	old_juggle_index_reset = juggle_index_reset;
	old_brightdepth = brightdepth;
	old_msmultiplier = msmultiplier;
	old_hue8 = hue8;
	old_bri8 = bri8;
	old_cwave_index = cwave_index;
	old_brightnessthetainc16 = brightnessthetainc16;
	old_hue16 = hue16;
	old_hueinc16 = hueinc16;
	old_ms = ms;
	old_deltams = deltams;
	old_brightnesstheta16 = brightnesstheta16;
	old_h16_128 = h16_128;
	old_b16 = b16;
	old_bri16 = bri16;
    old_sPseudotime = sPseudotime;
    old_sLastMillis = sLastMillis;
    old_sHue16 = sHue16;
	old_pixelnumber = pixelnumber;
	for (uint8_t i = 0; i < NUM_BALLS; i++) {   
		old_tLast[i] =tLast[i];
		old_h[i] = h[i];
		old_pos[i] = pos[i];                              
		old_vImpact[i] = vImpact[i];                   
		old_tCycle[i] = tCycle[i];
		old_COR[i] = COR[i];
	}
	old_ball_hue = ball_hue;
	old_shift_x = shift_x;
	old_shift_y = shift_y;
	old_real_x = real_x;
	old_real_y = real_y;
	old_real_z = real_z;
	old_noise = noise;
	old_circ_index = circ_index;
	old_circ_bri = circ_bri;
//	old_jug16_phase = jug16_phase;
//  for (uint8_t i = 0; i < num_gravs; i++){
//    old_gravs[i] = my_gravs[i];
//  }
//  old_gravs.dist_old = my_gravs.dist_old;
//  old_gravs.distance = my_gravs.distance;
//  old_gravs.vel_old = my_gravs.vel_old;
//  old_gravs.velocity = my_gravs.velocity;
//  old_gravs.fireworks_hue = my_gravs.fireworks_hue;
//  old_gravs.fireworks_sat = my_gravs.fireworks_sat;
//  old_gravs.fireworks_bri = my_gravs.fireworks_bri;
//	old_fireworks_state = fireworks_state;
//	old_my_count = my_count;
}
//
//class led_class {
//public:
//	struct CRGB leds[576];
//	CRGBPalette16 palette;
//
//	uint8_t all_freq;
//	uint8_t bg_clr;
//	uint8_t bg_bri;
//	uint8_t start_index;
//	uint8_t this_beat;
//	uint8_t this_bright;
//	uint8_t that_bright;
//	uint8_t this_cutoff;
//	bool this_delay;
//	uint8_t this_diff;
//	bool this_dir;
//	uint8_t this_fade;
//	uint8_t this_hue;
//	uint8_t this_index;
//	uint8_t this_inc;
//	int this_phase;
//	int that_phase;
//	uint8_t this_rot;
//	uint8_t this_sat;
//	uint8_t this_speed;
//	uint8_t that_speed;
//	uint8_t wave_brightness;
//
//	int plasma_phase1;
//	int plasma_phase2;
//	int plasmaIndex;
//	int plasmaBright;
//
//	int rip_color;
//	int rip_center;
//	int rip_step;
//	float rip_fadeRate;
//	uint32_t rip_currentBg;
//	uint32_t rip_nextBg;
//	uint8_t myfade;
//	uint8_t fadeval;
//	byte twinkle_speed;
//	byte twinkle_density;
//	CRGB twinkle_bg;
//	byte auto_select_background_color;
//	byte cool_like_incandescent;
//	uint8_t bglight;
//	uint8_t backgroundBrightness;
//	CRGB bg;
//
//	uint8_t numdots;
//	uint8_t numdots_ring;
//
//	uint8_t cooling;				
//	uint8_t cooling1;
//	uint8_t cooling2;
//	uint8_t cooling3;
//	uint8_t cooling4;
//	uint8_t sparking;				
//	uint8_t sparking1;
//	uint8_t sparking2;
//	uint8_t sparking3;
//	uint8_t sparking4;
//	
//	uint8_t zooming_beats_per_minute; 
//	uint8_t color_index;
//	uint8_t color_speed;
//	uint8_t color_inc;
//
//	uint16_t dist;        
//	uint16_t scale;         
//	uint16_t dist2;        
//	uint16_t scale2;
//
//	uint16_t Xorig = 0x013;
//	uint16_t Yorig = 0x021;
//	uint16_t X = Xorig;
//	uint16_t Y = Yorig;
//	uint16_t Xn;
//	uint16_t Yn;
//
//	uint16_t Xorig2 = 0x013;
//	uint16_t Yorig2 = 0x021;
//	uint16_t X2 = Xorig;
//	uint16_t Y2 = Yorig;
//	uint16_t Xn2;
//	uint16_t Yn2;
//
//	int wave1;
//	int wave2;
//	int wave3;
//	uint8_t mul1;
//	uint8_t mul2;
//	uint8_t mul3;
//
//	int wave1r;
//	int wave2r;
//	int wave3r;
//	uint8_t mul1r;
//	uint8_t mul2r;
//	uint8_t mul3r;
//
//	uint8_t thathue ;                                      
//	uint8_t thatrot;                                        
//	int8_t thatspeed;                                        
//	int thatphase;                                           
//	uint8_t thatcutoff;
//};






#endif
