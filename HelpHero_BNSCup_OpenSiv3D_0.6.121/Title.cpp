#include "stdafx.h"
#include "Title.h"
#include "Beeps.h"

Title::Title(const InitData& init) : IScene{ init }
{
	Background = Texture{ U"textures/Title.png" };
	Beeps::GetBeep(U"Title").setVolume(0.3);
	Beeps::GetBeep(U"Title").play();
}

Title::~Title()
{
}

void Title::update()
{
	if (MouseL.down())
	{
		// ストーリーシーンに遷移
		changeScene(State::Game);
		Beeps::GetBeep(U"Title").stop();
		Beeps::GetBeep(U"TitleEnter").playOneShot();
	}
}

void Title::draw() const
{
	Background.draw();
}
