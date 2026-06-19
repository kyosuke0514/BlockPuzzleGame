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
	RoundRect m_startButton;
	RoundRect m_rankingButton;
	RoundRect m_exitButton;

	Transition m_startTransition{ 0.4s, 0.2s };
	Transition m_rankingTransition{ 0.4s, 0.2s };
	Transition m_exitTransition{ 0.4s, 0.2s };

	
};

