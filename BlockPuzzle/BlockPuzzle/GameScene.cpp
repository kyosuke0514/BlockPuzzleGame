#include "GameScene.h"
#include "Block.h"
#include "Common.h"
#include <Siv3D.hpp>

GameScene::GameScene(const InitData& init) : IScene{ init }
{
	//BGM
	GameBGM.setVolume(0.3);
	GameBGM.play();

	getData().Score = 0;
	board = Array<Array<int>>(BoardHeight, Array<int>(BoardWidth, 0));
	for (int i = 0; i < 3; i++)
	{
		const int index = Random<int>(0, static_cast<int>(BlockShapes.size() - 1));
		CurrentBlocks << BlockShapes[index];
	}
}

void GameScene::update()
{
	//盤面の大きさ
	const int BoardPixelW = BoardWidth * CellSize + (BoardWidth - 1) * GridSize + 8;
	const int BoardPixelH = BoardHeight * CellSize + (BoardHeight - 1) * GridSize + 8;

	//真ん中に置くためのズレ計算
	const int BoardOffsetX = (Scene::Width() - BoardPixelW) / 2;
	const int BoardOffsetY = (Scene::Height() - BoardPixelH) / 2;

	//今マウスがどのマスの上にあるかの計算
	Point blockPos
	{
		(Cursor::Pos().x - HoldOffset.x - BoardOffsetX) / CellSize,
		(Cursor::Pos().y - HoldOffset.y - BoardOffsetY) / CellSize
	};

	//ブロックを回転
	if (isHolding&&MouseR.down())
	{
		CurrentBlock.rotate();
	}

	//ブロックを持っていないとき取得
	if (!isHolding)
	{
		//３つのブロックを順番に判定
		for (int i = 0; i < CurrentBlocks.size(); i++)
		{
			const int PreviewX = BoardOffsetX + BoardPixelW + 50;
			const int PreviewY = BoardOffsetY + 50 + i * 220;

			//ブロックを構成する各マスを判定
			for (const auto& cell : CurrentBlocks[i].shape)
			{
				Rect rect
				(
					PreviewX + cell.x * CellSize,
					PreviewY + cell.y * CellSize,
					CellSize,
					CellSize
				);

				//ブロックを取得
				if (rect.leftClicked())
				{
					//SE
					PickSE.setVolume(0.4);
					PickSE.play();

					SelectedBlock = i;
					CurrentBlock = CurrentBlocks[i];

					isHolding = true;

					HoldOffset =
					{
						Cursor::Pos().x - (PreviewX + cell.x * CellSize),
						Cursor::Pos().y - (PreviewY + cell.y * CellSize)
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
			//SE
			PlaceSE.setVolume(0.4);
			PlaceSE.play();

			//ブロックが重なっているか
			bool canPlace = true; 

			//盤面外でクリックしたらブロックが元の位置に移動
			if (!(0 <= blockPos.x && blockPos.x < BoardWidth && 0 <= blockPos.y && blockPos.y < BoardHeight))
			{
				isHolding = false;
				CurrentBlock = Block();
				SelectedBlock = -1;
				return;
			}
			
			//マウスカーソルが盤面内にある場合
			if (0 <= blockPos.x && blockPos.x < BoardWidth && 0 <= blockPos.y && blockPos.y < BoardHeight)
			{
				//配置可能か判定
				for (const auto& cell : CurrentBlock.shape)
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
					if (board[pos.y][pos.x]==1)
					{
						canPlace = false;
						break;
					}
				}

				//配置可能なら盤面に配置する
				if (canPlace)
				{
					//ブロックを盤面に配置
					for (const auto& cell : CurrentBlock.shape)
					{
						Point pos
						{
							blockPos.x + cell.x,
							blockPos.y + cell.y
						};

						board[pos.y][pos.x] = 1;
					}

					//横１列揃ったら消える
					Array<int>clearRows;
					//縦１列揃ったら消える
					Array<int> clearCols;

					//揃っている横一列を探す
					for (int y = 0; y < BoardHeight; y++)
					{
						int count = 0;

						for (int x = 0; x < BoardWidth; x++)
						{
							if (board[y][x] == 1)
							{
								count++;
							}
						}
						if (count == BoardWidth)
						{
							clearRows << y;
						}
					}
					//揃っている縦一列を探す
					for (int x = 0; x < BoardWidth; x++)
					{
						int count = 0;

						for (int y = 0; y < BoardHeight; y++)
						{
							if (board[y][x] == 1)
							{
								count++;
							}
						}

						if (count == BoardWidth)
						{
							clearCols << x;
						}
					}

					//揃った横一列のブロックを消す
					for (int y : clearRows)
					{
						for (int x = 0; x < BoardWidth; x++)
						{
							board[y][x] = 0;
						}
					}
					//揃った縦一列のブロックを消す
					for (int x : clearCols)
					{
						for (int y = 0; y < BoardHeight; y++)
						{
							board[y][x] = 0;
						}
					}

					//消した行数と列数を計算
					int clearCount = clearRows.size() + clearCols.size();
					
					//消したら1列につき１００点
					if (clearCount > 0)
					{
						//SE
						BlockSE.setVolume(0.4);
						BlockSE.play();

						getData().Score += clearCount * 100;
					}

					//使い終わったブロックを消す
					CurrentBlocks[SelectedBlock].shape.clear();
					CurrentBlock.shape.clear();
					SelectedBlock = -1;

					isHolding = false;

				}
					
				//３つのブロックを使い終わったか
				bool allEmpty = true;

				for (const auto& block : CurrentBlocks)
				{
					if (!block.shape.isEmpty())
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
	
	//3つのブロックのうち、1つも置ける場所がなくなったらゲームオーバー
	bool canPlaceAny = false;

	//残っているブロックを順番に確認
	for (const auto& block : CurrentBlocks)
	{
		if (block.shape.isEmpty())
		{
			continue;
		}

		if (CanPlaceBlock(block))
		{
			canPlaceAny = true;
			break;
		}
	}

	//どのブロックも配置できなければゲームオーバー
	if (!canPlaceAny)
	{
		getData().lastScore = getData().Score;
		changeScene(State::GameOver);
	}
}

void GameScene::draw() const
{
	//盤面の大きさ
	const int BoardPixelW = BoardWidth * CellSize + (BoardWidth - 1) * GridSize + 8;
	const int BoardPixelH = BoardHeight * CellSize + (BoardHeight - 1) * GridSize + 8;

	//真ん中に置くためのズレ計算
	const int BoardOffsetX = (Scene::Width() - BoardPixelW) / 2;
	const int BoardOffsetY = (Scene::Height() - BoardPixelH) / 2;

	//今マウスがどのマスの上にあるかの計算
	Point blockPos
	{
		(Cursor::Pos().x - HoldOffset.x - BoardOffsetX - 4) / CellPitch,
		(Cursor::Pos().y - HoldOffset.y - BoardOffsetY - 4) / CellPitch
	};

	//背景表示
	BackTexture.drawAt(Scene::Center());

	//基盤表示
	Board2Texture.draw(BoardOffsetX, BoardOffsetY);

	//スコア画像
	ScoreTexture.draw(40, 40);

	//ボタン画像
	LmouseTexture.scaled(1.1).draw(40,800);
	RmouseTexture.scaled(1.1).draw(40, 900);
	PickTexture.scaled(0.8).draw(130, 810);
	RotateTexture.scaled(0.8).draw(130, 920);

	//スコア数字画像
	const int DigitW = 64;
	const int DigitH = 128;

	String score = Format(getData().Score);

	//スコア数字画像表示
	for (size_t i = 0; i < score.size(); i++)
	{
		int num = score[i] - U'0';

		NumberTexture(Rect(num * DigitW, 0, DigitW, DigitH)).scaled(0.5).draw(50 + i * 50, 200);
	}


	//既存ブロック表示
	for (int y = 0; y< BoardHeight; y++)
	{
		for (int x = 0; x < BoardWidth; x++)
		{
			if (board[y][x] == 1)
			{
				GemTextures[10].scaled(4.0).draw(
					BoardOffsetX + 4 + x * CellPitch,
					BoardOffsetY + 4 + y * CellPitch
				);
			}
		}
	}

	//置かれる予定の位置が光る
	if (isHolding)
	{
		for (const auto& cell : CurrentBlock.shape)
		{
			Point pos
			{
				blockPos.x + cell.x,
				blockPos.y + cell.y
			};

			// ボード内だけ描画
			if (0 <= pos.x && pos.x < BoardWidth&& 0 <= pos.y && pos.y < BoardHeight)
			{
				Rect
				(
					BoardOffsetX + 4 + pos.x * CellPitch,
					BoardOffsetY + 4 + pos.y * CellPitch,
					CellSize,
					CellSize
				).drawFrame(4, Palette::Yellow);
			}
		}
	}

	//3個ブロック表示
	for (int i = 0; i<CurrentBlocks.size(); i++)
	{
		if (CurrentBlocks[i].shape.isEmpty())
		{
			continue;
		}

		if (isHolding && i == SelectedBlock)
		{
			continue;
		}

		const int PreviewX = BoardOffsetX + BoardPixelW + 50;
		const int PreviewY = BoardOffsetY + 50 + i * 220;

		CurrentBlocks[i].draw({ PreviewX, PreviewY });
	}

	Point drawPos;

	if (isHolding)
	{
		drawPos =
		{
			Cursor::Pos().x - HoldOffset.x,
			Cursor::Pos().y - HoldOffset.y
		};
	}
	else
	{
		drawPos =
		{
			CurrentBlockPos.x * CellPitch,
			CurrentBlockPos.y * CellPitch
		};
	}

	CurrentBlock.draw(drawPos);
}

bool GameScene::CanPlaceBlock(const Block& block) const
{
	//使用済みのブロックは配置できない
	if (block.shape.isEmpty())
	{
		return false;
	}

	//盤面の全てのマスを確認
	for (int y = 0; y < BoardHeight; y++)
	{
		for (int x = 0; x < BoardWidth; x++)
		{
			bool canPlace = true;
			for (const auto& cell : block.shape)
			{
				Point pos{ x + cell.x,y + cell.y };

				if (pos.x < 0 || pos.x >= BoardWidth || pos.y < 0 || pos.y >= BoardHeight)
				{
					canPlace = false;
					break;
				}

				if (board[pos.y][pos.x]==1)
				{
					canPlace = false;
					break;
				}
			}

			if (canPlace)
			{
				return true;
			}
		}
	}
	return false;
}


