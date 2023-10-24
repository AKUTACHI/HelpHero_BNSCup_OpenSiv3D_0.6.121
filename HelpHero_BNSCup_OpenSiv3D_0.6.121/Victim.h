#pragma once
#include "common.h"
#include"Foothold.h"
class Player;
class Robot;
class Victim//ちなみにvictimが被災者の英語らしい
{
	Vec2 pos = { 700,450 };
	bool carry=false;//運ばれてる
	Rect victimRect = { 0,0,40,40 };
	Player* player;
	Robot* robot;
public:
	Victim(Player* _player,Robot* _robot);
	void Update();
	void Draw();
	Vec2 getPos() { return pos; }
	Rect getRect() { return victimRect; }
};

