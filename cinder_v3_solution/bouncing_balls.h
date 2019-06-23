#ifndef BOUNCING_BALLS_H
#define BOUNCING_BALLS_H



//#define GRAVITY           -1              // Downward (negative) acceleration of gravity in m/s^2
//#define h0                1                  // Starting height, in meters, of the ball (strip length)
//#define NUM_BALLS         6                  // Number of bouncing balls you want (recommend < 7, but 20 is fun in its own way)
//
//float h[NUM_BALLS];                         // An array of heights
//float vImpact0 = sqrt(-2 * GRAVITY * h0);  // Impact velocity of the ball when it hits the ground if "dropped" from the top of the strip
//float vImpact[NUM_BALLS];                   // As time goes on the impact velocity will change, so make an array to store those values
//float tCycle[NUM_BALLS];                    // The time since the last time the ball struck the ground
//int   pos[NUM_BALLS];                       // The integer position of the dot on the strip (LED index)
//long  tLast[NUM_BALLS];                     // The clock time of the last ground strike
//float COR[NUM_BALLS];                       // Coefficient of Restitution (bounce damping)

//for (int i = 0; i < NUM_BALLS; i++) {    // Initialize variables
//	tLast[i] = millis();
//	h[i] = h0;
//	pos[i] = 0;                              // Balls start on the ground
//	vImpact[i] = vImpact0;                   // And "pop" up at vImpact0
//	tCycle[i] = 0;
//	COR[i] = 0.90 - float(i) / pow(NUM_BALLS, 2);
//}

void bouncing_balls(bool old) {
	mode_number = 52;
	if (old) {
		for (uint8_t i = 0; i < NUM_BALLS; i++) {
			fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
			old_tCycle[i] = millis() - old_tLast[i];     
			old_h[i] = 0.5 * GRAVITY * pow(old_tCycle[i] / 1000, 2.0) + old_vImpact[i] * old_tCycle[i] / 1000;
			if (old_h[i] < 0) {
				old_h[i] = 0;                          
				old_vImpact[i] = old_COR[i] * old_vImpact[i];   
				old_tLast[i] = millis();
				if (old_vImpact[i] < 0.01) { old_vImpact[i] = old_vImpact0; }
			}
			old_pos[i] = round(old_h[i] * (STRIP_LENGTH - 1) / h0);       
      ringCHSV(1, pos[i], (i*40), 255, 255);
			//old_leds[ringArray[old_pos[i]]] = CHSV((i * 40), 255, 255);
		}
	}
	else {
		for (uint8_t i = 0; i < NUM_BALLS; i++) {
			fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);
			tCycle[i] = millis() - tLast[i];     // Calculate the time since the last time the ball was on the ground

			// A little kinematics equation calculates positon as a function of time, acceleration (gravity) and intial velocity
			h[i] = 0.5 * GRAVITY * pow(tCycle[i] / 1000, 2.0) + vImpact[i] * tCycle[i] / 1000;

			if (h[i] < 0) {
				h[i] = 0;                            // If the ball crossed the threshold of the "ground," put it back on the ground
				vImpact[i] = COR[i] * vImpact[i];   // and recalculate its new upward velocity as it's old velocity * COR
				tLast[i] = millis();

				if (vImpact[i] < 0.01) { vImpact[i] = vImpact0; }  // If the ball is barely moving, "pop" it back up at vImpact0
			}
			pos[i] = round(h[i] * (STRIP_LENGTH - 1) / h0);       // Map "h" to a "pos" integer index position on the LED strip

      ringCHSV(0, pos[i], (i*40), 255, 255);
			//cur_leds[ringArray[pos[i]]] = CHSV((i * 40), 255, 255);
		}
	}
}


void bouncing_balls2(bool old) {
	mode_number = 53;
	if (old) {
		for (uint8_t i = 0; i < NUM_BALLS; i++) {
			fadeToBlackBy(old_leds, NUM_LEDS, old_this_fade);
			old_tCycle[i] = millis() - old_tLast[i];
			old_h[i] = 0.5 * GRAVITY * pow(old_tCycle[i] / 1000, 2.0) + old_vImpact[i] * old_tCycle[i] / 1000;
			if (old_h[i] < 0) {
				old_h[i] = 0;
				old_vImpact[i] = old_COR[i] * old_vImpact[i];
				old_tLast[i] = millis();
				if (old_vImpact[i] < 0.01) { old_vImpact[i] = old_vImpact0; }
			}
			old_pos[i] = round(old_h[i] * (STRIP_LENGTH - 1) / h0);
      //ringCHSV(1, old_pos[i], old_ball_hue + i*STRIP_LENGTH / NUM_BALLS, 255, 255);
			ringPaletteAdd(1, old_pos[i], old_palette, old_ball_hue + i * STRIP_LENGTH / NUM_BALLS, 255, current_blending);
      //old_leds[ringArray[old_pos[i]]] = CHSV(old_ball_hue + i * STRIP_LENGTH / NUM_BALLS, 255, 255);
			old_ball_hue++;
		}
	}
	else {
		for (uint8_t i = 0; i < NUM_BALLS; i++) {
			fadeToBlackBy(cur_leds, NUM_LEDS, this_fade);
			tCycle[i] = millis() - tLast[i];     // Calculate the time since the last time the ball was on the ground

			// A little kinematics equation calculates positon as a function of time, acceleration (gravity) and intial velocity
			h[i] = 0.5 * GRAVITY * pow(tCycle[i] / 1000, 2.0) + vImpact[i] * tCycle[i] / 1000;

			if (h[i] < 0) {
				h[i] = 0;                            // If the ball crossed the threshold of the "ground," put it back on the ground
				vImpact[i] = COR[i] * vImpact[i];   // and recalculate its new upward velocity as it's old velocity * COR
				tLast[i] = millis();

				if (vImpact[i] < 0.01) { vImpact[i] = vImpact0; }  // If the ball is barely moving, "pop" it back up at vImpact0
			}
			pos[i] = round(h[i] * (STRIP_LENGTH - 1) / h0);       // Map "h" to a "pos" integer index position on the LED strip
      //ringCHSV(0, pos[i], ball_hue + i * STRIP_LENGTH / NUM_BALLS, 255, 255);
			ringPaletteAdd(0, pos[i], current_palette, ball_hue + i * STRIP_LENGTH / NUM_BALLS, 255, current_blending);
			//cur_leds[ringArray[pos[i]]] = CHSV(ball_hue + i * STRIP_LENGTH / NUM_BALLS, 255, 255);
			ball_hue++;
		}
	}
}


#endif
