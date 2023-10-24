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
	E_B,//敵とブロック
	PA_E,//プレイヤー攻撃と敵
	P_E,//プレイヤーと敵
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


// 共有するデータ
struct GameData
{

};

using App = SceneManager<State, GameData>;
