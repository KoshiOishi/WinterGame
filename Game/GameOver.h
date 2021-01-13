#pragma once
#include "Scene.h"
#include "Object3D.h"
#include "Sprite.h"
#include <vector>

class GameOver
	: public Scene
{
	template <typename T>
	using vector = std::vector<T>;

private:
	const byte key = 1301;
	vector<int> easy;
	vector<int> normal;
	vector<int> hard;
	vector<int> superhard;
	vector<int> randomhard;

	vector<Sprite> sprRankNumber1st;
	vector<Sprite> sprRankNumber2nd;
	vector<Sprite> sprRankNumber3rd;
	vector<Sprite> sprRankNumber4th;
	vector<Sprite> sprRankNumber5th;

	Sprite sprBG;
	Sprite sprDiff;


public:
	GameOver();
	~GameOver();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void AddScore();
	void DisplayScore();
	bool CheckHeader();
	void CreateScoreBin();
	void LoadScore();
	void SortScore(vector<int>& scoreList, int newScore);
	void AddNumberSprite(int score, int rank, vector<Sprite>& sprList);
	void WriteScore();
};

