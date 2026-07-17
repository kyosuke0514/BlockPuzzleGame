# include "Common.h"
# include "TitleScene.h"
# include "GameScene.h"
# include "GameOverScene.h"
# include "Ranking.h"

void Main()
{
	//画面サイズ
	Window::Resize(1920, 1080);

	//各シーン
	App manager;
	manager.add<TitleScene>(State::Title);
	manager.add<GameScene>(State::Game);
	manager.add<GameOverScene>(State::GameOver);
	manager.add<Ranking>(State::Ranking);

	while (System::Update())
	{
		if (Key1.down())
		{
			manager.changeScene(State::Title);
		}
		if (Key2.down())
		{
			manager.changeScene(State::Game);
		}
		if (Key3.down())
		{
			manager.changeScene(State::GameOver);
		}
		if (Key4.down())
		{
			manager.changeScene(State::Ranking);
		}
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
