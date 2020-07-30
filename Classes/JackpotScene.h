#pragma once

#include "stdafx.h"

class JackpotScene : public LayerColor
{
private:
	//!< 애니메이션


public:
	Size winSize = Director::getInstance()->getWinSize();

	Sprite* m_Sprite[20];
	Sprite* m_Box[3];
	Animate* m_Animate[10];
	Animation * m_Animation[10];
	Layer* m_layer[10];
	LabelBMFont* m_label[10];
	Sprite* m_material[20];

	EventListenerTouchOneByOne * listener;
	int random;
	char an[255];
	int abc;
	int a, b;
	int nSet[100];
	int nRandom;
	int ntmp;
	int JackpotCheck;
	char str[255];

	bool bb = false;

	//	int random1, random2, random3;

	bool Check;
	bool Random(int nPassCard);

	static Scene* createScene();
	virtual bool init();
	void Sound();
	void menuCloseCallback(Ref* pSender);
	void Go_Adventure(Ref* pSender);
	void Go_Hangar(Ref* pSender);
	void Go_Option(Ref* pSender);
	void Rolling(Ref* pSender);
	void Go_Title(Ref* pSender);
	void OK(Ref* pSender);
	void hide();
	void showLayer0();
	void animation();
	void flash();
	void RandomMaterial();
	void Update(float dt);
	void boxopensound();


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
	CREATE_FUNC(JackpotScene);
};