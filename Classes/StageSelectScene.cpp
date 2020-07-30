#include "BlackScene.h"


Scene* StageSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StageSelectScene::create();
	scene->addChild(layer);
	return scene;
}


bool StageSelectScene::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
		return false;

	Table = Sprite::create("mapselect/table.png");
	Table->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(Table);

	n_Map = Sprite::create("mapselect/map.png");
	n_Map->setAnchorPoint(Vec2(0, 0.5));
	n_Map->setScale(0.9f);
	n_Map->setPosition(Vec2(0, D_DESIGN_HEIGHT / 2 - 50));
	this->addChild(n_Map);

	Title = MenuItemImage::create("mapselect/title_0.png", "mapselect/title_1.png", CC_CALLBACK_0(StageSelectScene::MoveScene,this));


	PostIt_1 = MenuItemImage::create("mapselect/postit_0.png", "mapselect/postit_1.png", CC_CALLBACK_1(StageSelectScene::StageSelect, this));
	PostIt_1->setTag(1);
	PostIt_1->setAnchorPoint(Vec2(0,0));


	PostIt_2 = MenuItemImage::create("mapselect/postit_0.png", "mapselect/postit_1.png", CC_CALLBACK_1(StageSelectScene::StageSelect,  this));
	PostIt_2->setTag(2);
	PostIt_2->setAnchorPoint(Vec2(0, 0));


	PostIt_3 = MenuItemImage::create("mapselect/postit_0.png", "mapselect/postit_1.png", CC_CALLBACK_1(StageSelectScene::StageSelect,  this));
	PostIt_3->setTag(3);
	PostIt_3->setAnchorPoint(Vec2(0, 0));

	Stage1ScoreL = LabelBMFont::create("0", "fonts/editfont.fnt");
	Stage1ScoreL->setScale(0.7f);
	Stage1ScoreL->setPosition(Vec2(8000, 8000));//145,25
	this->addChild(Stage1ScoreL, 10);

	Stage2ScoreL = LabelBMFont::create("0", "fonts/editfont.fnt");
	Stage2ScoreL->setScale(0.7f);
	Stage2ScoreL->setPosition(Vec2(8000, 8000));
	this->addChild(Stage2ScoreL, 10);

	Stage3ScoreL = LabelBMFont::create("0", "fonts/editfont.fnt");
	Stage3ScoreL->setScale(0.7f);
	Stage3ScoreL->setPosition(Vec2(8000, 8000));
	this->addChild(Stage3ScoreL, 10);


	

	menu1 = Menu::create(PostIt_1, nullptr);
	menu1->setPosition(Vec2(8000, 8000));
	n_Map->addChild(menu1);
	menu2 = Menu::create(PostIt_2, nullptr);
	menu2->setPosition(Vec2(8000, 8000));
	n_Map->addChild(menu2);
	menu3 = Menu::create(PostIt_3, nullptr);
	menu3->setPosition(Vec2(8000, 8000));
	n_Map->addChild(menu3);

	Vec2 Pos[3] = { Vec2(85, 130), Vec2(140, 145), Vec2(195, 130) };
	for (int i = 0; i < 3; i++)
	{
		Stage1WhiteGir[i] = Sprite::create("mapselect/whitegir.png");
		Stage1WhiteGir[i]->setPosition(Pos[i]);
		PostIt_1->addChild(Stage1WhiteGir[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		Stage1WhiteGir[i] = Sprite::create("mapselect/whitegir.png");
		Stage1WhiteGir[i]->setPosition(Pos[i]);
		PostIt_2->addChild(Stage1WhiteGir[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		Stage1WhiteGir[i] = Sprite::create("mapselect/whitegir.png");
		Stage1WhiteGir[i]->setPosition(Pos[i]);
		PostIt_3->addChild(Stage1WhiteGir[i]);
	}

	menu4 = Menu::create(Title, nullptr);
	menu4->setPosition(Vec2(80, 640));
	this->addChild(menu4);

	schedule(schedule_selector(StageSelectScene::update), 0.0f);


	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(StageSelectScene::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(StageSelectScene::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(StageSelectScene::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	nowSelectStage = 0;

	return true;
}

void StageSelectScene::update(float dt)
{
	if (nowSelectStage == 1)
	{
		menu1->setPosition(Vec2(366, 450));
		menu2->setPosition(Vec2(8000,8000));
		menu3->setPosition(Vec2(8000,8000));

		Stage1ScoreL->setPosition(Vec2(511, 475));
		Stage2ScoreL->setPosition(Vec2(8000, 8000));
		Stage3ScoreL->setPosition(Vec2(8000, 8000));
	}
	else if (nowSelectStage == 2)
	{
		menu1->setPosition(Vec2(8000, 8000));
		menu2->setPosition(Vec2(900, 100));
		menu3->setPosition(Vec2(8000, 8000));

		Stage1ScoreL->setPosition(Vec2(8000, 8000));
		Stage2ScoreL->setPosition(Vec2(995, 160));
		Stage3ScoreL->setPosition(Vec2(8000, 8000));
	}
	else if (nowSelectStage == 3)
	{
		menu1->setPosition(Vec2(8000, 8000));
		menu2->setPosition(Vec2(8000, 8000));
		menu3->setPosition(Vec2(815, 420));

		Stage1ScoreL->setPosition(Vec2(8000, 8000));
		Stage2ScoreL->setPosition(Vec2(8000, 8000));
		Stage3ScoreL->setPosition(Vec2(915, 450));
	}
	else
	{
		menu1->setPosition(Vec2(8000, 8000));
		menu2->setPosition(Vec2(8000, 8000));
		menu3->setPosition(Vec2(8000, 8000));
	}
}

void StageSelectScene::MoveScene()
{
	MapCode = 1;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}

void StageSelectScene::StageSelect(Ref * sender)
{
	nowSelectStage = ((MenuItemImage*)sender)->getTag();

	NowStage = nowSelectStage;
	ChangeBgm = true;
	MapCode = 10;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
	
}

void StageSelectScene::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{

	std::vector<Touch*>::const_iterator it = touches.begin();
	Touch *touch;
	Point location[2];

	for (int i = 0; i < touches.size(); i++)
	{
		touch = (Touch*)(*it);
		location[i] = touch->getLocation();
		it++;

		if (location[i].x>220 && location[i].x<345 &&
			location[i].y>435 && location[i].y < 555)
		{
			nowSelectStage = 1;
		}
		if (location[i].x>700 && location[i].x<820 &&
			location[i].y>120 && location[i].y < 195)
		{
			nowSelectStage = 2;
		}
		if (location[i].x>1000 && location[i].x<1100 &&
			location[i].y>435 && location[i].y < 555)
		{
			nowSelectStage = 3;
		}

	}
}

void StageSelectScene::onTouchesMoved(const std::vector<Touch*>& touches, Event* unused_event)
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

void StageSelectScene::onTouchesEnded(const std::vector<Touch*>& touches, Event* unused_event)
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