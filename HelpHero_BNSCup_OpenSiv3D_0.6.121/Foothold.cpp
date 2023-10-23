#include "stdafx.h"
#include "Foothold.h"

Foothold::Foothold(Player* _player, Robot* _robot,Rect _rect)
{
	player = _player;
	robot = _robot;
	footholdRect = _rect;
	pos = footholdRect.pos;
}

void Foothold::Update()
{
	if (footholdRect.intersects(robot->getRect())) {
			carry = true;
	}
	if (carry) {
		pos = robot->getPos();
		pos.y += robot->getRect().h;
	}
	footholdRect.x = pos.x;
	footholdRect.y = pos.y;
}

void Foothold::Draw()
{
	footholdRect.draw();
}
