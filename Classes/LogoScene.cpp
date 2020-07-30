#include "stdafx.h"



Scene* LogoScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LogoScene::create();

	scene->addChild(layer);

	return scene;
}

bool LogoScene::init()
{
	if (!Layer::init())
		return false;

	

	BG = Sprite::create("teamlogo.jpg");
	BG->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(BG);



	gg = false;

	schedule(schedule_selector(LogoScene::update), 0.0f);
	return true;
}

void LogoScene::update(float dt)
{
	r_Time -= dt;
	if (r_Time <= 0 && gg == false)
	{
		gg = true;
		MapCode = 0;
		Scene *scene = BlackScene::createScene();
		scene = TransitionCrossFade::create(0.3f, scene);
		Director::sharedDirector()->replaceScene(scene);
	}
}
