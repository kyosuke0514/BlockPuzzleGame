# include "GameScene.h"

GameScene::GameScene(const InitData& init)
	: IScene{ init }
{

}

void GameScene::update()
{
	
}

void GameScene::draw() const
{
	Scene::SetBackground(ColorF{ 0.2 });



	// スコアを描く
	FontAsset(U"Bold")(m_score).draw(24, Vec2{ 400, 16 });
}

Rect GameScene::getPaddle() const
{
	return{ Arg::center(Cursor::Pos().x, 500), 60, 10 };
}

