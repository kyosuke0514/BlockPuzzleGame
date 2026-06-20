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
	bool isHolding = false;//ブロックを持つか
	Array<Point> Blocks;//ブロックデータ
	Array<Array<int>>board;//盤面データ
	Point SpawnPos = { 12,3 };//生成位置
	Point CurrentBlockPos = { 12,3 };//操作中ブロック
	Point HoldOffset;//どこをつかむか
	Array<Point> CurrentBlock = {};// 現在のブロック形
	Array<Texture> GemTextures
	{
		Texture{ U"PuzzleSozai/BlockBlack.png" },
		Texture{ U"PuzzleSozai/BlockBlue.png" },
		Texture{ U"PuzzleSozai/BlockLightBlue.png" },
		Texture{ U"PuzzleSozai/BlockGreen.png" },
		Texture{ U"PuzzleSozai/BlockForestGreen.png" },
		Texture{ U"PuzzleSozai/BlockRed.png" },
		Texture{ U"PuzzleSozai/BlockOrange.png" },
		Texture{ U"PuzzleSozai/BlockYellow.png" },
		Texture{ U"PuzzleSozai/BlockViolet.png" },
		Texture{ U"PuzzleSozai/BlockPurple.png" },
		Texture{ U"PuzzleSozai/BlockGray.png" }
	};
	Texture BoardTexture{ U"PuzzleSozai/Board.png" };
	Array<Array<Point>>CurrentBlocks;
	int SelectedBlock = -1;
	Array<Array<Point>> BlockShapes =
	{
		// 1マス
		{
			{0,0}
		},
		// 横棒
		{
			{0,0},
			{1,0},
			{2,0}
		},
		// L字
		{
			{0,0},
			{0,1},
			{1,1}
		},
		// 四角
		{
			{0,0},
			{1,0},
			{0,1},
			{1,1}
		},
		// T字
		{
			{0,0},
			{1,0},
			{2,0},
			{1,1}
		}
	};
};


