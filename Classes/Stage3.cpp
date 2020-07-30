#include "stdafx.h"

Scene* Stage3::createScene()
{
	auto scene = Scene::create();

	auto layer = Stage3::create();

	scene->addChild(layer);

	return scene;
}

bool Stage3::init()
{
	if (!Layer::init())
		return false;

	UILayer = Layer::create();
	this->addChild(UILayer, 10);

	//!< 화면 사이즈 알아오는 구문
	Size size = Director::getInstance()->getVisibleSize();


	PauseButton = Sprite::create("pausebutton.png");
	PauseButton->setPosition(Vec2(1180, 670));
	UILayer->addChild(PauseButton);

	if (Bgm_Sound[2] == AudioEngine::INVALID_AUDIO_ID)
	{
		Bgm_Sound[2] = AudioEngine::play2d("sound/bgm/stage3.mp3", true, Volume);
	}

	//플레이어
	player = new cSubmarine;
	player->init(this);

	isPlayerMove = false;

	//쉴드
	shield = new cShieldmanager;
	shield->makeShield(this);

	//총알
	bullet = new cBulletmanager;
	bullet->makeBullet(this);


	//바리케이드
	barricade = new cBarricadeManager;
	barricade->makeBarricade(this);

	this->schedule(schedule_selector(Stage3::spawnBarricade), 1.0f);
	this->schedule(schedule_selector(Stage3::spawnBullet), 1.0f);
	this->schedule(schedule_selector(Stage3::Update));//충돌체크를 위한 스케줄  

	//터치
	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(Stage3::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(Stage3::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(Stage3::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//this->setTouchEnabled(true);
	//setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
	n_End = false;
	n_GameClear = false;
	n_pause = false;
	PlayTime = 0.0f;
	return true;
}

void Stage3::spawnBarricade(float dt)
{
	barricade->randomSpawn();
}

void Stage3::spawnBullet(float dt)
{
	bullet->randomBullet(player->SubmarinePoint->getPosition());
}

void Stage3::Update(float dt)
{
	if (v_GameClear.empty() == false)
	{
		for (GameClearLayer * layer : v_GameClear)
		{
			layer->m_update(dt);
		}
	}

	PlayTime += dt;
	if (PlayTime >= 60.0f && n_End == false)
	{
		n_GameClear = true;
		n_End = true;
	}
	if (n_End == false)
	{
		//쉴드 시간계산
		shield->schedule(dt);

		//플레이어
		player->move();

		//총알넘어감
		bullet->passBullet();

		//충돌체크
		for (int i = 0; i < shield->vShield.size(); i++)
		{
			if (shield->vShield.at(i)->complete)
			{
				if (bullet->checkCollision(shield->vShield.at(i)->sprShield->getBoundingBox()))
				{
					shield->shieldTime(i);
					log("check1");
				}
			}
		}

		if (bullet->checkCollision(player->SubmarinePoint->getBoundingBox()))
		{
			player->damage();
		}
		if (barricade->checkCollision(player->SubmarinePoint->getBoundingBox()))
		{
			player->damage();
		}
	}
	if (n_GameClear == true)
	{

			n_GameClear = false;
			GameClearLayer * Pause = GameClearLayer::n_create(UILayer, 0, 200000, 200000, PlayTime, 1, 1, 1, 2);//아이템
			UILayer->addChild(Pause);//스테이지 맥스 스코어
			v_GameClear.pushBack(Pause);

			auto ac = CallFunc::create(CC_CALLBACK_0(Stage3::GAmeClearAndScene, this));
			auto seq = Sequence::create(DelayTime::create(8.5f), RemoveSelf::create(), ac, NULL);
			Pause->runAction(seq);
		
	}
}

void Stage3::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{

	vector<Touch*> tps = touches;

	for (auto point : tps)
	{
		int touchIndex = point->getID();

		auto tp = point->getLocation();



		if (n_pause == false)
		{
			if (PauseButton->boundingBox().containsPoint(tp))
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

			isPlayerMove = player->touchBegan(tp, touchIndex);

			shield->BeganPointManager(tp, touchIndex);

		}
		else if (n_pause == true)
		{
			if (v_PauseLayer.front()->m_update(tp) == 1)
			{
				n_pause = false;

				v_PauseLayer.eraseObject(v_PauseLayer.front());

				this->resume();
				for (auto node : this->getChildren())
				{
					pauseRecursive(node, false);
				}
			}
			else if (v_PauseLayer.front()->m_update(tp) == 2)
			{
				//main
				ChangeBgm = true;
				MapCode = 1;
				Scene *scene = BlackScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			else if (v_PauseLayer.front()->m_update(tp) == 3)
			{
				//re
				ChangeBgm = true;
				MapCode = 0;
				Scene *scene = BlackScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
		}
	
	}

}

void Stage3::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{

	vector<Touch*> tps = touches;

	for (auto point : tps)
	{
		int touchIndex = point->getID();

		auto tp = point->getLocation();





		player->touchMove(tp, touchIndex);

		shield->MovedPointManager(tp, touchIndex);
	}

}

void Stage3::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	vector<Touch*> tps = touches;

	for (auto point : tps)
	{
		int touchIndex = point->getID();

		auto tp = point->getLocation();





		player->touchEnd(tp, touchIndex);

		shield->EndPointManager(tp, touchIndex);
		isPlayerMove = false;
	}
	
}

void Stage3::pauseRecursive(Node * _node, bool _pause)
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

void Stage3::GAmeClearAndScene()
{
	ChangeBgm = true;
	MapCode = 5;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}