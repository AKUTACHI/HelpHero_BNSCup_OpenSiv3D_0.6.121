#include "stdafx.h"
#include "Game.h"
Game::Game(const InitData& init)
	: IScene{ init } {
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	player = new Player(&world);
	robot = new Robot(&world);
	victim = new Victim(&world,player);

	/*for (int i = 0; i < 10; i++) {
		foothold[i] = new Foothold();
	}*/

	getData().currentStage->SetUpToWorld(world, player, victim, &ground, &foothold);

	//foothold[0]->set({ 0,500,800,100 },false,&world);

	texGround = Texture{ U"textures/Concrete.jpg" };
	ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 680, 1300, 680 });

	//背景テクスチャ読み込み
	texBack00Outlook = Texture{ U"textures/Back00_Outlook.png" };
	texBack01Robot = Texture{ U"textures/Back01_Robot.png" };
	texBack02Building = Texture{ U"textures/Back02_Building.png" };
	//背景ロボ位置初期化
	BackRobotPos = Vec2{ robot->getPos().x , 0 };

	BackRobotPos.y = Math::Sin(BackRobotPos.x / 50) * 50;
	BackRobotPos.x -= 1200;
	BackRobotPos.y -= 200;
}
Game::~Game() {
	delete player;
	delete robot;
	delete victim;
	for (auto& foot : foothold) {
		delete foot;
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
	robot->CheckGround(ground);
	for (auto foot:foothold) {
		if (foot->IsValid()) {
			foot->Update();
			foot->CheckCarry(robot);
		}
	}

	victim->carry_move(player->getNowPos());

	

	player->DecisionMave();


	if (victim->getRect().intersects(goal)) {//ゴールに被災者を持ってきたらクリア
		font(U"Clear!").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });
	}

	for (auto& item : effects)
	{
		item->Update();
	}

	effects.remove_if([](Efficacy* item) { return !item->IsValid(); });
}

void Game::draw() const  {
	//背景ロボット位置更新
	BackRobotPos = Vec2{ robot->getPos().x , 0};

	BackRobotPos.y = Math::Sin(BackRobotPos.x / 50) * 50;
	BackRobotPos.x -= 1200;
	BackRobotPos.y -= 200;
}

void Game::draw() const  {
	texBack00Outlook.draw();
	texBack01Robot.draw(BackRobotPos);
	texBack02Building.draw();
	player->Draw();
	robot->Draw();
	victim->Draw();
	player->Draw();
	for (auto& foot : foothold) {
		if (foot->IsValid()) {
			foot->Draw();
		}
	}
	Rect{ 0,400,150,200 }.draw(ColorF{ 0.9,0.7,0,0.5 });//ゴール

	for (const auto& body : bodies)//P2Bodyの描画
	{
		body.draw();
	}
	ground.draw();

	for (int32 i = 0; i < 12; i++)
	{
		Rect{ 125 * i,600,125,125 }(texGround).draw();
	}

	for (const auto& item : effects )
	{
		item->Draw();
	}
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
