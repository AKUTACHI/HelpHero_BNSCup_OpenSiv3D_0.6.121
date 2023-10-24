#include "stdafx.h"
#include "Victim.h"

Victim::Victim(Player* _player, Robot* _robot)
{
	player = _player;
	robot = _robot;
}

void Victim::Update()
{
	if (victimRect.intersects(player->getRect())) {
		if (KeyEnter.down() && carry==false) {
			carry = true;//プレイヤーに持ち上げられてる
		}
		else if (KeyEnter.down() && carry == true) {
			carry = false;//プレイヤーに降ろされた
			pos.y += 20;
		}
	}
	if (carry) {
		pos = player->getPos();
		pos.y -= 20;//プレイヤーに追従しつつちょっとずらす
	}

	victimRect.x = pos.x;
	victimRect.y = pos.y;
}

void Victim::Draw()
{
	victimRect.draw(ColorF{1.0,0,0});
}
