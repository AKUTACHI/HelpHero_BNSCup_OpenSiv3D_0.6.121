#pragma once
#include "common.h"
class Player
{
	P2World* world;
	P2Body body;
	P2Body beforeBody;
	Vec2 pos{0 ,450 };//位置 Rectに入る
	Vec2 beforePos;//更新前の位置
	float gravity = 5;
	float speed = 1000;
	Rect playerRect = { 0,0,80,80 };
	bool isJump;
public:
	Player(P2World* _world);
	void Update();

	void DecisionMave();//移動確定
	void Draw();

	void CheckGround();//接触判定　床の回数だけ呼ぶ あとで変える

	Vec2 getNowPos() { return pos; }
	Vec2 getBeforePos() { return beforePos; }
	Rect getRect() { return playerRect; }
};

