#pragma once
#include "Player.h"
#include "Victim.h"
#include "Foothold.h"
//ステージのバリエーションづくり
//ステージごとにStageDifinition派生クラスのインスタンスを一つづつ作成、グローバル変数なり共有変数にリストをつくる
//狙ったStageDifinition派生クラスのインスタンスのSetUpToWorldを呼び出してステージをセットアップ

//overrideでSetUpToWorldを上書きして、ステージごとに別の生成アルゴリズムを持つようにする。

class StageDifinition
{
private:
	Grid<int32> FootholdPos{4,0,-1};
public:
	StageDifinition();
	void ResetWorld(P2World& _world);
	void ReadStageData(String fileName,P2World& _world, Array<Foothold*>* _footholds);
	virtual void SetUpToWorld(P2World& _world,Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds);
	virtual int32 GetStageNum();
};

class Stage1 : public StageDifinition
{
public:
	Stage1();
	void SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds) override;
	int32 GetStageNum() override;
};

class Stage2 : public StageDifinition
{
public:
	Stage2();
	void SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds) override;
	int32 GetStageNum() override;
};

class Stage3 : public StageDifinition
{
public:
	Stage3();
	void SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds) override;
	int32 GetStageNum() override;
};


class BlankStage : public StageDifinition
{
public:
	BlankStage();
	void SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, P2Body* _ground, Array<Foothold*>* _footholds) override;
	int32 GetStageNum() override;
};
