#include "common.h"
void Main()
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	Player player;
	Robot robot(&player);
	Victim victim(&player,&robot);
	Foothold foothold(&player, &robot, Rect{0,500,800,100});
	Foothold foothold2(&player, &robot, Rect{ 400,400,150,100 });

	Rect goal{0,400,150,200};
	while (System::Update())
	{
		goal.draw(ColorF{ 0.9,0.7,0,0.5 });
		player.Update();
		player.CheckGround(&foothold);
		player.CheckGround(&foothold2);
		robot.Update();
		victim.Update();
		foothold.Update();
		foothold2.Update();

		player.Draw();
		robot.Draw();
		victim.Draw();
		foothold.Draw();
		foothold2.Draw();
		if (victim.getRect().intersects(goal)) {
			font(U"Clear!").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });
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
