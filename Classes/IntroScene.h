#pragma once

#include "stdafx.h"

class IntroScene : public LayerColor
{
private:
	EventListenerTouchAllAtOnce *listener;

	Sprite * Black;
	Layer * BGLayer;
	Layer * LLayer;
	CPNCamera * BG_Camera;
	Sprite * Logo;
	Sprite * TouchS;
	Sprite * BG1;
	Sprite * BG2;
	Sprite * BG3;


	float sceenS;
	bool gg;
public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float dt);

	void mapEdit();

	CREATE_FUNC(IntroScene);


	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
};