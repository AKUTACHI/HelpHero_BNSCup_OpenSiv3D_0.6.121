﻿#pragma once
#ifndef _SpreadEfficacy_H_
#define _SpreadEfficacy_H_
#include "Efficacy.h"

class SpreadEfficacy :public Efficacy
{//爆発エフェクトクラスFireEfficacy
public:
	//座標、テクスチャ、飛び散るエフェクトの数
	SpreadEfficacy(Vec2 _center,Texture _effect, int _Number);

	void Update();

	void Draw()const;

private:

	int Number=0;
	Array<double>clear;//透明度
	Array<Vec2>coursePos;//エフェクトの座標
	Array<Vec2>courseAngle;//エフェクトの移動角度
};

#endif
