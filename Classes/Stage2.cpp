#include "stdafx.h"

Scene* Stage2::createScene()
{
	auto scene = Scene::create();
	auto layer = Stage2::create();
	scene->addChild(layer);
	return scene;
}


bool Stage2::init()
{

	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
		return false;



	BGLayer = Layer::create();
	this->addChild(BGLayer, 0);
	GameLayer = Layer::create();
	this->addChild(GameLayer, 100);
	UILayer = Layer::create();
	this->addChild(UILayer, 150);



	if (Bgm_Sound[4] == AudioEngine::INVALID_AUDIO_ID)
	{
		Bgm_Sound[4] = AudioEngine::play2d("sound/bgm/stage2.mp3", true, Volume);
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
	ScoreLabel->setPosition(Vec2(50, 620));
	UILayer->addChild(ScoreLabel, 105);

	SubMarin = MySubmarin::n_create(Vec2(120, D_DESIGN_HEIGHT / 2), GameLayer, &v_TorpedoBoom, nowSubmarinFrame);
	SubMarin->setPosition(120, D_DESIGN_HEIGHT / 2);
	SubMarin->setScaleX(-1.0f);
	GameLayer->addChild(SubMarin, 1);

	BG_Camera = new CPNCamera();
	BG_Camera->init(BGLayer, Size(D_DESIGN_WIDTH * 3, D_DESIGN_HEIGHT), Size(D_DESIGN_WIDTH, D_DESIGN_HEIGHT));






	m_mapEdit();

	n_CameraMoving = true;
	GameOver = false;
	Boss = true;////sadfasdfasdfasdfasdfdsafd
	n_pause = false;
	n_GameClear = false;
	NowAghiNum = 0;
	NowHapari_Top_Num = 0;
	NowHapari_Center_Num = 0;
	NowHapari_Bottom_Num = 0;
	NowJaponicaNum = 0;
	NowUpAghiNum = 0;
	Player_Life = 100.0f;
	m_CameraSpeed = 50.0f;
	Player_Torpedo = 3;
	GameTime = 0.0f;
	GameScore = 0;
	PlayTime = 0.0f;

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Stage2::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Stage2::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Stage2::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(Stage2::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(Stage2::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	schedule(schedule_selector(Stage2::MakeUpdate), 0.0f);
	schedule(schedule_selector(Stage2::Update), 0.0f);

	MakePosInit();
	MakingInit();



	return true;
}

void Stage2::MakePosInit()
{
	MakeAttShipPos.push_back(Vec2(1580, 200));
	MakeAttShipPos.push_back(Vec2(1580, 520));
	MakeAttShipPos.push_back(Vec2(1580, 280));

	MakeMiniObPos.push_back(Vec2(1380, 120));
	MakeMiniObPos.push_back(Vec2(1380, 360));
	MakeMiniObPos.push_back(Vec2(1380, 600));

	MakeMiniObPos.push_back(Vec2(1380, 360));
	MakeMiniObPos.push_back(Vec2(1380, 240));
	MakeMiniObPos.push_back(Vec2(1380, 480));
	MakeMiniObPos.push_back(Vec2(1380, 120));
	MakeMiniObPos.push_back(Vec2(1380, 600));
	
	MakeMiniObPos.push_back(Vec2(1380, 120));
	MakeMiniObPos.push_back(Vec2(1380, 240));
	MakeMiniObPos.push_back(Vec2(1380, 480));
	MakeMiniObPos.push_back(Vec2(1380, 600));

	MakeMiniObPos.push_back(Vec2(1380, 120));
	MakeMiniObPos.push_back(Vec2(1380, 240));
	MakeMiniObPos.push_back(Vec2(1380, 360));
	MakeMiniObPos.push_back(Vec2(1380, 480));
	MakeMiniObPos.push_back(Vec2(1380, 600));

	MakeMiniObPos.push_back(Vec2(1380, 180));
	MakeMiniObPos.push_back(Vec2(1380, 540));


}

void Stage2::MakingInit()
{
	if (Boss == false)
	{
		f_MiniObMake.push_back(10.0f);
		f_MiniObMake.push_back(10.0f);
		f_MiniObMake.push_back(10.0f);

		f_MiniObMake.push_back(18.0f);
		f_MiniObMake.push_back(18.5f);
		f_MiniObMake.push_back(18.5f);
		f_MiniObMake.push_back(19.0f);
		f_MiniObMake.push_back(19.0f);

		f_MiniObMake.push_back(25.0f);
		f_MiniObMake.push_back(25.0f);
		f_MiniObMake.push_back(25.0f);
		f_MiniObMake.push_back(25.0f);



		f_RobotMake.push_back(32.0f);



		f_AttShipMake.push_back(12.0f);
		f_AttShipMake.push_back(5.0f);
	}
	else
	{
		f_FishHeadMake.push_back(22.0f);
		
		f_MiniObMake.push_back(6.0f);
		f_MiniObMake.push_back(6.4f);
		f_MiniObMake.push_back(6.8f);
		f_MiniObMake.push_back(7.2f);
		f_MiniObMake.push_back(7.6f);

		f_MiniObMake.push_back(10.0f);
		f_MiniObMake.push_back(10.0f);
		
		f_AttShipMake.push_back(10.0f);

		

	}

}

void Stage2::MakeUpdate(float dt)
{
	GameTime += dt;
	if (f_MiniObMake.empty() == false)
	{
		for (float time : f_MiniObMake)
		{
			if (time <= GameTime)
			{
				MakeMiniOb(MakeMiniObPos.front());
				MakeMiniObPos.erase(MakeMiniObPos.begin());
				f_MiniObMake.erase(f_MiniObMake.begin());
				break;
			}
		}
	}
	if (f_FishHeadMake.empty() == false)
	{
		for (float time : f_FishHeadMake)
		{
			if (time <= GameTime)
			{
				MakeFishHead(Vec2(1600, -770));
				f_FishHeadMake.erase(f_FishHeadMake.begin());
				break;
			}
		}
	}
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
	if (f_AttShipMake.empty() == false)
	{
		for (float time : f_AttShipMake)
		{
			if (time <= GameTime)
			{
				MakeAttShip(MakeAttShipPos.front());
				MakeAttShipPos.erase(MakeAttShipPos.begin());
				f_AttShipMake.erase(f_AttShipMake.begin());
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
				MakeHapari(MakeHapari_Top_Pos.front(), Hapari_Top.front());
				Hapari_Top.erase(Hapari_Top.begin());
				MakeHapari_Top_Pos.erase(MakeHapari_Top_Pos.begin());
				f_Hapari_Top_Make.erase(f_Hapari_Top_Make.begin());
				break;
			}
		}
	}
	if (f_Hapari_Center_Make.empty() == false)
	{
		for (float time : f_Hapari_Center_Make)
		{
			if (time <= GameTime)
			{
				MakeHapari(MakeHapari_Center_Pos.front(), Hapari_Center[NowHapari_Center_Num]);
				Hapari_Center.erase(Hapari_Center.begin());
				MakeHapari_Center_Pos.erase(MakeHapari_Center_Pos.begin());
				f_Hapari_Center_Make.erase(f_Hapari_Center_Make.begin());
				break;
			}
		}
	}
	if (f_Hapari_Bottom_Make.empty() == false)
	{
		for (float time : f_Hapari_Bottom_Make)
		{
			if (time <= GameTime)
			{
				MakeHapari(MakeHapari_Bottom_Pos.front(), Hapari_Bottom[NowHapari_Bottom_Num]);
				Hapari_Bottom.erase(Hapari_Bottom.begin());
				MakeHapari_Bottom_Pos.erase(MakeHapari_Bottom_Pos.begin());
				f_Hapari_Bottom_Make.erase(f_Hapari_Bottom_Make.begin());
				break;
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
	
	if (f_RobotMake.empty() == false)
	{
		for (float time : f_RobotMake)
		{
			if (time <= GameTime)
			{
				MakeBigRobot(Vec2(1500, 360));
				f_RobotMake.erase(f_RobotMake.begin());
				break;
			}
		}
	}
}

void Stage2::Update(float dt)
{
	BG_Camera->update((sceenS += dt * m_CameraSpeed));
	PlayTime += dt;

	if (KeyPath == 11)
	{
		MakeAttShip(Vec2(1580, 360));
		KeyPath = 0;
	}
	if (KeyPath == 12)
	{
		MakeBigRobot(Vec2(1500, 360));
		KeyPath = 0;
	}
	if (KeyPath == 13)
	{
		MakeFishHead(Vec2(1600,-770));
		KeyPath = 0;
	}





	char Torpedostr[256];
	sprintf(Torpedostr, "x %d", Player_Torpedo);
	TorpedoNumL->setString(Torpedostr);
	ScoreString = String::createWithFormat("%d", GameScore);
	ScoreLabel->setString(ScoreString->getCString());
	for (int i = 0; i < BGM_SOUND_NUM; i++)
	{
		AudioEngine::setVolume(Bgm_Sound[i], Volume);
		log("%f vol", Volume);
	}

	SubmarinUpdate(dt);
	MonsterUpdate(dt);

	Sol_Missail(dt);
	Sol_Torpedo(dt);
	Sol_Torpedo_Boom(dt);
}

void Stage2::SubmarinUpdate(float dt)
{
	if (Player_Life <= 0.0f)
		Player_Life = 0.0f;
	Player_Life_Cover->setScaleX((Player_Life - 100.0f) / -100.0f);////////////

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

void Stage2::MonsterUpdate(float dt)
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
	if (v_FishHeadDead.empty() == false)
	{
		for (FishHead_Dead * Mon : v_FishHeadDead)
		{
			Mon->m_update(dt);
		}
	}
	if (v_Roar.empty() == false)
	{
		for (FishHead_Roar * Mon : v_Roar)
		{
			Mon->m_update(dt);
		}
	}
	if (v_Rain.empty() == false)
	{
		for (FishHead_Rain * Mon : v_Rain)
		{
			Mon->m_update(dt);
		}
	}
	if (v_Hurricane.empty() == false)
	{
		for (FishHead_Hurricane * Mon : v_Hurricane)
		{
			Mon->m_update(dt);
			Vec2 Pos = Vec2(10, (100 - SubMarin->s_getPosition().y) / 50);
			SubMarin->s_setPosition(Vec2(SubMarin->s_getPosition().x + Pos.x, SubMarin->s_getPosition().y + Pos.y));
		}
	}
	if (v_Crash.empty() == false)
	{
		for (FishHead_Crash * Mon : v_Crash)
		{
			Mon->m_update(dt);
		}
	}
	if (v_FishHead.empty() == false)
	{
		for (M_FishHead * Mon : v_FishHead)
		{
			Mon->m_update(dt,KeyPath);
			if (Mon->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
			if (KeyPath != 0)
				KeyPath = 0;

			if (Mon->MakeHapari == true)
			{
				auto ac1 = CallFunc::create(CC_CALLBACK_0(Stage2::MakeCrab_Hapari, this));
				auto seq = Sequence::create(ac1, DelayTime::create(0.3f), NULL);
				this->runAction(Repeat::create(seq, 6));

				Mon->MakeHapari = false;
			}
		}
	}
	if (v_MiniOb.empty() == false)
	{
		for (M_MiniOb * Mon : v_MiniOb)
		{
			Mon->m_update(dt,SubMarin->s_getPosition());
			if (Mon->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_Attship.empty() == false)
	{
		for (M_AttShip * Mon : v_Attship)
		{
			Mon->m_update(dt);
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
	
	if (v_RobotMissail.empty() == false)
	{
		for (Robot_Missail * Wave : v_RobotMissail)
		{
			if (Wave->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_Crash.empty() == false)
	{
		for (FishHead_Crash * Wave : v_Crash)
		{
			if (Wave->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_Rain.empty() == false)
	{
		for (FishHead_Rain * Wave : v_Rain)
		{
			if (Wave->m_getRect().intersectsRect(SubMarin->s_getRect()))
			{
				SubHit();
			}
		}
	}
	if (v_RobotDead.empty() == false)
	{
		for (M_BigRobot_Dead * Mon : v_RobotDead)
		{
			Mon->m_update(dt);
			if (Mon->Dead == true)
			{
				GameLayer->removeChild(Mon);
				v_RobotDead.eraseObject(Mon);
				break;
			}
		}
	}
	
	if (v_BigRobot.empty() == false)
	{
		for (M_BigRobot * wave : v_BigRobot)
		{
			wave->m_update(dt,KeyPath);
			if (KeyPath != 0)
				KeyPath = 0;
		}
	}

	if (v_RobotMissail.empty() == false)
	{
		for (Robot_Missail * Mon : v_RobotMissail)
		{
			Mon->m_update(dt);
			if (Mon->del == true)
				break;
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

void Stage2::Sol_Missail(float dt)
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
		
		if (v_FishHead.empty() == false)//   hit
		{
			bool bre = false;

			for (M_FishHead * ag : v_FishHead)
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
						BoomFishHead(ag->m_getPosition());
						v_FishHead.eraseObject(ag);
						GameLayer->removeChild(ag, true);
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
						v_MiniOb.eraseObject(ag);
						GameLayer->removeChild(ag, true);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;

		}
		if (v_Attship.empty() == false)//   hit
		{
			bool bre = false;

			for (M_AttShip * ag : v_Attship)
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
						BoomAttship(ag->m_getPosition());
						v_Attship.eraseObject(ag);
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
		
		if (v_BigRobot.empty() == false)//   hit
		{
			bool bre = false;
			for (M_BigRobot * ag : v_BigRobot)
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
						BoomBigRobot(ag->m_getPosition());
						ag->removeAllChildren();
						v_BigRobot.eraseObject(ag);
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

void Stage2::Sol_Torpedo(float dt)
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
		if (v_Attship.empty() == false)//   hit
		{
			bool bre = false;

			for (M_AttShip * ag : v_Attship)
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
		if (v_FishHead.empty() == false)//   hit
		{
			bool bre = false;

			for (M_FishHead * ag : v_FishHead)
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
		
		if (v_BigRobot.empty() == false)//   hit
		{
			bool bre = false;

			for (M_BigRobot * ag : v_BigRobot)
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
	}
}

void Stage2::Sol_Torpedo_Boom(float dt)
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
		if (v_FishHead.empty() == false)//   hit
		{
			bool bre = false;

			for (M_FishHead * ag : v_FishHead)
			{
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
						BoomFishHead(ag->m_getPosition());
						v_FishHead.eraseObject(ag);
						GameLayer->removeChild(ag, true);
					}
					bre = true;
					break;
				}

			}
			if (bre == true)
				break;

		}
		if (v_Attship.empty() == false)//   hit
		{
			bool bre = false;

			for (M_AttShip * ag : v_Attship)
			{
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
						BoomAttship(ag->m_getPosition());
						v_Attship.eraseObject(ag);
						GameLayer->removeChild(ag, true);
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
	
		if (v_BigRobot.empty() == false)//   hit
		{
			bool bre = false;
			for (M_BigRobot * ag : v_BigRobot)
			{
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
						BoomBigRobot(ag->m_getPosition());
						ag->removeAllChildren();
						v_BigRobot.eraseObject(ag);
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



void Stage2::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//이런 식으로 키 값에 따라 처리를 하면 된다
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
	case EventKeyboard::KeyCode::KEY_H:
		KeyPath = 6;
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
	}
}

void Stage2::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}



void Stage2::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
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
				UILayer->addChild(Pause);
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

void Stage2::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
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

void Stage2::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
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

void Stage2::pauseRecursive(Node * _node, bool _pause)
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

void Stage2::m_mapEdit()//미완
{
	BG1 = Sprite::create("bg/stage2/bg0.png");
	BG1->setAnchorPoint(Vec2(0, 0));
	BG1->setPosition(Vec2(0, 0));
	BGLayer->addChild(BG1);

	BG2 = Sprite::create("bg/stage2/bg1.png");
	BG2->setAnchorPoint(Vec2(0, 0));
	BG2->setPosition(Vec2(BG1->boundingBox().size.width, 0));
	BGLayer->addChild(BG2);

	BG3 = Sprite::create("bg/stage2/bg2.png");
	BG3->setAnchorPoint(Vec2(0, 0));
	BG3->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width, 0));
	BGLayer->addChild(BG3);

	BG4 = Sprite::create("bg/stage2/bg3.png");
	BG4->setAnchorPoint(Vec2(0, 0));
	BG4->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width + BG3->boundingBox().size.width, 0));
	BGLayer->addChild(BG4);

	BG5 = Sprite::create("bg/stage2/bg4.png");
	BG5->setAnchorPoint(Vec2(0, 0));
	BG5->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width + BG3->boundingBox().size.width + BG4->boundingBox().size.width, 0));
	BGLayer->addChild(BG5);

	BG6 = Sprite::create("bg/stage2/bg5.png");
	BG6->setAnchorPoint(Vec2(0, 0));
	BG6->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width + BG3->boundingBox().size.width + BG4->boundingBox().size.width + BG5->boundingBox().size.width, 0));
	BGLayer->addChild(BG6);

	BG7 = Sprite::create("bg/stage2/bg6.png");
	BG7->setAnchorPoint(Vec2(0, 0));
	BG7->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width + BG3->boundingBox().size.width + BG4->boundingBox().size.width + BG5->boundingBox().size.width + BG6->boundingBox().size.width, 0));
	BGLayer->addChild(BG7);
}

void Stage2::MonsterSollisionUpdate()
{

}

void Stage2::MakeAghi(Vec2 Pos)
{
	M_Aghi * Aghi = M_Aghi::m_create(Pos, this, &v_Aghi);
	GameLayer->addChild(Aghi);

	v_Aghi.pushBack(Aghi);
}


void Stage2::MakeHapari(Vec2 Pos, int num)
{
	M_Hapari * Hapari = M_Hapari::m_create(Pos, GameLayer, &v_MonMissail, num, &v_Hapari);
	GameLayer->addChild(Hapari);

	v_Hapari.pushBack(Hapari);
}

void Stage2::MakeMiniOb(Vec2 Pos)
{
	M_MiniOb * Mob = M_MiniOb::m_create(Pos, GameLayer, &v_MonMissail, &v_MiniOb, 2);
	GameLayer->addChild(Mob);
	v_MiniOb.pushBack(Mob);

}

void Stage2::MakeJaponica(Vec2 Pos)
{
	M_Japonica * Japo = M_Japonica::m_create(Pos, GameLayer, &v_MonRazer);
	GameLayer->addChild(Japo, 15);

	v_Japonica.pushBack(Japo);
}

void Stage2::MakeUpAghi(Vec2 Pos)
{
	M_UpAghi * Aghi = M_UpAghi::m_create(Pos, this, &v_UpAghi);
	GameLayer->addChild(Aghi, 501);

	v_UpAghi.pushBack(Aghi);
}


void Stage2::MakeBigRobot(Vec2 Pos)
{
	M_BigRobot * Robot = M_BigRobot::m_create(Pos, GameLayer, &v_MonMissail, &v_MonRazer, &v_RobotMissail);
	GameLayer->addChild(Robot);

	v_BigRobot.pushBack(Robot);
}

void Stage2::MakeAttShip(Vec2 Pos)
{
	M_AttShip * Robot = M_AttShip::m_create(Pos, GameLayer, &v_MonMissail,&v_Attship);
	GameLayer->addChild(Robot);

	v_Attship.pushBack(Robot);

	auto seq = Sequence::create(DelayTime::create(26.0f), RemoveSelf::create(), NULL);
	Robot->runAction(seq);
}

void Stage2::MakeFishHead(Vec2 Pos)
{
	m_CameraSpeed = 0.0f;
	M_FishHead * FishHead = M_FishHead::m_create(Pos, GameLayer, &v_FishHead, &v_Roar,&v_MonRazer,&v_Hurricane, &v_Crash, &v_Rain);
	GameLayer->addChild(FishHead);

	v_FishHead.pushBack(FishHead);
}

bool Stage2::CircleSollision(Vec2 Pos1, Vec2 Pos2, float radi1, float radi2)
{
	if (sqrtf((Pos1.x - Pos2.x)*(Pos1.x - Pos2.x) + (Pos1.y - Pos2.y)*(Pos1.y - Pos2.y)) < radi1 + radi2)
	{
		return true;
	}
	return false;
}

void Stage2::BoomAghi(Vec2 Pos)
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

}

void Stage2::BoomHapari(Vec2 Pos)
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


}

void Stage2::BoomJaponica(Vec2 Pos)
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

}

void Stage2::BoomUpAghi(Vec2 Pos)
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


void Stage2::BoomBigRobot(Vec2 Pos)
{
	M_BigRobot_Dead * Ani = M_BigRobot_Dead::m_create(Vec2(Pos.x, Pos.y), GameLayer);
	GameLayer->addChild(Ani);
	v_RobotDead.pushBack(Ani);

	auto seq = Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL);
	Ani->runAction(seq);

	Boss = true;
	GameTime = 0.0f;
	MakingInit();

	GameScore += 50000;

}

void Stage2::BoomAttship(Vec2 Pos)
{
	Sprite * Ani = Sprite::create();
	Ani->setPosition(Pos);
	GameLayer->addChild(Ani, 50);
	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 3; i++)
	{
		sprintf(str1, "japmopdead%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.2f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);

	GameScore += 10000;

	Ani->runAction(seq);
}


void Stage2::BoomMiniOb(Vec2 Pos)
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

	GameScore += 2000;
	Ani->runAction(seq);
}

void Stage2::BoomFishHead(Vec2 Pos)
{
	FishHead_Dead * Ani = FishHead_Dead::m_create(Vec2(Pos.x, Pos.y), GameLayer);
	GameLayer->addChild(Ani);
	v_FishHeadDead.pushBack(Ani);

	n_GameClear = true;
	auto ac = CallFunc::create(CC_CALLBACK_0(Stage2::GameClear, this));
	auto seq = Sequence::create(DelayTime::create(3.0f),ac, RemoveSelf::create(), NULL);
	Ani->runAction(seq);

	GameScore += 50000;
}

void Stage2::TorButtonEffect()
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

void Stage2::MakeCrab_Hapari()
{
	random_device numrand;
	mt19937 Engine(numrand()); // 엔진에 시드를 세팅.
	std::uniform_real_distribution<> dist(50.0f, 670.0f);
	auto Num = dist(Engine);

	MakeHapari(Vec2(1320, Num), 11);
}

void Stage2::SubHit()
{
	if (SubMarin->s_getStrong() == false)
	{
		Player_Life -= 30.0f;
		SubMarin->s_hitting();
	}
}

void Stage2::GameClear()
{
	if (n_GameClear == true)
	{
		n_GameClear = false;
		GameClearLayer * Pause = GameClearLayer::n_create(UILayer, Player_Torpedo, GameScore, 150000, PlayTime, 1, 1, 1, 2);//아이템
		UILayer->addChild(Pause);//스테이지 맥스 스코어
		v_GameClear.pushBack(Pause);

		auto ac = CallFunc::create(CC_CALLBACK_0(Stage2::GAmeClearAndScene, this));
		auto seq = Sequence::create(DelayTime::create(8.5f), RemoveSelf::create(), ac, NULL);
		Pause->runAction(seq);
	}
}

void Stage2::GAmeClearAndScene()
{
	ChangeBgm = true;
	MapCode = 5;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}

void Stage2::menuCloseCallback(Ref* pSender)
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