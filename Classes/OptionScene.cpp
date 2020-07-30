#include "stdafx.h"


Scene* OptionScene::createScene()
{
	auto scene = Scene::create();
	auto layer = OptionScene::create();
	scene->addChild(layer);
	return scene;
}


bool OptionScene::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
		return false;

	Table = Sprite::create("option/table.png");
	Table->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);
	this->addChild(Table, 0);

	Volume = UserDefault::getInstance()->getFloatForKey("Volume");

	Credit = MenuItemImage::create("option/credit_0.png", "option/credit_1.png", CC_CALLBACK_0(OptionScene::CreditSprite, this));
	menu2 = Menu::create(Credit, nullptr);
	menu2->setAnchorPoint(Vec2(0,1));
	menu2->setPosition(Vec2(840,180));
	this->addChild(menu2);

	Help = MenuItemImage::create("option/help_0.png", "option/help_1.png", CC_CALLBACK_0(OptionScene::HelpScene, this));
	menu3 = Menu::create(Help, nullptr);
	menu3->setAnchorPoint(Vec2(1, 0));
	menu3->setPosition(Vec2(440, 270));
	this->addChild(menu3);

	Toon = MenuItemImage::create("option/toon_0.png", "option/toon_1.png", CC_CALLBACK_0(OptionScene::ToonScene, this));
	menu4 = Menu::create(Toon, nullptr);
	menu4->setAnchorPoint(Vec2(0, 0));
	menu4->setPosition(Vec2(840,270));
	this->addChild(menu4);

	Turn = MenuItemImage::create("option/turn_0.png", "option/turn_1.png", CC_CALLBACK_0(OptionScene::TurnLine, this));
	menu5 = Menu::create(Turn, nullptr);
	menu5->setAnchorPoint(Vec2(1, 1));
	menu5->setPosition(Vec2(440,180));
	this->addChild(menu5);

	GLabel = LabelBMFont::create("1000000", "fonts/undeadfont.fnt");
	GLabel->setPosition(Vec2(1140, 665));
	this->addChild(GLabel, 150);

	Title = MenuItemImage::create("mapselect/title_0.png", "mapselect/title_1.png", CC_CALLBACK_0(OptionScene::MoveScene, this));
	menu1 = Menu::create(Title, nullptr);
	menu1->setPosition(Vec2(80, 640));
	this->addChild(menu1,100);

	SoundButton = Sprite::create("option/soundicon.png");
	SoundButton->setPosition(Vec2(464+(591.0*Volume),379));
	this->addChild(SoundButton,20);

	TurnControl = UserDefault::getInstance()->getBoolForKey("TurnControl");


	if (Bgm_Sound[2] == AudioEngine::INVALID_AUDIO_ID)
	{
		Bgm_Sound[2] = AudioEngine::play2d("sound/bgm/mainmenu.mp3", true, Volume);
	}


	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(OptionScene::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(OptionScene::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(OptionScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	schedule(schedule_selector(OptionScene::update), 0.0f);

	return true;
}

void OptionScene::update(float dt)
{
	
}

void OptionScene::MoveScene()
{
	MapCode = 1;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}


void OptionScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{

	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		location[i] = touch->getLocation();
		it++;

		if (location[i].x>450.0f&&
			location[i].x<1080.0f&&
			location[i].y>360.0f&&
			location[i].y < 400.0f)
		{
			Vec2 Pos = location[i];
			if (Pos.x < 464.0f)
				Pos.x = 464.0f;
			if (Pos.x>1055.0f)
				Pos.x = 1055.0f;



			Volume = ((Pos.x - 464.0f)) / 591.0f;
			EffVolume = Volume*0.7f;
			UserDefault::getInstance()->setFloatForKey("Volume", Volume);
			for (int i = 0; i < BGM_SOUND_NUM; i++)
			{
				AudioEngine::setVolume(Bgm_Sound[i], Volume);
			}
			//EffectVolume
		}
		SoundButton->setPositionX(464 + (Volume * 591));
		if (SoundButton->getPositionX()<464.0f)
			SoundButton->setPositionX(464.0f);

		if (SoundButton->getPositionX()>1055.0f)
			SoundButton->setPositionX(1055.0f);

	}
}

void OptionScene::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		location[i] = touch->getLocation();
		it++;


		if (location[i].x>450.0f&&
			location[i].x<1080.0f&&
			location[i].y>320.0&&
			location[i].y < 450.0)
		{
			Vec2 Pos = location[i];
			if (Pos.x < 464.0f)
				Pos.x = 464.0f;
			if (Pos.x>1055.0f)
				Pos.x = 1055.0f;



			Volume = ((Pos.x - 464.0f)) / 591.0f;
			EffVolume = Volume*0.6f;
			UserDefault::getInstance()->setFloatForKey("Volume", Volume);
			for (int i = 0; i < BGM_SOUND_NUM; i++)
			{
				AudioEngine::setVolume(Bgm_Sound[i], Volume);
			}
			//EffectVolume
		}
		SoundButton->setPositionX(464 + (Volume * 591));
		if (SoundButton->getPositionX()<464.0f)
			SoundButton->setPositionX(464.0f);

		if (SoundButton->getPositionX()>1055.0f)
			SoundButton->setPositionX(1055.0f);
	}
}

void OptionScene::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
{
	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];


	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		location[i] = touch->getLocation();
		it++;


	}
}

void OptionScene::TurnLine()
{
	Sprite * ani = Sprite::create("option/turnline.png");
	ani->setPosition(Vec2(640,240));
	this->addChild(ani, 10);

	auto ac = FadeOut::create(1.0f);
	auto ac1 = MoveBy::create(1.0f, Vec2(0, 200));
	auto ac2 = Spawn::create(ac, ac1, NULL);
	auto seq = Sequence::create(DelayTime::create(1.0f), ac2,RemoveSelf::create(), NULL);
	ani->runAction(seq);

	TurnControl = UserDefault::getInstance()->getBoolForKey("TurnControl");
	if (TurnControl == false)
		TurnControl = true;
	else
		TurnControl = false;

	UserDefault::getInstance()->flush();
	UserDefault::getInstance()->setBoolForKey("TurnControl", TurnControl);
}

void OptionScene::CreditSprite()
{
	Sprite * Cre = Sprite::create("option/credit.png");
	Cre->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(Cre,50);
}

void OptionScene::HelpScene()
{

}

void OptionScene::ToonScene()
{

}