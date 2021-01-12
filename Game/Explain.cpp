#include "Explain.h"
#include "SceneManager.h"
#include "Input.h"
#include "DebugText.h"
#include "DX12Util.h"

Explain::Explain()
{
	sceneName = "Explain";
}

Explain::~Explain()
{
}

void Explain::Initialize()
{
	explain_left.Initialize(6, "Resources/explain.png");
	explain_right.SetTexNumber(6);
	explain_right.GenerateSprite();
	bg.SetTexNumber(1);
	bg.GenerateSprite();
	texX = -1280;
}

void Explain::Update()
{
	texX += 40;
	if (texX > 0) texX = 0;

	explain_left.SetPosition(texX, 0);
	explain_right.SetPosition(-texX, 0);

	if (Input::Trigger(DIK_SPACE))
	{
		SceneManager::SetScene("GamePlay");
	}
}

void Explain::Draw()
{
	//�`��J�n
	DX12Util::BeginDraw();

	//�w�i�X�v���C�g�`�悱������
	bg.Draw();

	//�w�i�`�悱���܂�
	DX12Util::ClearDepthBuffer();


	//�I�u�W�F�N�g�`�悱������

	//�I�u�W�F�N�g�`�悱���܂�

	//�O�i�X�v���C�g�`�悱������
	explain_left.Draw();
	explain_right.Draw();

	DebugText::DrawAll();

	//�O�i�X�v���C�g�`�悱���܂�

	//�`��I��
	DX12Util::EndDraw();
}
