#include "BlackScene.h"


Scene* BlackScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BlackScene::create();
	scene->addChild(layer);
	return scene;
}


bool BlackScene::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
		return false;

	if (ChangeBgm == true)
	{
		for (int i = 0; i < BGM_SOUND_NUM; i++)
		{
			AudioEngine::stop(Bgm_Sound[i]);
			Bgm_Sound[i] = AudioEngine::INVALID_AUDIO_ID;
		}
		ChangeBgm = false;
	}

	schedule(schedule_selector(BlackScene::update), 0.0f);

	Black = Sprite::create("black.png");
	Black->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(Black);

	
	return true;
}

void BlackScene::update(float dt)
{
	Time -= dt;
	if (Time <= 0.0f)
	{
		if (gg == false)
		{
			if (MapCode == 0)
			{
				gg = true;
				Scene *scene = IntroScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 1)
			{

				gg = true;
				Scene *scene = MainScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 2)
			{
				gg = true;
				Scene *scene = OptionScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 3)
			{

				gg = true;
				Scene *scene = GameoverScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 4)
			{

				gg = true;
				Scene *scene = MainScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 5)
			{

				gg = true;
				Scene *scene = StageSelectScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 6)//storage
			{
				gg = true;
				Scene *scene = StorageScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}

			if (MapCode == 7)//hanger
			{

				gg = true;
				Scene *scene = JackpotScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 10)
			{

				gg = true;
				Scene *scene = LoadScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 11)
			{

				gg = true;
				Scene *scene = Stage1::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 12)
			{

				gg = true;
				Scene *scene = Stage2::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 13)
			{

				gg = true;
				Scene *scene = Stage3::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
			if (MapCode == 30)
			{
				gg = true;
				Scene *scene = LogoScene::createScene();
				scene = TransitionCrossFade::create(0.3f, scene);
				Director::sharedDirector()->replaceScene(scene);
			}
		}
	}
}
