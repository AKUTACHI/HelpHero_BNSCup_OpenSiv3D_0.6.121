#include "stdafx.h"
#include "SpreadEfficacy.h"
SpreadEfficacy::SpreadEfficacy(Vec2 _center,Texture _effect,int _Number) {

	effect = _effect;
	Number = _Number;
	pos = _center;
	for (int i = 0; i < Number; i++) {
		int a = 360 / Number;
		courseAngle << angle_radius_normalization(a * i);
		coursePos << pos;
		clear << 1;
	}
	isValid = true;
}

void SpreadEfficacy::Update() {

	
	if (isValid)
	for (int i = 0; i < Number; i++) {//移動処理
		if (clear[i] <= 0)isValid = false;
		clear[i] -= Scene::DeltaTime();

		coursePos[i].x += courseAngle[i].x * 100 * Scene::DeltaTime();
		coursePos[i].y += courseAngle[i].y * 100 * Scene::DeltaTime();
	}
}

void SpreadEfficacy::Draw()const {

	if(isValid)
	for (int i = 0; i < Number; i++) {

		effect.drawAt(coursePos[i],ColorF(1, clear[i]));

	}
}
