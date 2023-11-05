#include "stdafx.h"
#include "Efficacy.h"
Efficacy::Efficacy() {
}

Vec2 Efficacy::angle_radius_normalization(int angle) {



	double rad = angle * 3.14159 / 180;

	double radY = sin(rad);
	double radX = cos(rad);

	return { radX,radY };
}
