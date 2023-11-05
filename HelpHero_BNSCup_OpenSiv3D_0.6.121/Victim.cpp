#include "stdafx.h"
#include "Common.h"
#include "Victim.h"

Victim::Victim(P2World* _world, Player* _player)
{
	world = _world;
	player = _player;
	body = world->createRect(P2Dynamic, Vec2{ pos.x + victimRect.w / 2,pos.y + victimRect.h / 2 }, SizeF{ 40,40 }, P2Material{ .density = 400 });

	texVictim = Texture{ U"textures/VictimA.png" };
}

void Victim::Update()
{
	if (victimRect.intersects(player->getRect())) {
		if (KeyEnter.down())
			if (!carry)carry = true;
			else {
				carry = false;
				body.setPos(Vec2(player->getRect().pos.x - 50, player->getRect().pos.y + 40));
			}
	}
	if (carry) {
		body.setFixedRotation(true);
		body.setAwake(false);
		body.setPos(Vec2(player->getRect().pos.x + 39, player->getRect().pos.y - 24));
	}
	else {
		body.setFixedRotation(false);
		body.setAwake(true);
	}
	pos.x = body.getPos().x - victimRect.w / 2;
	pos.y = body.getPos().y - victimRect.h / 2;
	victimRect.x = pos.x;
	victimRect.y = pos.y;
}

void Victim::Draw()
{
	//victimRect(texVictim).draw(ColorF{1.0,0,0});
	//body.draw();
	Circle(body.getPos(),60).draw(ColorF{ 1.0,0,0,0.4 });
	victimRect.movedBy(0,-20)(texVictim).draw();
}

void Victim::carry_move(Vec2 _player) {//掴まれている時プレイヤーに追従する
	/*if (carry) {
		pos.x = _player.x + 10;
	}*/
}
