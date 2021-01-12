#pragma once
#include <vector>

class GlobalFormat
{
	template<typename T>
	using vector = std::vector<T>;

public:
	struct Format5x5
	{
		bool shape[5][5];
	};

private:
	static vector<Format5x5> playerShapeLv1;
	static vector<Format5x5> playerShapeLv2;
	static vector<Format5x5> playerShapeLv3;
	static vector<Format5x5> playerShapeLv4;

	static int level;
	static int score;

public:
	static void Initialize();
	static void Clear();

	/// <summary>
	/// レベルに応じたプレイヤーの形状をランダムで返す
	/// </summary>
	/// <param name="level">難易度</param>
	/// <returns>プレイヤーの形状</returns>
	static Format5x5 GetPlayerShape(int level);

	/// <summary>
	/// レベルに応じた壁の形状をランダムで返す
	/// </summary>
	/// <param name="level">難易度</param>
	/// <returns></returns>
	static Format5x5 GetWallShape(int level, Format5x5 playerFormat);

	/// <summary>
	/// レベルをセットする
	/// </summary>
	static void SetLevel(int level) { GlobalFormat::level = level; }

	/// <summary>
	/// スコアをセットする
	/// </summary>
	static void SetScore(int score) { GlobalFormat::score = score; }

	/// <summary>
	/// レベルを取得する
	/// </summary>
	/// <returns>レベル</returns>
	static int GetLevel() { return GlobalFormat::level; }

	/// <summary>
	/// スコアを取得する
	/// </summary>
	/// <returns>スコア</returns>
	static int GetScore() { return GlobalFormat::score; }
};
