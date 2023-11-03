#pragma once
#include"common.h"

class Robot
{
	Vec2 pos = { 100,-700 };
	Vec2 beforePos = { 100,-700 };//更新前の位置
	int arm_move = Wait;//アームの動く方向
	bool ready = true;//入力を受け付ける状態
	const double WaitTime = 0.5;
	double WaitCount = 0;

	Rect robotRect = { 400,-700,150,800 };
	Rect area;//掘削範囲表示
	float speed = 100;
public:
	Robot();
	void Update();

	void DecisionMave();//移動確定
	void ArmMove();
	void Draw();

	void ArmWait() { if (ready) WaitCount = WaitTime; ready = false; }

	Vec2 getNowPos() { return pos; }
	Vec2 getBeforePos() { return beforePos; }
	Rect getRect() { return robotRect; }
};

