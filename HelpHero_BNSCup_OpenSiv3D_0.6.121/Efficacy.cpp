﻿#include "stdafx.h"
#include "Efficacy.h"
#include "Common.h"
Efficacy::Efficacy() {
}

Vec2 Efficacy::angle_radius_normalization(int angle) {



	double rad = angle * 3.14159 / 180;

	double radY = sin(rad);
	double radX = cos(rad);

	return { radX,radY };
}
double Efficacy::angle_easing(int angle) {

	double rad = angle * 3.14159 / 180;

	double radX = cos(rad);

	return  radX;

}
