# pragma once
# include <Siv3D.hpp>

// シーンのステート
enum class State
{
	Title,
	Game,
	Ranking,
};

// 共有するデータ
struct GameData
{
	// 直前のゲームのスコア
	int32 lastScore = 0;

	// ハイスコア
	Array<int32> highScores = {};
};

using App = SceneManager<State, GameData>;
