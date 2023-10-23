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
			carry = true;
		}
		else if (KeyEnter.down() && carry == true) {
			carry = false;
			pos.y += 20;
		}
	}
	if (carry) {
		pos = player->getPos();
		pos.y -= 20;
	}

	victimRect.x = pos.x;
	victimRect.y = pos.y;
}

void Victim::Draw()
{
	victimRect.draw(ColorF{1.0,0,0});
}
