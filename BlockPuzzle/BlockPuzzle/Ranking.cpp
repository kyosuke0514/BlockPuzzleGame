# include "Ranking.h"

Ranking::Ranking(const InitData& init)
	: IScene{ init }
{
	//BGM
	TitleBGM.setVolume(0.3);
	TitleBGM.play();

	auto& data = getData();

	if (data.lastScore)
	{
		//ランキングを再構成
		data.highScores << data.lastScore;
		data.highScores.rsort();
		data.highScores.resize(RankingCount);

		//ランクインしていたらm_rankに順位をセット
		for (int32 i = 0; i < RankingCount; ++i)
		{
			if (data.highScores[i] == data.lastScore)
			{
				m_rank = i;
				break;
			}
		}

		data.lastScore = 0;
	}
}

void Ranking::update()
{
	if (MouseL.down())
	{
		//SE
		BotanSE.setVolume(0.4);
		BotanSE.play();
		changeScene(State::Title);
	}
}

void Ranking::draw() const
{
	//画面中央
	const Vec2 center = Scene::Center();

	//背景
	BackTexture.drawAt(Scene::Center());

	//ランキング
	RankingTexture.scaled(1.5).drawAt(center.x, 300);

	const auto& data = getData();

	//ランキングを表示
	for (int32 i = 0; i < RankingCount; ++i)
	{
		const double rectW = 700;

		//枠
		const RectF rect{ Scene::Center().x - rectW / 2,450 + i * 100,rectW,80 };
		rect.draw(ColorF{ 0.8 });

		const int DigitW = 64;
		const int DigitH = 128;
		const double Scale = 0.4;

		String score = Format(data.highScores[i]);

		double digitWidth = DigitW * Scale;
		double totalWidth = score.size() * digitWidth;

		//数字全体が枠の中央に来るようにする
		double startX = rect.center().x - totalWidth / 2;

		for (size_t j = 0; j < score.size(); j++)
		{
			int num = score[j] - U'0';

			NumberTexture(Rect(num * DigitW, 0, DigitW, DigitH))
				.scaled(Scale)
				.draw(startX + j * digitWidth, rect.y + 15);
		}

		// ランクインしていたら
		if (i == m_rank)
		{
			rect.drawFrame(2, 10, ColorF{ 1.0, 0.8, 0.2 });
		}
	}


}
