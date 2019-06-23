#ifndef HEARTBEAT_H
#define HEARTBEAT_H

//***************************************************************
// Heart pulse, blood flowing example
// 
// Marc Miller, Jan 2016
//***************************************************************


//===============================================================
// Heart Beat Functions
//   The base for all this goodness came from Mark Kriegsman and
//   was initially coded up by Chris Thodey.  I updated it to use
//   HSV and provided all the variables to play with up above.
//   -Marc

uint8_t pulseWave8(uint32_t ms, uint16_t cycleLength, uint16_t pulseLength) {
  uint16_t T = ms % cycleLength;
  if (T > pulseLength) return baseBrightness;
  uint16_t halfPulse = pulseLength / 2;
  if (T <= halfPulse) {
    return (T * 255) / halfPulse;  //first half = going up
  }
  else {
    return((pulseLength - T) * 255) / halfPulse;  //second half = going down
  }
}

int sumPulse(int time_shift) {
  //time_shift = 0;  //Uncomment to heart beat/pulse all LEDs together
  int pulse1 = pulseWave8(millis() + time_shift, cycleLength, pulseLength);
  int pulse2 = pulseWave8(millis() + time_shift + pulseOffset, cycleLength, pulseLength);
  return qadd8(pulse1, pulse2);  // Add pulses together without overflow
}

void heartbeat() {
	if (this_dir == 0) { flowDirection = -1; }
	else { flowDirection = 1; }
	for (int i = 0; i < STRIP_LENGTH; i++) {
		uint8_t bloodVal = sumPulse((5 / STRIP_LENGTH / 2) + (STRIP_LENGTH / 2) * i * flowDirection);
		ringCHSV(i, bloodHue, bloodSat, bloodVal);
		//leds[i] = CHSV(bloodHue, bloodSat, bloodVal);
	}
}




//End_heart_beat_functions
//---------------------------------------------------------------

#endif
