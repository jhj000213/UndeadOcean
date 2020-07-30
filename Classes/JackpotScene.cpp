//추가해야하는것


//벨,해골,7,구

//레어: 솔라, 드레이븐
//언커먼: 블랙스틸, 엠타, 지프틴
//커먼: 마나피, 플론, 크내폰

//m_material[0] 드레이븐		(M1)
//m_material[1] 블랙스틸		(M2)
//m_material[2] 플론			(M3)
//m_material[3] 엠타			(M4)
//m_material[4] 지프틴			(M5)
//m_material[5] 크내폰			(M6)
//m_material[6] 마나피			(M7)
//m_material[7] 솔라			(M8)


//하급 상자   커먼:1~30     언커먼:10~20      레어:x
//중급 상자   커먼:30~50    언커먼:20~30     레어:1~3
//상급 상자   커먼:50~70   언커먼:30~40     레어:3~7

#include "stdafx.h"
#include <stdlib.h>
#include "SimpleAudioEngine.h"

int g_TimeCheck = 0;
bool g_StopCheck = false;
bool Check = false;
int random1;
int random2;
int random3;

Scene* JackpotScene::createScene()
{
	auto scene = Scene::create();
	auto layer = JackpotScene::create();
	scene->addChild(layer);
	return scene;
}

bool JackpotScene::init()
{
	srand((unsigned)time(NULL));
	//터치
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	//레이어
	if (!LayerColor::initWithColor(Color4B::GRAY))
		return false;
	//_screenSize 화면사이즈
	auto _screenSize = Director::sharedDirector()->getWinSize();

	int asdf = 10000000;							//임의로 골드값 지정
	UserDefault::getInstance()->setIntegerForKey("gold", asdf);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hm/rolling.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("hm/main/effect.plist");


	if (Bgm_Sound[3] == AudioEngine::INVALID_AUDIO_ID)
	{
		Bgm_Sound[3] = AudioEngine::play2d("sound/bgm/roulette.mp3", true, Volume);
	}

	g_StopCheck = false;
	g_TimeCheck = 0;
	JackpotCheck = 0;


	//	Sprite* sprite = Sprite::create("hanger.png");
	//	sprite->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);
	//	this->addChild(sprite, 100);
	//
	//	RotateBy* ro1 = RotateBy::create(0.15f, 20);
	//	RotateBy* ro2 = RotateBy::create(0.15f, -20);
	//	auto hide1 = CallFunc::create(CC_CALLBACK_0(JackpotScene::hideLayer0, this));
	//	auto show1 = CallFunc::create(CC_CALLBACK_0(JackpotScene::showLayer0, this));
	//	FadeIn* fadein = FadeIn::create(1.0f);
	//	FadeOut* fadeout = FadeOut::create(1.0f);
	//	Sequence* se1 = Sequence::create(ro1->clone(), ro2->clone(), ro2->clone(), ro1->clone(), NULL);
	//	Sequence* se2 = Sequence::create(fadein, fadeout, NULL);
	//	Repeat* ref = Repeat::create(se1->clone(), 5);
	//	Spawn* sp1 = Spawn::create(se2->clone(), ref->clone(), NULL);
	//
	//	sprite->runAction(sp1->clone());
	//


	m_layer[0] = LayerColor::create(Color4B(Color4B::BLACK), winSize.width, winSize.height);
	m_layer[0]->setPosition(0, 0);
	m_layer[0]->setTag(0);
	m_layer[0]->setOpacity(200);
	m_layer[0]->setVisible(false);
	this->addChild(m_layer[0], 5);

	for (int i = 0; i < 8; i++)					//재료 스프라이트
	{
		sprintf(str, "hm/making/M%d.png", i + 1);
		m_material[i] = Sprite::create(str);
		m_material[i]->setVisible(false);
		m_layer[0]->addChild(m_material[i], 15);
	}

	m_label[0] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");
	m_label[0]->setPosition(D_DESIGN_WIDTH - 150, D_DESIGN_HEIGHT - 55);		//돈
	this->addChild(m_label[0], 4);

	m_label[1] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");
	m_label[1]->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2 - 70);		//상자에서 나온 재료 개수
	m_label[1]->setScale(2);
	m_layer[0]->addChild(m_label[1], 17);

	m_Sprite[0] = Sprite::create();
	m_Sprite[0]->setPosition(winSize.width / 2 - 380, winSize.height / 2);		//a
	m_Sprite[0]->setTag(0);
	this->addChild(m_Sprite[0], 2);

	m_Sprite[1] = Sprite::create();
	m_Sprite[1]->setPosition(winSize.width / 2 - 80, winSize.height / 2);		//b
	m_Sprite[1]->setTag(1);
	this->addChild(m_Sprite[1], 2);

	m_Sprite[2] = Sprite::create();
	m_Sprite[2]->setPosition(winSize.width / 2 + 220, winSize.height / 2);		//c
	m_Sprite[2]->setTag(2);
	this->addChild(m_Sprite[2], 2);

	/////////////////////////////////////////////////////////////////////////

	Sprite* A = Sprite::create("hm/main/pic3.png");
	A->setPosition(D_DESIGN_WIDTH / 2 - 380, D_DESIGN_HEIGHT / 2);
	A->setTag(4);
	this->addChild(A, 2);

	Sprite* B = Sprite::create("hm/main/pic1.png");
	B->setPosition(D_DESIGN_WIDTH / 2 - 80, D_DESIGN_HEIGHT / 2);
	B->setTag(5);
	this->addChild(B, 2);

	Sprite* C = Sprite::create("hm/main/pic2.png");
	C->setPosition(D_DESIGN_WIDTH / 2 + 220, D_DESIGN_HEIGHT / 2);
	C->setTag(6);
	this->addChild(C, 2);

	//////////////////////////////////////////////////////////////////////////////////////

	m_Box[0] = Sprite::create("hm/main/steel.png");
	m_Box[0]->setPosition(D_DESIGN_WIDTH / 2 - 380, D_DESIGN_HEIGHT / 2);
	this->addChild(m_Box[0], 1);

	m_Box[1] = Sprite::create("hm/main/steel.png");
	m_Box[1]->setPosition(D_DESIGN_WIDTH / 2 - 80, D_DESIGN_HEIGHT / 2);
	this->addChild(m_Box[1], 1);

	m_Box[2] = Sprite::create("hm/main/steel.png");
	m_Box[2]->setPosition(D_DESIGN_WIDTH / 2 + 220, D_DESIGN_HEIGHT / 2);
	this->addChild(m_Box[2], 1);


	m_Sprite[3] = Sprite::create();
	m_Sprite[3]->setPosition(D_DESIGN_WIDTH / 2 - 380, D_DESIGN_HEIGHT / 2);
	this->addChild(m_Sprite[3], 3);

	m_Sprite[4] = Sprite::create();
	m_Sprite[4]->setPosition(D_DESIGN_WIDTH / 2 - 80, D_DESIGN_HEIGHT / 2);
	this->addChild(m_Sprite[4], 3);

	m_Sprite[5] = Sprite::create();
	m_Sprite[5]->setPosition(D_DESIGN_WIDTH / 2 + 220, D_DESIGN_HEIGHT / 2);
	this->addChild(m_Sprite[5], 3);

	m_Sprite[6] = Sprite::create("hm/main/box1.png");
	m_Sprite[6]->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);			//하급 재료박스
	//	m_Sprite[6]->setVisible(false);
	m_Sprite[6]->setOpacity(0);
	m_layer[0]->addChild(m_Sprite[6], 8);

	m_Sprite[7] = Sprite::create("hm/main/box2.png");
	m_Sprite[7]->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);			//중급 재료박스
	//	m_Sprite[7]->setVisible(false);
	m_Sprite[7]->setOpacity(0);
	m_layer[0]->addChild(m_Sprite[7], 8);

	m_Sprite[8] = Sprite::create(+"hm/main/box3.png");
	m_Sprite[8]->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);			//상급 재료박스
	//	m_Sprite[8]->setVisible(false);
	m_Sprite[8]->setOpacity(0);
	m_layer[0]->addChild(m_Sprite[8], 8);

	m_Sprite[9] = Sprite::create();
	m_Sprite[9]->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);	//상자나오는 이펙트
	m_Sprite[9]->setScale(0.5);
	m_layer[0]->addChild(m_Sprite[9], 10);

	m_Sprite[10] = Sprite::create();
	m_Sprite[10]->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);		//상자에서 나오는 재료
	m_Sprite[10]->setVisible(false);
	m_Sprite[10]->setScale(3);
	m_layer[0]->addChild(m_Sprite[10], 11);

	Sprite* background = Sprite::create("hm/main/main.png");		//배경
	Size winSize = Director::getInstance()->getWinSize();
	background->setPosition(ccp(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	background->setScale(winSize.width / background->getContentSize().width);
	this->addChild(background);


	///////////////////////////////////////////////////////////////////////////////////////


	auto AdB = MenuItemImage::create("hm/main/Ad.png", "hm/main/Ad.png", CC_CALLBACK_1(JackpotScene::Go_Adventure, this));
	AdB->setPosition(winSize.width / 2 - 380, 80);

	auto haB = MenuItemImage::create("hm/main/ha.png", "hm/main/ha.png", CC_CALLBACK_1(JackpotScene::Go_Hangar, this));
	haB->setPosition(winSize.width / 2 - 80, 80);

	auto opB = MenuItemImage::create("hm/main/op.png", "hm/main/op.png", CC_CALLBACK_1(JackpotScene::Go_Option, this));
	opB->setPosition(winSize.width / 2 + 220, 80);

	auto titleB = MenuItemImage::create("hm/main/titlebut.png", "hm/main/titlebut.png", CC_CALLBACK_1(JackpotScene::Go_Title, this));
	titleB->setPosition(50, 660);

	auto rollingB = MenuItemImage::create("hm/main/roulettestart.png", "hm/main/roulettestartSel.png", CC_CALLBACK_1(JackpotScene::Rolling, this));
	rollingB->setScale(0.5);
	rollingB->setPosition(1180, 400);


	auto MenU = Menu::create(AdB, haB, opB, rollingB, titleB, NULL);
	MenU->setPosition(Vec2::ZERO);
	this->addChild(MenU, 2);

	auto ok = MenuItemImage::create("hm/main/ok.png", "hm/main/okSel.png", CC_CALLBACK_1(JackpotScene::OK, this));
	ok->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2 - 130);

	auto MenU2 = Menu::create(ok, NULL);
	MenU2->setPosition(Vec2::ZERO);
	m_layer[0]->addChild(MenU2, 17);

	//	int nLoop = 0;										
	//	int tmp = 0;										
	//	srand((unsigned int)time(NULL));					
	//	while (nLoop < 20)									
	//	{													
	//														
	//		if (Random(50) == true)							
	//		{												
	//			log("success\n");							
	//		}												
	//														
	//		else											
	//		{												
	//			log("fail\n");								
	//														
	//		}												
	//		nLoop++;												 
	//	}				
	schedule(schedule_selector(JackpotScene::Update), 0.01f);

	return true;
}

void JackpotScene::Update(float dt)
{
	string gold = UserDefault::getInstance()->getStringForKey("gold");

	m_label[0]->setString(gold);

	//스케쥴, 시간받아오기
	if (g_StopCheck == true)
	{
		static float time = 0;
		time += dt;
		//		log("%f, %f", time ,dt)
		RotateBy* ro1 = RotateBy::create(0.2f, 30);
		RotateBy* ro2 = RotateBy::create(0.2f, -30);
		auto hide1 = CallFunc::create(CC_CALLBACK_0(JackpotScene::hide, this));
		auto show1 = CallFunc::create(CC_CALLBACK_0(JackpotScene::showLayer0, this));
		auto flash1 = CallFunc::create(CC_CALLBACK_0(JackpotScene::flash, this));
		auto sprite = CallFunc::create(CC_CALLBACK_0(JackpotScene::RandomMaterial, this));

		FadeIn* fadein = FadeIn::create(0.2f);
		FadeOut* fadeout = FadeOut::create(1.0f);
		DelayTime* de1 = DelayTime::create(1.0f);
		DelayTime* de2 = DelayTime::create(8.0f);

		Sequence* se1 = Sequence::create(ro1, ro2, ro2, ro1, de1, NULL);
		Sequence* se2 = Sequence::create(show1, fadein, de2, fadeout, hide1, NULL);
		Repeat* ref = Repeat::create(se1, 5);
		Sequence* se3 = Sequence::create(de1, ref, NULL);
		auto ac = CallFunc::create(CC_CALLBACK_0(JackpotScene::boxopensound, this));
		Sequence* se4 = Sequence::create(de2,ac, flash1, de1, de1, sprite, NULL);

		Spawn* sp1 = Spawn::create(se2, se3, se4, NULL);





		//애니메이션 종료후 스프라이트
		if (time > 2.0f)
		{
			time = 0.0f;


			int random = rand() % 2;
			if (g_TimeCheck == 0)
			{
				removeChildByTag(0);

				random1 = rand() % 4 + 1;
				sprintf(an, "hm/main/pic%d.png", random1);
				m_Sprite[3]->setTexture(an);

			}

			if (g_TimeCheck == 1)
			{
				removeChildByTag(1);

				if (random1 > 0 && random1 <= 2)
					random2 = rand() % 2 + 1;
				else
					random2 = rand() % 2 + 3;
				sprintf(an, "hm/main/pic%d.png", random2);
				m_Sprite[4]->setTexture(an);
			}

			if (g_TimeCheck == 2)
			{
				removeChildByTag(2);
				if (random2 > 0 && random2 <= 2)
					random3 = rand() % 2 + 1;
				else
					random3 = rand() % 2 + 3;


				sprintf(an, "hm/main/pic%d.png", random3);
				m_Sprite[5]->setTexture(an);
			}

			if (g_TimeCheck == 3)
			{

				g_StopCheck = false;
				g_TimeCheck = 0;

				if (random1 == random2 && random1 != random3)		//중급
				{
					log("random1 = %d", random1);
					log("random2 = %d", random2);
					log("random3 = %d", random3);
					m_layer[0]->setVisible(true);
					m_Sprite[7]->runAction(sp1->clone());
					m_Sprite[9]->runAction(se3->clone());
					JackpotCheck = 2;


					animation();
					m_Sprite[9]->runAction(Repeat::create(m_Animate[3], 1)->clone());
				}
				else if (random2 == random3 && random1 != random2)		//중급
				{
					log("random1 = %d", random1);
					log("random2 = %d", random2);
					log("random3 = %d", random3);

					m_layer[0]->setVisible(true);
					m_Sprite[7]->runAction(sp1->clone());
					m_Sprite[9]->runAction(se3->clone());
					JackpotCheck = 2;


					animation();
					m_Sprite[9]->runAction(Repeat::create(m_Animate[3], 1)->clone());
				}
				else if (random3 == random1 && random2 != random3)		//중급
				{
					log("random1 = %d", random1);
					log("random2 = %d", random2);
					log("random3 = %d", random3);
					m_layer[0]->setVisible(true);
					m_Sprite[7]->runAction(sp1->clone());
					m_Sprite[9]->runAction(se3->clone());
					JackpotCheck = 2;


					animation();
					m_Sprite[9]->runAction(Repeat::create(m_Animate[3], 1)->clone());
				}
				else if (random1 == random2 && random1 == random3)		//상급
				{
					log("random1 = %d", random1);
					log("random2 = %d", random2);
					log("random3 = %d", random3);
					m_layer[0]->setVisible(true);
					m_Sprite[8]->runAction(sp1->clone());
					m_Sprite[9]->runAction(se3->clone());
					JackpotCheck = 3;


					animation();
					m_Sprite[9]->runAction(Repeat::create(m_Animate[3], 1)->clone());
				}
				else                                                    //하급
				{
					log("random1 = %d", random1);
					log("random2 = %d", random2);
					log("random3 = %d", random3);
					m_layer[0]->setVisible(true);
					m_Sprite[6]->runAction(sp1->clone());
					m_Sprite[9]->runAction(se3->clone());
					JackpotCheck = 1;


					animation();
					m_Sprite[9]->runAction(Repeat::create(m_Animate[3], 1)->clone());
				}
			}

			//
			if (g_TimeCheck == 4)
			{
			}

			g_TimeCheck++;
		}
	}

	//스프라이트 같은것 찾기

}



/**
@brief : 메뉴 누르면 만들어지는 버튼 함수 생성
*/
void JackpotScene::menuCloseCallback(Ref* pSender){}

void JackpotScene::Go_Adventure(Ref* pSender)
{
	//	Director::sharedDirector()->pause();	//씬을 일시정지
	//	this->setTouchEnabled(false);
	ChangeBgm = true;
	MapCode = 5;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}
void JackpotScene::Go_Hangar(Ref* pSender)
{
	//씬전환 전에 씬으로 이동
	ChangeBgm = true;
	MapCode = 6;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}
void JackpotScene::Go_Option(Ref* pSender)
{
	Director::sharedDirector()->resume();	//씬을 다시 시작함
	g_StopCheck = false;
	g_TimeCheck = 0;
	ChangeBgm = true;
	MapCode = 2;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);

}
void JackpotScene::Rolling(Ref* pSender)
{
	if (bb == false)
	{
		bb = true;
		AudioEngine::play2d("sound/effect/roulette_button.mp3", false, Volume);
		Check = true;
		g_StopCheck = true;


		m_Animation[0] = Animation::create();
		m_Animation[0]->setDelayPerUnit(0.04);
		m_Animation[1] = Animation::create();
		m_Animation[1]->setDelayPerUnit(0.04);
		m_Animation[2] = Animation::create();
		m_Animation[2]->setDelayPerUnit(0.04);

		for (int i = 1; i <= 5; i++)
		{

			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("rolling-%d.png", i));
			m_Animation[0]->addSpriteFrame(frame);
			m_Animation[1]->addSpriteFrame(frame);
			m_Animation[2]->addSpriteFrame(frame);
		}

		m_Animate[0] = Animate::create(m_Animation[0]);
		m_Animate[1] = Animate::create(m_Animation[1]);
		m_Animate[2] = Animate::create(m_Animation[2]);

		m_Sprite[0]->runAction(RepeatForever::create(m_Animate[0])->clone());
		m_Sprite[1]->runAction(RepeatForever::create(m_Animate[1])->clone());
		m_Sprite[2]->runAction(RepeatForever::create(m_Animate[2])->clone());

		removeChildByTag(4);
		removeChildByTag(5);
		removeChildByTag(6);
	}
	
}
void JackpotScene::Go_Title(Ref* pSender)
{
	ChangeBgm = true;
	MapCode = 4;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}
void JackpotScene::hide()
{
	m_Sprite[9]->setVisible(false);
}
void JackpotScene::showLayer0()
{
	m_layer[0]->setVisible(true);
}
void JackpotScene::animation()
{
	m_Animation[3] = Animation::create();
	m_Animation[3]->setDelayPerUnit(2.0f);

	for (int i = 1; i < 6; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("shine%d.png", i));
		m_Animation[3]->addSpriteFrame(frame);
	}
	m_Animate[3] = Animate::create(m_Animation[3]);
}
void JackpotScene::flash()
{
	Sprite* flash = Sprite::create("hm/main/flash.png");
	flash->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);
	this->addChild(flash, 50);
	FadeOut* fadeout = FadeOut::create(1.0f);
	flash->runAction(fadeout);
}

void JackpotScene::OK(Ref* pSender)
{
	m_layer[0]->setVisible(false);
	Director::getInstance()->replaceScene(JackpotScene::createScene());
}

void JackpotScene::RandomMaterial()
{
	int abc = rand() % 100;
	int a = rand() % 2;
	int b = rand() % 3;
	int c = rand() % 3;
	int rm = 0;

	if (JackpotCheck == 1)
	{
		if (0 <= abc&&abc < 90)
		{
			if (c == 0)	//6번(마나피)
			{
				m_Sprite[10]->setTexture("hm/making/M7.png");
				rm = rand() % 30 + 1;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
			else if (c == 1)//2번(플론)
			{
				m_Sprite[10]->setTexture("hm/making/M3.png");
				rm = rand() % 30 + 1;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
			else if (c == 2)//5번(크내폰)
			{
				m_Sprite[10]->setTexture("hm/making/M6.png");
				rm = rand() % 30 + 1;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
		}
		else if (90 <= abc&&abc < 100)
		{
			if (b == 0)//블랙스틸
			{
				m_Sprite[10]->setTexture("hm/making/M2.png");
				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
			else if (b == 1)//엠타
			{
				m_Sprite[10]->setTexture("hm/making/M4.png");
				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
			else if (b == 2)//지프틴
			{
				m_Sprite[10]->setTexture("hm/making/M5.png");
				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}

		}
	}

	//
	else if (JackpotCheck == 2)
	{
		if (0 <= abc&&abc < 60)
		{
			if (c == 0)	//6번(마나피)
			{
				m_Sprite[10]->setTexture("hm/making/M7.png");
				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm + 30);
				m_label[1]->setString(str);
			}
			else if (c == 1)//2번(플론)
			{
				m_Sprite[10]->setTexture("hm/making/M3.png");
				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm + 30);
				m_label[1]->setString(str);
			}
			else if (c == 2)//5번(크내폰)
			{
				m_Sprite[10]->setTexture("hm/making/M6.png");
				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm + 30);
				m_label[1]->setString(str);
			}
		}
		else if (60 <= abc&&abc < 90)
		{
			if (b == 0)//블랙스틸
			{
				m_Sprite[10]->setTexture("hm/making/M2.png");
				rm = rand() % 10 + 1;
				sprintf(str, "%d", rm + 20);
				m_label[1]->setString(str);
			}
			else if (b == 1)//엠타
			{
				m_Sprite[10]->setTexture("hm/making/M4.png");
				rm = rand() % 10 + 1;
				sprintf(str, "%d", rm + 20);
				m_label[1]->setString(str);
			}
			else if (b == 2)//지프틴
			{
				m_Sprite[10]->setTexture("hm/making/M5.png");
				rm = rand() % 10 + 1;
				sprintf(str, "%d", rm + 20);
				m_label[1]->setString(str);
			}
		}
		else if (90 <= abc&&abc < 100)
		{
			if (a == 0)	//솔라
			{
				m_Sprite[10]->setTexture("hm/making/M8.png");
				rm = rand() % 3 + 1;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
			else if (a == 1)//드레이븐
			{
				m_Sprite[10]->setTexture("hm/making/M1.png");
				rm = rand() % 3 + 1;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
		}
	}

	//
	else if (JackpotCheck == 3)
	{
		if (0 <= abc&&abc < 60)
		{
			if (c == 0)	//6번(마나피)
			{
				m_Sprite[10]->setTexture("hm/making/M7.png");

				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm + 50);
				m_label[1]->setString(str);
			}
			else if (c == 1)//2번(플론)
			{
				m_Sprite[10]->setTexture("hm/making/M3.png");
				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm + 50);
				m_label[1]->setString(str);
			}
			else if (c == 2)//5번(크내폰)
			{
				m_Sprite[10]->setTexture("hm/making/M6.png");
				rm = rand() % 20 + 1;
				sprintf(str, "%d", rm + 50);
				m_label[1]->setString(str);
			}
		}
		else if (60 <= abc&&abc < 90)
		{
			if (b == 0)//블랙스틸
			{
				m_Sprite[10]->setTexture("hm/making/M2.png");
				rm = rand() % 10 + 1;
				sprintf(str, "%d", rm + 30);
				m_label[1]->setString(str);
			}
			else if (b == 1)//엠타
			{
				m_Sprite[10]->setTexture("hm/making/M4.png");
				rm = rand() % 10 + 1;
				sprintf(str, "%d", rm + 30);
				m_label[1]->setString(str);
			}
			else if (b == 2)//지프틴
			{
				m_Sprite[10]->setTexture("hm/making/M5.png");
				rm = rand() % 10 + 1;
				sprintf(str, "%d", rm + 30);
				m_label[1]->setString(str);
			}
		}
		else if (90 <= abc&&abc < 100)
		{
			if (a == 0)	//솔라
			{
				m_Sprite[10]->setTexture("hm/making/M8.png");
				rm = rand() % 5 + 3;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
			else if (a == 1)//드레이븐
			{
				m_Sprite[10]->setTexture("hm/making/M1.png");
				rm = rand() % 5 + 3;
				sprintf(str, "%d", rm);
				m_label[1]->setString(str);
			}
		}
	}

	m_Sprite[10]->setVisible(true);
}



bool JackpotScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}


void JackpotScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	Point location = touch->getLocation();

}
void JackpotScene::onTouchEnded(Touch *touch, Event *unused_event)
{

}

void JackpotScene::boxopensound()
{
	AudioEngine::play2d("sound/effect/box_open.mp3", false, Volume*10);
}






void JackpotScene::Sound()
{

}
//void mainScene::onTouchCancelled(Touch *touch, Event *unused_event){}
//void mainScene::onTouchesBegan(const  vector<Touch*>& touches, Event *unused_event){}
//void mainScene::onTouchesMoved(const  vector<Touch*>& touches, Event *unused_event){}
//void mainScene::onTouchesEnded(const  vector<Touch*>& touches, Event *unused_event){}
//void mainScene::onTouchesCancelled(const  vector<Touch*>&touches, Event *unused_event){}