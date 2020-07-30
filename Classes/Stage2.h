#pragma once

#include "stdafx.h"

class Stage2 : public LayerColor
{
private:
	EventListenerTouchAllAtOnce *listener;

	Layer * BGLayer;
	Layer * UILayer;
	Layer * GameLayer;


	Label * label;
	Sprite * BG1;
	Sprite * BG2;
	Sprite * BG3;
	Sprite * BG4;
	Sprite * BG5;
	Sprite * BG6;
	Sprite * BG7;
	int nowMapNum;

	int NowAghiNum;
	int NowHapari_Top_Num;
	int NowHapari_Center_Num;
	int NowHapari_Bottom_Num;
	int NowJaponicaNum;
	int NowUpAghiNum;

	Sprite * Player_Life_BG;
	Sprite * Player_Life_Block;
	Sprite * Player_Life_Cover;



	Vector<Sprite*> v_Button;
	Vector<M_Aghi*> v_Aghi;
	Vector<M_Hapari*> v_Hapari;
	Vector<M_Japonica*> v_Japonica;
	Vector<M_UpAghi*> v_UpAghi;
	Vector<PauseLayer*> v_PauseLayer;
	Vector<TorpedoBoom*> v_TorpedoBoom;
	Vector<M_BigRobot*> v_BigRobot;
	Vector<Robot_Missail*> v_RobotMissail;
	Vector<M_BigRobot_Dead*> v_RobotDead;
	Vector<GameClearLayer*> v_GameClear;
	Vector<M_AttShip*> v_Attship;
	Vector<M_MiniOb*> v_MiniOb;
	Vector<M_FishHead*> v_FishHead;
	Vector<FishHead_Crash*> v_Crash;
	Vector<FishHead_Rain*> v_Rain;
	Vector<FishHead_Dead*> v_FishHeadDead;
	Vector<FishHead_Hurricane*> v_Hurricane;
	Vector<FishHead_Roar*> v_Roar;

	float sceenS = 0.0f;
	float m_CameraSpeed;
	float GameTime;
	JoyStick * Stick;
	bool nowJoystickOn = false;
	bool n_CameraMoving;
	bool n_pause;
	bool GameOver;
	bool Boss;
	bool n_GameClear;
	Vec2 NowMovingPos;

	float Player_Life;
	int Player_Torpedo;
	LabelBMFont * TorpedoNumL;
	String * TorpedoNumS;
	LabelBMFont * ScoreLabel;
	String * ScoreString;

	int GameScore;
	float PlayTime;
	int Coin;
	int Item1;
	int Item2;
	int Item1Num;
	int Item2Num;

	int KeyPath;

	//vector<float> v_MapPosX;

	CPNCamera * BG_Camera;

	Sprite * UI_TorpedoButton;
	Sprite * UI_PauseButton;

	vector<float> f_AghiMake;
	vector<float> f_Hapari_Top_Make;
	vector<float> f_Hapari_Center_Make;
	vector<float> f_Hapari_Bottom_Make;
	vector<float> f_JaponicaMake;
	vector<float> f_UpAghiMake;
	vector<float> f_AttShipMake;
	vector<float> f_MiniObMake;
	vector<float> f_RobotMake;
	vector<float> f_FishHeadMake;

	vector<int> Hapari_Top;
	vector<int> Hapari_Center;
	vector<int> Hapari_Bottom;

	vector<Vec2>  MakeAghiPos;
	vector<Vec2> MakeHapari_Top_Pos;
	vector<Vec2> MakeHapari_Center_Pos;
	vector<Vec2> MakeHapari_Bottom_Pos;
	vector<Vec2> MakeJaponicaPos;
	vector<Vec2> MakeUpAghiPos;
	vector<Vec2> MakeAttShipPos;
	vector<Vec2> MakeMiniObPos;


	void m_mapEdit();

public:
	//Vector<MonsterMissail*>
	MySubmarin * SubMarin;
	Vector<MonsterMissail*> v_MonMissail;
	Vector<MonsterRazer*> v_MonRazer;

	static Scene* createScene();
	virtual bool init();
	void menuCloseCallback(Ref* pSender);

	void pauseRecursive(Node * node, bool pause);

	void Update(float dt);
	void MakeUpdate(float dt);
	void MonsterSollisionUpdate();

	void MakingInit();
	void MakePosInit();
	void MakeAghi(Vec2 Pos);
	void MakeHapari(Vec2 Pos, int num);
	void MakeJaponica(Vec2 Pos);
	void MakeUpAghi(Vec2 Pos);
	void MakeAttShip(Vec2 Pos);
	void MakeMiniOb(Vec2 Pos);
	void MakeBigRobot(Vec2 Pos);
	void MakeCrab_Hapari();
	void MakeFishHead(Vec2 Pos);

	void BoomAghi(Vec2 Pos);
	void BoomHapari(Vec2 Pos);
	void BoomJaponica(Vec2 Pos);
	void BoomUpAghi(Vec2 Pos);
	void BoomAttship(Vec2 Pos);
	void BoomMiniOb(Vec2 Pos);
	void BoomBigRobot(Vec2 Pos);
	void BoomFishHead(Vec2 Pos);

	void SubmarinUpdate(float dt);
	void MonsterUpdate(float dt);
	void Sol_Missail(float dt);
	void Sol_Torpedo(float dt);
	void Sol_Torpedo_Boom(float dt);

	void TorButtonEffect();

	void SubHit();

	void GameClear();
	void GAmeClearAndScene();

	bool CircleSollision(Vec2 Pos1, Vec2 Pos2, float radi1, float radi2);
	CREATE_FUNC(Stage2);



	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event);
};