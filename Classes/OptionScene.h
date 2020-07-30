#pragma once

#include "stdafx.h"

class OptionScene : public LayerColor
{
private:
	EventListenerTouchAllAtOnce *listener;

	Sprite * Table;
	Sprite * SoundButton;

	LabelBMFont * GLabel;

	MenuItemImage * Title;
	Menu * menu1;
	MenuItemImage * Credit;
	Menu * menu2;
	MenuItemImage * Help;
	Menu * menu3;
	MenuItemImage * Toon;
	Menu * menu4;
	MenuItemImage * Turn;
	Menu * menu5;

public:
	static Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	void MoveScene();
	void TurnLine();
	void CreditSprite();
	void HelpScene();
	void ToonScene();
	

	CREATE_FUNC(OptionScene);


	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
};