#include "stdafx.h"
#include "Robot.h"

Robot::Robot(Player* _player)
{
	player = _player;
}

void Robot::Update()
{
	if (KeyShift.pressed()) {
		if (KeyA.pressed()) {
			pos.x -= speed * Scene::DeltaTime();
		}
		if (KeyD.pressed()) {
			pos.x += speed * Scene::DeltaTime();
		}
		if (KeyEnter.down()) {
			pos.y += 400;
		}
		if (KeyEnter.up()) {
			pos.y -= 400;
		}
	}
	robotRect.x = pos.x;
	robotRect.y = pos.y;
}

void Robot::Draw()
{
	robotRect.draw(ColorF{ 1.0,1.0,0 });
}
