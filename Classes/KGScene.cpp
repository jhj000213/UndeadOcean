#include "stdafx.h"



Scene* KGScene::createScene()
{
	auto scene = Scene::create();

	auto layer = KGScene::create();

	scene->addChild(layer);

	return scene;
}

bool KGScene::init()
{
	if (!Layer::init())
		return false;



	BG = Sprite::create("kglogo.png");
	BG->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(BG);



	gg = false;

	schedule(schedule_selector(KGScene::update), 0.0f);
	return true;
}

void KGScene::update(float dt)
{
	r_Time -= dt;
	if (r_Time <= 0 && gg == false)
	{
		gg = true;
		MapCode = 30;
		Scene *scene = BlackScene::createScene();
		scene = TransitionCrossFade::create(0.3f, scene);
		Director::sharedDirector()->replaceScene(scene);
	}
}
