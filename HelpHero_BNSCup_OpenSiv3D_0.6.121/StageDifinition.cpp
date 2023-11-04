#include "stdafx.h"
#include "StageDifinition.h"

StageDifinition::StageDifinition()
{
}

void StageDifinition::ResetWorld(P2World& _world)
{
}

void StageDifinition::SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, Array<Foothold*>* _footholds)
{
}

int32 StageDifinition::GetStageNum()
{
	return -1;
}

Stage1::Stage1()
{
}

void Stage1::SetUpToWorld(P2World& _world, Player* _player, Victim* _victim, Array<Foothold*>* _footholds)
{
}

int32 Stage1::GetStageNum()
{
	return 1;
}
