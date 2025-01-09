#include "stdafx.h"
#include "StageManager.h"
#include "Game.h"
#include"Beeps.h"

extern Array<Efficacy*>* ptrEffects;

StageManager::StageManager(const InitData& init)
	: IScene{ init } {
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	player = new Player(&world);
	robot = new Robot(&world);
	victim = new Victim(&world, player);

	/*for (int i = 0; i < 10; i++) {
		foothold[i] = new Foothold();
	}*/
	getData().currentStage = new BlankStage();
	getData().currentStage->SetUpToWorld(world, player, victim, &ground, &foothold);

	//foothold[0]->set({ 0,500,800,100 },false,&world);

	texGround = Texture{ U"textures/Concrete.jpg" };
	//ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 680, 1300, 680 });

	//背景テクスチャ読み込み
	texBack00Outlook = Texture{ U"textures/Back00_Outlook.png" };
	texBack01Robot = Texture{ U"textures/Back01_Robot.png" };
	texBack02Building = Texture{ U"textures/Back02_Building.png" };
	//背景ロボ位置初期化
	BackRobotPos = Vec2{ robot->getPos().x , 0 };

	BackRobotPos.y = Math::Sin(BackRobotPos.x / 50) * 50;
	BackRobotPos.x -= 1200;
	BackRobotPos.y -= 200;

	ptrEffects = &effects;

	/*Beeps::GetBeep(U"Bgm").setVolume(0.15);
	Beeps::GetBeep(U"Bgm").play();
	Beeps::GetBeep(U"StageStart").setVolume(0.6);
	Beeps::GetBeep(U"StageStart").playOneShot();*/
	Beeps::GetBeep(U"Flames").setVolume(0.3);
	Beeps::GetBeep(U"Flames").play();

	//ファイル書き込み
	
	 writer = TextWriter{ U"testStage.txt"};
	
	if (not writer) {
		throw Error{ U"Failed to open a write file" };
	}

	//writer << U"100 100 300 300";



	Save();



	/*GenerateEffect(Vec2(0, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(100, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(200, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(300, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(400, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(500, 720), EffectVariant::Fire);

	GenerateEffect(Vec2(600, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(700, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(800, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(900, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(1000, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(1100, 720), EffectVariant::Fire);
	GenerateEffect(Vec2(1200, 720), EffectVariant::Fire);*/
}
StageManager::~StageManager() {
	delete player;
	delete robot;
	delete victim;
	for (auto& foot : foothold) {
		delete foot;
	}
}

void StageManager::update() {
	ClearPrint();

	if(!isClick)CreatePos.clear();

	if (isSimulate) {
		for (accumulatorSec += Scene::DeltaTime(); stepSec <= accumulatorSec; accumulatorSec -= stepSec)
		{
			// 2D 物理演算のワールドを更新
			world.update(stepSec);
		}
	}
	

	if (KeyL.down())//物理のデバッグ用
	{
		// クリックした場所に半径 10 cm のボールを作成
		bodies << world.createCircle(P2Dynamic, Cursor::PosF(), 10);
	}
	if (MouseL.down()) {
		if (!isClick) {
			isClick = true;
			CreatePos << Cursor::Pos().x;
			CreatePos << Cursor::Pos().y;
		}
		else if(isClick && CreatePos[0] < Cursor::Pos().x && CreatePos[1] < Cursor::Pos().y){
			CreatePos << Cursor::Pos().x - CreatePos[0];
			CreatePos << Cursor::Pos().y - CreatePos[1];



			Foothold* fh = new Foothold();
			fh->set({ CreatePos[0], CreatePos[1], CreatePos[2], CreatePos[3] }, false, &world);
			foothold << fh;
			String str;
			str = ToString(CreatePos[0]) + U" " + ToString(CreatePos[1]) + U" " + ToString(CreatePos[2]) + U" " + ToString(CreatePos[3]);
			writer.writeln(str);
			//writer << ToString(CreatePos[0]) << " " << ToString(CreatePos[1]) << " " << ToString(CreatePos[2]) << " " << ToString(CreatePos[3]);
			isClick = false;
		}
	}

	player->Update();
	robot->Update();
	victim->Update();
	robot->CheckGround(ground);
	for (auto foot : foothold) {
		if (foot->IsValid()) {
			foot->Update();
			foot->CheckCarry(robot);
		}
	}

	victim->carry_move(player->getNowPos());



	player->DecisionMave();
	if (KeyR.down()) {
		changeScene(State::Title, 0.3s);
		/*Beeps::GetBeep(U"Bgm").stop();
		Beeps::GetBeep(U"StageStart").stop();*/
		Beeps::GetBeep(U"Flames").stop();
	}

	/*if (Key3.down()) {
		if (!isClick)Save();



	}*/

	if (Key2.down()) {
		changeScene(State::StageManager);
		//if(!isClick)Save();
	}

	if (Key1.down()) {
		if (isSimulate)isSimulate = false;
		else isSimulate = true;
	}

	//if (KeyI.down())GenerateEffect(Vec2(400, 400), EffectVariant::Fire);

	for (auto& item : effects)
	{
		item->Update();
	}

	//effects.remove_if([](Efficacy* item) { return !item->IsValid(); });


	//背景ロボット位置更新
	BackRobotPos = Vec2{ robot->getPos().x , 0 };
	if (Math::Sin(BackRobotPos.x / 50) > 0.9)
	{
		if (!steped)
		{
			Beeps::GetBeep(U"FootStepRobot").playOneShot();
		}
		steped = true;
	}
	if (Math::Sin(BackRobotPos.x / 50) < 0)
	{
		steped = false;
	}
	//Print << Math::Sin(BackRobotPos.x / 50);
	BackRobotPos.y = Math::Sin(BackRobotPos.x / 50) * 50;
	BackRobotPos.x -= 1200;
	BackRobotPos.y -= 200;

	
}

void StageManager::draw() const {
	texBack00Outlook.draw();
	texBack01Robot.draw(BackRobotPos, ColorF{ 1.0,1.0,1.0,0.85 });
	texBack02Building.draw(ColorF{ 1.0,1.0,1.0,0.7 });
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

	for (const auto& item : effects)
	{
		item->Draw();
	}
	if (goal) {//ゴールに被災者を持ってきたらクリア
		font(U"Clear!").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });
		font(U"Enter to Next Stage").draw(64, Vec2{ 500, 200 }, ColorF{ 0.8, 1, 0.8 });
	}
	String stageStr = ToString(getData().stage + 1);
	font(U"Manage Mode").draw(50, 30, 30, ColorF{ 1.0,1.0,1 });
	font(U"[1]キー:物理演算切り替え [2]キー:書き込みファイル変更 [R]:タイトルへ").drawBaseAt(20, Scene::Rect().bottomCenter() + Vec2{ 0,-20 }, ColorF{ 1.0,0.2,0 });
	if (isClick && CreatePos[0] < Cursor::Pos().x && CreatePos[1] < Cursor::Pos().y) {
		Rect{ CreatePos[0],CreatePos[1],Cursor::Pos().x - CreatePos[0],Cursor::Pos().y - CreatePos[1] }.draw(ColorF{1.0,1.0,0,0.6});
	}
}


void StageManager::Save() {
	// .txt
	path = Dialog::SaveFile({ FileFilter::Text() });

	TextReader reader{ *path };

	if (not reader)
	{
	}
	else {
		String line;
		// 1 行ずつ読み込む
		while (reader.readLine(line))
		{
			// 空の文字列だった場合はスキップする
			if (not line)
			{
				continue;
			}

			// 空白文字で分割する
			const Array<String> items = line.split(U' ');

			// 想定した要素数でなかった場合はエラーを投げる
			if (items.size() != 4)
			{
				throw Error{ U"Invalid format" };
			}

			// データを格納する
			loadFootPos.push_back_row(-1);
			for (int i = 0; i < 4; i++) {
				loadFootPos[loadFootPos.height() - 1][i] = Parse<int32>(items[i]);
			}
		}
	}

	reader.close();
	if (path != none)
		writer = TextWriter{ *path };

	if (not writer) {
		throw Error{ U"Failed to open a write file" };
	}
	else {
		//障害物の座標を書き込み
		for (int i = 0; i < loadFootPos.height(); i++) {
			Foothold* instance = new Foothold();
			instance->set({ loadFootPos[i][0],loadFootPos[i][1],loadFootPos[i][2],loadFootPos[i][3] }, false, &world);
			foothold << instance;

			String str;
			str = ToString(loadFootPos[i][0]) + U" " + ToString(loadFootPos[i][1]) + U" " + ToString(loadFootPos[i][2]) + U" " + ToString(loadFootPos[i][3]);
			writer.writeln(str);
		}
	}
	
}
