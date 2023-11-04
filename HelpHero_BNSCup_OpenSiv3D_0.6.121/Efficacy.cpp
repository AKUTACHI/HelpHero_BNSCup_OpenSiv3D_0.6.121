#include "stdafx.h"
#include "Efficacy.h"
Efficacy::Efficacy() {
	komaNow = { 0,0 };
}

//座標、画像、コマ数
void Efficacy::set(Vec2 _pos, Texture _effect, Vec2 _komaSize, Vec2 _koma) {
	komaMax = _koma;
	komaSize = _komaSize;
	pos = _pos;
	effect = _effect;
	isValid = true;
}
void Efficacy::Update() {
	count += Scene::DeltaTime();
	if (count >= 0.1) {

		if (komaNow.x >= komaMax.x) {
			komaNow.x = 1;
			komaNow.y += 1;
		}
		count -= 0.1;
	}
}


void Efficacy::Draw() {
	effect(komaSize* komaNow, komaSize).draw(pos);
}
