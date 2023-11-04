#pragma once
#include "Common.h"
class Title : public App::Scene
{
public:

	Title(const InitData& init);

	~Title();

	void update() override;

	void draw() const override;

private:
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	Texture Background;
};

