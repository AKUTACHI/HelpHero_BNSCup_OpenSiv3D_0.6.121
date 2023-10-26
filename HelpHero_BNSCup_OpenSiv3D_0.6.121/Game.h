#pragma once
# include "Common.h"
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
	Foothold* foothold[10];//とりあえず、10個ブロックを準備する
};

