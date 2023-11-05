#include "stdafx.h"
#include "Title.h"

Title::Title(const InitData& init) : IScene{ init }
{
	Background = Texture{ U"textures/Title.png" };
}

Title::~Title()
{
}

void Title::update()
{
	if (MouseL.down() || KeyEnter.down())
	{
		// ストーリーシーンに遷移
		changeScene(State::Game);
	}
}

void Title::draw() const
{
	Background.draw();
}
