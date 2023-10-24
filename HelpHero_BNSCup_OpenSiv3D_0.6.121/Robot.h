#pragma once
#include"common.h"
class Player;
class Robot
{
	Vec2 pos = { 100,-700 };
	bool ready = true;//入力を受け付ける状態　今は使用してない
	Rect robotRect = { 400,-700,150,800 };
	Rect area;//掘削範囲表示
	float speed = 100;
	Player* player;//まだ使ってない
public:
	Robot(Player* _player);
	void Update();
	void Draw();
	Vec2 getPos() { return pos; }
	Rect getRect() { return robotRect; }
};

