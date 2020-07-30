#include "stdafx.h"



Scene* LoadScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadScene::init()
{
	if (!Layer::init())
		return false;

	TurnControl = UserDefault::getInstance()->getBoolForKey("TurnControl");

	BG = Sprite::create("loading_bg.png");
	BG->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(BG);

	Bar = Sprite::create("loading_bar.png");
	Bar->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(Bar,1);

	ghang = Sprite::create("loading_ghang.png");
	ghang->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	this->addChild(ghang, 1);

	auto ac = RotateBy::create(1.0f, 360);
	Bar->runAction(CCRepeatForever::create(ac));

	LoadSprite();
	LoadSound();

	
	EffVolume = Volume*0.3f;

	


	//for (int i = 0; i < EFFECT_SOUND_NUM; i++)
	//{
	//	AudioEngine::preload(EffectSoundName[i]);
	//}

	gg = false;
	e_Load = true;

	schedule(schedule_selector(LoadScene::update), 0.0f);
	return true;
}

void LoadScene::update(float dt)
{
	r_Time -= dt;
	if (r_Time <= 0 && e_Load == true && gg == false)
	{
		gg = true;
		MapCode = 10 + NowStage;
		Scene *scene = BlackScene::createScene();
		scene = TransitionCrossFade::create(0.3f, scene);
		Director::sharedDirector()->replaceScene(scene);
	}
}

void LoadScene::LoadSound()
{
	string BgmSoundName[BGM_SOUND_NUM] = { "sound/bgm/stage1.mp3", "sound/bgm/stage3.mp3",
		"sound/bgm/mainmenu.mp3", "sound/bgm/roulette.mp3", "sound/bgm/stage2.mp3" };
	for (int i = 0; i < BGM_SOUND_NUM; i++)
	{
		AudioEngine::preload(BgmSoundName[i]);
		Bgm_Sound[i] = AudioEngine::INVALID_AUDIO_ID;
	}

	AudioEngine::preload("sound/effect/aghi_dead.mp3");
	AudioEngine::preload("sound/effect/box_open.mp3");
	AudioEngine::preload("sound/effect/clear_num.mp3");
	AudioEngine::preload("sound/effect/clear_table.mp3");
	AudioEngine::preload("sound/effect/crab_dead.mp3");
	AudioEngine::preload("sound/effect/crab_hide.mp3");
	AudioEngine::preload("sound/effect/crab_thorn.mp3");
	AudioEngine::preload("sound/effect/crab_up.mp3");
	AudioEngine::preload("sound/effect/hapari_dead.mp3");
	AudioEngine::preload("sound/effect/hapari_shoot.mp3");
	AudioEngine::preload("sound/effect/japonica_dead.mp3");
	AudioEngine::preload("sound/effect/japonica_shoot.mp3");
	AudioEngine::preload("sound/effect/miniob_boom.mp3");
	AudioEngine::preload("sound/effect/missailhit_shild.mp3");
	AudioEngine::preload("sound/effect/roulette_button.mp3");
	AudioEngine::preload("sound/effect/roulette_jackpot.mp3");
	AudioEngine::preload("sound/effect/submarin_missail_shoot.mp3");
	AudioEngine::preload("sound/effect/torpedo_boom.mp3");
	AudioEngine::preload("sound/effect/torpedo_shoot.mp3");
	AudioEngine::preload("sound/effect/fishhead_breath.mp3");
	AudioEngine::preload("sound/effect/hanger_sceen.mp3");
	AudioEngine::preload("sound/effect/middleship_boom.mp3");
	AudioEngine::preload("sound/effect/fishhead_roar.mp3");
	AudioEngine::preload("sound/effect/fishhead_rain.mp3");
	AudioEngine::preload("sound/effect/bigrobot_missail.mp3");
	AudioEngine::preload("sound/effect/bigrobot_razer.mp3");
	AudioEngine::preload("sound/effect/middleship_rutan.mp3");
	AudioEngine::preload("sound/effect/dragon_razer.mp3");
	AudioEngine::preload("sound/effect/fishhead_hurricane.mp3");
	AudioEngine::preload("sound/effect/fishhead_crash.mp3");
}

void LoadScene::LoadSprite()
{
	//UI
	Director::getInstance()->getTextureCache()->addImage("joystick_top.png");
	Director::getInstance()->getTextureCache()->addImage("joystick_under.png");
	Director::getInstance()->getTextureCache()->addImage("pausebutton.png");
	Director::getInstance()->getTextureCache()->addImage("submarin/button/torpedobutton.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("submarin/button/torpedobuttomani.plist");

	//BG
	for (int i = 0; i < 6; i++)
	{
		char str[256];
		sprintf(str, "bg/stage1/bg%d.jpg", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "bg/stage2/bg%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	Director::getInstance()->getTextureCache()->addImage("bg/stage2/bg6.png");



	//Monster
	Director::getInstance()->getTextureCache()->addImage("enemy/hp_bar.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/hp_box.png");

	//Aghi
	Director::getInstance()->getTextureCache()->addImage("enemy/aghi/agi_hitpoint.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/aghi/aghidead.plist");
	for (int i = 0; i < 4; i++)
	{
		char str[256];
		sprintf(str, "enemy/aghi/agi%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/aghi/agiwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}



	//UpAghi
	Director::getInstance()->getTextureCache()->addImage("enemy/upaghi/agihit.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/upaghi/effect.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/upaghi/upaghidead.plist");
	for (int i = 0; i < 4; i++)
	{
		char str[256];
		sprintf(str, "enemy/upaghi/agi%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/upaghi/agiwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}


	//hapari
	Director::getInstance()->getTextureCache()->addImage("enemy/hapari/hapari_hitpoint.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/hapari/missail.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/hapari/haparidead.plist");
	for (int i = 0; i < 3; i++)
	{
		char str[256];
		sprintf(str, "enemy/hapari/hapari%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/hapari/hapariwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	//Japonica
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/japonica/dead/japonicadead.plist");
	Director::getInstance()->getTextureCache()->addImage("enemy/japonica/japonicahit.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/japonica/sparkjaponica0.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/japonica/sparkjaponica1.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/japonica/razer/razerhit.png");
	for (int i = 0; i < 18; i++)
	{
		char str[256];
		sprintf(str, "enemy/japonica/razer/danger%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	for (int i = 0; i < 8; i++)
	{
		char str[256];
		sprintf(str, "enemy/japonica/japonica%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/japonica/japonicawhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	//MiddleShip
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/middleship/hechi.plist");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/boom/b0.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/boom/b1.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/boom/b2.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/boom/b3.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/boom/b4.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/boom/b6.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/boom/bhitpoint.png");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/middleship/bullet/bullet.plist");

	for (int i = 0; i < 24; i++)
	{
		char str[256];
		sprintf(str, "enemy/middleship/change/midiumchange%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	for (int i = 0; i < 12; i++)
	{
		char str[256];
		sprintf(str, "enemy/middleship/dead/dragondead%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/dragon/dragonhit.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/dragon/dragonwhite.png");
	for (int i = 0; i < 17; i++)
	{
		char str[256];
		sprintf(str, "enemy/middleship/dragon/dragon%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/midium/midiumhit.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/midium/midiumwhite.png");
	for (int i = 0; i < 17; i++)
	{
		char str[256];
		sprintf(str, "enemy/middleship/midium/midium%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/middleship/miniob/dead/dead.plist");
	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/miniob/juggernautsmallsizehit.png");
	for (int i = 0; i < 3; i++)
	{
		char str[256];
		sprintf(str, "enemy/middleship/miniob/juggernautsmallsize%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/middleship/miniob/juggernautsmallsizewhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	Director::getInstance()->getTextureCache()->addImage("enemy/middleship/razer/razerhit.png");
	for (int i = 0; i < 22; i++)
	{
		char str[256];
		sprintf(str, "enemy/middleship/razer/razer%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}


	//Crab
	Director::getInstance()->getTextureCache()->addImage("enemy/crab/barrier/shildhit.png");
	for (int i = 0; i < 5; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/barrier/shild%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	Director::getInstance()->getTextureCache()->addImage("enemy/crab/body/bodyhit.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/crab/body/handhit.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/crab/body/body.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/crab/body/bodywhite.png");
	for (int i = 0; i < 4; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/body/bighand%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/crab/body/bighandwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	for (int i = 0; i < 4; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/body/smallhand%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/crab/body/smallhandwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/crab/call/call_h.plist");

	for (int i = 0; i < 13; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/dead/dead%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/crab/handboom/crab_handboom.plist");

	Director::getInstance()->getTextureCache()->addImage("enemy/crab/leg/leghit.png");
	for (int i = 0; i < 4; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/leg/left/leg%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/crab/leg/left/legwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	for (int i = 0; i < 4; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/leg/right/leg%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/crab/leg/right/legwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/crab/legboom/left/leftlegboom.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/crab/legboom/right/rightlegboom.plist");

	Director::getInstance()->getTextureCache()->addImage("enemy/crab/missail/dok.png");

	for (int i = 0; i < 9; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/punch/punch%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/crab/punch/punchwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	for (int i = 0; i < 7; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/shildmake/shildmake%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/crab/shildmake/shildmakewhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	for (int i = 0; i < 12; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/shildbreak/shieldbreak%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	for (int i = 0; i < 11; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/smoke/smog%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	Director::getInstance()->getTextureCache()->addImage("enemy/crab/wave/wavehit.png");
	for (int i = 0; i < 3; i++)
	{
		char str[256];
		sprintf(str, "enemy/crab/wave/wave%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}




	//BigRobot
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/bigrobot/midrazer/normal.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/bigrobot/midrazer/shoot.plist");

	Director::getInstance()->getTextureCache()->addImage("enemy/bigrobot/dead/white.png");
	for (int i = 0; i < 12; i++)
	{
		char str[256];
		sprintf(str, "enemy/bigrobot/dead/middead%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	Director::getInstance()->getTextureCache()->addImage("enemy/bigrobot/missail/missailhit.png");
	for (int i = 0; i < 21; i++)
	{
		char str[256];
		sprintf(str, "enemy/bigrobot/missail/missail%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	Director::getInstance()->getTextureCache()->addImage("enemy/bigrobot/normal/robothit.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/bigrobot/missail/robotwhite.png");
	for (int i = 0; i < 6; i++)
	{
		char str[256];
		sprintf(str, "enemy/bigrobot/normal/robot%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	Director::getInstance()->getTextureCache()->addImage("enemy/bigrobot/razer/razerhit.png");
	for (int i = 0; i < 11; i++)
	{
		char str[256];
		sprintf(str, "enemy/bigrobot/razer/midshoot%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	//AttShip
	Director::getInstance()->getTextureCache()->addImage("enemy/attship/normal/attshiphit.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/attship/normal/attshipwhite.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("enemy/attship/dead/attshipdead.plist");
	for (int i = 0; i < 10; i++)
	{
		char str[256];
		sprintf(str, "enemy/attship/normal/attship%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	//FishHead
	Director::getInstance()->getTextureCache()->addImage("enemy/fishhead/breath/breathhit.png");
	for (int i = 0; i < 19; i++)
	{
		char str[256];
		sprintf(str, "enemy/fishhead/breath/breath%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	Director::getInstance()->getTextureCache()->addImage("enemy/fishhead/crash/crashhit.png");
	for (int i = 0; i < 4; i++)
	{
		char str[256];
		sprintf(str, "enemy/fishhead/crash/crash%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	for (int i = 0; i < 9; i++)
	{
		char str[256];
		sprintf(str, "enemy/fishhead/dead/dead%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	for (int i = 0; i < 2; i++)
	{
		char str[256];
		sprintf(str, "enemy/fishhead/hurricane/hurricane%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	Director::getInstance()->getTextureCache()->addImage("enemy/fishhead/normal/fishheadhit.png");
	for (int i = 0; i < 5; i++)
	{
		char str[256];
		sprintf(str, "enemy/fishhead/normal/fishhead%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
		sprintf(str, "enemy/fishhead/normal/fishheadwhite%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	Director::getInstance()->getTextureCache()->addImage("enemy/fishhead/rain/storn.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/fishhead/rain/stornhit.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/fishhead/rain/rainboom0.png");
	Director::getInstance()->getTextureCache()->addImage("enemy/fishhead/rain/rainboom1.png");
	for (int i = 0; i < 12; i++)
	{
		char str[256];
		sprintf(str, "enemy/fishhead/roar/roar%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}

	//Submarin
	Director::getInstance()->getTextureCache()->addImage("submarin/missail_black.png");
	Director::getInstance()->getTextureCache()->addImage("submarin/missail_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("submarin/animation/bubble.plist");
	//life
	Director::getInstance()->getTextureCache()->addImage("submarin/hp_bar.png");
	Director::getInstance()->getTextureCache()->addImage("submarin/hp_cover.png");
	Director::getInstance()->getTextureCache()->addImage("submarin/hp_gaze.png");
	Director::getInstance()->getTextureCache()->addImage("submarin/submarinhitpoint.png");
	Director::getInstance()->getTextureCache()->addImage("submarin/airgun/airgun.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("submarin/airgun/airgun_boom.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("submarin/animation/torpedo_boom.plist");


	//mapselect
	Director::getInstance()->getTextureCache()->addImage("mapselect/map.png");
	Director::getInstance()->getTextureCache()->addImage("mapselect/postit_0.png");
	Director::getInstance()->getTextureCache()->addImage("mapselect/postit_1.png");
	Director::getInstance()->getTextureCache()->addImage("mapselect/table.png");
	Director::getInstance()->getTextureCache()->addImage("mapselect/title_0.png");
	Director::getInstance()->getTextureCache()->addImage("mapselect/title_1.png");
	Director::getInstance()->getTextureCache()->addImage("mapselect/whitegir.png");

	Director::getInstance()->getTextureCache()->addImage("pause/main.png");
	Director::getInstance()->getTextureCache()->addImage("pause/restart.png");
	Director::getInstance()->getTextureCache()->addImage("pause/resume.png");
	Director::getInstance()->getTextureCache()->addImage("pause/sound.png");
	Director::getInstance()->getTextureCache()->addImage("pause/table.png");

	//gameclear
	Director::getInstance()->getTextureCache()->addImage("gameclear/coin.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/graygir.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/missail.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/msicom0.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/msicom1.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/msicom2.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/score.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/table.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/time.png");
	Director::getInstance()->getTextureCache()->addImage("gameclear/whitegir.png");

	//gameover
	for (int i = 0; i < 6; i++)
	{
		char str[256];
		sprintf(str, "gameover/gameover%d.png", i);
		Director::getInstance()->getTextureCache()->addImage(str);
	}
	Director::getInstance()->getTextureCache()->addImage("gameover/main.png");
	Director::getInstance()->getTextureCache()->addImage("gameover/restart.png");


	//HM


}

