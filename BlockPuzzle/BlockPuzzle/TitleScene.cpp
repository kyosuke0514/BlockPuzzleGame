#include "TitleScene.h"
#include <Siv3D.hpp>


TitleScene::TitleScene(const InitData& init)
	: IScene{ init }
{
	//BGM
	TitleBGM.setVolume(0.3);
	TitleBGM.play();

	const Vec2 center = Scene::Center();

	m_startButton = RoundRect{ Arg::center(center.x, center.y+50), 300, 60, 8 };
	m_rankingButton = RoundRect{ Arg::center(center.x, center.y +150), 300, 60, 8 };
	m_exitButton = RoundRect{ Arg::center(center.x, center.y + 250), 300, 60, 8 };
}

void TitleScene::update()
{
	const Vec2 center = Scene::Center();

	m_startTransition.update(m_startButton.mouseOver());
	m_rankingTransition.update(m_rankingButton.mouseOver());
	m_exitTransition.update(m_exitButton.mouseOver());

	//マウスカーソルを手の形にする
	if (m_startButton.mouseOver() || m_rankingButton.mouseOver() || m_exitButton.mouseOver())
	{
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	
	//ボタンのクリック処理
	if (m_startButton.leftClicked())//ゲームへ
	{
		//SE
		BotanSE.setVolume(0.4);
		BotanSE.play();
		changeScene(State::Game);
	}
	else if (m_rankingButton.leftClicked())//ランキングへ
	{
		//SE
		BotanSE.setVolume(0.4);
		BotanSE.play();
		changeScene(State::Ranking);
	}
	else if (m_exitButton.leftClicked())//終了
	{
		//SE
		BotanSE.setVolume(0.4);
		BotanSE.play();
		System::Exit();
	}
}

void TitleScene::draw() const
{
	//背景
	BackTexture.drawAt(Scene::Center());

	//画面中央
	const Vec2 center = Scene::Center();

	double alpha = Periodic::Sine0_1(3s);

	//タイトル画像
	STexture.scaled(1.5).drawAt(center.x +365, 315, ColorF{ 1.0,alpha });
	LTexture.scaled(1.5).drawAt(center.x -380, 300,ColorF{1.0,alpha });
	TitleTexture.scaled(1.5).drawAt(center.x, 300);
	CTexture.scaled(1.5).drawAt(center.x + 15, 320, ColorF{ 1.0,alpha });

	//ホバー時に拡大
	const double startScale =0.5 + m_startTransition.value() * 0.1;
	const double rankingScale =0.5 + m_rankingTransition.value() * 0.1;
	const double exitScale =0.5 + m_exitTransition.value() * 0.1;

	//ボタン画像
	PlayTexture.scaled(startScale).drawAt(m_startButton.center());
	RankingTexture.scaled(rankingScale).drawAt(m_rankingButton.center());
	ExitTexture.scaled(exitScale).drawAt(m_exitButton.center());

	//選択中ブロック
	if (m_startTransition.value() > 0.0)
	{
		RectF{m_startButton.x - 60,m_startButton.center().y - 15,30,30}.draw(ColorF{ 0.3,0.7,1.0 });
	}

	if (m_rankingTransition.value() > 0.0)
	{
		RectF{m_rankingButton.x - 60,m_rankingButton.center().y - 15,30,30}.draw(ColorF{ 0.4,1.0,0.5 });
	}

	if (m_exitTransition.value() > 0.0)
	{
		RectF{m_exitButton.x - 60,m_exitButton.center().y - 15,30,30}.draw(ColorF{ 1.0,0.5,0.5 });
	}
}
