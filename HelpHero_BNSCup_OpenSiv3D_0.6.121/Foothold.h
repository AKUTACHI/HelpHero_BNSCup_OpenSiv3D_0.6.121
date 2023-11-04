#pragma once
#include "common.h"
class Robot;
//ブロック
class Foothold
{
	P2World* world;
	P2Body body;
	Vec2 pos = { 0,500 };//playerと一緒
	bool carry = false;//運ばれてるか
	Rect footholdRect = {0,500,800,100 };
	bool isHold = false;//持てるかどうか
	bool isValid = false;//有効かどうか
public:
	Foothold();
	void set(Rect _setRect,bool _isHold,P2World* _world);
	void Update();
	void Draw();

	void CheckCarry(Robot* _robot); //掴まれている時ロボットに追従する

	Vec2 getPos() { return pos; }
	Rect getRect() { return footholdRect; }

	bool IsValid(){ return isValid; }
};

