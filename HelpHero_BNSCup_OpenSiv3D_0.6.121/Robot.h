#pragma once
#include"common.h"
class Player;
class Robot
{
	Vec2 pos = { 100,-700 };
	bool ready = true;
	Rect robotRect = { 400,-700,150,800 };
	Rect area;
	float speed = 100;
	Player* player;
public:
	Robot(Player* _player);
	void Update();
	void Draw();
	Vec2 getPos() { return pos; }
	Rect getRect() { return robotRect; }
};

