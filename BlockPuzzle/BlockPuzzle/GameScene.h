#pragma once
#include "Common.h"

// ゲームシーン
class GameScene : public App::Scene
{
public:
	GameScene(const InitData& init);
	void update() override;
	void draw() const override;

private:
	Array<Point> Blocks;//ブロックデータ
	Array<Array<int>>board;//盤面データ
	Point SpawnPos = { 12,3 };//生成位置
	Point CurrentBlockPos = { 12,3 };//操作中ブロック
	bool isHolding = false;//ブロックを持つか
};


