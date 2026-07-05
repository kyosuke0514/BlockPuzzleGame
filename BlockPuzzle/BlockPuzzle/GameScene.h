#pragma once
#include "Common.h"
#include "Block.h"

// ゲームシーン
class GameScene : public App::Scene
{
public:
	GameScene(const InitData& init);
	void update() override;
	void draw() const override;

private:
	int SelectedBlock = -1;
	bool isHolding = false;//ブロックを持つか
	bool CanPlaceBlock(const Block& block) const;
	Array<Block>Blocks;//ブロックデータ
	Array<Array<int>>board;//盤面データ
	Array<Block>CurrentBlocks;
	Point CurrentBlockPos = { 12,3 };
	Point HoldOffset;//どこをつかむか
	Block CurrentBlock;// 現在のブロック形
	Array<Block>BlockShapes
	{
		// 1マス
		Block({{ 0, 0 }}),
		// 横棒
		Block({{0,0},{1,0},{2,0}}),
		// L字
		Block({{0,0},{0,1},{1,1}}),
		// 四角
		Block({{0,0},{1,0},{0,1},{1,1}}),
		// T字
		Block({{0,0},{1,0},{2,0},{1,1}}),
		//3*3
		Block({{0,0},{1,0},{2,0},{0,1},{1,1},{2,1},{0,2},{1,2},{2,2}})
	};

	Texture Board1Texture{ U"PuzzleSozai/Board1.png" };
	Texture Board2Texture{ U"PuzzleSozai/Board2.png" };
	Texture BackTexture{ U"PuzzleSozai/Back1.png" };
	Texture ScoreTexture{ U"PuzzleSozai/Score.png" };
	Texture NumberTexture{ U"PuzzleSozai/Number.png" };
	
};


