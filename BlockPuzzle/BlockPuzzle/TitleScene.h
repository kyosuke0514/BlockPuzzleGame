# pragma once
# include "Common.h"

// タイトルシーン
class TitleScene : public App::Scene
{
public:
	TitleScene(const InitData& init);
	void update() override;
	void draw() const override;

private:
	//イラスト素材
	Texture TitleTexture{ U"PuzzleSozai/Title.png" };
	Texture PlayTexture{ U"PuzzleSozai/Play.png" };
	Texture RankingTexture{ U"PuzzleSozai/Ranking.png" };
	Texture ExitTexture{ U"PuzzleSozai/Exit.png" };
	Texture LTexture{ U"PuzzleSozai/L.png" };
	Texture CTexture{ U"PuzzleSozai/C.png" };
	Texture STexture{ U"PuzzleSozai/s.png" };
	Texture BackTexture{ U"PuzzleSozai/Back1.png" };

	//ボタンの当たり判定
	RoundRect m_startButton;
	RoundRect m_rankingButton;
	RoundRect m_exitButton;

	//ホバー時のアニメーション
	Transition m_startTransition{ 0.4s, 0.2s };
	Transition m_rankingTransition{ 0.4s, 0.2s };
	Transition m_exitTransition{ 0.4s, 0.2s };
};

