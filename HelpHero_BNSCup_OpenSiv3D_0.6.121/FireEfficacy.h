#pragma once
#ifndef _FireEfficacy_H_
#define _FireEfficacy_H_
#include "Efficacy.h"
class FireEfficacy :public Efficacy
{//爆発エフェクトクラスFireEfficacy
public:
	//座標、テクスチャ、飛び散るエフェクトの数
	FireEfficacy(Vec2 _center, Texture _effect, int _Number);

	void Update();

	void Draw()const;

	void CenterUpdate(Vec2 _center) { pos = _center; }//エフェクト位置更新

private:

	int Number = 0;
	Array<double>clear;//透明度
	Array<Vec2>coursePos;//エフェクトの座標
	Array<Vec2>courseAngle;//エフェクトの移動角度
};

#endif
