#pragma once

#include "stdafx.h"

class KGScene : public Layer
{
private:

	Sprite * BG;
	Sprite * Bar;
	Sprite * ghang;

	float r_Time = 1.0f;
	bool e_Load = false;
	bool gg = false;
public:

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(KGScene);

	void LoadSprite();
	void LoadSound();

	void update(float dt);
};