#include "GamePlay.h"
#include "DX12Util.h"
#include "Input.h"
#include "Sound.h"
#include "Object3D.h"
#include "SceneManager.h"
#include "DebugText.h"
#include "GlobalFormat.h"
#include "Collision.h"

using namespace DirectX;

GamePlay::GamePlay()
{
	sceneName = "GamePlay";
}

GamePlay::~GamePlay()
{
}

void GamePlay::Initialize()
{
	Object3D::SetEye(25, 35, -100);
	Sprite::LoadTexture(7, "Resources/number.png");

	//ライト初期化
	light.Initialize();
	light.SetLightColor({ 1,1,1 });
	light.SetLightDir({ 0, 1, 5, 0 });
	Object3D::SetLight(light);

	//モデル初期化
	modelBox.CreateBox(10, 10, 10, 0, false);
	modelBox.Initialize();

	modelSphere.CreateSphere(30, 30, 5, 1, false);
	modelSphere.Initialize();

	modelSquare.CreateSquare(10,10,2);
	modelSquare.Initialize();

	modelCube.CreateFromOBJ("Resources/cube/cube.obj", 5);
	modelCube.Initialize();

	//モデルの種類を指定
	int r = rand() % 4;
	if (r == 0)
		modelnum = Model_Box;
	else if (r == 1)
		modelnum = Model_Sphere;
	else if (r == 2)
		modelnum = Model_Square;
	else if (r == 3)
		modelnum = Model_Cube;

	//レベルを初期化
	level = GlobalFormat::GetLevel();

	//3Dオブジェクト初期化
	InitPlayer(level);

	//壁オブジェクト初期化
	InitWall(level);

	//スピード初期化
	wallSpeed = -1.0f;

	//カメラアングル移動量初期化
	cameraVelocity = 0.05f;

	//衝突フラグ初期化
	isCollision = false;

	//演出用衝突ブロックリスト初期化
	collisionList.clear();

	//演出用衝突からの経過時間初期化
	afterCollisionDrawTimer = 0;
	//オブジェクト回転値初期化
	objectRotate = 0;

	//天球オブジェクトの初期化
	modelSky.CreateFromOBJ("Resources/sky/sky.obj", 4);
	modelSky.Initialize();

	objSky.SetModel(modelSky);
	objSky.Initialize();
	objSky.SetScale(1.5f,1.5f,1.5f);

	score = 0;

	sprScoreText.Initialize(10, "Resources/game_score.png");
	sprScoreText.SetPosition(0,50);

	UpdateSprScore();
}

void GamePlay::Update()
{

#pragma region 更新処理


	//壁が通り過ぎたらプレイヤーと壁の形状をリセット、壁のスピードを上げる
	if (objWalls[0].GetPosition().z < -100)
	{
		InitPlayer(level);
		InitWall(level);
		wallSpeed -= 0.1f;
		if (wallSpeed < -3.0f) wallSpeed = -3.0f;

		score++;
		UpdateSprScore();
	}
	else
	{
		for (int i = 0; i < objWalls.size(); i++)
		{
			//壁を移動させる
			objWalls[i].AddPosition(0, 0, wallSpeed);
			colWalls[i].center = XMVectorSet(objWalls[i].GetPosition().x, objWalls[i].GetPosition().y, objWalls[i].GetPosition().z, 0);
		}

		//衝突判定
		if (objWalls[0].GetPosition().z <= -40 + MODEL_LENGTH && objWalls[0].GetPosition().z > -40 - MODEL_LENGTH)
		{
			CollisionPlayer2Wall();
		}
	}

	//プレイヤー移動処理
	UpdatePlayerPosition();

	//衝突後の処理
	AfterCollision();

	//カメラ移動処理
	UpdateCameraAngle();

	//オブジェクト回転処理
	RotateObject();

#pragma endregion


#pragma region オブジェクトアップデート
	light.Update();
	objSky.Update();
	for (int i = 0; i < objPlayers.size(); i++)
		objPlayers[i].Update();

	for (int i = 0; i < objWalls.size(); i++)
		objWalls[i].Update();

#pragma endregion

}

void GamePlay::Draw()
{
	//描画開始
	DX12Util::BeginDraw();

	//背景スプライト描画ここから


	//背景描画ここまで
	DX12Util::ClearDepthBuffer();


	//オブジェクト描画ここから

	objSky.Draw();

	for (int i = 0; i < objPlayers.size(); i++)
	{
		if (!isCollision)
		{
			objPlayers[i].Draw();
		}
		else
		{
			for (int j = 0; j < collisionList.size(); j++)
			{
				if (i == collisionList[j])
				{
					if (afterCollisionDrawTimer >= 60 || (afterCollisionDrawTimer / 5) % 2 == 0)
					{
						objPlayers[i].Draw();
					}
					break;
				}
				if (j < collisionList.size() - 1) continue;
				else
					objPlayers[i].Draw();
			}
		}
	}

	for (int i = 0; i < objWalls.size(); i++)
		objWalls[i].Draw();
	
	//オブジェクト描画ここまで

	//前景スプライト描画ここから

	sprScoreText.Draw();
	for (int i = 0; i < sprScore.size(); i++)
		sprScore[i].Draw();

	DebugText::DrawAll();

	//前景スプライト描画ここまで

	//描画終了
	DX12Util::EndDraw();
}

void GamePlay::InitPlayer(int level)
{
	objPlayers.clear();
	colPlayers.clear();
	GlobalFormat::Format5x5 format = GlobalFormat::GetPlayerShape(level);
	playerFormat = format;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (format.shape[i][j] == true)
			{
				Object3D obj;
				if (modelnum == Model_Box)
					obj.SetModel(modelBox);
				else if (modelnum == Model_Sphere)
					obj.SetModel(modelSphere);
				else if (modelnum == Model_Square)
					obj.SetModel(modelSquare);
				else if (modelnum == Model_Cube)
					obj.SetModel(modelCube);

				obj.Initialize();
				if (modelnum == Model_Square)
					obj.SetIsLight(false);
				obj.SetPosition(j * 10 - 25, i * -10 + 25, -40);
				objPlayers.push_back(obj);

				//当たり判定
				Sphere sphere;
				sphere.center = XMVectorSet(j * 10 - 25, i * -10 + 25, -40, 0);
				sphere.radius = MODEL_LENGTH / 2;
				colPlayers.push_back(sphere);
			}
			else
			{
				Object3D obj;
				if (modelnum == Model_Box)
					obj.SetModel(modelBox);
				else if (modelnum == Model_Sphere)
					obj.SetModel(modelSphere);
				else if (modelnum == Model_Square)
					obj.SetModel(modelSquare);
				else if (modelnum == Model_Cube)
					obj.SetModel(modelCube);

				obj.Initialize();
				if (modelnum == Model_Square)
					obj.SetIsLight(false);
				obj.SetPosition(j * 10 - 25, i * -10 + 25, -40);
				obj.SetColorAs0To255(128,128,128,128);
				obj.SetIsWireFlame(true);
				objPlayers.push_back(obj);
			}
		}
	}
}

void GamePlay::InitWall(int level)
{
	objWalls.clear();
	colWalls.clear();
	GlobalFormat::Format5x5 format = GlobalFormat::GetWallShape(level, playerFormat);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (format.shape[i][j] == true)
			{
				Object3D obj;
				if (modelnum == Model_Box)
					obj.SetModel(modelBox);
				else if (modelnum == Model_Sphere)
					obj.SetModel(modelSphere);
				else if (modelnum == Model_Square)
					obj.SetModel(modelSquare);
				else if (modelnum == Model_Cube)
					obj.SetModel(modelCube);

				obj.Initialize();
				if (modelnum == Model_Square)
					obj.SetIsLight(false);
				obj.SetPosition(j * 10 - 25, i * -10 + 25, 150);
				obj.SetColorAs0To255(255, 64, 64, 255);
				objWalls.push_back(obj);

				//当たり判定
				Sphere sphere;
				sphere.center = XMVectorSet(j * 10 - 25, i * -10 + 25, 150, 0);
				sphere.radius = MODEL_LENGTH / 2 - 1;	//隣接時に判定を取らないようにすこし小さめ
				colWalls.push_back(sphere);
			}
		}
	}

	wallFormat = format;

}

void GamePlay::UpdatePlayerPosition()
{
	if (isCollision) return;

	if (Input::Trigger(DIK_D) || Input::Trigger(DIK_RIGHT))
	{
		//端にブロックがないとき
		if (playerFormat.shape[0][4] != true &&
			playerFormat.shape[1][4] != true &&
			playerFormat.shape[2][4] != true &&
			playerFormat.shape[3][4] != true &&
			playerFormat.shape[4][4] != true)
		{
			GlobalFormat::Format5x5 format = playerFormat;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (j != 0)
						format.shape[i][j] = playerFormat.shape[i][j - 1];
					else
						format.shape[i][j] = playerFormat.shape[i][4];
				}
			}

			SetPlayerObjects(format);
		}
	}

	if (Input::Trigger(DIK_A) || Input::Trigger(DIK_LEFT))
	{
		//端にブロックがないとき
		if (playerFormat.shape[0][0] != true &&
			playerFormat.shape[1][0] != true &&
			playerFormat.shape[2][0] != true &&
			playerFormat.shape[3][0] != true &&
			playerFormat.shape[4][0] != true)
		{
			GlobalFormat::Format5x5 format = playerFormat;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (j != 4)
						format.shape[i][j] = playerFormat.shape[i][j + 1];
					else
						format.shape[i][j] = playerFormat.shape[i][0];
				}
			}

			objPlayers.clear();

			SetPlayerObjects(format);
		}

	}

	if (Input::Trigger(DIK_W) || Input::Trigger(DIK_UP))
	{
		//端にブロックがないとき
		if (playerFormat.shape[0][0] != true &&
			playerFormat.shape[0][1] != true &&
			playerFormat.shape[0][2] != true &&
			playerFormat.shape[0][3] != true &&
			playerFormat.shape[0][4] != true)
		{
			GlobalFormat::Format5x5 format = playerFormat;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i != 4)
						format.shape[i][j] = playerFormat.shape[i + 1][j];
					else
						format.shape[i][j] = playerFormat.shape[0][j];
				}
			}

			objPlayers.clear();

			SetPlayerObjects(format);
		}

	}

	if (Input::Trigger(DIK_S) || Input::Trigger(DIK_DOWN))
	{
		//端にブロックがないとき
		if (playerFormat.shape[4][0] != true &&
			playerFormat.shape[4][1] != true &&
			playerFormat.shape[4][2] != true &&
			playerFormat.shape[4][3] != true &&
			playerFormat.shape[4][4] != true)
		{
			GlobalFormat::Format5x5 format = playerFormat;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (i != 0)
						format.shape[i][j] = playerFormat.shape[i - 1][j];
					else
						format.shape[i][j] = playerFormat.shape[4][j];
				}
			}

			objPlayers.clear();

			SetPlayerObjects(format);
		}

	}

}

void GamePlay::UpdateCameraAngle()
{
	if (isCollision) return;

	Object3D::AddEye(cameraVelocity, 0, 0);
	if (Object3D::GetEye().x > 30 || Object3D::GetEye().x < -30)
		cameraVelocity *= -1;
}

void GamePlay::SetPlayerObjects(GlobalFormat::Format5x5 format)
{
	objPlayers.clear();
	colPlayers.clear();
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (format.shape[i][j] == true)
			{
				Object3D obj;
				if (modelnum == Model_Box)
					obj.SetModel(modelBox);
				else if (modelnum == Model_Sphere)
					obj.SetModel(modelSphere);
				else if (modelnum == Model_Square)
					obj.SetModel(modelSquare);
				else if (modelnum == Model_Cube)
					obj.SetModel(modelCube);

				obj.Initialize();
				if (modelnum == Model_Square)
					obj.SetIsLight(false);
				obj.SetPosition(j * 10 - 25, i * -10 + 25, -40);
				objPlayers.push_back(obj);

				//当たり判定
				Sphere sphere;
				sphere.center = XMVectorSet(j * 10 - 25, i * -10 + 25, -40, 0);
				sphere.radius = MODEL_LENGTH / 2;
				colPlayers.push_back(sphere);
			}
			else
			{
				Object3D obj;
				if (modelnum == Model_Box)
					obj.SetModel(modelBox);
				else if (modelnum == Model_Sphere)
					obj.SetModel(modelSphere);
				else if (modelnum == Model_Square)
					obj.SetModel(modelSquare);
				else if (modelnum == Model_Cube)
					obj.SetModel(modelCube);

				obj.Initialize();
				if (modelnum == Model_Square)
					obj.SetIsLight(false);
				obj.SetPosition(j * 10 - 25, i * -10 + 25, -40);
				obj.SetColorAs0To255(128, 128, 128, 128);
				obj.SetIsWireFlame(true);
				objPlayers.push_back(obj);
			}
		}
	}

	playerFormat = format;

}

void GamePlay::CollisionPlayer2Wall()
{
	if (isCollision) return;

	for (int i = 0; i < colPlayers.size(); i++)
	{
		for (int j = 0; j < colWalls.size(); j++)
			if (Collision::CheckSphere2Sphere(colPlayers[i], colWalls[j]))
				isCollision = true;
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			//旧処理　当たり判定を計算で取るのが必須なのを忘れてましたチーーーン


			//プレイヤーブロックと壁の場所フラグが両方真のとき衝突
			if (playerFormat.shape[i][j] == true && wallFormat.shape[i][j] == true)
			{
				collisionList.push_back(i * 5 + j);
			}


		}
	}
}

void GamePlay::AfterCollision()
{
	if (isCollision)
	{
		wallSpeed = 0;
		afterCollisionDrawTimer++;
		if (afterCollisionDrawTimer >= 120)
		{
			GlobalFormat::SetScore(score);
			SceneManager::SetScene("GameOver");
		}
	}
}

void GamePlay::RotateObject()
{
	if (modelnum != Model_Sphere) return;

	objectRotate += 1.0f;

	for (int i = 0; i < objPlayers.size(); i++)
	{
		if (objPlayers[i].GetIsWireFlame() == false)
			objPlayers[i].SetRotation(0, objectRotate, 0);
	}

	for (int i = 0; i < objWalls.size(); i++)
	{
		objWalls[i].SetRotation(0, objectRotate, 0);
	}


}

void GamePlay::UpdateSprScore()
{
	//最初の処理
	if (score == 0)
	{
		sprScore.clear();
		Sprite spr;
		spr.SetTexNumber(7);//Number.png
		spr.GenerateSprite();
		spr.SetDrawRectangle(0, 0, 60, 100);
		spr.SetPosition(300,53);
		sprScore.push_back(spr);
		return;
	}

	//まず桁数が合っているかチェック
	int n = score;
	int keta = 0;
	while (n != 0)
	{
		n /= 10;
		keta++;
	}

	while (keta > sprScore.size())
	{
		Sprite spr;
		spr.SetTexNumber(7);//Number.png
		spr.GenerateSprite();
		sprScore.push_back(spr);
	}

	int n2 = score;

	//数字に合わせてレクタングルをセット
	for (int i = 0; i < sprScore.size(); i++)
	{
		int drawnum = n2 % 10;

		sprScore[(sprScore.size() - 1) - i].SetDrawRectangle(60 * drawnum, 0, 60, 100);
		sprScore[(sprScore.size() - 1) - i].SetPosition(300 + ((sprScore.size() - 1) - i) * 50, 53);

		n2 /= 10;
	}
}
