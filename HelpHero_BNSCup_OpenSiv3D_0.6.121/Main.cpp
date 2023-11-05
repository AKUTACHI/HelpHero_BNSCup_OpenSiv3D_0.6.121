#include "Common.h"
#include"Game.h"
#include "StageDifinition.h"
#include "Beeps.h"

Array<Efficacy*>* ptrEffects;

#include "Title.h"
void Main()
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	Window::Resize(1280,720);
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	Beeps::AddBeep(U"Title", Audio{ Audio::Stream,U"audios/Title.mp3", Loop::Yes });
	Beeps::AddBeep(U"TitleEnter", Audio{ U"audios/Enter.mp3" });

	// シーンマネージャーを作成
	App manager;

	manager.get()->currentStage = new Stage1();
	// シーンを登録
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);

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
