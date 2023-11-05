#include "stdafx.h"
#include "Common.h"
#include "Foothold.h"

Foothold::Foothold()
{
	pos = footholdRect.pos;

	texFoothold = Texture{ U"textures/Foothold.png" };
}

void Foothold::set(Rect _setRect, bool _isHold,P2World* _world) {//ブロックのセッティング
	isValid = true;
	isHold = _isHold;
	world = _world;
	pos = _setRect.pos;
	footholdRect = _setRect;
	body = world->createRect(P2Dynamic, Vec2{ pos.x + footholdRect.w / 2,pos.y + footholdRect.h / 2 }, SizeF{ footholdRect.w,footholdRect.h }, P2Material{ .density = 1000 });
}

void Foothold::Update()
{
	pos = body.getPos();
	footholdRect.x = pos.x - footholdRect.w / 2;
	footholdRect.y = pos.y - footholdRect.h / 2;
	if (footholdRect.bottomY() < 0) {
		body.release();
		isValid = false;
	}
}

void Foothold::Draw()
{
	//footholdRect.draw();
	//body.draw();
	if(isValid)
		Rect{ (int32)body.getPos().x - footholdRect.w / 2,(int32)body.getPos().y- footholdRect.h ,footholdRect.w,footholdRect.h*2 }(texFoothold).draw();
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
