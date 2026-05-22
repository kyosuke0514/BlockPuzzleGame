# pragma once
# include "Common.h"

// ゲームシーン
class GameScene : public App::Scene
{
public:

	GameScene(const InitData& init);
	void update() override;
	void draw() const override;

private:

	// ブロックのサイズ
	static constexpr Size BrickSize{ 40, 40 };

	// 現在のゲームのスコア
	int32 m_score = 0;

	Rect getPaddle() const;
};


