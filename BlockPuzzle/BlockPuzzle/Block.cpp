#include "stdafx.h"
#include "Block.h"



Block::Block()
{
}

Block::Block(const Array<Point>& shape,Texture tex)
{
	this->shape = shape;
	maintex = tex;
}

void Block::update()
{
	
}

void Block::draw(const Point& drawPos) const
{
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
	Array<Point> rotated;//回転データ
	Vec2 center(0, 0);
	for (const auto& cell :shape)
	{
		center += Vec2(cell);
	}

	center /=shape.size();

	for (const auto& cell : shape)
	{
		double relX = cell.x - center.x;
		double relY = cell.y - center.y;

		int newX = static_cast<int>(Round(-relY + center.x));
		int newY = static_cast<int>(Round(relX + center.y));

		rotated << Point(newX, newY);
	}

	shape = rotated;
}



