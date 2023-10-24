#pragma once
#include "common.h"
#include "Player.h"
#include "Robot.h"
class Foothold
{
	Vec2 pos = { 0,500 };//playerと一緒
	bool carry = false;//運ばれてるか
	Rect footholdRect = {0,500,800,100 };
	Player* player;//位置とる用
	Robot* robot;
public:
	Foothold(Player* _player, Robot* _robot,Rect _rect);
	void Update();
	void Draw();
	Vec2 getPos() { return pos; }
	Rect getRect() { return footholdRect; }
};

