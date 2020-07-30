#include "stdafx.h"

#define FRAME_TIME 0.1f
Scene* GameoverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameoverScene::create();
	scene->addChild(layer);
	return scene;
}


bool GameoverScene::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
		return false;

	Table = Sprite::create("gameover/gameover0.png");
	Table->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(Table);

	RestartButton = Sprite::create("gameover/restart.png");
	RestartButton->setPosition(Vec2(8000, 8000));
	this->addChild(RestartButton,10);

	MainButton = Sprite::create("gameover/main.png");
	MainButton->setPosition(Vec2(8000, 8000));
	this->addChild(MainButton, 10);

	nowFrame = 0;
	n_time = FRAME_TIME;

	AudioEngine::stop(Bgm_Sound[0]);

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(GameoverScene::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(GameoverScene::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(GameoverScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	schedule(schedule_selector(GameoverScene::update), 0.0f);

	return true;
}

void GameoverScene::update(float dt)
{
	n_time -= dt;
	if (n_time <= 0.0f)
	{
		n_time = FRAME_TIME;
		nowFrame++;
		if (nowFrame == 6)
		{
			nowFrame = 5;
			RestartButton->setPosition(Vec2(920,120));
			MainButton->setPosition(Vec2(370,120));
		}
			

		char str[256];
		sprintf(str, "gameover/gameover%d.png", nowFrame);
		Table->setTexture(str);
	}
}
void GameoverScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{

	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		location[i] = touch->getLocation();
		it++;

		if (RestartButton->boundingBox().containsPoint(location[i]))
		{
			MapCode = 0;
			Scene *scene = BlackScene::createScene();
			scene = TransitionCrossFade::create(0.3f, scene);
			Director::sharedDirector()->replaceScene(scene);
		}
		if (MainButton->boundingBox().containsPoint(location[i]))
		{
			MapCode = 1;
			Scene *scene = BlackScene::createScene();
			scene = TransitionCrossFade::create(0.3f, scene);
			Director::sharedDirector()->replaceScene(scene);
		}
	}
}

void GameoverScene::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
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

void GameoverScene::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
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