#pragma once
#include"common.h"
class Robot
{
	P2World* world;
	P2Body body;
	P2Body child;
	Stopwatch timer;
	Vec2 pos = { 100,-830 };
	double arm_contraction = 0;//アームの下げる数値


	bool up = false;//アームを上げる
	const double wait_time = 0.5;//止まる時間
	double wait_count = 0;

	bool ready = true;//入力を受け付ける状態
	Rect robotRect = { 100,-830,150,800 };
	Rect bodyRect;
	Rect area;//掘削範囲表示
	float speed = 130;
public:
	Robot(P2World* _world);
	void Update();
	void Draw();
	bool CheckGround(const P2Body ground);
	float getSpeed() { return speed; }
	Vec2 getPos() { return pos; }
	Rect getRect() { return robotRect; }
	P2Body getBody() { return body; }
	Rect getBodyRect() { return bodyRect; }

	Texture texHandOpen;
	Texture texHandClose;
};

