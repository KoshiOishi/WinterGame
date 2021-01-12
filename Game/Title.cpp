#include "Title.h"
#include "SceneManager.h"
#include "Input.h"
#include "DebugText.h"
#include "DX12Util.h"
#include "GlobalFormat.h"

Title::Title()
{
	sceneName = "Title";
}

Title::~Title()
{
}

void Title::Initialize()
{
	Object3D::SetEye(0,0,-10);

	//ライト初期化
	light.Initialize();
	light.SetLightColor({ 1,1,1 });
	light.SetLightDir({ 0, 1, 5, 0 });
	Object3D::SetLight(light);

	modelCursol.CreateFromOBJ("Resources/cursol/cursol.obj", 3);
	modelCursol.Initialize();

	modelTitleText.CreateFromOBJ("Resources/titleName/titleName.obj", 4);
	modelTitleText.Initialize();

	objCursol.SetModel(modelCursol);
	objCursol.Initialize();
	objCursol.SetRotation(0, 0, 270);
	objCursol.SetScale(0.5f, 0.5f, 0.5f);
	objCursol.SetPosition(-3, -2.8f, 0);

	objTitleText.SetModel(modelTitleText);
	objTitleText.Initialize();
	objTitleText.SetPosition(0,1.5,0);
	objTitleText.SetScale(3,3,3);

	sprTitleBG.Initialize(1, "Resources/title_bg.png");
	sprTitleEffect1.Initialize(2, "Resources/title_effect1.png");
	sprTitleEffect2.Initialize(3, "Resources/title_effect2.png");
	sprTitleStart.Initialize(4, "Resources/title_start.png");
	sprTitleStart.SetPosition(512, 470);
	sprTitleStart.SetScale(256,128);

	sprTitleDiff.Initialize(5, "Resources/title_diff.png");
	sprTitleDiff.SetPosition(0, 360);

	isStart = false;
	cursolnum = 0;
}

void Title::Update()
{

	if (isStart == false)
	{
		objCursol.SetPosition(-3, -2.8f, 0);
		cursolnum = 0;
		if (Input::Trigger(DIK_SPACE))
		{
			isStart = true;
		}
	}
	else
	{
		if (Input::Trigger(DIK_SPACE))
		{
			if (cursolnum != 5)
			{
				GlobalFormat::SetLevel(cursolnum + 1);
				SceneManager::SetScene("Explain");
			}
			else
			{
				isStart = false;
			}
		}

		if (Input::Trigger(DIK_UP))
		{
			cursolnum--;

			if (cursolnum < 0)
				cursolnum = 5;
		}
		if (Input::Trigger(DIK_DOWN))
		{
			cursolnum++;

			if (cursolnum > 5)
				cursolnum = 0;
		}


		if (cursolnum == 0)
		{
			objCursol.SetPosition(-6.8f, -1.4f, 0);
		}
		else if (cursolnum == 1)
		{
			objCursol.SetPosition(-6.8f, -2.8f, 0);
		}
		else if (cursolnum == 2)
		{
			objCursol.SetPosition(-6.8f, -4.2f, 0);
		}
		else if (cursolnum == 3)
		{
			objCursol.SetPosition(1, -1.4f, 0);
		}
		else if (cursolnum == 4)
		{
			objCursol.SetPosition(1, -2.8f, 0);
		}
		else
		{
			objCursol.SetPosition(1, -4.2f, 0);
		}
	}

	objCursol.AddRotation(1.0f, 0, 0);
	objTitleText.AddRotation(-5.0f, 0, 0);


	light.Update();
	objCursol.Update();
	objTitleText.Update();
}

void Title::Draw()
{
	//描画開始
	DX12Util::BeginDraw();

	//背景スプライト描画ここから
	sprTitleBG.Draw();

	//背景描画ここまで
	DX12Util::ClearDepthBuffer();


	//オブジェクト描画ここから

	objCursol.Draw();
	objTitleText.Draw();

	//オブジェクト描画ここまで

	//前景スプライト描画ここから
	if (isStart == false)
		sprTitleStart.Draw();
	else
		sprTitleDiff.Draw();

	DebugText::DrawAll();

	//前景スプライト描画ここまで

	//描画終了
	DX12Util::EndDraw();
}
