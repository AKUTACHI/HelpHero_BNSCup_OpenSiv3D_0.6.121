#include "stdafx.h"
#include "Victim.h"

Victim::Victim()
{
}

void Victim::Update()
{
	
		if (KeyEnter.down() && carry==false) {
			carry = true;//プレイヤーに持ち上げられてる
		}
		else if (KeyEnter.down() && carry == true) {
			carry = false;//プレイヤーに降ろされた
			pos.y += 20;
		}
	

	victimRect.x = pos.x;
	victimRect.y = pos.y;
}

void Victim::Draw()
{
	victimRect.draw(ColorF{1.0,0,0});
}

void Victim::carry_move(Rect _player) {//掴まれている時プレイヤーに追従する
	if (carry) {
		pos = _player.pos;
		pos.y -= 20;
	}
}
