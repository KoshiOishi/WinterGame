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
		Box,
		Sphere,
		Square,
	};

private:
	Sprite sprite1;

	//�I�u�W�F�N�g
	vector<Object3D> objPlayers;
	vector<Object3D> objWalls;
	Object3D objSky;

	//���f��
	Model modelBox;
	Model modelSphere;
	Model modelSquare;
	Model modelSky;

	//���C�g
	Light light;

	//���f���̌`��
	ModelNum modelnum = Square;

	//�v���C���[�̌`��t���O(5x5��bool�^)
	GlobalFormat::Format5x5 playerFormat;

	//�ǂ̌`��t���O(5x5��bool�^)
	GlobalFormat::Format5x5 wallFormat;

	//���x��
	int level = 1;

	//�ǈړ����x
	float wallSpeed = -1.0f;

	//�J�����ړ���
	float cameraVelocity = 0.05f;

	//���f����1�ӂ̒���
	const float MODEL_LENGTH = 10;

	//�Փ˃t���O
	bool isCollision = false;

	//���o�p�Փ˃u���b�N���X�g
	vector<int> collisionList;

	//���o�p�Փ˂���̌o�ߎ���
	int afterCollisionDrawTimer = 0;

	//�I�u�W�F�N�g��]�l
	float objectRotate = 0;

	//�X�R�A
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
};

