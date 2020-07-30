#pragma once

#include "stdafx.h"

class ExternScene : public LayerColor
{
private:
	Sprite * Black;


public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	float Time = 0.7f;
	bool gg = false;
	CREATE_FUNC(ExternScene);



};