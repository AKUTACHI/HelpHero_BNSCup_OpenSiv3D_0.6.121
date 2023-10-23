#pragma once
#include "common.h"
class Foothold;
class Player
{
	Vec2 pos = { 0,0 };
	float gravity = 5;
	float speed = 100;
	Rect playerRect = { 0,480,50,50 };
public:
	Player();
	void Update();
	void Draw();
	void CheckGround(Foothold* foothold);
	Vec2 getPos() { return pos; }
	Rect getRect() { return playerRect; }
};

