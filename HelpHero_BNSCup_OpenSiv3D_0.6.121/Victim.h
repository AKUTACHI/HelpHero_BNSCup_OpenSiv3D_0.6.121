#pragma once
#include "common.h"
class Victim//ちなみにvictimが被災者の英語らしい
{
	Vec2 pos = { 700,450 };
	bool carry=false;//運ばれてる
	Rect victimRect = { 0,0,40,40 };
public:
	Victim();
	void Update();
	void Draw();

	void carry_move(Vec2 _player); //掴まれている時ロボットに追従する
	void carry_flip() { carry = !carry; }//掴まれているかの反転

	Vec2 getPos() { return pos; }
	Rect getRect() { return victimRect; }
};

