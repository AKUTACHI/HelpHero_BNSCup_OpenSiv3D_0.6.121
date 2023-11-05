#include "stdafx.h"
#include "FireEfficacy.h"
FireEfficacy::FireEfficacy(Vec2 _center, int _range, Texture _effect, int _density) {

	effect = _effect;
	density = _density;
	range = _range;
	pos = _center;
	isValid = true;
}

void FireEfficacy::Update() {
	count+= Scene::DeltaTime();
	//炎召喚
	if (count >= Time / density) {
		count -= Time / density;
		Number++;

		courseDirectionX << 0;
		coursePos << Vec2(Random(int(pos.x), int(pos.x) + range), pos.y);
		speed << Random(10, 50) * 10;
		clear << 1;
		angle << 0;
		Firecount << Time;
		
	}


	if (isValid)
		for (int i = 0; i < Number; i++) {//移動処理
			if (Firecount[i] < 0) {//要素の削除
				Firecount.pop_back();
				clear.pop_back();
				coursePos.pop_back();
				speed.pop_back();
				courseDirectionX.pop_back();
				angle.pop_back();

				Number--;
			}
			Firecount[i] -= Scene::DeltaTime();

			angle[i] += 1;
			courseDirectionX[i] = angle_easing(angle[i]);

			clear[i] = Firecount[i] / Time;

			coursePos[i].x += courseDirectionX[i] * Random(1, 3) * 10 * Scene::DeltaTime();
			coursePos[i].y -= speed[i] * Scene::DeltaTime();
		}
	Print << Number;
}

void FireEfficacy::Draw()const {

	if (isValid)
		for (int i = 0; i < Number; i++) {

			effect.drawAt(coursePos[i], ColorF(1, clear[i]));

		}
}
