#include "stdafx.h"
#include "Robot.h"

Robot::Robot(Player* _player)
{
	player = _player;
	area = robotRect;
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
		if (KeyEnter.pressed()) {
			pos.y += 400;
		}
		if (KeyEnter.up()) {
			pos.y -= 400;
		}

	}
	robotRect.x = pos.x;
	robotRect.y = pos.y;
	area = robotRect;
	area.h += 500;
}

void Robot::Draw()
{
	if (KeyShift.pressed()) {
		area.draw(ColorF{ 1,0.2,0,0.5 });
	}
	robotRect.draw(ColorF{ 1.0,1.0,0 });
}
