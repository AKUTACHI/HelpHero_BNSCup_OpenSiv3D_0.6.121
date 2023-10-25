#include "stdafx.h"
#include "Game.h"
Game::Game(const InitData& init)
	: IScene{ init } {
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	player = new Player();
	robot = new Robot();
	victim = new Victim();
	foothold = new Foothold();
	foothold2 = new Foothold();//足場はあとで動的配列とかにする
}

Game::~Game() {

}

void Game::update()  {
	const Rect goal{ 0,400,150,200 };//仮ゴール判定
	player->Update();
	robot->Update();
	victim->Update();
	foothold->Update();
	foothold2->Update();

	victim->carry_move(player->getRect());

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

	//救助者の前後左右の現在位置
	double victimNowPosL = victim->getPos().x;
	double victimNowPosR = victim->getPos().x + victim->getRect().w;
	double victimNowPosU = victim->getPos().y;
	double victimNowPosD = victim->getPos().y + victim->getRect().h;

	//プレイヤーと救助者の当たり判定
	MotionHit(playerNowPosL, playerNowPosR, playerNowPosU, playerNowPosD,
		playerNextPosL, playerNextPosR, playerNextPosU, playerNextPosD,
		victimNowPosL, victimNowPosR, victimNowPosU, victimNowPosD, P_V);

	//ブロックの前後左右の位置
	double footholdPosL = foothold->getPos().x;
	double footholdPosR = foothold->getPos().x;
	double footholdPosU = foothold->getPos().y;
	double footholdPosD = foothold->getPos().y;

	//プレイヤーとブロックの当たり判定
	MotionHit(playerNowPosL, playerNowPosR, playerNowPosU, playerNowPosD,
		playerNextPosL, playerNextPosR, playerNextPosU, playerNextPosD,
		footholdPosL, footholdPosR, footholdPosU, footholdPosD, P_B);

	player->DecisionMave();

	if (victim->getRect().intersects(goal)) {//ゴールに被災者を持ってきたらクリア
		font(U"Clear!").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });
	}
}

void Game::draw() const  {
	player->Draw();
	robot->Draw();
	victim->Draw();
	foothold->Draw();
	foothold2->Draw();
	Rect{ 0,400,150,200 }.draw(ColorF{ 0.9,0.7,0,0.5 });//ゴール
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

				}
			}
			//プレイヤーから右方向の衝突
			if (NowPosL <= partnerPosR &&//現プレイヤー左がブロック右より左な時
					 NowPosR <= partnerPosL) {//現プレイヤー右がブロック左より左な時
				if (IsMario == P_B) {

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
