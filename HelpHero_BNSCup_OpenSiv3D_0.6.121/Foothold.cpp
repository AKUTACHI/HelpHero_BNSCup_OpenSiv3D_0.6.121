#include "stdafx.h"
#include "Foothold.h"

Foothold::Foothold()
{
	pos = footholdRect.pos;
}

void Foothold::set(Rect _setRect, bool _isHold,P2World* _world) {//ブロックのセッティング
	isValid = true;
	isHold = _isHold;
	world = _world;
	pos = _setRect.pos;
	footholdRect = _setRect;
	body = world->createRect(P2Dynamic, Vec2{pos.x + footholdRect.w / 2,pos.y + footholdRect.h / 2 }, SizeF{ footholdRect.w,footholdRect.h });
}

void Foothold::Update()
{
	pos = body.getPos();
	footholdRect.x = pos.x - footholdRect.w / 2;
	footholdRect.y = pos.y - footholdRect.h / 2;
}

void Foothold::Draw()
{
	//footholdRect.draw();
	body.draw();
}

void Foothold::carry_move(Rect _robot) {//掴まれている時ロボットに追従する
	if (carry&& isHold) {
		pos = _robot.pos;
		pos.y += _robot.h;
	}
}
