#ifndef PLASMA_H
#define PLASMA_H

void plasma(bool old) {
	mode_number = 28;
	if (old) {
		old_plasma_phase1 = beatsin8(6, -64, 64);
		old_plasma_phase2 = beatsin8(7, -64, 64);

		for (int k = 0; k < STRIP_LENGTH; k++) {
			old_plasmaIndex = cubicwave8((k * 23) + old_plasma_phase1) / 2 + cos8((k * 15) + old_plasma_phase2) / 2;
			old_plasmaBright = qsuba(old_plasmaIndex, beatsin8(7, 0, 96));

			ringPalette(1, k, old_palette, old_plasmaIndex, old_plasmaBright, current_blending);
		}
	}
	else {
		plasma_phase1 = beatsin8(6, -64, 64);
		plasma_phase2 = beatsin8(7, -64, 64);

		for (int k = 0; k < STRIP_LENGTH; k++) {
			plasmaIndex = cubicwave8((k * 23) + plasma_phase1) / 2 + cos8((k * 15) + plasma_phase2) / 2;
			plasmaBright = qsuba(plasmaIndex, beatsin8(7, 0, 96));

			ringPalette(0, k, current_palette, plasmaIndex, plasmaBright, current_blending);
		}
	}
} // plasma()

#endif
