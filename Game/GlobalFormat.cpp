#include "GlobalFormat.h"
#include <ctime>

GlobalFormat::vector<GlobalFormat::Format5x5> GlobalFormat::playerShapeLv1;
GlobalFormat::vector<GlobalFormat::Format5x5> GlobalFormat::playerShapeLv2;
GlobalFormat::vector<GlobalFormat::Format5x5> GlobalFormat::playerShapeLv3;
GlobalFormat::vector<GlobalFormat::Format5x5> GlobalFormat::playerShapeLv4;

int GlobalFormat::level = 1;
int GlobalFormat::score = 0;

void GlobalFormat::Initialize()
{
	srand((unsigned int)time(0));

	//すでに読み込んであったらリターン
	if (playerShapeLv1.size() > 0)
		return;

#pragma region プレイヤー


	bool P1_1[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,1,1,0,0},
					{0,0,0,0,0},
					{0,0,0,0,0} };

	bool P1_2[5][5]{{0,0,0,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,0,0,0},
					{0,0,0,0,0} };

	bool P1_3[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,0,1,1,0},
					{0,0,0,0,0},
					{0,0,0,0,0} };

	bool P1_4[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,0,0,0} };

	bool P1_5[5][5]{{0,0,0,0,0},
					{0,1,0,0,0},
					{0,0,1,0,0},
					{0,0,0,0,0},
					{0,0,0,0,0} };

	bool P1_6[5][5]{{0,0,0,0,0},
					{0,0,0,1,0},
					{0,0,1,0,0},
					{0,0,0,0,0},
					{0,0,0,0,0} };

	bool P1_7[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,0,1,0,0},
					{0,0,0,1,0},
					{0,0,0,0,0} };

	bool P1_8[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,0,1,0,0},
					{0,1,0,0,0},
					{0,0,0,0,0} };


	Format5x5 f;
	memcpy(f.shape, P1_1, sizeof(bool[5][5]));
	playerShapeLv1.push_back(f);
	memcpy(f.shape, P1_2, sizeof(bool[5][5]));
	playerShapeLv1.push_back(f);
	memcpy(f.shape, P1_3, sizeof(bool[5][5]));
	playerShapeLv1.push_back(f);
	memcpy(f.shape, P1_4, sizeof(bool[5][5]));
	playerShapeLv1.push_back(f);
	memcpy(f.shape, P1_5, sizeof(bool[5][5]));
	playerShapeLv1.push_back(f);
	memcpy(f.shape, P1_6, sizeof(bool[5][5]));
	playerShapeLv1.push_back(f);
	memcpy(f.shape, P1_7, sizeof(bool[5][5]));
	playerShapeLv1.push_back(f);
	memcpy(f.shape, P1_8, sizeof(bool[5][5]));
	playerShapeLv1.push_back(f);


	bool P2_1[5][5]{{0,0,0,0,0},
					{0,0,1,0,0},
					{0,1,1,0,0},
					{0,0,0,0,0},
					{0,0,0,0,0} };

	bool P2_2[5][5]{{0,0,0,0,0},
					{0,0,1,0,0},
					{0,0,1,1,0},
					{0,0,0,0,0},
					{0,0,0,0,0} };

	bool P2_3[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,0,1,1,0},
					{0,0,1,0,0},
					{0,0,0,0,0} };

	bool P2_4[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,1,1,0,0},
					{0,0,1,0,0},
					{0,0,0,0,0} };

	bool P2_5[5][5]{{0,0,0,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,0,0,0,0} };

	bool P2_6[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,1,1,1,0},
					{0,0,0,0,0},
					{0,0,0,0,0} };

	bool P2_7[5][5]{{0,0,0,0,0},
					{0,1,0,0,0},
					{0,0,1,0,0},
					{0,0,0,1,0},
					{0,0,0,0,0} };

	bool P2_8[5][5]{{0,0,0,0,0},
					{0,0,0,1,0},
					{0,0,1,0,0},
					{0,1,0,0,0},
					{0,0,0,0,0} };


	memcpy(f.shape, P2_1, sizeof(bool[5][5]));
	playerShapeLv2.push_back(f);
	memcpy(f.shape, P2_2, sizeof(bool[5][5]));
	playerShapeLv2.push_back(f);
	memcpy(f.shape, P2_3, sizeof(bool[5][5]));
	playerShapeLv2.push_back(f);
	memcpy(f.shape, P2_4, sizeof(bool[5][5]));
	playerShapeLv2.push_back(f);
	memcpy(f.shape, P2_5, sizeof(bool[5][5]));
	playerShapeLv2.push_back(f);
	memcpy(f.shape, P2_6, sizeof(bool[5][5]));
	playerShapeLv2.push_back(f);
	memcpy(f.shape, P2_7, sizeof(bool[5][5]));
	playerShapeLv2.push_back(f);
	memcpy(f.shape, P2_8, sizeof(bool[5][5]));
	playerShapeLv2.push_back(f);


	bool P3_1[5][5]{{0,0,0,0,0},
					{0,0,1,0,0},
					{0,1,1,1,0},
					{0,0,1,0,0},
					{0,0,0,0,0} };

	bool P3_2[5][5]{{0,0,0,0,0},
					{0,1,1,0,0},
					{0,0,1,0,0},
					{0,0,1,1,0},
					{0,0,0,0,0} };

	bool P3_3[5][5]{{0,0,0,0,0},
					{0,0,0,1,0},
					{0,1,1,1,0},
					{0,0,1,0,0},
					{0,0,0,0,0} };

	bool P3_4[5][5]{{0,0,0,0,0},
					{0,0,1,0,0},
					{0,0,1,0,0},
					{0,1,1,1,0},
					{0,0,0,0,0} };

	bool P3_5[5][5]{{0,0,0,0,0},
					{0,1,0,1,0},
					{0,0,1,0,0},
					{0,1,0,1,0},
					{0,0,0,0,0} };

	bool P3_6[5][5]{{0,0,0,0,0},
					{0,1,0,0,0},
					{0,1,0,0,0},
					{0,1,1,1,0},
					{0,0,0,0,0} };

	bool P3_7[5][5]{{0,0,0,0,0},
					{0,1,1,0,0},
					{0,0,1,1,0},
					{0,0,0,1,0},
					{0,0,0,0,0} };

	bool P3_8[5][5]{{0,0,0,0,0},
					{0,0,0,0,0},
					{0,1,0,1,0},
					{0,1,1,1,0},
					{0,0,0,0,0} };


	memcpy(f.shape, P3_1, sizeof(bool[5][5]));
	playerShapeLv3.push_back(f);
	memcpy(f.shape, P3_2, sizeof(bool[5][5]));
	playerShapeLv3.push_back(f);
	memcpy(f.shape, P3_3, sizeof(bool[5][5]));
	playerShapeLv3.push_back(f);
	memcpy(f.shape, P3_4, sizeof(bool[5][5]));
	playerShapeLv3.push_back(f);
	memcpy(f.shape, P3_5, sizeof(bool[5][5]));
	playerShapeLv3.push_back(f);
	memcpy(f.shape, P3_6, sizeof(bool[5][5]));
	playerShapeLv3.push_back(f);
	memcpy(f.shape, P3_7, sizeof(bool[5][5]));
	playerShapeLv3.push_back(f);
	memcpy(f.shape, P3_8, sizeof(bool[5][5]));
	playerShapeLv3.push_back(f);

	bool P4_1[5][5]{{0,0,0,0,0},
					{0,0,1,1,0},
					{0,1,1,1,0},
					{0,1,1,0,0},
					{0,0,0,0,0} };

	bool P4_2[5][5]{{0,0,0,0,0},
					{0,1,1,1,0},
					{0,0,1,0,0},
					{0,1,1,1,0},
					{0,0,0,0,0} };

	bool P4_3[5][5]{{0,0,0,0,0},
					{0,1,0,1,0},
					{0,1,1,1,0},
					{0,0,1,0,0},
					{0,0,0,0,0} };

	bool P4_4[5][5]{{0,0,0,0,0},
					{0,1,0,1,0},
					{0,1,0,1,0},
					{0,1,0,1,0},
					{0,0,0,0,0} };

	bool P4_5[5][5]{{0,0,0,0,0},
					{0,1,1,1,0},
					{0,0,1,1,0},
					{0,0,0,1,0},
					{0,0,0,0,0} };

	bool P4_6[5][5]{{0,0,0,0,0},
					{0,1,0,0,0},
					{0,1,1,0,0},
					{0,1,1,1,0},
					{0,0,0,0,0} };

	bool P4_7[5][5]{{0,0,0,0,0},
					{0,1,1,0,0},
					{0,0,1,1,0},
					{0,1,0,1,0},
					{0,0,0,0,0} };

	bool P4_8[5][5]{{0,0,0,0,0},
					{0,1,1,1,0},
					{0,1,0,1,0},
					{0,1,1,1,0},
					{0,0,0,0,0} };


	memcpy(f.shape, P4_1, sizeof(bool[5][5]));
	playerShapeLv4.push_back(f);
	memcpy(f.shape, P4_2, sizeof(bool[5][5]));
	playerShapeLv4.push_back(f);
	memcpy(f.shape, P4_3, sizeof(bool[5][5]));
	playerShapeLv4.push_back(f);
	memcpy(f.shape, P4_4, sizeof(bool[5][5]));
	playerShapeLv4.push_back(f);
	memcpy(f.shape, P4_5, sizeof(bool[5][5]));
	playerShapeLv4.push_back(f);
	memcpy(f.shape, P4_6, sizeof(bool[5][5]));
	playerShapeLv4.push_back(f);
	memcpy(f.shape, P4_7, sizeof(bool[5][5]));
	playerShapeLv4.push_back(f);
	memcpy(f.shape, P4_8, sizeof(bool[5][5]));
	playerShapeLv4.push_back(f);

#pragma endregion

/*
3_1
　■
■■■
　■

3_2
■■
　■
　■■

3_3
　　■
■■■
　■

3_4
　■
　■
■■■

3_5
■　■
　■
■　■

3_6
■
■
■■■

*/

}

void GlobalFormat::Clear()
{
	playerShapeLv1.clear();
	playerShapeLv2.clear();
	playerShapeLv3.clear();
	playerShapeLv4.clear();
}

GlobalFormat::Format5x5 GlobalFormat::GetPlayerShape(int level)
{
	if (level == 1)
	{
		Format5x5 format;
		int r = std::rand() % playerShapeLv1.size();
		memcpy(format.shape, playerShapeLv1[r].shape, sizeof(bool[5][5]));
		return format;
	}
	else if (level == 2)
	{
		Format5x5 format;
		int r = std::rand() % playerShapeLv2.size();
		memcpy(format.shape, playerShapeLv2[r].shape, sizeof(bool[5][5]));
		return format;
	}
	else if (level == 3)
	{
		Format5x5 format;
		int r = std::rand() % playerShapeLv3.size();
		memcpy(format.shape, playerShapeLv3[r].shape, sizeof(bool[5][5]));
		return format;
	}
	else if (level == 4)
	{
		Format5x5 format;
		int r = std::rand() % playerShapeLv4.size();
		memcpy(format.shape, playerShapeLv4[r].shape, sizeof(bool[5][5]));
		return format;
	}
	else
	{
		//ランダムモード
		//数（4～6こ）と配置をランダムで決める
		int count = (rand() % 3) + 4;
		vector<int> shape;

		//重複しないようにshapeに0～8の数字をcount個入れる
		for (int i = 0; i < count; i++)
		{
			int r = rand() % 9;
			bool bOK = true;
			for (int j = 0; j < shape.size(); j++)
			{
				if (r == shape[j])
				{
					bOK = false;
				}
			}

			if (bOK)
				shape.push_back(r);
			else
			{
				i--;
			}
		}

		//Format5x5の形式にして返す
		//中央の3x3に↑で指定した形を配置
		Format5x5 format = {};
		for (int i = 0; i < shape.size(); i++)
		{
			format.shape[shape[i] / 3 + 1][shape[i] % 3 + 1] = 1;
		}

		return format;
	}

}

GlobalFormat::Format5x5 GlobalFormat::GetWallShape(int level, Format5x5 playerFormat)
{
	//とりあえずプレイヤーは3*3に収まるように設定するので
	//3*3の配列を作成
	bool format3x3[3][3] = { {playerFormat.shape[1][1], playerFormat.shape[1][2], playerFormat.shape[1][3]},
								{playerFormat.shape[2][1], playerFormat.shape[2][2], playerFormat.shape[2][3]},
								{playerFormat.shape[3][1], playerFormat.shape[3][2], playerFormat.shape[3][3]} };

	//穴の位置を乱数で決める
	int rX = (rand() % 3);
	int rY = (rand() % 3);

	Format5x5 hollFormat = {};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int rW = rand() % 2;
			if (i >= rX && i < rX + 3 && j >= rY && j < rY + 3)
			{
				if (format3x3[i - rX][j - rY] == true)
					hollFormat.shape[i][j] = 0;
				else
					hollFormat.shape[i][j] = rW;
			}
			else
			{
				hollFormat.shape[i][j] = rW;
			}
		}
	}

	return hollFormat;
}
