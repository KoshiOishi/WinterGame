#include "GameOver.h"
#include "SceneManager.h"
#include "Input.h"
#include "DebugText.h"
#include "DX12Util.h"
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
}

void GameOver::Update()
{
	DebugText::Print("GameOver", 0, 0);

	if (Input::Trigger(DIK_SPACE))
	{
		SceneManager::SetScene("Title");
	}
}

void GameOver::Draw()
{
	//描画開始
	DX12Util::BeginDraw();

	//背景スプライト描画ここから


	//背景描画ここまで
	DX12Util::ClearDepthBuffer();


	//オブジェクト描画ここから

	//オブジェクト描画ここまで

	//前景スプライト描画ここから

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
		assert(0);
	}
	else
	{
		std::ifstream ifs;
		std::vector<int> scoreList;

		ifs.open("Resources/score.bin", std::ios::binary);
		ifs.read();
	}

}

void GameOver::DisplayScore()
{

}

bool GameOver::CheckHeader()
{
	std::ifstream ifs;
	ifs.open("Resources/score.bin", std::ios::binary);
	byte key = 1301;
	std::string header = "Yokemasyoune_score";

	//オープン失敗
	if (ifs.fail())
	{
		//新規作成
		std::ofstream ofs("Resources/score.bin", std::ios::binary);
		std::string header_another = header;
		for (int i = 0; i < header.length(); i++)
		{
			header_another[i] = header[i] ^ key;
		}
		int n = header_another.length();
		ofs.write(header_another.c_str(), n);
		ofs.close();

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
