#pragma once
#include "Common.h"
class ClearScene : public App::Scene
{
public:

	ClearScene(const InitData& init);

	~ClearScene();

	void update() override;

	void draw() const override;

private:
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	Texture Background;
};

