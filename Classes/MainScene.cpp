#include "stdafx.h"



Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainScene::init()
{
	Check = true;
	srand((unsigned)time(NULL));
	//터치
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//레이어
	if (!LayerColor::initWithColor(Color4B::GRAY))
		return false;




	Submarin = Sprite::create();
	Submarin->setPosition(Vec2(350, 360));
	this->addChild(Submarin, 50);
	if (nowSubmarinFrame == 1)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 0; i < 4; i++)
		{
			sprintf(str1, "%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.05f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Submarin->runAction(CCRepeatForever::create(seq));
	}
	else if (nowSubmarinFrame == 4)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 0; i < 12; i++)
		{
			sprintf(str1, "submarin_devil%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Submarin->runAction(CCRepeatForever::create(seq));
	}







	if (Bgm_Sound[2] == AudioEngine::INVALID_AUDIO_ID)
	{
		Bgm_Sound[2] = AudioEngine::play2d("sound/bgm/mainmenu.mp3", true, Volume);
	}
	EffVolume = Volume*0.7f;


	log("%f",Volume );




	Size winSize = Director::getInstance()->getWinSize();


	int asdf = 1000000;
	UserDefault::getInstance()->setIntegerForKey("gold", asdf);
	UserDefault::getInstance()->flush();


	m_label[0] = LabelBMFont::create(" ", "hm/fonts/font.fnt");
	m_label[0]->setPosition(350, 115);
	this->addChild(m_label[0], 2);



	Sprite* background = Sprite::create("hm/mainmenu/back.png");			//배경화면
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	background->setScale(winSize.width / background->getContentSize().width);
	this->addChild(background);

	m_Sprite[0] = Sprite::create();
	m_Sprite[0]->setPosition(750, 400);
	m_Sprite[0]->setScale(0.8);
	this->addChild(m_Sprite[0], 15);

	m_Sprite[1] = Sprite::create();
	m_Sprite[1]->setPosition(1100, 400);
	m_Sprite[1]->setScale(0.8);
	this->addChild(m_Sprite[1], 3);

	m_Sprite[2] = Sprite::create("hm/mainmenu/kal.png");
	m_Sprite[2]->setPosition(D_DESIGN_WIDTH, D_DESIGN_HEIGHT);
	m_Sprite[2]->setVisible(false);
	this->addChild(m_Sprite[2], 5);

	

	m_Menu[0] = MenuItemImage::create("hm/mainmenu/st1.png", "hm/mainmenu/st3.png", CC_CALLBACK_1(MainScene::GameStart, this));	//게임 시작
	m_Menu[0]->setScale(0.8);
	m_Menu[0]->setPosition(750, 400);

	m_Menu[1] = MenuItemImage::create("hm/mainmenu/hanger0.png", "hm/mainmenu/hangerD.png", CC_CALLBACK_1(MainScene::Go_Hanger, this));	//hanger
	m_Menu[1]->setScale(0.8);
	m_Menu[1]->setPosition(1100, 400);

	m_Menu[2] = MenuItemImage::create("hm/mainmenu/Roulette.png", "hm/mainmenu/Roulette.png", CC_CALLBACK_1(MainScene::Go_MiniGame, this));	//룰렛
	m_Menu[2]->setPosition(750, 150);

	m_Menu[3] = MenuItemImage::create("hm/mainmenu/option.png", "hm/mainmenu/option.png", CC_CALLBACK_1(MainScene::Go_Option, this));//옵션
	m_Menu[3]->setPosition(1100, 150);

	auto MenU = Menu::create(m_Menu[0], m_Menu[1], m_Menu[2], m_Menu[3], NULL);
	MenU->setPosition(Vec2::ZERO);
	this->addChild(MenU, 1);







	schedule(schedule_selector(MainScene::Update), 0.0f);

	return true;

}

void MainScene::Update(float dt)
{
	string gold = UserDefault::getInstance()->getStringForKey("gold");
	m_label[0]->setString(gold);
	static float time = 0;
	time += dt;

}
/**
@brief : 메뉴 누르면 만들어지는 버튼 함수 생성
*/
void MainScene::menuCloseCallback(Ref* pSender){}


void MainScene::GameStart(Ref* pSender)
{
	if (bb == false)
	{
		bb = true;
		m_Sprite[2]->setVisible(true);
		m_Animation[0] = Animation::create();
		m_Animation[0]->setDelayPerUnit(0.15);
		AudioEngine::play2d("sound/effect/knifeswing.mp3", false, EffVolume);
		for (int i = 0; i < 4; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("HB%d.png", i));
			m_Animation[0]->addSpriteFrame(frame);
		}
		m_Animate[0] = Animate::create(m_Animation[0]);
		CallFunc* changeScene = CallFunc::create(CC_CALLBACK_0(MainScene::ChangeStart, this));
		DelayTime* de = DelayTime::create(0.7f);
		auto ac13 = CallFunc::create(CC_CALLBACK_0(MainScene::makecover, this));
		auto se = Sequence::create(de, ac13, m_Animate[0], changeScene, NULL);
		m_Sprite[0]->runAction(se);

		MoveTo* move = MoveTo::create(0.7f, Point(780, 450));
		RotateBy* rotate = RotateBy::create(0.7f, -1800);
		Spawn* sp = Spawn::create(move, rotate, NULL);
		m_Sprite[2]->runAction(sp);
	}
	

}
void MainScene::Go_Hanger(Ref* pSender)
{
	AudioEngine::play2d("sound/effect/hanger_sceen.mp3", false, Volume);

	m_Menu[1]->setVisible(false);
	m_Animation[1] = Animation::create();
	m_Animation[1]->setDelayPerUnit(0.2);



	for (int i = 1; i < 4; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("hanger%d.png", i));
		m_Animation[1]->addSpriteFrame(frame);
	}

	m_Animate[1] = Animate::create(m_Animation[1]);

	CallFunc* changeScene = CallFunc::create(CC_CALLBACK_0(MainScene::ChangeStorage, this));
	auto se = Sequence::create(m_Animate[1], changeScene, NULL);

	m_Sprite[1]->runAction(se);
}
void MainScene::Go_Shop(Ref* pSender)
{

}
void MainScene::Go_MiniGame(Ref* pSender)
{
	ChangeBgm = true;
	MapCode = 7;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}
void MainScene::Go_Option(Ref* pSender)
{
	MapCode = 2;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}




bool MainScene::onTouchBegan(Touch *touch, Event *unused_event)
{

	//	Director::getInstance()->replaceScene(Jackpot::createScene());
	return true;
}
void MainScene::onTouchMoved(Touch *touch, Event *unused_event){}
void MainScene::onTouchEnded(Touch *touch, Event *unused_event){}
//void mainMenu::onTouchCancelled(Touch *touch, Event *unused_event){}
//void mainMenu::onTouchesBegan(const  vector<Touch*>& touches, Event *unused_event){}
//void mainMenu::onTouchesMoved(const  vector<Touch*>& touches, Event *unused_event){}
//void mainMenu::onTouchesEnded(const  vector<Touch*>& touches, Event *unused_event){}
//void mainMenu::onTouchesCancelled(const  vector<Touch*>&touches, Event *unused_event){}
void MainScene::ChangeStorage()
{
	MapCode = 6;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}
void MainScene::ChangeStart()
{
	MapCode = 5;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}


void MainScene::makecover()
{
	AudioEngine::play2d("sound/effect/knifeboom.mp3", false, EffVolume);
	Sprite * Spr = Sprite::create("hm/mainmenu/st2.png");
	Spr->setPosition(Vec2(750, 400));
	Spr->setScale(0.8);
	this->addChild(Spr, 10);
}