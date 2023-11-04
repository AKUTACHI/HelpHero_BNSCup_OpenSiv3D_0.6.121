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
	instance[0]->set({500,400,200,100}, false, &_world);
	instance[1] = new Foothold();
	instance[1]->set({ 500,250,150,100 }, false, &_world);
	instance[2] = new Foothold();
	instance[2]->set({ 700,400,200,100 }, false, &_world);
	*_footholds << instance[0];
	*_footholds << instance[1];
	*_footholds << instance[2];

	*_ground = _world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 600, 1300, 600 });
}

int32 Stage1::GetStageNum()
{
	return 1;
}
