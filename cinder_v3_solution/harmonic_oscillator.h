#ifndef HARMONIC_OSCILLATOR_H
#define HARMONIC_OSCILLATOR_H

float eval_v_func_DHO(float v, float x, float acc_ext, float damping,	float springconstant, float mass)
{
	// acc_ext is generally negative when Flamingo is upright.
	// m x'' = - k x - c v + F_ext
	// with F_ext = m acc_ext
	return -damping * v - springconstant * x + mass * acc_ext;
}





// Integrates acceleration to get velocity for DHO
float get_next_v_DHO(float oldv, float oldx, float acc_ext, float damping,	float springconstant, float mass)
{
	float k1, k2, k3, k4;
	k1 = eval_v_func_DHO(oldv, oldx, acc_ext, damping, springconstant, mass);
	k2 = eval_v_func_DHO(oldv + 0.5 * k1, oldx, acc_ext, damping, springconstant,		mass);
	k3 = eval_v_func_DHO(oldv + 0.5 * k2, oldx, acc_ext, damping, springconstant,		mass);
	k4 = eval_v_func_DHO(oldv + k3, oldx, acc_ext, damping, springconstant, mass);
	return (float)(oldv + timestep_f * ((k1 / 6.0) + (k2 / 3.0) + (k3 / 3.0) +	(k4 / 6.0)));
}



float get_next_x_DHO(float oldv, float oldx)
{
	return (float)(oldx + timestep_f * oldv);
}



int ballToStrandPosition_DHO(float ballPos_DHO)
{
	return (STRIP_LENGTH / 2) + ballPos_DHO * (STRIP_LENGTH / 2);
};

// DAMPED HARMONIC OSCILLATOR, real physical units. Returns object position as a
// float, centered on 0, so maxrange is half the length of the strip.  Resting
// location is at 0.0
float getBallPosition_DHO(void)
{
	if (first_iter == 1)  // first iteration
	{
		pos0 = 0.0;
		vel0 = 0.0;
		timenow_i = 0;
		timestep_i = timenow_i - timeold_i;
		timeold_i = millis();  // why is this timeold and not timenow? I moved
							   // this from below btw
		timestep_f = 0.01 * ((float)timestep_i);

		// getNormalizedAccelY() is negative when Flamingo is upright.
		// getNormalizedAccelY() returns normalized acc in units of g
		// Right side up: 1.0
		// Upside Down:   -1.0
		acc_ext = G_ACC_MAGNITUDE * getNormalizedAccelY();
		vel1 = get_next_v_DHO(vel0, pos0, acc_ext, DAMPING_REAL,	SPRINGCONSTANT_REAL, MASS_REAL);
		pos1 = get_next_x_DHO(vel0, pos0);

		timeold_i = timenow_i;
		pos0 = pos1;
		vel0 = vel1;

		first_iter = 0;
	}
	else
	{
		timenow_i = millis();
		timestep_i = timenow_i - timeold_i;
		timestep_f = 0.01 * ((float)timestep_i);

		// acc_ext is generally negative because getNormalizedAccelY() returns
		// negative when Flamingo is upright.
		// G_ACC_MAGNITUDE is positive.
		acc_ext = G_ACC_MAGNITUDE * getNormalizedAccelY();
		vel1 = get_next_v_DHO(vel0, pos0, acc_ext, DAMPING_REAL,SPRINGCONSTANT_REAL, MASS_REAL);
		pos1 = get_next_x_DHO(vel0, pos0);
		vel0 = vel1;
		pos0 = pos1;
		timeold_i = timenow_i;


		uint16_t timet = millis();
		if (timet - sendTime > 100)
		{
			Serial.print(F("Time:\t"));
			Serial.print(timet);
			Serial.print(F("\tpos1:\t"));
			Serial.print((pos1));
			Serial.print(F("\tBallPosition:\t"));
			Serial.print((pos1 / (MASS_REAL * G_ACC_MAGNITUDE / SPRINGCONSTANT_REAL))+ 1.0); Serial.print(F("\tPixel Index:\t"));
			Serial.print(ballToStrandPosition_DHO((pos1 / (MASS_REAL * G_ACC_MAGNITUDE / SPRINGCONSTANT_REAL))+ 1.0)); Serial.print(F("\tgetNormalizedAccelY:\t"));
			Serial.print(getNormalizedAccelY());
			Serial.print(F("\tgetNormalizedOffsetAccelY:\t"));
			Serial.println(getNormalizedOffsetAccelY());

			sendTime = timet;
		}

	}
	// Resting location is at 0.0
	float temp = (pos1 / (MASS_REAL * G_ACC_MAGNITUDE / SPRINGCONSTANT_REAL)) + 1.0;

	return temp;
}



// 1
//////////// DHO SINGLE PIXEL
////////////////////////////////////////////////////////////////////////////////////////

void DHO_SinglePixel(bool old)
{
	float BallPosition = getBallPosition_DHO();
	if (old) {
		fill_solid(old_leds, NUM_LEDS, CRGB(0, 0, 0));
		ringCRGB(1, ballToStrandPosition_DHO(BallPosition), color.r, color.g, color.b);
	}
	else {
		fill_solid(cur_leds, NUM_LEDS, CRGB(0, 0, 0));
		ringCRGB(0, ballToStrandPosition_DHO(BallPosition), color.r, color.g, color.b);
	}
	//setPixelByStrandIndex(ballToStrandPosition_DHO(BallPosition), color);
	  Serial.print("\tBallPosition:\t");
	Serial.print(BallPosition);
	Serial.print("\tPixel Index:\t");
	Serial.println(ballToStrandPosition_DHO(BallPosition));
	
	//FastLED.show();
}

// 2
//////////// DHO Blob
////////////////////////////////////////////////////////////////////////////////////////



void DHO_Blob(bool old)
{
	if (old) {
		float BallPosition = getBallPosition_DHO();

		//FastLED.clear();
		fill_solid(old_leds, NUM_LEDS, CRGB(0, 0, 0));

		int centerindex = (uint16_t((float)STRIP_LENGTH / 2.0) + BallPosition * ((float)STRIP_LENGTH / 2.0));
		float attnFactor;

		for (int k = -9; k <= 9; k++)
		{
			attnFactor = (uint8_t)((uint8_t)pgm_read_byte_near(gaussianTable + k + 9));

			Serial.print("attnFactor: ");
			Serial.println(attnFactor);
			Serial.print("k: ");
			Serial.println(k);

			//setPixelByStrandIndex(centerindex + k, scale8(color.r, attnFactor),scale8(color.g, attnFactor),	scale8(color.b, attnFactor));
			ringCRGB(1, centerindex + k, scale8(color.r, attnFactor), scale8(color.g, attnFactor), scale8(color.b, attnFactor));
		}
	}
	else {
		float BallPosition = getBallPosition_DHO();

		//FastLED.clear();
		fill_solid(cur_leds, NUM_LEDS, CRGB(0, 0, 0));

		int centerindex = (uint16_t((float)STRIP_LENGTH / 2.0) + BallPosition * ((float)STRIP_LENGTH / 2.0));
		float attnFactor;

		for (int k = -9; k <= 9; k++)
		{
			attnFactor = (uint8_t)((uint8_t)pgm_read_byte_near(gaussianTable + k + 9));

			Serial.print("attnFactor: ");
			Serial.println(attnFactor);
			Serial.print("k: ");
			Serial.println(k);

			//setPixelByStrandIndex(centerindex + k, scale8(color.r, attnFactor),scale8(color.g, attnFactor),	scale8(color.b, attnFactor));
			ringCRGB(0, centerindex + k, scale8(color.r, attnFactor), scale8(color.g, attnFactor), scale8(color.b, attnFactor));
		}
	}
	//FastLED.show();
}


// 3
//////////// DHO Rainbow
////////////////////////////////////////////////////////////////////////////////////////
void DHO_Rainbow(bool old)
{
	if (old) {
		float BallPosition = getBallPosition_DHO();

		int centerindex = (uint16_t((float)STRIP_LENGTH / 2.0) +	BallPosition * ((float)STRIP_LENGTH / 2.0));

		CRGB rainbowhue;
		for (int i = 0; i < STRIP_LENGTH; i++)
		{
			rainbowhue = CHSV(2 * centerindex + 255 * (i / ((float)STRIP_LENGTH)), 255, 255);
			//setPixelByStrandIndex(i, rainbowhue);
			ringCRGB(1, i, rainbowhue.r, rainbowhue.g, rainbowhue.b);
		}
	}
	else {
		float BallPosition = getBallPosition_DHO();

		int centerindex = (uint16_t((float)STRIP_LENGTH / 2.0) +	BallPosition * ((float)STRIP_LENGTH / 2.0));

		CRGB rainbowhue;
		for (int i = 0; i < STRIP_LENGTH; i++)
		{
			rainbowhue =	CHSV(2 * centerindex + 255 * (i / ((float)STRIP_LENGTH)), 255, 255);
			//setPixelByStrandIndex(i, rainbowhue);
			ringCRGB(0, i, rainbowhue.r, rainbowhue.g, rainbowhue.b);
		}
	}
	//FastLED.show();
}

///////////////////////////////////////////////////////
// DHO FADE
void DHO_Fade(bool old)
{
	if (old) {
		// about 1 to 2 ms
		float BallPosition = getBallPosition_DHO();

		// about 7 ms
		fadeWholeStrip(1, (uint8_t)FADE_COEF);

		// < 0 ms
		//setPixelByStrandIndex(ballToStrandPosition_DHO(BallPosition), color);
		ringCRGB(1, ballToStrandPosition_DHO(BallPosition), color.r, color.g, color.b);

		Serial.print("\tBallPosiition:\t");
		Serial.print(BallPosition);
		Serial.print("\tPixel Index:\t");
		Serial.println(ballToStrandPosition_DHO(BallPosition));

	}
	else {
		// about 1 to 2 ms
		float BallPosition = getBallPosition_DHO();

		// about 7 ms
		fadeWholeStrip(0, (uint8_t)FADE_COEF);

		// < 0 ms
		//setPixelByStrandIndex(ballToStrandPosition_DHO(BallPosition), color);
		ringCRGB(0, ballToStrandPosition_DHO(BallPosition), color.r, color.g, color.b);

		Serial.print("\tBallPosiition:\t");
		Serial.print(BallPosition);
		Serial.print("\tPixel Index:\t");
		Serial.println(ballToStrandPosition_DHO(BallPosition));
	}
	// about 1 ms
	//FastLED.show();
}

//float getBallPositionReal(void);


#endif
