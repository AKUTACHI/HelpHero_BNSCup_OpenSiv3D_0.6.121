#include "stdafx.h"
#include "StageDifinition.h"

StageDifinition::StageDifinition()
{
}

void StageDifinition::ResetWorld(P2World& _world)
{
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
	instance[0] = new Foothold();
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
	*_footholds << instance[7];

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
	instance[0] = new Foothold();
	instance[0]->set({ 650,300,100,150 }, false, &_world);
	instance[1] = new Foothold();
	instance[1]->set({ 530,200,450,100 }, false, &_world);
	instance[2] = new Foothold();
	instance[2]->set({ 900,300,100,150 }, false, &_world);
	instance[3] = new Foothold();
	instance[3]->set({ 650,450,100,150 }, false, &_world);
	instance[4] = new Foothold();
	instance[4]->set({ 900,450,100,150 }, false, &_world);
	instance[5] = new Foothold();
	instance[5]->set({ 630,120,170,80 }, false, &_world);
	instance[6] = new Foothold();
	instance[6]->set({ 750,120,170,80 }, false, &_world);
	instance[7] = new Foothold();
	instance[7]->set({ 1000,400,150,70 }, false, &_world);
	instance[8] = new Foothold();
	instance[8]->set({ 1100,470,80,140 }, false, &_world);
	*_footholds << instance[0];
	*_footholds << instance[1];
	*_footholds << instance[2];
	*_footholds << instance[3];
	*_footholds << instance[4];
	*_footholds << instance[5];
	*_footholds << instance[6];
	*_footholds << instance[7];
	*_footholds << instance[8];

	_victim->setPos(Vec2(1080,600));

	*_ground = _world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 600, 1300, 600 });
}

int32 Stage2::GetStageNum()
{
	return 2;
}
