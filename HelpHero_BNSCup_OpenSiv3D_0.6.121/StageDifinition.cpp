﻿#include "stdafx.h"
#include "StageDifinition.h"

StageDifinition::StageDifinition()
{
}

void StageDifinition::ResetWorld(P2World& _world)
{
}

void StageDifinition::ReadStageData(String fileName,P2World& _world, Array<Foothold*>* _footholds)
{
	Grid<int32> FPos{ 4,0,-1 };
	FootholdPos = FPos;

	TextReader reader{fileName };

	if (not reader)
	{
		throw Error{ U"Failed to open a file" };
	}

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
		FootholdPos.push_back_row(-1);
		for (int i = 0; i < 4; i++) {
			FootholdPos[FootholdPos.height() - 1][i] = Parse<int32>(items[i]);
		}
	}

	for (int i = 0; i < FootholdPos.height(); i++) {
		Foothold* instance = new Foothold();
		instance->set({ FootholdPos[i][0],FootholdPos[i][1],FootholdPos[i][2],FootholdPos[i][3]}, false, &_world);
		*_footholds << instance;
	}
}

void StageDifinition::SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds)
{
}

int32 StageDifinition::GetStageNum()
{
	return -1;
}

Stage1::Stage1()
{
}

void Stage1::SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds)
{
	
	Foothold* instance[10];
	/*instance[0] = new Foothold();
	instance[0]->set({450,400,200,100}, false, &_world);
	instance[1] = new Foothold();
	instance[1]->set({ 500,250,150,100 }, false, &_world);
	instance[2] = new Foothold();
	instance[2]->set({ 700,400,200,100 }, false, &_world);
	instance[3] = new Foothold();
	instance[3]->set({ 550,300,100,100 }, false, &_world);
	instance[4] = new Foothold();
	instance[4]->set({ 650,300,50,200 }, false, &_world);
	instance[5] = new Foothold();
	instance[5]->set({ 430,250,100,100 }, false, &_world);
	instance[6] = new Foothold();
	instance[6]->set({ 400,350,150,250 }, false, &_world);
	instance[7] = new Foothold();
	instance[7]->set({ 900,350,100,250 }, false, &_world);
	*_footholds << instance[0];
	*_footholds << instance[1];
	*_footholds << instance[2];
	*_footholds << instance[3];
	*_footholds << instance[4];
	*_footholds << instance[5];
	*_footholds << instance[6];
	*_footholds << instance[7];*/

	ReadStageData(U"Stage1.txt", _world, _footholds);

	*_ground = _world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 600, 1300, 600 });
}

int32 Stage1::GetStageNum()
{
	return 1;
}

Stage2::Stage2()
{
}

void Stage2::SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds)
{
	Foothold* instance[20];
	
	_victim->setPos(Vec2(1080,600));

	ReadStageData(U"Stage2.txt", _world, _footholds);

	*_ground = _world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 600, 1300, 600 });
}

int32 Stage2::GetStageNum()
{
	return 2;
}


BlankStage::BlankStage()
{
}

void BlankStage::SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds)
{

	/*Foothold* instance[10]; 外部ファイル読み込みに変更
	instance[0] = new Foothold();
	instance[0]->set({1004,212,262,386}, false, &_world);
	instance[1] = new Foothold();
	instance[1]->set({ 713,530,290,62}, false, &_world);
	instance[2] = new Foothold();
	instance[2]->set({ 651,570,61,25 }, false, &_world);
	instance[3] = new Foothold();
	instance[3]->set({ 595,575,44,11 }, false, &_world);
	instance[4] = new Foothold();
	instance[4]->set({ 495,485,83,113 }, false, &_world);
	instance[5] = new Foothold();
	instance[5]->set({ 407,439,85,85 }, false, &_world);
	instance[6] = new Foothold();
	instance[6]->set({ 350,526,42,48 }, false, &_world);
	*_footholds << instance[0];
	*_footholds << instance[1];
	*_footholds << instance[2];
	*_footholds << instance[3];
	*_footholds << instance[4];
	*_footholds << instance[5];
	*_footholds << instance[6];*/

	//ReadStageData(U"Stage2.txt", _world, _footholds);

	*_ground = _world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 600, 1300, 600 });
}

int32 BlankStage::GetStageNum()
{
	return 1;
}

Stage3::Stage3()
{
}

void Stage3::SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds)
{
	Foothold* instance[10];

	ReadStageData(U"Stage3.txt", _world, _footholds);
	_victim->setPos(Vec2(1180, 200));
	*_ground = _world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 600, 1300, 600 });
}

int32 Stage3::GetStageNum()
{
	return 3;
}
