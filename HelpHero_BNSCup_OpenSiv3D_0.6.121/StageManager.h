#pragma once
#include "Common.h"
#include "Efficacy.h"
#include "SpreadEfficacy.h"
#include "Foothold.h"
#include "Player.h"
#include "Robot.h"
#include "Victim.h"

class StageManager : public App::Scene
{
public:

	StageManager(const InitData& init);

	~StageManager();

	void update() override;

	void draw() const override;

	void Save();

	//衝突判定
		//0:左1:右2:上3:下
	void MotionHit(
		double NowPosL, double NowPosR, double NowPosU, double NowPosD,
		double NextPosL, double NextPosR, double NextPosU, double NextPosD,
		double partnerPos1, double partnerPos2, double partnerPos3, double partnerPos4, int IsMario);
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
	bool goal = false;
	Rect goalRect{ 0,400,150,200 };
	Texture texGround;
	//背景テクスチャ
	Texture texBack00Outlook;
	Texture texBack01Robot;
	Texture texBack02Building;
	Vec2 BackRobotPos;
	bool steped = false;
	bool isSimulate;
	TextWriter writer;
	bool isClick=false;
	Array<int32> CreatePos;
	Optional<FilePath> path;

	Grid<int32> loadFootPos{ 4,0,-1 };
};

