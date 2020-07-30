#pragma once

#include "stdafx.h"

class GameoverScene : public LayerColor
{
private:
	EventListenerTouchAllAtOnce *listener;

	Sprite * Table;
	float n_time;
	int nowFrame;

	Sprite * RestartButton;
	Sprite * MainButton;

public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float dt);

	CREATE_FUNC(GameoverScene);

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
};