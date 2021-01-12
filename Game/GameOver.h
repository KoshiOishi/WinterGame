#pragma once
#include "Scene.h"
#include "Object3D.h"
#include "Sprite.h"

class GameOver
	: public Scene
{

public:
	GameOver();
	~GameOver();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void AddScore();
	void DisplayScore();
	bool CheckHeader();
};

