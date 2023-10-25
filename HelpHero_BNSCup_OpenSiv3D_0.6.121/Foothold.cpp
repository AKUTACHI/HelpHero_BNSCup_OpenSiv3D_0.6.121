#include "stdafx.h"
#include "Foothold.h"

Foothold::Foothold()
{
	pos = footholdRect.pos;
}

void Foothold::set(Rect _setRect) {

}

void Foothold::Update()
{
	
	if (carry) {//ロボットに触れられたらくっついていく
		
	}
	footholdRect.x = pos.x;
	footholdRect.y = pos.y;
}

void Foothold::Draw()
{
	footholdRect.draw();
}

void Foothold::carry_move(Rect _robot) {//掴まれている時ロボットに追従する
	if (carry) {
		pos = _robot.pos;
		pos.y += _robot.h;
	}
}
