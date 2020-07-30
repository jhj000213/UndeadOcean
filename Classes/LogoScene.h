#pragma once

#include "stdafx.h"

class LogoScene : public Layer
{
private:

	Sprite * BG;


	float r_Time = 1.5f;

	bool gg = false;
public:

	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(LogoScene);


	void update(float dt);
};