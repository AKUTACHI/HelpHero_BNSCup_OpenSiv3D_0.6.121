﻿#pragma once
class Efficacy
{//efficacy
protected:
	int EfficacyNo;

	Vec2 pos = { 0,0 };//座標
	Texture effect;//テクスチャ
	bool isValid = false;//有効かどうか

	Timer timer;

	double count=0;
public:
	Efficacy();

	virtual void Update() = 0;
	virtual void Draw()const = 0;

	bool IsValid() { return isValid; }

	Vec2 angle_radius_normalization(int angle);
	double angle_easing(int angle);
};
