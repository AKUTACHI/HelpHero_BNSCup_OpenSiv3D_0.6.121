#include "Common.h"
#include "Game.h"
#include "StageDifinition.h"
#include "Beeps.h"
#include"StageManager.h"

Array<Efficacy*>* ptrEffects;

#include "Title.h"
void Main()
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	Window::Resize(1280,720);
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	Beeps::AddBeep(U"Title", Audio{ Audio::Stream,U"audios/Title.mp3", Loop::Yes });
	Beeps::AddBeep(U"TitleEnter", Audio{ U"audios/Enter.mp3" });
	Beeps::AddBeep(U"StageStart", Audio{ U"audios/StageStart.mp3"});
	Beeps::AddBeep(U"FootStepHero", Audio{ U"audios/FootStepHero.mp3" });
	Beeps::AddBeep(U"FootStepRobot", Audio{ U"audios/FootStepRobot.mp3" });
	Beeps::AddBeep(U"Rock", Audio{ U"audios/Rock.mp3" });
	Beeps::AddBeep(U"ArmDown", Audio{ U"audios/ArmDown.mp3" });
	Beeps::AddBeep(U"ArmUp", Audio{ U"audios/ArmUp.mp3" });
	Beeps::AddBeep(U"ArmCatch", Audio{ U"audios/ArmCatch.mp3" });
	Beeps::AddBeep(U"CatchVictim", Audio{ U"audios/CatchVictim.mp3" });
	Beeps::AddBeep(U"Success", Audio{ U"audios/Success.mp3" });
	Beeps::AddBeep(U"Bgm", Audio{ U"audios/Bgm.mp3"  ,Loop::Yes });
	Beeps::AddBeep(U"Flames", Audio{ U"audios/Flames.mp3",Loop::Yes });

	// シーンマネージャーを作成
	App manager;

	manager.get()->currentStage = new Stage1();
	// シーンを登録
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);
	manager.add<StageManager>(State::StageManager);
	while (System::Update())
	{
		ClearPrint();
		// 現在のシーンを実行
		// シーンに実装した .update() と .draw() が実行される
		if (not manager.update())
		{
			break;
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
