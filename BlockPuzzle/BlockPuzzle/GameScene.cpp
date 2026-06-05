#include "GameScene.h"
#include "Common.h"
#include <Siv3D.hpp>

GameScene::GameScene(const InitData& init)
	: IScene{ init }
{
	board = Array<Array<int>>(BoardHeight, Array<int>(BoardWidth, 0));
	for (int i = 0; i < 3; i++)
	{
		const int index = Random<int>(0, static_cast<int>(BlockShapes.size() - 1));
		CurrentBlocks << BlockShapes[index];
	}
}

void GameScene::update()
{
	Point blockPos
	{
		(Cursor::Pos().x - HoldOffset.x - BoardOffsetX) / CellSize,
		(Cursor::Pos().y - HoldOffset.y - BoardOffsetY) / CellSize
	};

	//ブロックを回転
	if (isHolding&&MouseR.down())
	{
		Array<Point> rotated;//回転データ
		Vec2 center(0, 0);
		for (const auto& cell : CurrentBlock)
		{
			center += Vec2(cell);
		}

		center /= CurrentBlock.size();

		for (const auto& cell : CurrentBlock)
		{
			double relX = cell.x - center.x;
			double relY = cell.y - center.y;

			int newX = static_cast<int>(Round(-relY + center.x));
			int newY = static_cast<int>(Round(relX + center.y));

			rotated << Point(newX, newY);
		}

		CurrentBlock = rotated;
	}

	//ブロックを取得
	if (!isHolding)
	{
		for (int i = 0; i < CurrentBlocks.size(); i++)
		{
			Point previewPos{ 12, 3 + i * 5 };

			for (const auto& cell : CurrentBlocks[i])
			{
				Rect rect
				(
					(previewPos.x + cell.x) * CellSize,
					(previewPos.y + cell.y) * CellSize,
					CellSize,
					CellSize
				);

				if (rect.leftClicked())
				{
					SelectedBlock = i;
					CurrentBlock = CurrentBlocks[i];

					isHolding = true;

					HoldOffset =
					{
						Cursor::Pos().x - previewPos.x * CellSize,
						Cursor::Pos().y - previewPos.y * CellSize
					};
				}
			}
		}
	}
	else
	{
		//ブロックを配置
		if (MouseL.up())
		{
			bool canPlace = true; //ブロックが重なっているか

			if (0 <= blockPos.x && blockPos.x < BoardWidth && 0 <= blockPos.y && blockPos.y < BoardHeight)
			{
				//配置可能か判定
				for (const auto& cell : CurrentBlock)
				{
					Point pos
					{
						blockPos.x + cell.x,
						blockPos.y + cell.y
					};

					//盤面外チェック
					if (pos.x < 0 || pos.x >= BoardWidth || pos.y < 0 || pos.y >= BoardHeight)
					{
						canPlace = false;
						break;
					}

					//重なりチェック
					if (Blocks.contains(pos))
					{
						canPlace = false;
						break;
					}
				}

				if (canPlace)
				{
					for (const auto& cell : CurrentBlock)
					{
						Blocks << Point
						{
							blockPos.x + cell.x,
							blockPos.y + cell.y
						};
					}

					//横１列揃ったら消える
					Array<int>clearRows;

					for (int y = 0; y < BoardHeight; y++)
					{
						int count = 0;

						for (const auto& block : Blocks)
						{
							if (block.y == y)
							{
								count++;
							}
						}
						if (count == BoardHeight)
						{
							clearRows << y;
						}
					}

					for (int row : clearRows)
					{
						for (int i = static_cast<int>(Blocks.size()) - 1; i >= 0; --i)
						{
							if (Blocks[i].y == row)
							{
								Blocks.erase(Blocks.begin() + i);
							}
						}
					}

					//縦１列揃ったら消える
					Array<int> clearCols;

					for (int x = 0; x < BoardWidth; x++)
					{
						int count = 0;

						for (const auto& block : Blocks)
						{
							if (block.x == x)
							{
								count++;
							}
						}

						if (count == BoardHeight)
						{
							clearCols << x;
						}
					}

					for (int col : clearCols)
					{
						for (int i = static_cast<int>(Blocks.size()) - 1; i >= 0; --i)
						{
							if (Blocks[i].x == col)
							{
								Blocks.erase(Blocks.begin() + i);
							}
						}
					}

					//使い終わったブロックを消す
					CurrentBlocks[SelectedBlock].clear();
					CurrentBlock.clear();
					SelectedBlock = -1;

					isHolding = false;
				}
					
				// ３つのブロックを使い終わったか
				bool allEmpty = true;

				for (const auto& block : CurrentBlocks)
				{
					if (!block.isEmpty())
					{
						allEmpty = false;
						break;
					}
				}

				//新しいブロック生成
				if (allEmpty)
				{
					CurrentBlocks.clear();

					for (int i = 0; i < 3; i++)
					{
						int index = Random<int>
						(0,static_cast<int>(BlockShapes.size() - 1));
						CurrentBlocks << BlockShapes[index];
					}
				}
			}
		}
	}
}

void GameScene::draw() const
{
	//基盤表示
	for (int y = 0; y < BoardHeight; ++y)
	{
		for (int x = 0; x < BoardWidth; ++x)
		{
			Rect rect
			(
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

	//3個ブロック表示
	for (int i = 0; i<CurrentBlocks.size(); i++)
	{
		if (CurrentBlocks[i].isEmpty())
		{
			continue;
		}

		if (isHolding && i == SelectedBlock)
		{
			continue;
		}

		Point previewPos{ 12, 3 + i * 5 };

		for (const auto& cell : CurrentBlocks[i])
		{
			Rect
			(
				(previewPos.x + cell.x) * CellSize,
				(previewPos.y + cell.y) * CellSize,
				CellSize,
				CellSize
			).draw(Palette::Orange);
		}
	}

	//新規ブロック表示
	for (const auto& cell : CurrentBlock)
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


