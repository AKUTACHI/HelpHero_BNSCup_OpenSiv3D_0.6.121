#include "stdafx.h"
#include "ClearScene.h"
#include "Beeps.h"

ClearScene::ClearScene(const InitData& init) : IScene{ init }
{
	Background = Texture{ U"textures/CLEAR_IMAGE.png" };
	Beeps::GetBeep(U"Title").setVolume(0.3);
	Beeps::GetBeep(U"Title").play();
}

ClearScene::~ClearScene()
{
}

void ClearScene::update()
{
	if (MouseL.down() || KeyEnter.down())
	{
		// ストーリーシーンに遷移
		changeScene(State::Title);
		Beeps::GetBeep(U"Title").stop();
		//Beeps::GetBeep(U"TitleEnter").playOneShot();
	}
	if (Key9.down()) {
		Beeps::GetBeep(U"Title").stop();
		changeScene(State::StageManager);
	}
}

void ClearScene::draw() const
{
	Background.draw();
}
