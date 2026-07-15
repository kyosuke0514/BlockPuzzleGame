#pragma once
#include "Common.h"

class GameOverScene : public App::Scene
{
public:
	GameOverScene(const InitData& init);
	void update()override;
	void draw()const override;

private:
	//イラスト素材
	Texture TitleTexture{ U"PuzzleSozai/Title.png" };
	Texture PlayTexture{ U"PuzzleSozai/Play.png" };
	Texture RankingTexture{ U"PuzzleSozai/Ranking.png" };
	Texture ExitTexture{ U"PuzzleSozai/Exit.png" };
	Texture BackTexture{ U"PuzzleSozai/Back1.png" };
	Texture GameOverTexture{ U"PuzzleSozai/GameOver.png" };
	Texture ScoreTexture{ U"PuzzleSozai/Score1.png" };
	Texture NumberTexture{ U"PuzzleSozai/Number.png" };

	//ボタンの当たり判定
	RoundRect m_startButton;
	RoundRect m_rankingButton;
	RoundRect m_exitButton;

	//ホバー時のアニメーション
	Transition m_startTransition{ 0.4s, 0.2s };
	Transition m_rankingTransition{ 0.4s, 0.2s };
	Transition m_exitTransition{ 0.4s, 0.2s };

	//BGM素材
	const Audio TitleBGM{ Audio::Stream, U"Data/TitleBGM.mp3", Loop::Yes };

	//SE素材
	const Audio BotanSE{ Audio::Stream, U"Data/BotanSE.mp3" };
};

