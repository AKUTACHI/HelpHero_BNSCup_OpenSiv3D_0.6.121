#pragma once
#include "common.h"
//ブロック
class Foothold
{
	Vec2 pos = { 0,500 };//playerと一緒
	bool carry = false;//運ばれてるか
	Rect footholdRect = {0,500,800,100 };
public:
	Foothold();
	void set(Rect _setRect);
	void Update();
	void Draw();

	void carry_move(Rect _robot); //掴まれている時ロボットに追従する

	Vec2 getPos() { return pos; }
	Rect getRect() { return footholdRect; }
};

