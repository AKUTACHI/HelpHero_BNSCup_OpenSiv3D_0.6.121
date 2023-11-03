#pragma once
# include <Siv3D.hpp> // Siv3D v0.6.12
#include"Player.h"
#include"Victim.h"
#include"Foothold.h"
#include"Robot.h"
// シーンの名前
enum class State
{
	Game,
};

enum {//衝突相手
	P_B,//プレイヤーとブロック
	P_V,//プレイヤーと救助者
	R_B,//ロボットとブロック
};

enum {//プレイヤー向き
	Wait,
	Up,
	Down,

};


// 共有するデータ
struct GameData
{

};

using App = SceneManager<State, GameData>;
