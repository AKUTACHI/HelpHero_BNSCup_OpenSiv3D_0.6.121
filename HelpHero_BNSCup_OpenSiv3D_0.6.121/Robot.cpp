#include "stdafx.h"
#include "Robot.h"

Robot::Robot(P2World* _world)
{
	area = robotRect;
	world = _world;
	body = world->createRect(P2Dynamic, Vec2{ pos.x + robotRect.w / 2,pos.y + robotRect.h / 2 }, SizeF{ robotRect.w, robotRect.h }, P2Material{ .density = 10, .restitution = 0.0, .friction = 1.0 }).setAwake(false);
	timer.reset();
}

void Robot::Update()
{
	if (KeyShift.pressed()) {//Shift中はロボットの操作　プレイヤーは動かない
		if (KeyA.pressed()&& ready) {
			pos.x -= speed * Scene::DeltaTime();
		}
		if (KeyD.pressed()&& ready) {
			pos.x += speed * Scene::DeltaTime();
		}
		if (KeyEnter.down()) {
			ready = false;
			arm_move = true;
		}

	}

	if (!ready) {
		if (arm_move)arm_contraction += 200 * Scene::DeltaTime();
		if (!arm_move)arm_contraction -= 200 * Scene::DeltaTime();
	}
	if (arm_contraction < 0)arm_contraction = 0;

	robotRect.x = pos.x;//反映
	robotRect.y = pos.y + arm_contraction;
	area = robotRect;
	area.h += 500;
}

void Robot::Draw()
{
	if (KeyShift.pressed()) {//掘削範囲
		area.draw(ColorF{ 1,0.2,0,0.5 });
	}
	robotRect.draw(ColorF{ 1.0,1.0,0 });//腕
}
