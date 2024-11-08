﻿#pragma once
#include <Siv3D.hpp> // Siv3D v0.6.12

#include"StageDifinition.h"

#include"Player.h"
#include"Victim.h"
#include"Foothold.h"
#include"Robot.h"
#include"Beeps.h"
#include"Efficacy.h"
#include "SpreadEfficacy.h"
#include "FireEfficacy.h"
// 共有するデータ
struct HelpHeroGameData
{
	int32 stage = 0;
	StageDifinition* currentStage;
};

//struct Data
//{
//	Chhese* currentStage;
//};
// シーンの名前
enum class State
{
	Title,
	Game,
	StageManager,
	Clear,
	End
};

enum {//衝突相手
	P_B,//プレイヤーとブロック
	P_V,//プレイヤーと救助者
	R_B,//ロボットとブロック
};

enum {//プレイヤー向き
	Wait,
	Left,
	Right,
	Up,
	Down,
	UpLeft = 5,
	UpRight = 6,
	DownLeft = 9,
	DownRight = 10,

};

enum {
	parapara,
	barabara,

};

using App = SceneManager<State, HelpHeroGameData>;

const double stepSec = (1.0 / 200.0);
// 重力加速度 (cm/s^2)
const double gravity = 980;
// 2D 物理演算のワールド

enum class EffectVariant//エフェクトのバリエーション
{
	Impact,
	Success,
	Dust,
	Fire,
	DustFall,
};

void GenerateEffect(Vec2 pos, EffectVariant val);
