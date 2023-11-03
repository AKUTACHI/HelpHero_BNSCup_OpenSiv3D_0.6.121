#pragma once
#include"common.h"

class Robot
{
	P2World* world;
	P2Body body;
	Stopwatch timer;
	Vec2 pos = { 100,-700 };
	bool ready = true;//入力を受け付ける状態　今は使用してない
	Rect robotRect = { 400,-700,150,800 };
	Rect area;//掘削範囲表示
	float speed = 100;
public:
	Robot(P2World* _world);
	void Update();

	void DecisionMave();//移動確定
	void ArmMove();
	void Draw();


	Vec2 getNowPos() { return pos; }
	Rect getRect() { return robotRect; }
};

