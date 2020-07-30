#include "stdafx.h"

int MapCode;
bool ChangeBgm;
int NowStage;
bool TurnControl;
float Volume;
float EffVolume;
int nowSubmarinFrame;

int Bgm_Sound[BGM_SOUND_NUM];

Scene* ExternScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ExternScene::create();
	scene->addChild(layer);
	return scene;
}


bool ExternScene::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
		return false;


	schedule(schedule_selector(ExternScene::update), 0.0f);

	Black = Sprite::create("black.png");
	Black->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(Black);

	for (int i = 0; i < BGM_SOUND_NUM; i++)
	{
		AudioEngine::stop(Bgm_Sound[i]);
	}
	ChangeBgm = false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hm/mainmenu/hanger.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hm/mainmenu/HB.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hm/rolling.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("submarin/animation/submarin_normal.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("submarin/animation/submarin_devil.plist");

	//if (UserDefault::getInstance()->getBoolForKey("FirstStart") == false)
	{
		UserDefault::getInstance()->setBoolForKey("TurnControl",false);
		UserDefault::getInstance()->setIntegerForKey("SubmarinFrame", 1);
		UserDefault::getInstance()->setBoolForKey("FirstStart", true);

		UserDefault::getInstance()->setFloatForKey("Volume", 1.0f);
		UserDefault::getInstance()->flush();
	}
	nowSubmarinFrame = UserDefault::getInstance()->getIntegerForKey("SubmarinFrame");
	Volume = UserDefault::getInstance()->getFloatForKey("Volume");
	EffVolume = Volume*0.7f;


	for (int i = 0; i < BGM_SOUND_NUM; i++)
	{
		Bgm_Sound[i] = AudioEngine::INVALID_AUDIO_ID;
		AudioEngine::setVolume(Bgm_Sound[i], Volume);
	}



	return true;
}

void ExternScene::update(float dt)
{
	if (gg == false)
	{
		gg = true;
		Scene *scene = KGScene::createScene();
		scene = TransitionCrossFade::create(0.3f, scene);
		Director::sharedDirector()->replaceScene(scene);
	}
}
