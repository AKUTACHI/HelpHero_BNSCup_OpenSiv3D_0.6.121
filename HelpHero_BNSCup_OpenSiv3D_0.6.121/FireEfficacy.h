#pragma once
#include "Efficacy.h"

struct Particle
{
	double Firecount;
	double clear;
	Vec2 coursePos;
	double speed;
	double courseDirectionX;
	int32 angle;
	Timer lifetime;
};

class FireEfficacy :public Efficacy
{//爆発エフェクトクラスFireEfficacy
public:
	//座標、炎範囲、テクスチャ、炎の密度
	FireEfficacy(Vec2 _center, int _range, Texture _effect, int _density);

	void Update()override;

	void Draw()const;

	void CenterUpdate(Vec2 _center) { pos = _center; }//エフェクト位置更新

	void Digestion() { isValid = false; }//消化
private:

	int Number = 0;
	int density;
	double count;
	int range;//炎の範囲
	Array<Particle> particles;
	const double Time = 1;
	//Array<double>Firecount;
	//Array<double>clear;//透明度
	//Array<Vec2>coursePos;//エフェクトの座標
	//Array<double> speed;//エフェクトの移動スピード
	//Array<double>courseDirectionX;//エフェクトの移動方向
	//Array<int>angle;//炎のイージング
};
