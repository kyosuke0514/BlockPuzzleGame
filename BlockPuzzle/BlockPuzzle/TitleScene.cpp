#include "TitleScene.h"


TitleScene::TitleScene(const InitData& init)
	: IScene{ init }
{
	const Vec2 center = Scene::Center();

	m_startButton = RoundRect{ Arg::center(center.x, center.y), 300, 60, 8 };
	m_rankingButton = RoundRect{ Arg::center(center.x, center.y + 100), 300, 60, 8 };
	m_exitButton = RoundRect{ Arg::center(center.x, center.y + 200), 300, 60, 8 };
}

void TitleScene::update()
{
	// ボタンの更新
	{
		const Vec2 center = Scene::Center();

		m_startButton.setCenter(center);
		m_rankingButton.setCenter(center + Vec2{ 0,100 });
		m_exitButton.setCenter(center + Vec2{ 0, 200 });

		//マウスカーソルを手の形にする
		if (m_startButton.mouseOver() || m_rankingButton.mouseOver() || m_exitButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}

	// ボタンのクリック処理
	if (m_startButton.leftClicked()) // ゲームへ
	{
		changeScene(State::Game);
	}
	else if (m_rankingButton.leftClicked()) // ランキングへ
	{
		changeScene(State::Ranking);
	}
	else if (m_exitButton.leftClicked()) // 終了
	{
		System::Exit();
	}
}

void TitleScene::draw() const
{
	Scene::SetBackground(ColorF{ 0.2, 0.6, 1.0 });

	const Vec2 center = Scene::Center();

	// タイトル描画
	FontAsset(U"TitleFont")(U"BlockPuzzle")
		.drawAt(
			TextStyle::OutlineShadow(0.2, ColorF{ 0.0, 0.0, 0.0 },
				Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }),
			100,
			Vec2{ center.x, 150 + Sin(Scene::Time() * 2) * 10 }
		);

	// ボタン描画
	{
		//中が白色.枠が黒色のボタン
		m_startButton.draw(ColorF{ 1.0 }).drawFrame(2, ColorF{ 0.0,0.0,0.0 });
		m_rankingButton.draw(ColorF{ 1.0 }).drawFrame(2, ColorF{ 0.0,0.0,0.0 });
		m_exitButton.draw(ColorF{ 1.0 }).drawFrame(2, ColorF{ 0.0,0.0,0.0 });

		const Font& boldFont = FontAsset(U"Bold");
		boldFont(U"プレイ").drawAt(36, m_startButton.center(), ColorF{ 0.1 });
		boldFont(U"ランキング").drawAt(36, m_rankingButton.center(), ColorF{ 0.1 });
		boldFont(U"終了").drawAt(36, m_exitButton.center(), ColorF{ 0.1 });
	}
}
