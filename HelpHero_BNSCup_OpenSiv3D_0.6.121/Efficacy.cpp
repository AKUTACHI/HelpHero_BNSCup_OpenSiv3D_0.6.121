#include "stdafx.h"
#include "Efficacy.h"
Efficacy::Efficacy() {
	komaNow = { 0,0 };
}

Efficacy::Efficacy(Vec2 _pos, Texture _effect, Vec2 _komaSize, Vec2 _koma) {
	set(_pos,_effect, _komaSize, _koma);
}
//座標、画像、コマ数
void Efficacy::set(Vec2 _pos, Texture _effect, Vec2 _komaSize, Vec2 _koma) {
	EfficacyNo = parapara;
	komaMax = _koma;
	komaSize = _komaSize;
	pos = _pos;
	effect = _effect;
	count = 0;
	isValid = true;
	timer.set(1s);
	timer.start();
}

//バラけるタイプ
//中心座標、画像
void Efficacy::set(Vec2 _center, Texture _effect) {
	EfficacyNo = barabara;
	pos = _center;
	effect = _effect;
	count = 1;
	isValid = true;
	angle = angle_radius_normalization(Random(359));

}

void Efficacy::Update() {
	if (EfficacyNo == parapara) {
		count += Scene::DeltaTime();
		if (count >= 0.1) {

			if (komaNow == komaMax)isValid = false;

			if (komaNow.x >= komaMax.x) {
				komaNow.x = 1;
				komaNow.y += 1;
			}
			count -= 0.1;
		}
	}

	if (EfficacyNo == barabara) {

		if (count <= 0)isValid = false;

		pos += angle * Scene::DeltaTime();
		count -= Scene::DeltaTime();
	}
	if (timer.reachedZero())
	{
		isValid = false;
	}
}


void Efficacy::Draw() {
	if (EfficacyNo == parapara)effect(komaSize * komaNow, komaSize).draw(pos, ColorF(1, 1));
	if (EfficacyNo == barabara)effect(komaSize * komaNow, komaSize).draw(pos, ColorF(1, count));
}

Vec2 Efficacy::angle_radius_normalization(int angle) {



	double rad = angle * 3.14159 / 180;

	double radY = sin(rad);
	double radX = cos(rad);

	return { radX,radY };
}
