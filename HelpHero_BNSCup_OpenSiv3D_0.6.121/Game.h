﻿#pragma once
#include "Common.h"
#include "Efficacy.h"
#include "SpreadEfficacy.h"
#include "Foothold.h"
#include "Player.h"
#include "Robot.h"
#include "Victim.h"

class Game : public App::Scene
{
public:

	Game(const InitData& init);

	~Game();

	void update() override;

	void draw() const override;
	void CheckGoal();
	void BackGroundUpdate();
	void InputsUpdate();
private:
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	Player* player;
	Robot* robot;
	Victim* victim;
	Array<Foothold*> foothold;//アレイ化
	double accumulatorSec = 0.0;
	P2World world{ gravity };
	// 重力加速度 (cm/s^2)
	Array<P2Body> bodies;
	P2Body ground;

	Array<Efficacy*> effects;

	bool goal=false;
	Rect goalRect{ 0,400,150,200 };
	Texture texGround;
	//背景テクスチャ
	Texture texBack00Outlook;
	Texture texBack01Robot;
	Texture texBack02Building;
	Vec2 BackRobotPos;
	bool steped = false;
	HashTable<P2BodyID, int32> hashTable;

	Camera2D* camera;
};

