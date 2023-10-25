#pragma once
#include "common.h"
class Player
{
	Vec2 pos{0 ,450 };//位置 Rectに入る
	Vec2 beforePos;//更新前の位置
	float gravity = 5;
	float speed = 100;
	Rect playerRect = { 0,0,50,50 };
public:
	Player();
	void Update();
	void Draw();
	void CheckGround();//接触判定　床の回数だけ呼ぶ あとで変える
	Vec2 getNowPos() { return pos; }
	Vec2 getBeforePos() { return beforePos; }
	Rect getRect() { return playerRect; }
};

