#include "stdafx.h"
#include "Robot.h"

Robot::Robot(P2World* _world)
{
	area = robotRect;
	world = _world;
	//body = world->createRect(P2Dynamic, Vec2{ pos.x + robotRect.w / 2,pos.y + robotRect.h / 2 }, SizeF{ robotRect.w, robotRect.h }, {}, {});
	timer.reset();
}

void Robot::Update()
{
	if (KeyShift.pressed()) {//Shift中はロボットの操作　プレイヤーは動かない
		if (KeyA.pressed()&& ready) {
			beforePos.x -= speed * Scene::DeltaTime();
		}
		if (KeyD.pressed()&& ready) {
			beforePos.x += speed * Scene::DeltaTime();
		}
		if (KeyEnter.down()&& ready) {
			ready = false;
		}

	}
	
}

void Robot::ArmMove() {

	if (arm_move!=Wait) {

		beforePos.y += 200 * arm_move * Scene::DeltaTime();

	}

}

void Robot::DecisionMave() {//移動確定

	pos = beforePos;
	robotRect.x = pos.x;//反映
	robotRect.y = pos.y;
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
