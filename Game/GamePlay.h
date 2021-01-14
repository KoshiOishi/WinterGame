#pragma once
#include "Scene.h"
#include "Object3D.h"
#include "Sprite.h"
#include "CollisionPrimitive.h"
#include "Interpolation.h"
#include "Model.h"
#include "Light.h"
#include "GlobalFormat.h"
#include <vector>

class GamePlay :
	public Scene
{
	template<typename T>
	using vector = std::vector<T>;

	enum ModelNum
	{
		Model_Box,
		Model_Sphere,
		Model_Square,
		Model_Cube
	};

private:
	//スコア文字
	vector<Sprite> sprScore;
	Sprite sprScoreText;

	//オブジェクト
	vector<Object3D> objPlayers;
	vector<Object3D> objWalls;
	Object3D objSky;

	//当たり判定
	vector<Sphere> colPlayers;
	vector<Sphere> colWalls;

	//モデル
	Model modelBox;
	Model modelSphere;
	Model modelSquare;
	Model modelSky;
	Model modelCube;

	//ライト
	Light light;

	//モデルの形状
	ModelNum modelnum = Model_Square;

	//プレイヤーの形状フラグ(5x5のbool型)
	GlobalFormat::Format5x5 playerFormat;

	//壁の形状フラグ(5x5のbool型)
	GlobalFormat::Format5x5 wallFormat;

	//レベル
	int level = 1;

	//壁移動速度
	float wallSpeed = -1.0f;

	//カメラ移動量
	float cameraVelocity = 0.05f;

	//モデルの1辺の長さ
	const float MODEL_LENGTH = 10;

	//衝突フラグ
	bool isCollision = false;

	//演出用衝突ブロックリスト
	vector<int> collisionList;

	//演出用衝突からの経過時間
	int afterCollisionDrawTimer = 0;

	//オブジェクト回転値
	float objectRotate = 0;

	//スコア
	int score = 0;

public:
	GamePlay();
	~GamePlay();
	void Initialize() override;
	void Update() override;
	void Draw() override;

	void InitPlayer(int level);
	void InitWall(int level);
	void UpdatePlayerPosition();
	void UpdateCameraAngle();
	void SetPlayerObjects(GlobalFormat::Format5x5 format);
	void CollisionPlayer2Wall();
	void AfterCollision();
	void RotateObject();
	void UpdateSprScore();
};

