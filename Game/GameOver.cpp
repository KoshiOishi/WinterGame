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
	//�`��J�n
	DX12Util::BeginDraw();

	//�w�i�X�v���C�g�`�悱������


	//�w�i�`�悱���܂�
	DX12Util::ClearDepthBuffer();


	//�I�u�W�F�N�g�`�悱������

	//�I�u�W�F�N�g�`�悱���܂�

	//�O�i�X�v���C�g�`�悱������

	DebugText::DrawAll();

	//�O�i�X�v���C�g�`�悱���܂�

	//�`��I��
	DX12Util::EndDraw();
}

void GameOver::AddScore()
{
	//�t�@�C���̐������`�F�b�N
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

	//�I�[�v�����s
	if (ifs.fail())
	{
		//�V�K�쐬
		std::ofstream ofs("Resources/score.bin", std::ios::binary);
		std::string header_another = header;
		for (int i = 0; i < header.length(); i++)
		{
			header_another[i] = header[i] ^ key;
		}
		int n = header_another.length();
		ofs.write(header_another.c_str(), n);
		ofs.close();

		//�ĂуI�[�v��
		ifs.open("Resources/score.bin", std::ios::binary);
	}

	if (ifs.fail())
	{
		assert(0);
	}

	//�t�@�C���������`�F�b�N
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
