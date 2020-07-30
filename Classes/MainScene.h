#pragma once

#include "stdafx.h"

class MainScene : public LayerColor
{
private:
	//!< 애니메이션

public:
	Size winSize = Director::getInstance()->getWinSize();

	Sprite * Submarin;
	Sprite* m_Sprite[10];
	Animate* m_Animate[10];
	Animation * m_Animation[10];
	EventListenerTouchOneByOne * listener;
	LabelBMFont* m_label[20];
	MenuItemImage* m_Menu[20];

	bool bb = false;


	bool Check;
	bool abab;
	//	int random1, random2, random3;


	static Scene* createScene();
	virtual bool init();

	void menuCloseCallback(Ref* pSender);

	void Go_Hanger(Ref* pSender);
	void Go_Shop(Ref* pSender);
	void GameStart(Ref* pSender);
	void Go_Option(Ref* pSender);
	void Go_MiniGame(Ref* pSender);
	void ChangeStorage();
	void ChangeStart();
	void makecover();

	void Update(float dt);


	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	//virtual void onTouchCancelled(Touch *touch, Event *unused_event);
	//
	//virtual void onTouchesBegan(const vector<Touch*>& touches, Event *unused_event);
	//virtual void onTouchesMoved(const vector<Touch*>& touches, Event *unused_event);
	//virtual void onTouchesEnded(const vector<Touch*>& touches, Event *unused_event);
	//virtual void onTouchesCancelled(const vector<Touch*>&touches, Event *unused_event);
	//!< 씬을 등록 시킴
	CREATE_FUNC(MainScene);
};