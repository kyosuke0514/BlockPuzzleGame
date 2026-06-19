#pragma once
#include <Siv3D.hpp>

//共通基盤データ
constexpr int BoardWidth = 10;
constexpr int BoardHeight = 10;
constexpr int CellSize = 64;

//シーンのステート
enum class State
{
	Title,
	Game,
	Ranking,
};

//共有するデータ
struct GameData
{
	//直前のゲームのスコア
	int32 lastScore = 0;

	//ハイスコア
	Array<int32> highScores = {};
};

using App = SceneManager<State, GameData>;
