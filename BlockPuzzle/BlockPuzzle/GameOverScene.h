#pragma once
#include "Common.h"

class GameOverScene
{
public:
	GameOverScene();
	void update();
	void draw();

private:
	Texture BackTexture{ U"PuzzleSozai/Back1.png" };
};

