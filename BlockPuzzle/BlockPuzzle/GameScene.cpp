#include "GameScene.h"
#include "Common.h"
#include <Siv3D.hpp>
GameScene::GameScene(const InitData& init)
	: IScene{ init }
{
	board = Array<Array<int>>(BoardHeight, Array<int>(BoardWidth, 0));
	const int index = Random<int>(0, static_cast<int>(BlockShapes.size() - 1));
	CurrentBlock = BlockShapes[index];
}

void GameScene::update()
{
	bool touched = false;



	//マウスの座標
	Point mouseGrid{
		Cursor::Pos().x / CellSize,
		Cursor::Pos().y / CellSize
	};

	

	//ブロックを取得した時
	if (!isHolding)
	{
		//ブロック
		for (const auto& cell : CurrentBlock)
		{
			Rect rect
			(
			(CurrentBlockPos.x + cell.x) * CellSize,
			(CurrentBlockPos.y + cell.y) * CellSize,
			CellSize,
			CellSize
			);

			if (rect.leftClicked())
			{
				isHolding = true;
				HoldOffset =
				{
					Cursor::Pos().x - CurrentBlockPos.x * CellSize,
					Cursor::Pos().y - CurrentBlockPos.y * CellSize
				};
				
			}
		}
	}
	else
	{
		if (MouseL.up())
		{
			if (0 <= mouseGrid.x && mouseGrid.x < BoardWidth && 0 <= mouseGrid.y && mouseGrid.y < BoardHeight)
			{
				for (const auto& cell : CurrentBlock)
				{
					Blocks << Point
					{
						mouseGrid.x + cell.x,
						mouseGrid.y + cell.y
					};
				}
				// 新しいブロック生成
				const int index = Random<int>(0, static_cast<int>(BlockShapes.size() - 1));

				CurrentBlock = BlockShapes[index];
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
		Rect
		(
			block.x * CellSize,
			block.y * CellSize,
			CellSize,
			CellSize
		).draw(Palette::Skyblue);
	}

	//新規ブロック表示
	for(const auto &cell:CurrentBlock)
	{
		Point drawPos;
		if (!isHolding)
		{
			drawPos =
			{
				(CurrentBlockPos.x + cell.x) * CellSize,//ブロック本体の位置＋移動したときの各マスのずれ
				(CurrentBlockPos.y + cell.y) * CellSize
			};
		}
		else
		{
			drawPos =
			{
				Cursor::Pos().x - HoldOffset.x + cell.x * CellSize,
				Cursor::Pos().y - HoldOffset.y + cell.y * CellSize
			};
		}
		Rect
		(
			drawPos.x,
			drawPos.y,
			CellSize,
			CellSize
		).draw(Palette::Skyblue);
	}
	
}


