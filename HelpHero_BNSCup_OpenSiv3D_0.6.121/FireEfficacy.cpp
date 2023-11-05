#include "stdafx.h"
#include "FireEfficacy.h"
FireEfficacy::FireEfficacy(Vec2 _center, int _range, Texture _effect, int _density) {

	effect = _effect;
	density = _density;
	range = _range;
	pos = _center;
	isValid = true;
	particles.clear();
}

void FireEfficacy::Update() {
	count+= Scene::DeltaTime();
	//炎召喚
	if (count >= Time / density) {
		count -= Time / density;
		Number++;

		Particle item;
		item.courseDirectionX = 0;
		item.coursePos = Vec2(Random(int(pos.x), int(pos.x) + range), pos.y);
		item.speed = Random(10, 50) * 10;
		item.clear = 1;
		item.angle = 0;
		item.Firecount = Time;
		item.lifetime.set(1s);
		item.lifetime.start();
		particles << item;
	}


	if (isValid)
		for (auto& item: particles)
		{
			item.Firecount -= Scene::DeltaTime();
			item.angle += 1;
			item.courseDirectionX = angle_easing(item.angle);
			item.clear = item.Firecount / Time;

			item.coursePos.x += item.courseDirectionX * Random(1, 3) * 10 * Scene::DeltaTime();
			item.coursePos.y -= item.speed * Scene::DeltaTime();
		}
	particles.remove_if([](Particle item) { return item.lifetime.reachedZero(); });
	Print << Number;
}

void FireEfficacy::Draw()const {

	if (isValid)
		for (auto& item : particles)
		{
			effect.drawAt(item.coursePos, ColorF(1, item.clear));
		}
}
