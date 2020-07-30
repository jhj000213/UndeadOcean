#include "stdafx.h"


Scene* IntroScene::createScene()
{
	auto scene = Scene::create();
	auto layer = IntroScene::create();
	scene->addChild(layer);
	return scene;
}


bool IntroScene::init()
{

	if (!LayerColor::initWithColor(Color4B(255,255,255,255)))
		return false;

	BGLayer = Layer::create();
	this->addChild(BGLayer);
	LLayer = Layer::create();
	this->addChild(LLayer,10);

	Logo = Sprite::create("title.png");
	Logo->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	LLayer->addChild(Logo, 10);

	TouchS = Sprite::create("touchtoscreen.png");
	TouchS->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2 - 200));
	LLayer->addChild(TouchS, 20);

	auto seq = Sequence::create(DelayTime::create(0.5f), FadeOut::create(1.0f), FadeIn::create(0.7f), NULL);
	TouchS->runAction(CCRepeatForever::create(seq));

	mapEdit();

	BG_Camera = new CPNCamera();
	BG_Camera->init(BGLayer, Size(D_DESIGN_WIDTH * 3, D_DESIGN_HEIGHT), Size(D_DESIGN_WIDTH, D_DESIGN_HEIGHT));



	if (Bgm_Sound[2] == AudioEngine::INVALID_AUDIO_ID)
	{
		Bgm_Sound[2] = AudioEngine::play2d("sound/bgm/mainmenu.mp3", true, Volume);
	}



	gg = false;
	sceenS = 0.0f;
	schedule(schedule_selector(IntroScene::update), 0.0f);

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(IntroScene::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(IntroScene::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(IntroScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void IntroScene::update(float dt)
{
	BG_Camera->update(sceenS += dt * 20.0f);
}

void IntroScene::mapEdit()
{
	BG1 = Sprite::create("bg/stage1/bg3.jpg");
	BG1->setAnchorPoint(Vec2(0, 0));
	BG1->setPosition(Vec2(0, 0));
	BGLayer->addChild(BG1);

	BG2 = Sprite::create("bg/stage1/bg4.jpg");
	BG2->setAnchorPoint(Vec2(0, 0));
	BG2->setPosition(Vec2(BG1->boundingBox().size.width, 0));
	BGLayer->addChild(BG2);

	BG3 = Sprite::create("bg/stage1/bg5.jpg");
	BG3->setAnchorPoint(Vec2(0, 0));
	BG3->setPosition(Vec2(BG1->boundingBox().size.width + BG2->boundingBox().size.width, 0));
	BGLayer->addChild(BG3);


}

void IntroScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{

	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		location[i] = touch->getLocation();
		it++;

		if (gg == false)
		{
			gg = true;
			MapCode = 1;
			Scene *scene = BlackScene::createScene();
			scene = TransitionCrossFade::create(0.3f, scene);
			Director::sharedDirector()->replaceScene(scene);
		}
	}
}

void IntroScene::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
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

void IntroScene::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
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