#include "stdafx.h"
#include "Common.h"
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
	if (footholdRect.bottomY() < 0) {
		body.release();
	}
}

void Foothold::Draw()
{
	//footholdRect.draw();
	body.draw();
}

void Foothold::CheckCarry(Robot* _robot) {//掴まれている時ロボットに追従する
	/*Vec2 rPos = _robot->getBody().getPos();
	Vec2 r
	if(rPos.x <pos.x && rPos.x+rPos.)*/

	for (auto [pair, collision] : world->getCollisions())
	{
		if ((pair.a == body.id() && _robot->getBody().id() == pair.b) || (pair.b == body.id() && pair.a == _robot->getBody().id()))
		{
			carry = true;
			//body.applyLinearImpulse(Vec2{ 0,-1500 * Scene::DeltaTime() });
		}
	}

	if (carry) {
		body.setAwake(false);
		body.setPos(Vec2(body.getPos().x, body.getPos().y - (_robot->getSpeed() * Scene::DeltaTime())));
	}
}
