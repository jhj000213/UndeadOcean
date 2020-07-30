#include "stdafx.h"

Scene* Stage1::createScene()
{
	auto scene = Scene::create();
	auto layer = Stage1::create();
	scene->addChild(layer);
	return scene;
}


bool Stage1::init()
{

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
		return false;



	BGLayer = Layer::create();
	this->addChild(BGLayer, 0);
	GameLayer = Layer::create();
	this->addChild(GameLayer, 100);
	UILayer = Layer::create();
	this->addChild(UILayer, 150);



	if (Bgm_Sound[0] == AudioEngine::INVALID_AUDIO_ID)
	{
		Bgm_Sound[0] = AudioEngine::play2d("sound/bgm/stage1.mp3", true, Volume);
	}

	Stick = JoyStick::n_create(Vec2(200, 200), UILayer);
	Stick->j_setOpacity(0);
	UILayer->addChild(Stick, 10);



	UI_PauseButton = Sprite::create("pausebutton.png");
	UI_PauseButton->setPosition(Vec2(1180, 670));
	UILayer->addChild(UI_PauseButton);
	v_Button.pushBack(UI_PauseButton);

	if (TurnControl == false)
	{
		UI_TorpedoButton = Sprite::create("submarin/button/torpedobutton.png");
		UI_TorpedoButton->setPosition(Vec2(1150, 100));
		UILayer->addChild(UI_TorpedoButton);
		v_Button.pushBack(UI_TorpedoButton);
	}
	else
	{
		UI_TorpedoButton = Sprite::create("submarin/button/torpedobutton.png");
		UI_TorpedoButton->setPosition(Vec2(130, 100));
		UILayer->addChild(UI_TorpedoButton);
		v_Button.pushBack(UI_TorpedoButton);
	}


	Player_Life_BG = Sprite::create("submarin/hp_bar.png");
	Player_Life_BG->setPosition(Vec2(230, 650));
	UILayer->addChild(Player_Life_BG, 100);

	Player_Life_Block = Sprite::create("submarin/hp_gaze.png");
	Player_Life_Block->setPosition(Vec2(230, 650));
	UILayer->addChild(Player_Life_Block, 150);

	Player_Life_Cover = Sprite::create("submarin/hp_cover.png");
	Player_Life_Cover->setAnchorPoint(Vec2(1, 0.5));
	Player_Life_Cover->setScaleX(0);
	Player_Life_Cover->setPosition(Vec2(410, 650));
	UILayer->addChild(Player_Life_Cover, 151);

	TorpedoNumL = LabelBMFont::create("3", "fonts/undeadfont.fnt");
	TorpedoNumL->setPosition(UI_TorpedoButton->getPositionX() + 60, UI_TorpedoButton->getPositionY() + 60);
	UILayer->addChild(TorpedoNumL, 105);

	ScoreLabel = LabelBMFont::create("0", "fonts/undeadfont.fnt");
	ScoreLabel->setAnchorPoint(Vec2(0, 1));
	ScoreLabel->setScale(1.6f);
	ScoreLabel->setPosition(Vec2(50,620));
	UILayer->addChild(ScoreLabel, 105);

	SubMarin = MySubmarin::n_create(Vec2(120, D_DESIGN_HEIGHT / 2), GameLayer, &v_TorpedoBoom,nowSubmarinFrame);
	SubMarin->setPosition(120, D_DESIGN_HEIGHT / 2);
	SubMarin->setScaleX(-1.0f);
	GameLayer->addChild(SubMarin, 1);

	BG_Camera = new CPNCamera();
	BG_Camera->init(BGLayer, Size(D_DESIGN_WIDTH * 3, D_DESIGN_HEIGHT), Size(D_DESIGN_WIDTH, D_DESIGN_HEIGHT));




	MakePosInit();


	m_mapEdit();

	n_CameraMoving = true;
	GameOver = false;
	Boss = false;////sadfasdfasdfasdfasdfdsafd
	n_pause = false;
	n_GameClear = false;
	NowAghiNum = 0;
	NowHapari_Top_Num = 0;
	NowHapari_Center_Num = 0;
	NowHapari_Bottom_Num = 0;
	NowJaponicaNum = 0;
	NowUpAghiNum = 0;
	GameScore = 0;
	KeyPath = 0;
	Player_Life = 100.0f;
	m_CameraSpeed = 30.0f;
	Player_Torpedo = 3;
	GameTime = 0.0f;
	PlayTime = 0.0f;

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Stage1::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Stage1::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Stage1::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(Stage1::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(Stage1::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	schedule(schedule_selector(Stage1::MakeUpdate), 0.0f);
	schedule(schedule_selector(Stage1::Update), 0.0f);


	MakingInit();

	return true;
}

void Stage1::MakePosInit()
{
	Hapari_Top.push_back(1);
	Hapari_Top.push_back(1);
	Hapari_Top.push_back(1);
	Hapari_Top.push_back(1);
	Hapari_Top.push_back(1);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(2);
	Hapari_Top.push_back(3);
	Hapari_Top.push_back(3);
	Hapari_Top.push_back(3);
	Hapari_Top.push_back(3);
	Hapari_Top.push_back(3);
	Hapari_Top.push_back(4);
	Hapari_Top.push_back(4);
	Hapari_Top.push_back(4);
	Hapari_Top.push_back(4);
	Hapari_Top.push_back(4);


	Hapari_Center.push_back(5);
	Hapari_Center.push_back(10);
	Hapari_Center.push_back(5);
	Hapari_Center.push_back(10);
	Hapari_Center.push_back(5);


	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(7);
	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(7);
	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(7);
	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(7);
	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(7);
	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(6);
	Hapari_Bottom.push_back(8);
	Hapari_Bottom.push_back(8);
	Hapari_Bottom.push_back(8);
	Hapari_Bottom.push_back(8);
	Hapari_Bottom.push_back(8);
	Hapari_Bottom.push_back(9);
	Hapari_Bottom.push_back(9);
	Hapari_Bottom.push_back(9);
	Hapari_Bottom.push_back(9);
	Hapari_Bottom.push_back(9);


	MakeAghiPos.push_back(Vec2(1380, 360));
	MakeAghiPos.push_back(Vec2(1380, 240));
	MakeAghiPos.push_back(Vec2(1380, 480));
	MakeAghiPos.push_back(Vec2(1380, 240));
	MakeAghiPos.push_back(Vec2(1380, 480));
	MakeAghiPos.push_back(Vec2(1380, 360));
	MakeAghiPos.push_back(Vec2(1380, 240));
	MakeAghiPos.push_back(Vec2(1380, 480));
	MakeAghiPos.push_back(Vec2(1380, 360));
	MakeAghiPos.push_back(Vec2(1380, 240));
	MakeAghiPos.push_back(Vec2(1380, 480));


	MakeHapari_Top_Pos.push_back(Vec2(440, 740));
	MakeHapari_Top_Pos.push_back(Vec2(440, 740));
	MakeHapari_Top_Pos.push_back(Vec2(440, 740));
	MakeHapari_Top_Pos.push_back(Vec2(440, 740));
	MakeHapari_Top_Pos.push_back(Vec2(440, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(640, 740));
	MakeHapari_Top_Pos.push_back(Vec2(1280, 740));
	MakeHapari_Top_Pos.push_back(Vec2(1280, 740));
	MakeHapari_Top_Pos.push_back(Vec2(1280, 740));
	MakeHapari_Top_Pos.push_back(Vec2(1280, 740));
	MakeHapari_Top_Pos.push_back(Vec2(1280, 740));
	MakeHapari_Top_Pos.push_back(Vec2(960, 740));
	MakeHapari_Top_Pos.push_back(Vec2(960, 740));
	MakeHapari_Top_Pos.push_back(Vec2(960, 740));
	MakeHapari_Top_Pos.push_back(Vec2(960, 740));
	MakeHapari_Top_Pos.push_back(Vec2(960, 740));


	MakeHapari_Center_Pos.push_back(Vec2(1320, 360));
	MakeHapari_Center_Pos.push_back(Vec2(1320, 360));
	MakeHapari_Center_Pos.push_back(Vec2(1320, 360));
	MakeHapari_Center_Pos.push_back(Vec2(1320, 360));
	MakeHapari_Center_Pos.push_back(Vec2(1320, 360));


	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));//

	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(640, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(1280, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(1280, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(1280, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(1280, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(1280, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(960, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(960, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(960, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(960, -20));
	MakeHapari_Bottom_Pos.push_back(Vec2(960, -20));


	MakeJaponicaPos.push_back(Vec2(1380, 240));
	MakeJaponicaPos.push_back(Vec2(1380, 480));
	MakeJaponicaPos.push_back(Vec2(1380, 180));
	MakeJaponicaPos.push_back(Vec2(1380, 360));
	MakeJaponicaPos.push_back(Vec2(1380, 540));

	MakeJaponicaPos.push_back(Vec2(1380, 180));
	MakeJaponicaPos.push_back(Vec2(1380, 540));
	MakeJaponicaPos.push_back(Vec2(1380, 240));
	MakeJaponicaPos.push_back(Vec2(1380, 480));


	MakeUpAghiPos.push_back(Vec2(600, -100));
	MakeUpAghiPos.push_back(Vec2(400, -100));
	MakeUpAghiPos.push_back(Vec2(200, -100));
	MakeUpAghiPos.push_back(Vec2(320, -100));
	MakeUpAghiPos.push_back(Vec2(400, -100));
	MakeUpAghiPos.push_back(Vec2(480, -100));
}

void Stage1::MakingInit()
{
	if (Boss == false)
	{
		f_AghiMake.push_back(16.0f);
		f_AghiMake.push_back(17.0f);
		f_AghiMake.push_back(17.0f);
		f_AghiMake.push_back(35.0f);
		f_AghiMake.push_back(35.0f);

		f_Hapari_Top_Make.push_back(10.0f);//일렬로 U자형 오른쪽으로 감
		f_Hapari_Top_Make.push_back(10.4f);
		f_Hapari_Top_Make.push_back(10.8f);
		f_Hapari_Top_Make.push_back(11.2f);
		f_Hapari_Top_Make.push_back(11.6f);

		f_Hapari_Top_Make.push_back(12.0f);//일렬로 |형
		f_Hapari_Top_Make.push_back(12.4f);
		f_Hapari_Top_Make.push_back(12.8f);
		f_Hapari_Top_Make.push_back(13.2f);
		f_Hapari_Top_Make.push_back(13.6f);

		f_Hapari_Top_Make.push_back(24.0f);//일렬로 \형
		f_Hapari_Top_Make.push_back(24.4f);
		f_Hapari_Top_Make.push_back(24.8f);
		f_Hapari_Top_Make.push_back(25.2f);
		f_Hapari_Top_Make.push_back(25.6f);

		f_Hapari_Top_Make.push_back(28.4f);//한마리씩 \형
		f_Hapari_Top_Make.push_back(29.0f);
		f_Hapari_Top_Make.push_back(29.6f);
		f_Hapari_Top_Make.push_back(30.2f);

		f_Hapari_Top_Make.push_back(40.0f);//일렬로 /형
		f_Hapari_Top_Make.push_back(40.4f);
		f_Hapari_Top_Make.push_back(40.8f);
		f_Hapari_Top_Make.push_back(41.2f);
		f_Hapari_Top_Make.push_back(41.6f);

		f_Hapari_Bottom_Make.push_back(11.0f);
		f_Hapari_Bottom_Make.push_back(11.4f);
		f_Hapari_Bottom_Make.push_back(11.8f);
		f_Hapari_Bottom_Make.push_back(12.2f);
		f_Hapari_Bottom_Make.push_back(12.6f);

		f_Hapari_Bottom_Make.push_back(20.0f);//일렬로 n자로 왼쪽으로 감
		f_Hapari_Bottom_Make.push_back(20.0f);///일렬로 /형
		f_Hapari_Bottom_Make.push_back(20.4f);
		f_Hapari_Bottom_Make.push_back(20.4f);
		f_Hapari_Bottom_Make.push_back(20.8f);
		f_Hapari_Bottom_Make.push_back(20.8f);
		f_Hapari_Bottom_Make.push_back(21.2f);
		f_Hapari_Bottom_Make.push_back(21.2f);
		f_Hapari_Bottom_Make.push_back(21.6f);
		f_Hapari_Bottom_Make.push_back(21.6f);


		f_Hapari_Bottom_Make.push_back(34.0f);
		f_Hapari_Bottom_Make.push_back(34.4f);
		f_Hapari_Bottom_Make.push_back(34.8f);
		f_Hapari_Bottom_Make.push_back(35.2f);

		f_Hapari_Bottom_Make.push_back(40.0f);
		f_Hapari_Bottom_Make.push_back(40.4f);
		f_Hapari_Bottom_Make.push_back(40.8f);
		f_Hapari_Bottom_Make.push_back(41.2f);
		f_Hapari_Bottom_Make.push_back(41.6f);




		f_Hapari_Center_Make.push_back(25.0f);
		f_Hapari_Center_Make.push_back(25.4f);
		f_Hapari_Center_Make.push_back(25.8f);
		f_Hapari_Center_Make.push_back(26.2f);
		f_Hapari_Center_Make.push_back(26.6f);

		

		f_JaponicaMake.push_back(14.0f);
		f_JaponicaMake.push_back(14.0f);

		f_JaponicaMake.push_back(32.0f);
		f_JaponicaMake.push_back(32.0f);
		f_JaponicaMake.push_back(32.0f);

		f_MiddleShipMake.push_back(47.0f);

		f_UpAghiMake.push_back(26.0f);
		f_UpAghiMake.push_back(27.0f);
		f_UpAghiMake.push_back(28.0f);
	}
	else
	{
		f_AghiMake.push_back(8.0f);
		f_AghiMake.push_back(14.0f);
		f_AghiMake.push_back(14.0f);
		f_AghiMake.push_back(16.0f);
		f_AghiMake.push_back(30.0f);
		f_AghiMake.push_back(30.0f);

	
		f_JaponicaMake.push_back(5.0f);
		f_JaponicaMake.push_back(5.0f);

		f_JaponicaMake.push_back(26.0f);
		f_JaponicaMake.push_back(26.0f);

		f_UpAghiMake.push_back(18.0f);
		f_UpAghiMake.push_back(20.6f);
		f_UpAghiMake.push_back(23.0f);

		f_CrabMake.push_back(40.0f);
	}

}

void Stage1::MakeUpdate(float dt)
{
	GameTime += dt;
	log("Time : %f", GameTime);
	if (f_AghiMake.empty() == false)
	{
		for (float time : f_AghiMake)
		{
			if (time <= GameTime)
			{
				MakeAghi(MakeAghiPos.front());
				MakeAghiPos.erase(MakeAghiPos.begin());
				f_AghiMake.erase(f_AghiMake.begin());
				break;
			}
		}
	}
	if (f_Hapari_Top_Make.empty() == false)
	{
		for (float time : f_Hapari_Top_Make)
		{
			if (time <= GameTime)
			{
				if (MakeHapari_Top_Pos.empty() == false)
				{
					MakeHapari(MakeHapari_Top_Pos.front(), Hapari_Top.front());
					Hapari_Top.erase(Hapari_Top.begin());
					MakeHapari_Top_Pos.erase(MakeHapari_Top_Pos.begin());
					f_Hapari_Top_Make.erase(f_Hapari_Top_Make.begin());
					break;
				}
				
			}
		}
	}
	if (f_Hapari_Center_Make.empty() == false)
	{
		for (float time : f_Hapari_Center_Make)
		{
			if (time <= GameTime)
			{
				if (MakeHapari_Center_Pos.empty() == false)
				{
					MakeHapari(MakeHapari_Center_Pos.front(), Hapari_Center[NowHapari_Center_Num]);
					Hapari_Center.erase(Hapari_Center.begin());
					MakeHapari_Center_Pos.erase(MakeHapari_Center_Pos.begin());
					f_Hapari_Center_Make.erase(f_Hapari_Center_Make.begin());
					break;
				}
			}
		}
	}
	if (f_Hapari_Bottom_Make.empty() == false)
	{
		for (float time : f_Hapari_Bottom_Make)
		{
			if (time <= GameTime)
			{
				if (MakeHapari_Bottom_Pos.empty() == false)
				{
					MakeHapari(MakeHapari_Bottom_Pos.front(), Hapari_Bottom[NowHapari_Bottom_Num]);
					Hapari_Bottom.erase(Hapari_Bottom.begin());
					MakeHapari_Bottom_Pos.erase(MakeHapari_Bottom_Pos.begin());
					f_Hapari_Bottom_Make.erase(f_Hapari_Bottom_Make.begin());
					break;
				}
			}
		}
	}
	if (f_JaponicaMake.empty() == false)
	{
		for (float time : f_JaponicaMake)
		{
			if (time <= GameTime)
			{
				MakeJaponica(MakeJaponicaPos.front());
				MakeJaponicaPos.erase(MakeJaponicaPos.begin());
				f_JaponicaMake.erase(f_JaponicaMake.begin());
				break;
			}
		}
	}
	if (f_UpAghiMake.empty() == false)
	{
		for (float time : f_UpAghiMake)
		{
			if (time <= GameTime)
			{
				MakeUpAghi(MakeUpAghiPos.front());
				MakeUpAghiPos.erase(MakeUpAghiPos.begin());
				NowUpAghiNum++;
				f_UpAghiMake.erase(f_UpAghiMake.begin());
				break;
			}
		}
	}
	if (f_MiddleShipMake.empty() == false)
	{
		for (float time : f_MiddleShipMake)
		{
			if (time <= GameTime)
			{
				MakeMiddleShip(Vec2(1500, 360));
				f_MiddleShipMake.erase(f_MiddleShipMake.begin());
				break;
			}
		}
	}
	if (f_CrabMake.empty() == false)
	{
		for (float time : f_CrabMake)
		{
			if (time <= GameTime)
			{
				MakeCrab(Vec2(1500, 360));
				m_CameraSpeed = 40.0f;
				f_CrabMake.erase(f_CrabMake.begin());
				break;
			}
		}
	}
	
}

void Stage1::Update(float dt)
{
	if (KeyPath == 11)
	{
		MakeAghi(Vec2(1380, 480));
		MakeAghi(Vec2(1380, 240));
		KeyPath = 0;
	}
	if (KeyPath == 12)
	{
		MakeUpAghi(Vec2(600,-100));
		MakeUpAghi(Vec2(400, -100));
		KeyPath = 0;
	}
	if (KeyPath == 13)
	{
		MakeJaponica(Vec2(1380, 240));
		MakeJaponica(Vec2(1380, 480));
		KeyPath = 0;
	}
	if (KeyPath == 14)
	{
		MakeMiddleShip(Vec2(1500, 360));
		KeyPath = 0;
	}
	if (KeyPath == 15)
	{
		MakeCrab(Vec2(1500, 360));
		KeyPath = 0;
	}


	PlayTime += dt;
	BG_Camera->update((sceenS += dt * m_CameraSpeed));

	//
	TorpedoNumS = String::createWithFormat("x %d", Player_Torpedo);
	TorpedoNumL->setString(TorpedoNumS->getCString());
	ScoreString = String::createWithFormat("%d", GameScore);
	ScoreLabel->setString(ScoreString->getCString());
	//
	for (int i = 0; i < BGM_SOUND_NUM; i++)
	{
		AudioEngine::setVolume(Bgm_Sound[i], Volume);
		//log("%f vol", Volume);
	}

	SubmarinUpdate(dt);
	MonsterUpdate(dt);

	Sol_Missail(dt);
	Sol_Torpedo(dt);
	Sol_Torpedo_Boom(dt);
}

void Stage1::SubmarinUpdate(float dt)
{
	if (Player_Life <= 0.0f)
		Player_Life = 0.0f;
	Player_Life_Cover->setScaleX((Player_Life - 100.0f)/-100.0f);////////////
	
	if (Player_Life <= 0)
	{


		if (GameOver == false)
		{
			ChangeBgm = true;
			Director::getInstance()->getTextureCache()->reloadAllTextures();

			MapCode = 3;
			Scene *scene = BlackScene::createScene();
			scene = TransitionCrossFade::create(0.3f, scene);
			Director::sharedDirector()->replaceScene(scene);
		}
		GameOver = true;
	}



	if (SubMarin->s_Moving == true)
	{
		SubMarin->s_Speed += dt;
	}
	SubMarin->n_update(dt);
	//log("%d", nowJoystickOn);
	if (nowJoystickOn)
	{
		Vec2 SomePos = Stick->j_update(NowMovingPos, SubMarin->s_Speed);

		float dx = SubMarin->s_getPosition().x + SomePos.x;
		float dy = SubMarin->s_getPosition().y + SomePos.y;
		//log("SubPos : X = %f Y = %f", SubMarin->s_getPosition().x, SubMarin->s_getPosition().y);
		//log("%f. %f", dx, dy);
		if (!(SubMarin->s_ScreenSollisionX(dx)))
			SubMarin->s_setPositionX(dx);
		if (!(SubMarin->s_ScreenSollisionY(dy)))
			SubMarin->s_setPositionY(dy);

	}
}

void Stage1::MonsterUpdate(float dt)
{
	if (v_GameClear.empty() == false)
	{
		for (GameClearLayer * layer : v_GameClear)
		{
			layer->m_update(dt);
		}
	}
	if (v_Aghi.empty() == false)
	{
		for (M_Aghi * Mon : v_Aghi)
		{
			Mon->m_update(dt);
			if (Mon->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_MiddleShip.empty() == false)
	{
		for (M_middleShip * Mon : v_MiddleShip)
		{
			Mon->m_update(dt, KeyPath);
			if (KeyPath != 0)
				KeyPath = 0;
			if (Mon->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_Hapari.empty() == false)
	{
		for (M_Hapari * Mon : v_Hapari)
		{
			Mon->m_update(dt, SubMarin->s_getPosition());
			if (Mon->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_MiddleShip_2.empty() == false)
	{
		for (M_MiddleShip_2 * Mon : v_MiddleShip_2)
		{
			Mon->m_update(dt, KeyPath);
			if (KeyPath != 0)
				KeyPath = 0;

		}
	}
	if (v_MiniOb.empty() == false)
	{
		for (M_MiniOb * Mob : v_MiniOb)
		{
			Mob->m_update(dt, SubMarin->s_getPosition());
			if (Mob->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_Japonica.empty() == false)
	{
		for (M_Japonica * Mob : v_Japonica)
		{
			Mob->m_update(dt);
			if (Mob->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_UpAghi.empty() == false)
	{
		for (M_UpAghi * Mon : v_UpAghi)
		{
			Mon->m_update(dt);
			if (Mon->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();//
			}
		}
	}
	if (v_CrabWave.empty() == false)
	{
		for (Crab_Wave * Wave : v_CrabWave)
		{
			if (Wave->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	
	if (v_CrabThorn.empty() == false)
	{
		for (Crab_Thorn * Wave : v_CrabThorn)
		{
			if (Wave->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}

	if (v_MiddleShip_Dead.empty() == false)
	{
		for (M_MiddleShipDead * Mon : v_MiddleShip_Dead)
		{
			Mon->m_update(dt);
			if (Mon->Dead == true)
			{
				GameLayer->removeChild(Mon);
				v_MiddleShip_Dead.eraseObject(Mon);
				break;
			}
		}
	}
	if (v_CrabDead.empty() == false)
	{
		for (Crab_Dead * Mon : v_CrabDead)
		{
			Mon->m_update(dt);
			if (Mon->Dead == true)
			{
				GameLayer->removeChild(Mon);
				v_CrabDead.eraseObject(Mon);
				break;
			}
		}
	}
	
	if (v_Crab.empty() == false)
	{
		for (M_Crab * Mon : v_Crab)
		{
			Mon->m_update(dt, SubMarin->s_getPosition(),KeyPath);
			if (KeyPath != 0)
				KeyPath = 0;
			if (Mon->MakeHapari == true)
			{
				auto ac1 = CallFunc::create(CC_CALLBACK_0(Stage1::MakeCrab_Hapari, this));
				auto seq = Sequence::create(ac1, DelayTime::create(0.3f), NULL);
				this->runAction(Repeat::create(seq, 6));

				Mon->MakeHapari = false;
			}
			if (Mon->CanMove == false)
				m_CameraSpeed = 0.0f;
		}
	}
	if (v_CrabShild.empty() == false)
	{
		for (M_CrabShild * Mon : v_CrabShild)
		{
			Mon->m_update(dt);
		}
	}
	if (v_CrabWave.empty() == false)
	{
		for (Crab_Wave * wave : v_CrabWave)
		{
			wave->m_update(dt);
		}
	}
	if (v_CrabThorn.empty() == false)
	{
		for (Crab_Thorn * wave : v_CrabThorn)
		{
			wave->m_update(dt);
		}
	}
	
	if (v_ShildBreak.empty() == false)
	{
		for (ShildBreak * Mon : v_ShildBreak)
		{
			Mon->m_update(dt);
			if (Mon->Dead == true)
			{
				GameLayer->removeChild(Mon);
				v_ShildBreak.eraseObject(Mon);
				break;
			}
		}
	}
	


	if (v_MonMissail.empty() == false)
	{
		for (MonsterMissail * mm : v_MonMissail)
		{
			mm->m_update(dt);

			if (v_TorpedoBoom.empty() == false)
			{
				bool bre = false;

				for (TorpedoBoom * boom : v_TorpedoBoom)
				{
					if (boom->m_getRect().intersectsRect(mm->m_getRect()))
					{
						GameLayer->removeChild(mm, true);
						v_MonMissail.eraseObject(mm);
						bre = true;
						break;
					}

				}
				if (bre == true)
					break;
			}
			if (mm->m_getPosition().x + mm->MissailWidth <= 0)
			{
				GameLayer->removeChild(mm, true);
				v_MonMissail.eraseObject(mm);
				break;
			}
			else if (mm->m_getPosition().x - mm->MissailWidth >= D_DESIGN_WIDTH)
			{
				GameLayer->removeChild(mm, true);
				v_MonMissail.eraseObject(mm);
				break;
			}
			else if (mm->m_getPosition().y + mm->MissailWidth <= 0)
			{
				GameLayer->removeChild(mm, true);
				v_MonMissail.eraseObject(mm);
				break;
			}
			else if (mm->m_getPosition().y - mm->MissailWidth >= D_DESIGN_HEIGHT)
			{
				GameLayer->removeChild(mm, true);
				v_MonMissail.eraseObject(mm);
				break;
			}
		}
	}
	if (v_MonRazer.empty() == false)
	{
		for (MonsterRazer * MR : v_MonRazer)
		{
			MR->m_update(dt);
			if (MR->del == true)
			{
				v_MonRazer.eraseObject(MR);

				break;
			}
		}
	}

	if (v_MonRazer.empty() == false)
	{
		for (MonsterRazer * MR : v_MonRazer)
		{
			if (MR->m_sollisionCheck() == true &&
				SubMarin->s_getRect().intersectsRect(MR->m_getRect()))
			{
				if (MR->getParent() != NULL)
				{
					if (SubMarin->s_getStrong() == false)
					{
						Player_Life -= 35.0f;
						SubMarin->s_hitting();
						break;
					}
				}
			}
		}
	}
	if (v_MonMissail.empty() == false)
	{
		for (MonsterMissail * MM : v_MonMissail)
		{
			if (CircleSollision(SubMarin->s_getPosition(), MM->m_getPosition(),
				SubMarin->HackWidth,
				MM->MissailWidth))
			{
				if (SubMarin->s_getStrong() == false)
				{
					SubHit();
					GameLayer->removeChild(MM, true);
					v_MonMissail.eraseObject(MM);
					break;
				}

			}

		}
	}

}

void Stage1::Sol_Missail(float dt)
{
	for (MyMissail * v_Missail : SubMarin->AirGun)
	{
		if (v_Missail->m_getPositionX() >= D_DESIGN_WIDTH + v_Missail->Missail->boundingBox().size.width / 2)
		{

			SubMarin->AirGun.eraseObject(v_Missail);
			break;
		}//  out Window



		if (v_Aghi.empty() == false)//   hit
		{
			bool bre = false;

			for (M_Aghi * ag : v_Aghi)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Dmg(SubMarin->MissailDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomAghi(ag->m_getPosition());
						v_Aghi.eraseObject(ag);
						GameLayer->removeChild(ag, true);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;

		}
		if (v_UpAghi.empty() == false)//   hit
		{
			bool bre = false;

			for (M_UpAghi * ag : v_UpAghi)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Dmg(SubMarin->MissailDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomUpAghi(ag->m_getPosition());
						v_UpAghi.eraseObject(ag);
						GameLayer->removeChild(ag, true);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;

		}

		if (v_MiddleShip.empty() == false)//   hit
		{
			bool bre = false;
			for (M_middleShip * ag : v_MiddleShip)
			{
				if (ag->v_MSB.empty() == false)
				{
					for (MiddleShip_Boom * MS : ag->v_MSB)
					{
						if (v_Missail->m_getRect().intersectsRect(MS->m_getRect()))
						{
							v_Missail->m_boomEffect();
							v_Missail->m_setPosition(Vec2(8000, 8000));
							SubMarin->AirGun.eraseObject(v_Missail);
							MS->m_Dmg(SubMarin->MissailDamege);
							MS->m_sollision();
							if (MS->M_HP <= 0)
							{
								BoomMiniOb(MS->m_getPosition());
								ag->v_MSB.eraseObject(MS);
								GameLayer->removeChild(MS, true);
							}
							bre = true;
							break;
						}
					}
					if (bre == true)
						break;
				}
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Dmg(SubMarin->MissailDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						Vec2 Pos = ag->Mother->getPosition();
						while (ag->v_MSB.empty() == false)
						{
							MiddleShip_Boom * MS = ag->v_MSB.front();
							BoomMiniOb(MS->m_getPosition());
							ag->v_MSB.eraseObject(MS);
							GameLayer->removeChild(MS, true);
						}

						v_MiddleShip.eraseObject(ag);
						GameLayer->removeChild(ag, true);

						//페이즈 전환
						M_MiddleShip_2 * Mon = M_MiddleShip_2::m_create(Vec2(Pos.x + 50, Pos.y - 25), GameLayer, &v_MonMissail, &v_MonRazer);
						v_MiddleShip_2.pushBack(Mon);
						GameLayer->addChild(Mon);
					}
					bre = true;
					break;
				}
			}
			if (bre == true)
				break;
		}

		if (v_MiddleShip_2.empty() == false)
		{
			bool bre = false;
			for (M_MiddleShip_2 * ag : v_MiddleShip_2)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()) && ag->Changeing == false)
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Dmg(SubMarin->MissailDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomMiddleShip(ag->m_getPosition());
						ag->removeAllChildren();
						v_MiddleShip_2.eraseObject(ag);
						GameLayer->removeChild(ag, false);
						Boss = true;
						MakingInit();
						GameTime = 0.0f;
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_Hapari.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Hapari * ag : v_Hapari)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Dmg(SubMarin->MissailDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomHapari(ag->m_getPosition());
						ag->removeAllChildren();
						v_Hapari.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_MiniOb.empty() == false)//   hit
		{
			bool bre = false;
			for (M_MiniOb * ag : v_MiniOb)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Dmg(SubMarin->MissailDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomMiniOb(ag->m_getPosition());
						ag->removeAllChildren();
						v_MiniOb.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}
		if (v_Japonica.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Japonica * ag : v_Japonica)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Dmg(SubMarin->MissailDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomJaponica(ag->m_getPosition());
						ag->removeAllChildren();
						v_Japonica.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}
		if (v_CrabShild.empty() == false)//   hit
		{
			bool bre = false;
			for (M_CrabShild * ag : v_CrabShild)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{
					AudioEngine::play2d("sound/effect/missailhit_shild.mp3", false, EffVolume/0.5f);
					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Dmg(SubMarin->MissailDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomShild(ag->m_getPosition());
						ag->removeAllChildren();
						v_CrabShild.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_Crab.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Crab * ag : v_Crab)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getHandRect()) && ag->HandDead == false)
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Hand_Dmg(SubMarin->MissailDamege);
					ag->m_handsollision();
					if (ag->M_Hand_HP <= 0)
					{
						ag->M_Body_HP -= 1500;
						GameScore += 20000;
						ag->HandDead = true;
						ag->m_setOpacityLaw();
						ag->m_BoomHand();
						//파트 죽는곳
						//ag->removeAllChildren();
						//v_Crab.eraseObject(ag);
						//GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}
				else if (v_Missail->m_getRect().intersectsRect(ag->m_getLegRect()) && ag->LegDead == false)
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Leg_Dmg(SubMarin->MissailDamege);
					ag->m_legsollision();
					if (ag->M_Leg_HP <= 0)
					{
						ag->M_Body_HP -= 1500;
						GameScore += 30000;
						m_CameraSpeed = 0.0f;
						ag->LegDead = true;
						ag->m_setOpacityLaw();
						ag->m_BoomLeg();
						//파트 죽는곳
						//ag->removeAllChildren();
						//v_Crab.eraseObject(ag);
						//GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}
				else if (v_Missail->m_getRect().intersectsRect(ag->m_getBodyRect()))
				{

					v_Missail->m_boomEffect();
					v_Missail->m_setPosition(Vec2(8000, 8000));
					SubMarin->AirGun.eraseObject(v_Missail);
					ag->m_Body_Dmg(SubMarin->MissailDamege);
					ag->m_bodysollision();
					if (ag->M_Body_HP <= 0)
					{
						if (ag->LegDead == false)
						{
							ag->m_BoomLeg();
						}
						if (ag->HandDead == false)
						{
							ag->m_BoomHand();
						}
						//파트 죽는곳
						m_CameraSpeed = 0.0f;
						BoomCrab(ag->m_getPosition());//
						ag->removeAllChildren();
						v_Crab.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}


	}
}

void Stage1::Sol_Torpedo(float dt)
{
	for (MyTorpedo * v_Missail : SubMarin->v_Torpedo)
	{


		if (v_Aghi.empty() == false)//   hit
		{
			bool bre = false;

			for (M_Aghi * ag : v_Aghi)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));


					bre = true;
					break;
				}

			}
			if (bre == true)
				break;

		}
		if (v_UpAghi.empty() == false)//   hit
		{
			bool bre = false;

			for (M_UpAghi * ag : v_UpAghi)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));


					bre = true;
					break;
				}

			}
			if (bre == true)
				break;

		}

		if (v_MiddleShip.empty() == false)//   hit
		{
			bool bre = false;
			for (M_middleShip * ag : v_MiddleShip)
			{
				if (ag->v_MSB.empty() == false)
				{
					for (MiddleShip_Boom * MS : ag->v_MSB)
					{
						if (v_Missail->m_getRect().intersectsRect(MS->m_getRect()))
						{
							v_Missail->m_createBoom();
							v_Missail->m_setPosition(Vec2(8000, 8000));


							bre = true;
							break;
						}
					}
					if (bre == true)
						break;
				}
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));


					bre = true;
					break;
				}
			}
			if (bre == true)
				break;
		}

		if (v_MiddleShip_2.empty() == false)
		{
			bool bre = false;
			for (M_MiddleShip_2 * ag : v_MiddleShip_2)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()) && ag->Changeing == false)
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));


					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_Hapari.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Hapari * ag : v_Hapari)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));


					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_MiniOb.empty() == false)//   hit
		{
			bool bre = false;
			for (M_MiniOb * ag : v_MiniOb)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));

					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}
		if (v_Japonica.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Japonica * ag : v_Japonica)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));


					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}
		if (v_CrabShild.empty() == false)//   hit
		{
			bool bre = false;
			for (M_CrabShild * ag : v_CrabShild)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));

					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_Crab.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Crab * ag : v_Crab)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getHandRect()) && ag->HandDead == false)
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));

					bre = true;
					break;
				}
				else if (v_Missail->m_getRect().intersectsRect(ag->m_getLegRect()) && ag->LegDead == false)
				{

					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));

					bre = true;
					break;
				}
				else if (v_Missail->m_getRect().intersectsRect(ag->m_getBodyRect()))
				{
					v_Missail->m_createBoom();
					v_Missail->m_setPosition(Vec2(8000, 8000));


					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}
		
	}
}

void Stage1::Sol_Torpedo_Boom(float dt)
{
	for (TorpedoBoom * v_Missail : v_TorpedoBoom)
	{
		if (v_Aghi.empty() == false)//   hit
		{
			bool bre = false;

			for (M_Aghi * ag : v_Aghi)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{



					ag->m_Dmg(SubMarin->TorpedoDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomAghi(ag->m_getPosition());
						v_Aghi.eraseObject(ag);
						GameLayer->removeChild(ag, true);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;

		}
		if (v_UpAghi.empty() == false)//   hit
		{
			bool bre = false;

			for (M_UpAghi * ag : v_UpAghi)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{
					ag->m_Dmg(SubMarin->TorpedoDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomUpAghi(ag->m_getPosition());
						v_UpAghi.eraseObject(ag);
						GameLayer->removeChild(ag, true);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;

		}

		if (v_MiddleShip.empty() == false)//   hit
		{
			bool bre = false;
			for (M_middleShip * ag : v_MiddleShip)
			{
				if (ag->v_MSB.empty() == false)
				{
					for (MiddleShip_Boom * MS : ag->v_MSB)
					{
						if (v_Missail->m_getRect().intersectsRect(MS->m_getRect()))
						{
							MS->m_Dmg(SubMarin->TorpedoDamege);
							MS->m_sollision();
							if (MS->M_HP <= 0)
							{
								BoomMiniOb(MS->m_getPosition());
								ag->v_MSB.eraseObject(MS);
								GameLayer->removeChild(MS, true);
							}
							bre = true;
							break;
						}
					}
					if (bre == true)
						break;
				}
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{
					if (ag->hitBoom == false)
					{
						ag->hitBoom = true;
						ag->m_Dmg(SubMarin->TorpedoDamege);
					}
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						Vec2 Pos = ag->Mother->getPosition();
						while (ag->v_MSB.empty() == false)
						{
							MiddleShip_Boom * MS = ag->v_MSB.front();
							BoomMiniOb(MS->m_getPosition());
							ag->v_MSB.eraseObject(MS);
							GameLayer->removeChild(MS, true);
						}

						v_MiddleShip.eraseObject(ag);
						GameLayer->removeChild(ag, true);

						//페이즈 전환
						M_MiddleShip_2 * Mon = M_MiddleShip_2::m_create(Vec2(Pos.x + 50, Pos.y - 25), GameLayer, &v_MonMissail, &v_MonRazer);
						v_MiddleShip_2.pushBack(Mon);
						GameLayer->addChild(Mon);
					}
					bre = true;
					break;
				}
			}
			if (bre == true)
				break;
		}

		if (v_MiddleShip_2.empty() == false)
		{
			bool bre = false;
			for (M_MiddleShip_2 * ag : v_MiddleShip_2)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()) && ag->Changeing == false)
				{
					if (ag->hitBoom == false)
					{
						ag->hitBoom = true;
						ag->m_Dmg(SubMarin->TorpedoDamege);
					}
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomMiddleShip(ag->m_getPosition());
						ag->removeAllChildren();
						v_MiddleShip_2.eraseObject(ag);
						GameLayer->removeChild(ag, false);
						Boss = true;
						MakingInit();
						GameTime = 0.0f;
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_Hapari.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Hapari * ag : v_Hapari)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{
					ag->m_Dmg(SubMarin->TorpedoDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomHapari(ag->m_getPosition());
						ag->removeAllChildren();
						v_Hapari.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_MiniOb.empty() == false)//   hit
		{
			bool bre = false;
			for (M_MiniOb * ag : v_MiniOb)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{
					ag->m_Dmg(SubMarin->TorpedoDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomMiniOb(ag->m_getPosition());
						ag->removeAllChildren();
						v_MiniOb.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}
		if (v_Japonica.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Japonica * ag : v_Japonica)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{
					ag->m_Dmg(SubMarin->TorpedoDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomJaponica(ag->m_getPosition());
						ag->removeAllChildren();
						v_Japonica.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}
		if (v_CrabShild.empty() == false)//   hit
		{
			bool bre = false;
			for (M_CrabShild * ag : v_CrabShild)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getRect()))
				{
					ag->m_Dmg(SubMarin->TorpedoDamege);
					ag->m_sollision();
					if (ag->M_HP <= 0)
					{
						BoomJaponica(ag->m_getPosition());
						ag->removeAllChildren();
						v_CrabShild.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;
		}

		if (v_Crab.empty() == false)//   hit
		{
			bool bre = false;
			for (M_Crab * ag : v_Crab)
			{
				if (v_Missail->m_getRect().intersectsRect(ag->m_getBodyRect()))
				{
					if (ag->hitBoom == false)
					{
						ag->hitBoom = true;
						ag->m_Body_Dmg(SubMarin->TorpedoDamege);
						
					}
					ag->m_bodysollision();
					if (ag->M_Body_HP <= 0)
					{
						if (ag->LegDead == false)
						{
							ag->m_BoomLeg();
						}
						if (ag->HandDead == false)
						{
							ag->m_BoomHand();
						}
						//파트 죽는곳
						m_CameraSpeed = 0.0f;
						BoomCrab(ag->m_getPosition());//
						ag->removeAllChildren();
						v_Crab.eraseObject(ag);
						GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}
				if (v_Missail->m_getRect().intersectsRect(ag->m_getHandRect()) && ag->HandDead == false)
				{
					if (ag->hitBoom == false)
					{
						ag->hitBoom = true;
						ag->m_Body_Dmg(SubMarin->TorpedoDamege);
					}
					ag->m_handsollision();
					if (ag->M_Hand_HP <= 0)
					{
						ag->M_Body_HP -= 1500;
						GameScore += 20000;
						ag->HandDead = true;
						ag->m_setOpacityLaw();
						ag->m_BoomHand();
						//파트 죽는곳
						//ag->removeAllChildren();
						//v_Crab.eraseObject(ag);
						//GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}
				if (v_Missail->m_getRect().intersectsRect(ag->m_getLegRect()) && ag->LegDead == false)
				{
					if (ag->hitBoom == false)
					{
						ag->hitBoom = true;
						if (ag->HandDead == false)
							ag->m_Hand_Dmg(SubMarin->TorpedoDamege);
						if (ag->LegDead == false)
							ag->m_Leg_Dmg(SubMarin->TorpedoDamege);
						ag->m_Body_Dmg(SubMarin->TorpedoDamege);
					}
					ag->m_legsollision();
					if (ag->M_Leg_HP <= 0)
					{
						ag->M_Body_HP -= 1500;
						GameScore += 30000;
						m_CameraSpeed = 0.0f;
						ag->LegDead = true;
						ag->m_setOpacityLaw();
						ag->m_BoomLeg();
						//파트 죽는곳
						//ag->removeAllChildren();
						//v_Crab.eraseObject(ag);
						//GameLayer->removeChild(ag, false);
					}
					bre = true;
					break;
				}
				

			}
			if (bre == true)
				break;
		}
		
	}
}



void Stage1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//이런 식으로 키 값에 따라 처리를 하면 된다
	KeyPath = 0;
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		KeyPath = 1;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		KeyPath = 2;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		KeyPath = 3;
		break;
	case EventKeyboard::KeyCode::KEY_F:
		KeyPath = 4;
		break;
	case EventKeyboard::KeyCode::KEY_G:
		KeyPath = 5;
		break;


	case EventKeyboard::KeyCode::KEY_Q:
		KeyPath = 11;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		KeyPath = 12;
		break;
	case EventKeyboard::KeyCode::KEY_E:
		KeyPath = 13;
		break;
	case EventKeyboard::KeyCode::KEY_R:
		KeyPath = 14;
		break;
	case EventKeyboard::KeyCode::KEY_T:
		KeyPath = 15;
		break;
	}
}

void Stage1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}



void Stage1::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{

	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		location[i] = touch->getLocation();
		it++;

		if (n_pause == false)
		{

			if (TurnControl == false)
			{
				if (location[i].x < D_DESIGN_WIDTH / 3)
				{
					NowMovingPos = location[i];
					Stick->j_setPosition(location[i]);
					Stick->j_setOpacity(170);
					Stick->j_startMove(location[i]);
					nowJoystickOn = true;
				}
			}
			else
			{
				if (location[i].x > (D_DESIGN_WIDTH / 3) * 2)
				{
					NowMovingPos = location[i];
					Stick->j_setPosition(location[i]);
					Stick->j_setOpacity(170);
					Stick->j_startMove(location[i]);
					nowJoystickOn = true;
				}
			}

			if (UI_TorpedoButton->boundingBox().containsPoint(location[i]))
			{
				if (Player_Torpedo > 0)
				{
					if (SubMarin->s_Torpedo() == true)
					{
						TorButtonEffect();
						Player_Torpedo--;
					}
				}
			}
			//pause
			if (UI_PauseButton->boundingBox().containsPoint(location[i]))
			{
				if (n_pause == false)
					n_pause = true;




				PauseLayer * Pause = PauseLayer::n_create(UILayer);
				UILayer->addChild(Pause,9999);
				v_PauseLayer.pushBack(Pause);

				this->pause();


				_eventDispatcher->resumeEventListenersForTarget(this);


				for (auto node : this->getChildren())
				{
					pauseRecursive(node, true);
				}

			}
			//
		}
		else if (n_pause == true)
		{
			if (v_PauseLayer.front()->m_update(location[i]) == 1)
			{
				n_pause = false;

				v_PauseLayer.eraseObject(v_PauseLayer.front());

				this->resume();
				for (auto node : this->getChildren())
				{
					pauseRecursive(node, false);
				}
			}
			else if (v_PauseLayer.front()->m_update(location[i]) == 2)
			{
				//main
				ChangeBgm = true;
				MapCode = 1;
				Scene *scene = BlackScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			else if (v_PauseLayer.front()->m_update(location[i]) == 3)
			{
				//re
				ChangeBgm = true;
				MapCode = 10;
				Scene *scene = BlackScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
		}
	}
}

void Stage1::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		location[i] = touch->getLocation();
		it++;
		if (n_pause == true)
		{
			v_PauseLayer.front()->m_moveupdate(location[i]);
		}
		else
		{
			if (TurnControl == false)
			{
				if (location[i].x < D_DESIGN_WIDTH / 2 + (D_DESIGN_WIDTH / 10) && nowJoystickOn == true)
				{
					SubMarin->s_Moving = true;
					NowMovingPos = location[i];
				}
			}
			else
			{
				if (location[i].x > D_DESIGN_WIDTH / 2 - (D_DESIGN_WIDTH / 10) && nowJoystickOn == true)
				{
					SubMarin->s_Moving = true;
					NowMovingPos = location[i];
				}
			}
		}
	}
}

void Stage1::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];

	if (n_pause == false)
	{
		for (int i = 0; i < touches.size(); i++)
		{
			touch = (Touch*)(*it);
			location[i] = touch->getLocation();
			it++;

			bool UITouch = false;
			for (Sprite * B : v_Button)
			{
				if (B->boundingBox().containsPoint(location[i]))
				{
					UITouch = true;
					break;
				}
			}

			if (!UITouch)
			{
				Stick->j_setOpacity(0);
				SubMarin->s_Moving = false;
				SubMarin->s_Speed = 0.0f;
				nowJoystickOn = false;
			}
		}
	}
}

void Stage1::pauseRecursive(Node * _node, bool _pause)
{
	if (_pause)
		_node->pause();
	else
		_node->resume();

	Ref* child = nullptr;
	auto children = _node->getChildren();
	for (size_t i = 0; i < children.size(); i++)
	{
		pauseRecursive(children.at(i), _pause);
	}
}

void Stage1::m_mapEdit()//미완
{
	BG1 = Sprite::create("bg/stage1/bg0.jpg");
	BG1->setAnchorPoint(Vec2(0, 0));
	BG1->setPosition(Vec2(0, 0));
	BGLayer->addChild(BG1);

	BG2 = Sprite::create("bg/stage1/bg1.jpg");
	BG2->setAnchorPoint(Vec2(0, 0));
	BG2->setPosition(Vec2(BG1->boundingBox().size.width, 0));
	BGLayer->addChild(BG2);

	BG3 = Sprite::create("bg/stage1/bg2.jpg");
	BG3->setAnchorPoint(Vec2(0, 0));
	BG3->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width, 0));
	BGLayer->addChild(BG3);

	BG4 = Sprite::create("bg/stage1/bg3.jpg");
	BG4->setAnchorPoint(Vec2(0, 0));
	BG4->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width + BG3->boundingBox().size.width, 0));
	BGLayer->addChild(BG4);

	BG5 = Sprite::create("bg/stage1/bg3.jpg");
	BG5->setAnchorPoint(Vec2(0, 0));
	BG5->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width + BG3->boundingBox().size.width + BG4->boundingBox().size.width, 0));
	BGLayer->addChild(BG5);

	BG6 = Sprite::create("bg/stage1/bg3.jpg");
	BG6->setAnchorPoint(Vec2(0, 0));
	BG6->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width + BG3->boundingBox().size.width + BG4->boundingBox().size.width + BG5->boundingBox().size.width, 0));
	BGLayer->addChild(BG6);
}

void Stage1::MonsterSollisionUpdate()
{
	if (v_Aghi.empty() == false)
	{
		for (M_Aghi * mon : v_Aghi)
		{

		}
	}
}

void Stage1::MakeAghi(Vec2 Pos)
{
	M_Aghi * Aghi = M_Aghi::m_create(Pos, this, &v_Aghi);
	GameLayer->addChild(Aghi);

	v_Aghi.pushBack(Aghi);
}

void Stage1::MakeMiddleShip(Vec2 Pos)
{
	M_middleShip * MiddleShip = M_middleShip::m_create(Pos, GameLayer, &v_MonMissail, &v_MiniOb);
	GameLayer->addChild(MiddleShip);

	v_MiddleShip.pushBack(MiddleShip);
}

void Stage1::MakeHapari(Vec2 Pos, int num)
{
	M_Hapari * Hapari = M_Hapari::m_create(Pos, GameLayer, &v_MonMissail, num, &v_Hapari);
	GameLayer->addChild(Hapari);

	v_Hapari.pushBack(Hapari);
}

void Stage1::MakeJaponica(Vec2 Pos)
{
	M_Japonica * Japo = M_Japonica::m_create(Pos, GameLayer, &v_MonRazer);
	GameLayer->addChild(Japo, 15);

	v_Japonica.pushBack(Japo);
}

void Stage1::MakeUpAghi(Vec2 Pos)
{
	M_UpAghi * Aghi = M_UpAghi::m_create(Pos, this, &v_UpAghi);
	GameLayer->addChild(Aghi, 501);

	v_UpAghi.pushBack(Aghi);
}

void Stage1::MakeCrab(Vec2 Pos)
{
	M_Crab * Crab = M_Crab::m_create(Pos, GameLayer, &v_Crab, &v_CrabShild, &v_MonMissail, &v_CrabWave, &v_CrabThorn);
	GameLayer->addChild(Crab);

	v_Crab.pushBack(Crab);
}

void Stage1::MakeCrab_Hapari()
{
	random_device numrand;
	mt19937 Engine(numrand()); // 엔진에 시드를 세팅.
	std::uniform_real_distribution<> dist(50.0f, 670.0f);
	auto Num = dist(Engine);

	MakeHapari(Vec2(1320, Num), 11);
}



bool Stage1::CircleSollision(Vec2 Pos1, Vec2 Pos2, float radi1, float radi2)
{
	if (sqrtf((Pos1.x - Pos2.x)*(Pos1.x - Pos2.x) + (Pos1.y - Pos2.y)*(Pos1.y - Pos2.y)) < radi1 + radi2)
	{
		return true;
	}
	return false;
}

void Stage1::BoomAghi(Vec2 Pos)
{
	Sprite * Ani = Sprite::create();
	Ani->setPosition(Pos);
	GameLayer->addChild(Ani, 50);
	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 3; i++)
	{
		sprintf(str1, "agidead%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.18f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	Ani->runAction(seq);

	GameScore += 2000;

	AudioEngine::play2d("sound/effect/aghi_dead.mp3", false, Volume);
}

void Stage1::BoomMiddleShip(Vec2 Pos)
{
	M_MiddleShipDead * Ani = M_MiddleShipDead::m_create(Vec2(Pos.x, Pos.y), GameLayer);
	GameLayer->addChild(Ani);
	v_MiddleShip_Dead.pushBack(Ani);

	auto seq = Sequence::create(DelayTime::create(1.65f), RemoveSelf::create(), NULL);
	Ani->runAction(seq);

	GameScore += 30000;

	AudioEngine::play2d("sound/effect/middleship_boom.mp3", false, Volume);
}

void Stage1::BoomHapari(Vec2 Pos)
{
	Sprite * Ani = Sprite::create();
	Ani->setPosition(Pos);
	GameLayer->addChild(Ani, 50);
	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 3; i++)
	{
		sprintf(str1, "heparidead%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.18f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	Ani->runAction(seq);

	GameScore += 100;

	AudioEngine::play2d("sound/effect/hapari_dead.mp3", false, Volume);
}

void Stage1::BoomJaponica(Vec2 Pos)
{
	Sprite * Ani = Sprite::create();
	Ani->setPosition(Pos);
	GameLayer->addChild(Ani, 50);
	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 4; i++)
	{
		sprintf(str1, "bemjangadead%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	Ani->runAction(seq);

	GameScore += 4000;

	AudioEngine::play2d("sound/effect/japonica_dead.mp3", false, Volume);
}

void Stage1::BoomUpAghi(Vec2 Pos)
{
	Sprite * Ani = Sprite::create();
	Ani->setRotation(90);
	Ani->setPosition(Pos);
	GameLayer->addChild(Ani, 50);
	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 4; i++)
	{
		sprintf(str1, "upaghidead%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	Ani->runAction(seq);

	GameScore += 3500;
}

void Stage1::BoomMiniOb(Vec2 Pos)
{
	Sprite * Ani = Sprite::create();
	Ani->setPosition(Vec2(Pos.x + 20, Pos.y));
	GameLayer->addChild(Ani, 50);
	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 4; i++)
	{
		sprintf(str1, "smalldead%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	Ani->runAction(seq);

	AudioEngine::play2d("sound/effect/miniob_boom.mp3", false, Volume);
}

void Stage1::BoomCrab(Vec2 Pos)
{
	Crab_Dead * Ani = Crab_Dead::m_create(Vec2(1000, 360), GameLayer);
	GameLayer->addChild(Ani);
	v_CrabDead.pushBack(Ani);

	auto seq = Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL);
	Ani->runAction(seq);

	n_GameClear = true;
	auto ac = CallFunc::create(CC_CALLBACK_0(Stage1::GameClear, this));
	auto seq1 = Sequence::create(DelayTime::create(2.0f), ac, NULL);
	this->runAction(seq1);

	m_CameraSpeed = 0.0f;
	GameScore += 50000;

	AudioEngine::play2d("sound/effect/crab_dead.mp3", false, Volume);
}

void Stage1::BoomShild(Vec2 Pos)
{
	ShildBreak * Ani = ShildBreak::m_create(Vec2(Pos.x, Pos.y), GameLayer);
	GameLayer->addChild(Ani);
	v_ShildBreak.pushBack(Ani);

	auto seq = Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), NULL);
	Ani->runAction(seq);

	GameScore += 1000;
}

void Stage1::TorButtonEffect()
{
	Sprite * Spr = Sprite::create();
	Spr->setPosition(UI_TorpedoButton->getPosition());
	UILayer->addChild(Spr, 10);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 6; i++)
	{
		sprintf(str1, "torbut%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	Spr->runAction(seq);
}

void Stage1::SubHit()
{
	if (SubMarin->s_getStrong() == false)
	{
		Player_Life -= 30.0f;
		SubMarin->s_hitting();
	}
}

void Stage1::GameClear()
{
	if (n_GameClear == true)
	{
		n_GameClear = false;
		GameClearLayer * Pause = GameClearLayer::n_create(UILayer, Player_Torpedo, GameScore, 200000, PlayTime, 1, 1, 1, 2);//아이템
		UILayer->addChild(Pause);//스테이지 맥스 스코어
		v_GameClear.pushBack(Pause);

		auto ac = CallFunc::create(CC_CALLBACK_0(Stage1::GAmeClearAndScene, this));
		auto seq = Sequence::create(DelayTime::create(8.5f), RemoveSelf::create(), ac, NULL);
		Pause->runAction(seq);
	}
}

void Stage1::GAmeClearAndScene()
{
	ChangeBgm = true;
	MapCode = 5;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}

void Stage1::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}