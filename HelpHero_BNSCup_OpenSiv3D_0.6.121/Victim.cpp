#include "stdafx.h"
#include "Victim.h"

Victim::Victim(P2World* _world)
{
	world = _world;
}

void Victim::Update()
{
	
	victimRect.x = pos.x;
	victimRect.y = pos.y - carry * 20;
}

void Victim::Draw()
{
	Print << carry;
	victimRect.draw(ColorF{1.0,0,0});
}

void Victim::carry_move(Vec2 _player) {//掴まれている時プレイヤーに追従する
	if (carry) {
		pos.x = _player.x+10;
	}
}
