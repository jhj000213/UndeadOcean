#pragma once

#include "stdafx.h"

class StorageScene : public LayerColor
{
private:
	//!< 애니메이션

public:
	Size winSize = Director::getInstance()->getWinSize();

	char asdf[255];

	int j[20];
	int mm;
	int mm2;
	char str[255];
	char str2[255];
	Sprite * Submarin;
	Sprite* m_material[20];
	Sprite* m_Sprite[20];
	Animate* m_Animate[20];
	Animation * m_Animation[20];
	LayerColor* m_layer[50];
	EventListenerTouchOneByOne * listener;
	LabelBMFont* m_label[20];

	int Umaterial_0;
	int Umaterial_1;
	int Umaterial_2;
	int Umaterial_3;
	int Umaterial_4;
	int Umaterial_5;
	int Umaterial_6;
	int Umaterial_7;


	Sprite* MakeParts1_[15];
	Sprite* MakeParts2_[15];
	Sprite* MakeParts3_[15];
	Sprite* MakeParts4_[15];
	Sprite* MakeParts5_[15];
	Sprite* MakeParts6_[15];

	Sprite* MaterialParts1_[15];
	Sprite* MaterialParts2_[15];
	Sprite* MaterialParts3_[15];
	Sprite* MaterialParts4_[15];
	Sprite* MaterialParts5_[15];
	Sprite* MaterialParts6_[15];

	Sprite* bar[3][10];
	Sprite* UPlvL[6];

	bool popup;


	static Scene* createScene();
	virtual bool init();
	void menuCloseCallback(Ref* pSender);
	void closeLayer6();

	bool Check[20];
	bool SelCheck[10];

	void Go_Back(Ref* pSender);
	void Go_Making(Ref* pSender);

	void Go_Rapid(Ref* pSender);
	void Go_Metal(Ref* pSender);
	void Go_Spread(Ref* pSender);

	void Go_Rader(Ref* pSender);
	void Go_Engine(Ref* pSender);
	void Go_Barrier(Ref* pSender);

	void PL1(Ref* pSender);
	void PL2(Ref* pSender);
	void PL3(Ref* pSender);
	void PL4(Ref* pSender);
	void PL5(Ref* pSender);
	void PL6(Ref* pSender);

	void make(Ref* pSender);
	void cancel(Ref* pSender);

	void SceneReload();





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
	CREATE_FUNC(StorageScene);
};