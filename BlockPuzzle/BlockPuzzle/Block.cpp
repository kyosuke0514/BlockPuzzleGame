#include "stdafx.h"
#include "Block.h"

Array<Texture> Block::GemTextures =
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

Block::Block()
{
}

Block::Block(const Array<Point>& shape)
{
	this->shape = shape;
}

void Block::update()
{
	
}

void Block::draw(const Point& drawPos) const
{
	for (const auto& cell : shape)
	{
		GemTextures[color].scaled(4.0).draw(
			drawPos.x + cell.x * CellPitch,
			drawPos.y + cell.y * CellPitch
		);
	}
}



