﻿#include "stdafx.h"
#include "Game.h"
Game::Game(const InitData& init)
	: IScene{ init } {
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	player = new Player(&world);
	robot = new Robot(&world);
	victim = new Victim(&world);
	for (int i = 0; i < 10; i++) {
		foothold[i] = new Foothold();
	}

	foothold[0]->set({ 0,500,800,100 },false,&world);
	foothold[1]->set({ 500,400,200,100 }, false,&world);
	foothold[2]->set({ 500,250,150,100 }, false, &world);
	foothold[3]->set({ 700,400,200,100 }, false, &world);

	ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 680, 1300, 680 });
}
Game::~Game() {
	delete player;
	delete robot;
	delete victim;
	for (int i = 0; i < 10; i++) {
		delete foothold[i];
	}
}

void Game::update()  {
	for (accumulatorSec += Scene::DeltaTime(); stepSec <= accumulatorSec; accumulatorSec -= stepSec)
	{
		// 2D 物理演算のワールドを更新
		world.update(stepSec);
	}

	if (KeyL.down())//物理のデバッグ用
	{
		// クリックした場所に半径 10 cm のボールを作成
		bodies << world.createCircle(P2Dynamic, Cursor::PosF(), 10);
	}

	const Rect goal{ 0,400,150,200 };//仮ゴール判定
	player->Update();
	robot->Update();
	victim->Update();

	for (int i = 0; i < 10; i++) {
		if (foothold[i]->IsValid())foothold[i]->Update();
	}

	victim->carry_move(player->getNowPos());

	//プレイヤーの前後左右の現在位置
	double playerNowPosL = player->getNowPos().x;
	double playerNowPosR = player->getNowPos().x + player->getRect().w;
	double playerNowPosU = player->getNowPos().y;
	double playerNowPosD = player->getNowPos().y + player->getRect().h;
	//プレイヤーの前後左右の確認位置
	double playerNextPosL = player->getBeforePos().x;
	double playerNextPosR = player->getBeforePos().x + player->getRect().w;
	double playerNextPosU = player->getBeforePos().y;
	double playerNextPosD = player->getBeforePos().y + player->getRect().h;

	//プレイヤーの前後左右の現在位置
	double robotNowPosL = robot->getNowPos().x;
	double robotNowPosR = robot->getNowPos().x + robot->getRect().w;
	double robotNowPosU = robot->getNowPos().y;
	double robotNowPosD = robot->getNowPos().y + robot->getRect().h;
	//プレイヤーの前後左右の確認位置
	double robotNextPosL = robot->getBeforePos().x;
	double robotNextPosR = robot->getBeforePos().x + robot->getRect().w;
	double robotNextPosU = robot->getBeforePos().y;
	double robotNextPosD = robot->getBeforePos().y + robot->getRect().h;

	//救助者の前後左右の現在位置
	double victimNowPosL = victim->getPos().x;
	double victimNowPosR = victim->getPos().x + victim->getRect().w;
	double victimNowPosU = victim->getPos().y;
	double victimNowPosD = victim->getPos().y + victim->getRect().h;

	//プレイヤーと救助者の当たり判定
	MotionHit(playerNowPosL, playerNowPosR, playerNowPosU, playerNowPosD,
		playerNextPosL, playerNextPosR, playerNextPosU, playerNextPosD,
		victimNowPosL, victimNowPosR, victimNowPosU, victimNowPosD, P_V);

	for (int i = 0; i < 10; i++) {
		if (foothold[i]->IsValid()) {
			//ブロックの前後左右の位置
			double footholdPosL = foothold[i]->getPos().x;
			double footholdPosR = foothold[i]->getPos().x + foothold[i]->getRect().w;
			double footholdPosU = foothold[i]->getPos().y;
			double footholdPosD = foothold[i]->getPos().y + foothold[i]->getRect().h;

			//プレイヤーとブロックの当たり判定
			MotionHit(playerNowPosL, playerNowPosR, playerNowPosU, playerNowPosD,
				playerNextPosL, playerNextPosR, playerNextPosU, playerNextPosD,
				footholdPosL, footholdPosR, footholdPosU, footholdPosD, P_B);
		}
	}

	player->DecisionMave();
	robot->DecisionMave();


	if (victim->getRect().intersects(goal)) {//ゴールに被災者を持ってきたらクリア
		font(U"Clear!").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });
	}
}

void Game::draw() const  {
	player->Draw();
	robot->Draw();
	victim->Draw();
	for (int i = 0; i < 10; i++) {
		if (foothold[i]->IsValid()) {
			foothold[i]->Draw();
		}
	}
	Rect{ 0,400,150,200 }.draw(ColorF{ 0.9,0.7,0,0.5 });//ゴール

	for (const auto& body : bodies)//P2Bodyの描画
	{
		body.draw();
	}
	ground.draw();
}

//衝突判定
// 使い方
// １：引数を入れる
// 上から
// 現在の座標
// 確認用の座標
// 衝突する対象の座標
// ２：Common.hに書いてある//衝突相手//の欄にあるものから適切な物を引数IsMarioに入れる
// ３：衝突した時に走るif分の中にif (IsMario == ○○)を追加し、使いたい処理を書く
	//0:左1:右2:上3:下
void Game::MotionHit(
	double NowPosL, double NowPosR, double NowPosU, double NowPosD,
	double NextPosL, double NextPosR, double NextPosU, double NextPosD,
	double partnerPosL, double partnerPosR, double partnerPosU, double partnerPosD, int IsMario) {
	if (NextPosL <= partnerPosR && //プレイヤーから左側面の衝突
		NextPosR >= partnerPosL && //プレイヤーから右側面の衝突
		NextPosU <= partnerPosD && //プレイヤーから上側面の衝突
		NextPosD >= partnerPosU) {//プレイヤーから下側面の衝突

		if (IsMario == P_V) {
			if (KeyP.down()) {
				victim->carry_flip();
			}
		}

		//プレイヤーから横方向の衝突
		if (NowPosU <= partnerPosD &&//現プレイヤー上がブロック下より上な時
			NowPosD >= partnerPosU) {//現プレイヤー下がブロック上より下

			//プレイヤーから左方向の衝突
			if (NowPosL >= partnerPosR &&//現プレイヤー左がブロック右より右な時
				NowPosR >= partnerPosL) {//現プレイヤー右がブロック左より右な時
				if (IsMario == P_B) {
					player->B_HitX();
				}
			}
			//プレイヤーから右方向の衝突
			if (NowPosL <= partnerPosR &&//現プレイヤー左がブロック右より左な時
					 NowPosR <= partnerPosL) {//現プレイヤー右がブロック左より左な時
				if (IsMario == P_B) {
					player->B_HitX();
				}
			}

		}

		//プレイヤーから縦方向の衝突
		if (NowPosL <= partnerPosR &&//現プレイヤー左がブロック右より左な時
			NowPosR >= partnerPosL) {//現プレイヤー右がブロック左より右な時

			//プレイヤーから上方向の衝突
			if (NowPosU >= partnerPosD &&//現プレイヤー上がブロック下より下な時
				NowPosD >= partnerPosU) {//現プレイヤー下がブロック上より下
				if (IsMario == P_B) {

				}
			}
			//プレイヤーから下方向の衝突

			if (NowPosU <= partnerPosD &&//現プレイヤー上がブロック下より上な時
				 NowPosD <= partnerPosU) {//現プレイヤー下がブロック上より上
				if (IsMario == P_B) {
					player->CheckGround();
				}
			}
		}
	}


	
}
