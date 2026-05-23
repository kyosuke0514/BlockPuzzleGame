#include "GameScene.h"
#include "Common.h"

GameScene::GameScene(const InitData& init)
	: IScene{ init }
{
	board = Array<Array<int>>(BoardHeight, Array<int>(BoardWidth, 0));
}

void GameScene::update()
{
	//マウスの座標
	Point mouseGrid{
		Cursor::Pos().x / CellSize,
		Cursor::Pos().y / CellSize
	};

	//ブロック
	Rect startBlock(
		CurrentBlockPos.x * CellSize,
		CurrentBlockPos.y * CellSize,
		CellSize,
		CellSize
	);

	//ブロックを取得した時
	if (!isHolding) {
		if(startBlock.leftClicked()) {
			isHolding = true;
		}
	}else {
		if (MouseL.up()) {
			if (0 <= mouseGrid.x && mouseGrid.x < BoardWidth && 0 <= mouseGrid.y && mouseGrid.y < BoardHeight) {
				Blocks << mouseGrid;

				// 新しいブロック生成
				CurrentBlockPos = SpawnPos;
			}
			isHolding = false;
		}
	}
}

void GameScene::draw() const
{
	//基盤表示
	for (int y = 0; y < BoardHeight; ++y) {
		for (int x = 0; x < BoardWidth; ++x) {
			Rect rect(
				x * CellSize,
				y * CellSize,
				CellSize,
				CellSize
			);
			rect.drawFrame(1, Palette::Black);
		}
	}

	//既存ブロック表示
	for (const auto& block : Blocks)
	{
		Rect(
			block.x * CellSize,
			block.y * CellSize,
			CellSize,
			CellSize
		).draw(Palette::Skyblue);
	}

	//新規ブロック表示
	if (!isHolding)
	{
		Rect(
			CurrentBlockPos.x * CellSize,
			CurrentBlockPos.y * CellSize,
			CellSize,
			CellSize
		).draw(Palette::Skyblue);
	}
	else
	{
		Rect(
			Cursor::Pos().x - CellSize / 2,
			Cursor::Pos().y - CellSize / 2,
			CellSize,
			CellSize
		).draw(Palette::Skyblue);
	}
}


