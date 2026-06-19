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
	void update();
	void draw();

	Array<Point>shape;
	Point pos;
	int color = 0;

private:

};

