#include "Common.h"

extern Array<Efficacy*>* ptrEffects;

void GenerateEffect(Vec2 pos, EffectVariant val)
{
	switch (val)
	{
	case EffectVariant::Impact:
		break;
	default:
		*ptrEffects << new Efficacy(pos, Texture{ U"textures/effecttest.png" }, Vec2{ 10,10 }, Vec2{ 1,1 });
		break;
	}
}
