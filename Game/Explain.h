#pragma once
#include "Scene.h"
#include "Object3D.h"
#include "Sprite.h"

class Explain
	: public Scene
{
private:
	Sprite explain_left;
	Sprite explain_right;
	Sprite bg;

	float texX = -1280;

public:
	Explain();
	~Explain();
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

