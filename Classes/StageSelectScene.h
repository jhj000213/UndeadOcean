#pragma once

#include "stdafx.h"

class StageSelectScene : public LayerColor
{
private:
	EventListenerTouchAllAtOnce *listener;

	Sprite * Table;
	Sprite * n_Map;
	MenuItemImage * Title;
	MenuItemImage * PostIt_1;
	MenuItemImage * PostIt_2;
	MenuItemImage * PostIt_3;
	Menu * menu1;
	Menu * menu2;
	Menu * menu3;
	Menu * menu4;

	LabelBMFont * Stage1ScoreL;
	LabelBMFont * Stage2ScoreL;
	LabelBMFont * Stage3ScoreL;

	Sprite * Stage1WhiteGir[3];
	Sprite * Stage2WhiteGir[3];
	Sprite * Stage3WhiteGir[3];




	int nowSelectStage;
public:
	void StageSelect(Ref * sender);
	void MoveScene();

	static Scene* createScene();
	virtual bool init();
	virtual void update(float dt);


	CREATE_FUNC(StageSelectScene);


	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
};