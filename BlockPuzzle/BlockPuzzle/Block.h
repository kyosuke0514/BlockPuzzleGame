#pragma once
#include "Common.h"


class Block
{
public:
	Block();
	Block(const Array<Point>& shape,Texture tex);
	void update();
	void draw(const Point& drawPos) const;
	void rotate();

	Array<Point>shape;
	Point pos;
	
private:
	//ブロック画像
	Texture maintex;
};

