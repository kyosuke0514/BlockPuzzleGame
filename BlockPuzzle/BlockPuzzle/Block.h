#pragma once
#include "Common.h"

enum class BlockColor
{
	Black,
	Blue,
	LightBlue,
	Green,
	ForestGreen,
	Red,
	Orange,
	Yellow,
	violet,
	Purple,
	Gray

};

class Block
{
public:
	Block();
	Block(const Array<Point>& shape);
	void update();
	void draw(const Point& drawPos) const;

	Array<Point>shape;
	Point pos;
	int color = 10;

private:
	static Array<Texture> GemTextures;
};

