#pragma once
#include "common.h"
class Foothold;
class Player
{
	Vec2 pos{0 ,450 };//初期位置　posを更新したらRectに入る
	Vec2 beforePos;//衝突(仮）あとでテンプレートの方にする
	float gravity = 5;
	float speed = 100;
	Rect playerRect = { 0,0,50,50 };
public:
	Player();
	void Update();
	void Draw();
	void CheckGround(Foothold* foothold);//接触判定　床の回数だけ呼ぶ あとで変える
	Vec2 getPos() { return pos; }
	Rect getRect() { return playerRect; }
};

