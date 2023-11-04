#pragma once
#include "common.h"
class Efficacy
{
	int EfficacyNo;

	Vec2 komaMax;//コマ数
	Vec2 komaNow;//コマ数
	Vec2 komaSize;//コマサイズ
	Vec2 pos;//座標
	Texture effect;//テクスチャ
	bool isValid = false;//有効かどうか

	Timer timer;

	double count=0;

	Vec2 angle;

public:
	Efficacy();
	Efficacy(Vec2 _pos, Texture _effect, Vec2 _komaSize, Vec2 _koma);
	Efficacy(Vec2 _pos, Texture _effect);

	//座標、画像、コマサイズ、コマ数
	void set(Vec2 _pos, Texture _effect,Vec2 _komaSize,Vec2 _koma);
	//バラけるタイプ
	//中心座標、画像
	void set(Vec2 _center, Texture _effect);

	void Update();

	void Draw();

	bool IsValid() { return isValid; }

	Vec2 angle_radius_normalization(int angle);
};
