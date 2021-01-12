#pragma once
#include "Scene.h"
#include "Object3D.h"
#include "Sprite.h"
#include "Light.h"

class Title
	: public Scene
{
private:
	Sprite sprTitleBG;
	Sprite sprTitleEffect1;
	Sprite sprTitleEffect2;
	Sprite sprTitleStart;
	Sprite sprTitleDiff;

	Object3D objCursol;
	Object3D objTitleText;

	Model modelCursol;
	Model modelTitleText;

	Light light;

	bool isStart = false;
	int cursolnum = 0;

public:
	Title();
	~Title();
	void Initialize() override;
	void Update() override;
	void Draw() override;
};

