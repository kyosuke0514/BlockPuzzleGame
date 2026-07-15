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
	Array<Array<int>>board;//盤面データ
	Point CurrentBlockPos = { 12,3 };
	Point HoldOffset;//どこをつかむか
	Block CurrentBlock;// 現在のブロック形
	Array<Block>CurrentBlocks;
	Array<Texture> GemTextures =
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
	Array<Block> BlockShapes
	{
		Block(Array<Point>{ Point{0,0} },GemTextures[10]),
		Block(Array<Point>{ Point{0,0}, Point{1,0}, Point{2,0} },GemTextures[10]),
		Block(Array<Point>{ Point{0,0}, Point{0,1}, Point{1,1} },GemTextures[10]),
		Block(Array<Point>{ Point{0,0}, Point{1,0}, Point{0,1}, Point{1,1} },GemTextures[10]),
		Block(Array<Point>{ Point{0,0}, Point{1,0}, Point{2,0}, Point{1,1} },GemTextures[10]),
		Block(Array<Point>{Point{0,0}, Point{1,0}, Point{2,0},Point{0,1}, Point{1,1}, Point{2,1},Point{0,2}, Point{1,2}, Point{2,2},},GemTextures[10])
	};

	//イラスト素材
	Texture Board1Texture{ U"PuzzleSozai/Board1.png" };
	Texture Board2Texture{ U"PuzzleSozai/Board2.png" };
	Texture BackTexture{ U"PuzzleSozai/Back1.png" };
	Texture ScoreTexture{ U"PuzzleSozai/Score.png" };
	Texture NumberTexture{ U"PuzzleSozai/Number.png" };
	Texture LmouseTexture{ U"PuzzleSozai/Lmouse.png" };
	Texture RmouseTexture{ U"PuzzleSozai/Rmouse.png" };
	Texture PickTexture{ U"PuzzleSozai/Pick.png" };
	Texture RotateTexture{ U"PuzzleSozai/Rotate.png" };

	//BGM素材
	const Audio GameBGM{ Audio::Stream, U"Data/BGM.mp3", Loop::Yes };

	//SE素材
	const Audio PickSE{ Audio::Stream, U"Data/PickSE.mp3" };
	const Audio PlaceSE{ Audio::Stream, U"Data/PlaceSE.mp3" };
	const Audio BlockSE{ Audio::Stream, U"Data/BlockSE.mp3" };
};


