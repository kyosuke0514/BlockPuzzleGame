#include "stdafx.h"
#include "Block.h"

Block::Block()
{
}

Block::Block(const Array<Point>& shape,Texture tex)
{
	//ブロックの形状とテクスチャを初期化
	this->shape = shape;
	maintex = tex;
}

void Block::update()
{
	
}

void Block::draw(const Point& drawPos) const
{
	//ブロックを構成する各マスを描画
	for (const auto& cell : shape)
	{
		maintex.scaled(4.0).draw(
			drawPos.x + cell.x * CellPitch,
			drawPos.y + cell.y * CellPitch
		);
	}
}

void Block::rotate()
{
	//回転後の座標を保存
	Array<Point> rotated;
	//ブロックの中心座標を計算
	Vec2 center(0, 0);
	for (const auto& cell :shape)
	{
		center += Vec2(cell);
	}

	center /=shape.size();

	//各マスの中心を基準に90度回転
	for (const auto& cell : shape)
	{
		double relX = cell.x - center.x;
		double relY = cell.y - center.y;

		int newX = static_cast<int>(Round(-relY + center.x));
		int newY = static_cast<int>(Round(relX + center.y));

		rotated << Point(newX, newY);
	}

	//回転後の形状を反映
	shape = rotated;
}



