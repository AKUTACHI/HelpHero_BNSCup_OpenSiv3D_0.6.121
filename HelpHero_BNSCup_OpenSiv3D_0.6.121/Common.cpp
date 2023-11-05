#include "Common.h"

extern Array<Efficacy*>* ptrEffects;

void GenerateEffect(Vec2 pos, EffectVariant val)
{
	switch (val)
	{
	case EffectVariant::Impact:
		*ptrEffects << new SpreadEfficacy(pos, Texture{ U"textures/particles-single.png" }, 10);
		break;
	case EffectVariant::Fire:
		*ptrEffects << new FireEfficacy(pos,100, Texture{ U"textures/effecttest.png" }, 20);
		break;
	default:
		*ptrEffects << new SpreadEfficacy(pos, Texture{ U"textures/effecttest.png" },10);
		break;
	}
}
