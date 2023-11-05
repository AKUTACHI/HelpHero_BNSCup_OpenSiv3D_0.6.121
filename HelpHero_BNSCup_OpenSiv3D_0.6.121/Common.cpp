#include "Common.h"

extern Array<Efficacy*>* ptrEffects;

void GenerateEffect(Vec2 pos, EffectVariant val)
{
	switch (val)
	{
	case EffectVariant::Impact:
		break;
	default:
		*ptrEffects << new SpreadEfficacy(pos, Texture{ U"textures/effecttest.png" },10);
		break;
	}
}
