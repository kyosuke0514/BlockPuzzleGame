# pragma once
#include "Common.h"

// ランキングシーン
class Ranking : public App::Scene
{
public:
	Ranking(const InitData& init);
	void update() override;
	void draw() const override;

private:
	//イラスト素材
	Texture BackTexture{ U"PuzzleSozai/Back1.png" };
	Texture RankingTexture{ U"PuzzleSozai/Ranking1.png" };
	Texture NumberTexture{ U"PuzzleSozai/Number.png" };

	//表示件数
	static constexpr int32 RankingCount = 5;

	//順位
	int32 m_rank = -1;

	//BGM素材
	const Audio TitleBGM{ Audio::Stream, U"Data/TitleBGM.mp3", Loop::Yes };

	//SE素材
	const Audio BotanSE{ Audio::Stream, U"Data/BotanSE.mp3" };
};

