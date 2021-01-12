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
	//描画開始
	DX12Util::BeginDraw();

	//背景スプライト描画ここから
	bg.Draw();

	//背景描画ここまで
	DX12Util::ClearDepthBuffer();


	//オブジェクト描画ここから

	//オブジェクト描画ここまで

	//前景スプライト描画ここから
	explain_left.Draw();
	explain_right.Draw();

	DebugText::DrawAll();

	//前景スプライト描画ここまで

	//描画終了
	DX12Util::EndDraw();
}
