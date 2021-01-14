#include "GameOver.h"
#include "SceneManager.h"
#include "Input.h"
#include "DebugText.h"
#include "DX12Util.h"
#include "GlobalFormat.h"
#include <vector>
#include <fstream>
#include <string>

GameOver::GameOver()
{
	sceneName = "GameOver";
}

GameOver::~GameOver()
{
}

void GameOver::Initialize()
{
	AddScore();
	WriteScore();
	sprBG.Initialize(8, "Resources/gameover_BG.png");
	sprDiff.Initialize(9, "Resources/gameover_diff.png");
	sprDiff.SetDrawRectangle(0, 71 * (GlobalFormat::GetLevel() - 1), 282, 71);
	sprDiff.SetPosition(994, 148);

	sprRankNumber1st.clear();
	sprRankNumber2nd.clear();
	sprRankNumber3rd.clear();
	sprRankNumber4th.clear();
	sprRankNumber5th.clear();

	//Easy
	if (GlobalFormat::GetLevel() == 1)
	{
		AddNumberSprite(easy[0], 0, sprRankNumber1st);
		AddNumberSprite(easy[1], 1, sprRankNumber2nd);
		AddNumberSprite(easy[2], 2, sprRankNumber3rd);
		AddNumberSprite(easy[3], 3, sprRankNumber4th);
		AddNumberSprite(easy[4], 4, sprRankNumber5th);
	}
	//Normal
	else if (GlobalFormat::GetLevel() == 2)
	{
		AddNumberSprite(normal[0], 0, sprRankNumber1st);
		AddNumberSprite(normal[1], 1, sprRankNumber2nd);
		AddNumberSprite(normal[2], 2, sprRankNumber3rd);
		AddNumberSprite(normal[3], 3, sprRankNumber4th);
		AddNumberSprite(normal[4], 4, sprRankNumber5th);
	}
	//Hard
	else if (GlobalFormat::GetLevel() == 3)
	{
		AddNumberSprite(hard[0], 0, sprRankNumber1st);
		AddNumberSprite(hard[1], 1, sprRankNumber2nd);
		AddNumberSprite(hard[2], 2, sprRankNumber3rd);
		AddNumberSprite(hard[3], 3, sprRankNumber4th);
		AddNumberSprite(hard[4], 4, sprRankNumber5th);
	}
	//SuperHard
	else if (GlobalFormat::GetLevel() == 4)
	{
		AddNumberSprite(superhard[0], 0, sprRankNumber1st);
		AddNumberSprite(superhard[1], 1, sprRankNumber2nd);
		AddNumberSprite(superhard[2], 2, sprRankNumber3rd);
		AddNumberSprite(superhard[3], 3, sprRankNumber4th);
		AddNumberSprite(superhard[4], 4, sprRankNumber5th);
	}
	//RandomHard
	else
	{
		AddNumberSprite(randomhard[0], 0, sprRankNumber1st);
		AddNumberSprite(randomhard[1], 1, sprRankNumber2nd);
		AddNumberSprite(randomhard[2], 2, sprRankNumber3rd);
		AddNumberSprite(randomhard[3], 3, sprRankNumber4th);
		AddNumberSprite(randomhard[4], 4, sprRankNumber5th);
	}
}

void GameOver::Update()
{

	if (Input::Trigger(DIK_SPACE))
	{
		SceneManager::SetScene("Title");
	}

	//DisplayScore();
}

void GameOver::Draw()
{
	//描画開始
	DX12Util::BeginDraw();

	//背景スプライト描画ここから
	sprBG.Draw();

	//背景描画ここまで
	DX12Util::ClearDepthBuffer();


	//オブジェクト描画ここから

	//オブジェクト描画ここまで

	//前景スプライト描画ここから
	sprDiff.Draw();

	for (int i = 0; i < sprRankNumber1st.size(); i++)
	{
		sprRankNumber1st[i].Draw();
	}
	for (int i = 0; i < sprRankNumber2nd.size(); i++)
	{
		sprRankNumber2nd[i].Draw();
	}
	for (int i = 0; i < sprRankNumber3rd.size(); i++)
	{
		sprRankNumber3rd[i].Draw();
	}
	for (int i = 0; i < sprRankNumber4th.size(); i++)
	{
		sprRankNumber4th[i].Draw();
	}
	for (int i = 0; i < sprRankNumber5th.size(); i++)
	{
		sprRankNumber5th[i].Draw();
	}


	DebugText::DrawAll();

	//前景スプライト描画ここまで

	//描画終了
	DX12Util::EndDraw();
}

void GameOver::AddScore()
{
	//ファイルの整合性チェック
	if (CheckHeader() == false)
	{
		//あたらしくbinファイルを作り直す
		CreateScoreBin();
	}
	else
	{
		LoadScore();

		//Easy
		if (GlobalFormat::GetLevel() == 1)
		{
			SortScore(easy, GlobalFormat::GetScore());
		}
		//Normal
		else if (GlobalFormat::GetLevel() == 2)
		{
			SortScore(normal, GlobalFormat::GetScore());
		}
		//Hard
		else if (GlobalFormat::GetLevel() == 3)
		{
			SortScore(hard, GlobalFormat::GetScore());
		}
		//SuperHard
		else if (GlobalFormat::GetLevel() == 4)
		{
			SortScore(superhard, GlobalFormat::GetScore());
		}
		//RandomHard
		else
		{
			SortScore(randomhard, GlobalFormat::GetScore());
		}

	}

}

void GameOver::DisplayScore()
{
	//282,71

	//Easy
	if (GlobalFormat::GetLevel() == 1)
	{
		for (int i = 0; i < easy.size(); i++)
		{
			//表示は5位まで
			if (i >= 5) break;

			DebugText::Print(std::to_string(i + 1) + ". " + std::to_string(easy[i]), 0, i * 20 + 30);
		}
	}
	//Normal
	else if (GlobalFormat::GetLevel() == 2)
	{
		for (int i = 0; i < normal.size(); i++)
		{
			//表示は5位まで
			if (i >= 5) break;

			DebugText::Print(std::to_string(i + 1) + ". " + std::to_string(normal[i]), 0, i * 20 + 30);
		}
	}
	//Hard
	else if (GlobalFormat::GetLevel() == 3)
	{
		for (int i = 0; i < hard.size(); i++)
		{
			//表示は5位まで
			if (i >= 5) break;

			DebugText::Print(std::to_string(i + 1) + ". " + std::to_string(hard[i]), 0, i * 20 + 30);
		}
	}
	//SuperHard
	else if (GlobalFormat::GetLevel() == 4)
	{
		for (int i = 0; i < superhard.size(); i++)
		{
			//表示は5位まで
			if (i >= 5) break;

			DebugText::Print(std::to_string(i + 1) + ". " + std::to_string(superhard[i]), 0, i * 20 + 30);
		}
	}
	//RandomHard
	else
	{
		for (int i = 0; i < randomhard.size(); i++)
		{
			//表示は5位まで
			if (i >= 5) break;

			DebugText::Print(std::to_string(i + 1) + ". " + std::to_string(randomhard[i]), 0, i * 20 + 30);
		}
	}

}

bool GameOver::CheckHeader()
{
	std::ifstream ifs;
	ifs.open("Resources/score.bin", std::ios::binary);
	std::string header = "Yokemasyoune_score";

	//オープン失敗
	if (ifs.fail())
	{
		CreateScoreBin();
		//再びオープン
		ifs.open("Resources/score.bin", std::ios::binary);
	}

	if (ifs.fail())
	{
		assert(0);
	}

	//ファイル整合性チェック
	char c[18];
	ifs.read(c, sizeof(c));

	for (int i = 0; i < sizeof(c) / sizeof(char); i++)
	{
		c[i] = c[i] ^ key;
	}

	char cb[18];
	for (int i = 0; i < sizeof(cb) / sizeof(char); i++)
	{
		cb[i] = header.c_str()[i];
	}

	bool bOK = true;
	for (int i = 0; i < sizeof(c) / sizeof(char); i++)
	{
		if (c[i] == cb[i])
			continue;
		else
		{
			bOK = false;
			break;
		}
	}

	ifs.close();
	return bOK;
}

void GameOver::CreateScoreBin()
{
	std::string header = "Yokemasyoune_score";

	//新規作成
	std::ofstream ofs("Resources/score.bin", std::ios::binary);
	std::string write = header + "\n" + "Easy:" + "\n" + "Normal:" + "\n" + "Hard:" + "\n" + "SuperHard:" + "\n" + "RandomHard:" + "\n";
	//std::string write = header + "\n" + "Easy:5,4,3,2,1" + "\n" + "Normal:10,9,8,7,6" + "\n" + "Hard:15,14,13,12,11" + "\n" + "SuperHard:20,19,18,17,16" + "\n" + "RandomHard:25,24,23,22,21" + "\n";
	for (int i = 0; i < write.length(); i++)
	{
		write[i] = write[i] ^ key;
	}
	int n = write.length();
	ofs.write(write.c_str(), n);
	ofs.close();
}

void GameOver::LoadScore()
{
	std::ifstream ifs;

	ifs.open("Resources/score.bin", std::ios::binary);
	ifs.seekg(0, std::ios::end);
	int size = ifs.tellg();
	ifs.seekg(0);

	char* data = new char[size];
	ifs.read(data, size);
	std::string str_data;

	for (int i = 0; i < size; i++)
	{
		data[i] = data[i] ^ key;
		str_data += data[i];
	}

	//ヘッダーを読み飛ばす

	//Easy
	int nes = str_data.find("Easy:") + 5;
	int nee = str_data.find('\n', nes);
	std::string strEasy = str_data.substr(nes, nee - nes);

	while (strEasy.length() > 0)
	{
		int pos = strEasy.find(',');
		if (pos != -1)
		{
			std::string score = strEasy.substr(0, pos);
			easy.push_back(atoi(score.c_str()));
			strEasy = strEasy.substr(pos + 1);
		}
		else
		{
			easy.push_back(atoi(strEasy.c_str()));
			break;
		}
	}

	while (easy.size() < 5)
	{
		easy.push_back(0);
	}

	//Normal
	int nns = str_data.find("Normal:") + 7;
	int nne = str_data.find('\n', nns);
	std::string strNormal = str_data.substr(nns, nne - nns);

	while (strNormal.length() > 0)
	{
		int pos = strNormal.find(',');
		if (pos != -1)
		{
			std::string score = strNormal.substr(0, pos);
			normal.push_back(atoi(score.c_str()));
			strNormal = strNormal.substr(pos + 1);
		}
		else
		{
			normal.push_back(atoi(strNormal.c_str()));
			break;
		}
	}

	while (normal.size() < 5)
	{
		normal.push_back(0);
	}

	//Hard
	int nhs = str_data.find("Hard:") + 5;
	int nhe = str_data.find('\n', nhs);
	std::string strHard = str_data.substr(nhs, nhe - nhs);

	while (strHard.length() > 0)
	{
		int pos = strHard.find(',');
		if (pos != -1)
		{
			std::string score = strHard.substr(0, pos);
			hard.push_back(atoi(score.c_str()));
			strHard = strHard.substr(pos + 1);
		}
		else
		{
			hard.push_back(atoi(strHard.c_str()));
			break;
		}
	}

	while (hard.size() < 5)
	{
		hard.push_back(0);
	}

	//SuperHard
	int nshs = str_data.find("SuperHard:") + 10;
	int nshe = str_data.find('\n', nshs);
	std::string strSuperHard = str_data.substr(nshs, nshe - nshs);

	while (strSuperHard.length() > 0)
	{
		int pos = strSuperHard.find(',');
		if (pos != -1)
		{
			std::string score = strSuperHard.substr(0, pos);
			superhard.push_back(atoi(score.c_str()));
			strSuperHard = strSuperHard.substr(pos + 1);
		}
		else
		{
			superhard.push_back(atoi(strSuperHard.c_str()));
			break;
		}
	}

	while (superhard.size() < 5)
	{
		superhard.push_back(0);
	}

	//RandomHard
	int nrhs = str_data.find("RandomHard:") + 11;
	int nrhe = str_data.find('\n', nrhs);
	std::string strRandomHard = str_data.substr(nrhs, nrhe - nrhs);

	while (strRandomHard.length() > 0)
	{
		int pos = strRandomHard.find(',');
		if (pos != -1)
		{
			std::string score = strRandomHard.substr(0, pos);
			randomhard.push_back(atoi(score.c_str()));
			strRandomHard = strRandomHard.substr(pos + 1);
		}
		else
		{
			randomhard.push_back(atoi(strRandomHard.c_str()));
			break;
		}
	}

	while (randomhard.size() < 5)
	{
		randomhard.push_back(0);
	}


	//ifs.read();
	ifs.close();

}

void GameOver::SortScore(vector<int>& scoreList, int newScore)
{
	if (scoreList.size() == 0)
	{
		scoreList.push_back(newScore);
	}

	//一番最後の値が最新のスコア
	vector<int> newList;
	bool isAdd = false;

	for (int i = 0; i < scoreList.size(); i++)
	{
		if (scoreList[i] < newScore && !isAdd)
		{
			newList.push_back(newScore);
			isAdd = true;
		}
		newList.push_back(scoreList[i]);
	}

	scoreList = newList;
}

void GameOver::AddNumberSprite(int score, int rank, vector<Sprite>& sprList)
{
	//1桁ずつスプライトに格納

	//画像がデカすぎたのでコッチで調整 400,67
	vector<int> num;
	int s = score;
	do
	{
		//後ろから一桁格納していく
		int n = s % 10;
		num.push_back(n);
		s /= 10;
	} while (s != 0);

	vector<int> temp = num;

	for (int i = 0; i < num.size(); i++)
	{
		num[i] = temp[(temp.size() - 1) - i];
	}

	for (int i = 0; i < num.size(); i++)
	{
		Sprite spr;
		spr.SetTexNumber(7);
		spr.GenerateSprite();

		spr.SetDrawRectangle(num[i] * 60, 0, 60, 100);
		spr.SetScale(40,67);
		spr.SetPosition(DX12Util::GetWindowWidth() / 2 - ((num.size() - i) * 30), rank * 60 + 295);
		sprList.push_back(spr);
	}

}

void GameOver::WriteScore()
{
	std::string write = "Yokemasyoune_score\nEasy:" + std::to_string(easy[0]) + "," + std::to_string(easy[1]) + "," + std::to_string(easy[2]) + "," + std::to_string(easy[3]) + "," + std::to_string(easy[4]) + "\n" +
		"Normal:" + std::to_string(normal[0]) + "," + std::to_string(normal[1]) + "," + std::to_string(normal[2]) + "," + std::to_string(normal[3]) + "," + std::to_string(normal[4]) + "\n" +
		"Hard:" + std::to_string(hard[0]) + "," + std::to_string(hard[1]) + "," + std::to_string(hard[2]) + "," + std::to_string(hard[3]) + "," + std::to_string(hard[4]) + "\n" +
		"SuperHard:" + std::to_string(superhard[0]) + "," + std::to_string(superhard[1]) + "," + std::to_string(superhard[2]) + "," + std::to_string(superhard[3]) + "," + std::to_string(superhard[4]) + "\n" +
		"RandomHard:" + std::to_string(randomhard[0]) + "," + std::to_string(randomhard[1]) + "," + std::to_string(randomhard[2]) + "," + std::to_string(randomhard[3]) + "," + std::to_string(randomhard[4]);

	for (int i = 0; i < write.length(); i++)
	{
		write[i] = write[i] ^ key;
	}

	std::ofstream ofs;
	ofs.open("Resources/score.bin", std::ios::binary);
	ofs.write(write.c_str(), write.length());
	ofs.close();
}
