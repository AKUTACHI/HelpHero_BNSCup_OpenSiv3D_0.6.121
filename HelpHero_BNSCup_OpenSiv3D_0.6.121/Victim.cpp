#include "stdafx.h"
#include "Common.h"
#include "Victim.h"

Victim::Victim(P2World* _world)
{
	world = _world;
	body = world->createRect(P2Dynamic, Vec2{ pos.x + victimRect.w / 2,pos.y + victimRect.h / 2 }, SizeF{ victimRect.w,victimRect.h });
}

void Victim::Update()
{
	pos.x = body.getPos().x - victimRect.w / 2;
	pos.y = body.getPos().y - victimRect.h / 2;
	victimRect.x = pos.x;
	victimRect.y = pos.y - carry * 20;
}

void Victim::Draw()
{
	Print << carry;
	victimRect.draw(ColorF{1.0,0,0});
	body.draw();
}

void Victim::carry_move(Vec2 _player) {//掴まれている時プレイヤーに追従する
	if (carry) {
		pos.x = _player.x+10;
	}
}
