#pragma once
#include <Siv3D.hpp>

//共通基盤データ
constexpr int BoardWidth = 10;//マスの幅
constexpr int BoardHeight = 10;//マスの高さ
constexpr int CellSize = 64;//マス１個の大きさ
constexpr int GridSize = 2;//マスとマスの線の太さ
constexpr int CellPitch = 66;//次のマスまでの間隔

//シーンのステート
enum class State
{
	Title,
	Game,
	Ranking,
	GameOver
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
