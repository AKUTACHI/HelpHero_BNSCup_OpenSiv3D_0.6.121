#pragma once
#include"common.h"
class Robot
{
	P2World* world;
	P2Body body;
	Stopwatch timer;
	Vec2 pos = { 100,-700 };
	double arm_contraction = 0;//アームの下げる数値


	bool arm_move = false;//アームを下げる
	const double wait_time = 0.5;//止まる時間
	double wait_count = 0;

	bool ready = true;//入力を受け付ける状態
	Rect robotRect = { 100,-700,150,800 };
	Rect area;//掘削範囲表示
	float speed = 100;
public:
	Robot(P2World* _world);
	void Update();
	void Draw();
	Vec2 getPos() { return pos; }
	Rect getRect() { return robotRect; }
};

