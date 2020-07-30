//추가해야하는것


//파츠종류
//m_layer[0] 수압총
//m_layer[1] 철갑형 수압총
//m_layer[2] 확산형 수압총
//m_layer[3] 레이더
//m_layer[4] 동력
//m_layer[5] 장갑
//m_layer[6] 제작(팝업창)
//m_layer[7] 제작 성공유무(팝업창)

//재료 종류 8가지
//m_material[0] 드레이븐		(draven)
//m_material[1] 블랙스틸		(blacksteel)
//m_material[2] 플론			(floan)
//m_material[3] 엠타			(emta)
//m_material[4] 지프틴			(gyptin)
//m_material[5] 크내폰			(kynepon)
//m_material[6] 마나피			(manapy)
//m_material[7] 솔라			(solar)



#include "stdafx.h"
#include <stdlib.h>
#include "SimpleAudioEngine.h"
#include "math.h"
bool g_Check = true;

bool layerCheck = false;

Scene* StorageScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StorageScene::create();
	scene->addChild(layer);
	return scene;
}

bool StorageScene::init()
{
	srand((unsigned)time(NULL));
	//터치
	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	//레이어
	if (!LayerColor::initWithColor(Color4B::GRAY))
		return false;








	Submarin = Sprite::create();
	Submarin->setPosition(Vec2(975, 400));
	this->addChild(Submarin, 4);
	if (nowSubmarinFrame == 1)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 0; i < 4; i++)
		{
			sprintf(str1, "%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.05f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Submarin->runAction(CCRepeatForever::create(seq));
	}
	else if (nowSubmarinFrame == 4)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 0; i < 12; i++)
		{
			sprintf(str1, "submarin_devil%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Submarin->runAction(CCRepeatForever::create(seq));
	}





	if (Bgm_Sound[2] == AudioEngine::INVALID_AUDIO_ID)
	{
		Bgm_Sound[2] = AudioEngine::play2d("sound/bgm/mainmenu.mp3", true, Volume);
	}




	int goldex = 100000;
	UserDefault::getInstance()->setIntegerForKey("gold", goldex);


	m_label[7] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");		//임시 돈
	m_label[7]->setPosition(D_DESIGN_WIDTH - 150, D_DESIGN_HEIGHT - 55);
	this->addChild(m_label[7], 4);

	Umaterial_0 = 40;
	Umaterial_1 = 400;
	Umaterial_2 = 400;
	Umaterial_3 = 400;
	Umaterial_4 = 400;
	Umaterial_5 = 400;
	Umaterial_6 = 400;
	Umaterial_7 = 400;
	UserDefault::getInstance()->setIntegerForKey("material_0", Umaterial_0);
	UserDefault::getInstance()->setIntegerForKey("material_1", Umaterial_1);
	UserDefault::getInstance()->setIntegerForKey("material_2", Umaterial_2);
	UserDefault::getInstance()->setIntegerForKey("material_3", Umaterial_3);
	UserDefault::getInstance()->setIntegerForKey("material_4", Umaterial_4);
	UserDefault::getInstance()->setIntegerForKey("material_5", Umaterial_5);
	UserDefault::getInstance()->setIntegerForKey("material_6", Umaterial_6);
	UserDefault::getInstance()->setIntegerForKey("material_7", Umaterial_7);


	m_layer[0] = LayerColor::create(Color4B(), winSize.width, winSize.height);
	m_layer[0]->setPosition(0, 0);
	m_layer[0]->setTag(0);
	m_layer[0]->setVisible(true);
	this->addChild(m_layer[0], 3);


	for (int i = 1; i < 6; i++)		//레이어 선언
	{
		m_layer[i] = LayerColor::create(Color4B(), winSize.width, winSize.height);
		m_layer[i]->setPosition(0, 0);
		m_layer[i]->setTag(i);
		m_layer[i]->setVisible(false);
		this->addChild(m_layer[i], 3);
	}
	m_layer[6] = LayerColor::create(Color4B(Color4B::BLACK), winSize.width, winSize.height);	//제작
	m_layer[6]->setPosition(0, 0);
	m_layer[6]->setOpacity(200);
	m_layer[6]->setTag(6);
	m_layer[6]->setVisible(false);
	this->addChild(m_layer[6], 4);

	m_layer[7] = LayerColor::create(Color4B(), winSize.width, winSize.height);	//제작 성공
	m_layer[7]->setPosition(0, 0);
	m_layer[7]->setTag(7);
	m_layer[7]->setOpacity(200);
	m_layer[7]->setVisible(false);
	this->addChild(m_layer[7], 5);

	for (int i = 0; i < 8; i++)					//재료 스프라이트
	{
		sprintf(str2, "hm/making/M%d.png", i + 1);
		m_material[i] = Sprite::create(str2);
		m_material[i]->setScale(1.3);
		m_material[i]->setVisible(false);
		m_layer[6]->addChild(m_material[i], 4);
	}



	for (int i = 0; i < 6; i++)
	{
		sprintf(str2, "hm/making/UPL_%d.png", i + 1);		//제작 파츠 레벨표시글(동력LV, 장갑LV, ....)
		UPlvL[i] = Sprite::create(str2);
		UPlvL[i]->setPosition(330, 300);
		UPlvL[i]->setVisible(false);
		m_layer[6]->addChild(UPlvL[i], 4);
	}

	for (int i = 0; i < 10; i++)
	{
		bar[0][i] = Sprite::create("hm/making/attackspeed-bar.png");		//연사력 바
		bar[0][i]->setVisible(false);
		bar[0][i]->setPosition(350 + 10 * i, 220);
		bar[0][i]->setScale(0.7);
		m_layer[6]->addChild(bar[0][i], 4);

		bar[1][i] = Sprite::create("hm/making/range-bar.png");		//범위 바
		bar[1][i]->setVisible(false);
		bar[1][i]->setPosition(350 + 10 * i, 190);
		bar[1][i]->setScale(0.7);
		m_layer[6]->addChild(bar[1][i], 4);

		bar[2][i] = Sprite::create("hm/making/damage-bar.png");		//공격력 바
		bar[2][i]->setVisible(false);
		bar[2][i]->setPosition(350 + 10 * i, 160);
		bar[2][i]->setScale(0.7);
		m_layer[6]->addChild(bar[2][i], 4);
	}
	for (int i = 0; i < 15; i++)		//제작페이지에 파츠 스프라이트 제작
	{
		sprintf(str2, "hm/item/slv%d.png", i + 1);//연사형 수압총(만들것)
		MakeParts1_[i] = Sprite::create(str2);
		MakeParts1_[i]->setScale(1.3);
		MakeParts1_[i]->setPosition(100, 100);
		MakeParts1_[i]->setVisible(false);

		sprintf(str2, "hm/item/glv%d.png", i + 1);//철갑형 수압총(만들것)
		MakeParts2_[i] = Sprite::create(str2);
		MakeParts2_[i]->setScale(1.3);
		MakeParts2_[i]->setPosition(100, 100);
		MakeParts2_[i]->setVisible(false);

		sprintf(str2, "hm/item/hlv%d.png", i + 1);//확산형 수압총(만들것)
		MakeParts3_[i] = Sprite::create(str2);
		MakeParts3_[i]->setScale(1.3);
		MakeParts3_[i]->setPosition(100, 100);
		MakeParts3_[i]->setVisible(false);

		sprintf(str2, "hm/item/ulv%d.png", i + 1);//레이더(만들것)
		MakeParts4_[i] = Sprite::create(str2);
		MakeParts4_[i]->setScale(1.3);
		MakeParts4_[i]->setPosition(100, 100);
		MakeParts4_[i]->setVisible(false);

		sprintf(str2, "hm/item/dlv%d.png", i + 1);//동력(만들것)
		MakeParts5_[i] = Sprite::create(str2);
		MakeParts5_[i]->setScale(1.3);
		MakeParts5_[i]->setPosition(100, 100);
		MakeParts5_[i]->setVisible(false);

		sprintf(str2, "hm/item/jlv%d.png", i + 1);//장갑(만들것)
		MakeParts6_[i] = Sprite::create(str2);
		MakeParts6_[i]->setScale(1.3);
		MakeParts6_[i]->setPosition(100, 100);
		MakeParts6_[i]->setVisible(false);

		sprintf(str2, "hm/item/slv%d.png", i + 1);//연사형 수압총(재료)
		MaterialParts1_[i] = Sprite::create(str2);
		MaterialParts1_[i]->setScale(1.3);
		MaterialParts1_[i]->setPosition(100, 100);
		MaterialParts1_[i]->setVisible(false);

		sprintf(str2, "hm/item/glv%d.png", i + 1);//철갑형 수압총(재료)
		MaterialParts2_[i] = Sprite::create(str2);
		MaterialParts2_[i]->setScale(1.3);
		MaterialParts2_[i]->setPosition(100, 100);
		MaterialParts2_[i]->setVisible(false);

		sprintf(str2, "hm/item/hlv%d.png", i + 1);//확산형 수압총(재료)
		MaterialParts3_[i] = Sprite::create(str2);
		MaterialParts3_[i]->setScale(1.3);
		MaterialParts3_[i]->setPosition(100, 100);
		MaterialParts3_[i]->setVisible(false);

		sprintf(str2, "hm/item/ulv%d.png", i + 1);//레이더(재료)
		MaterialParts4_[i] = Sprite::create(str2);
		MaterialParts4_[i]->setScale(1.3);
		MaterialParts4_[i]->setPosition(100, 100);
		MaterialParts4_[i]->setVisible(false);

		sprintf(str2, "hm/item/dlv%d.png", i + 1);//동력(재료)
		MaterialParts5_[i] = Sprite::create(str2);
		MaterialParts5_[i]->setScale(1.3);
		MaterialParts5_[i]->setPosition(100, 100);
		MaterialParts5_[i]->setVisible(false);

		sprintf(str2, "hm/item/jlv%d.png", i + 1);//장갑(재료)
		MaterialParts6_[i] = Sprite::create(str2);
		MaterialParts6_[i]->setScale(1.3);
		MaterialParts6_[i]->setPosition(100, 100);
		MaterialParts6_[i]->setVisible(false);

		m_layer[6]->addChild(MakeParts1_[i], 4);
		m_layer[6]->addChild(MakeParts2_[i], 4);
		m_layer[6]->addChild(MakeParts3_[i], 4);
		m_layer[6]->addChild(MakeParts4_[i], 4);
		m_layer[6]->addChild(MakeParts5_[i], 4);
		m_layer[6]->addChild(MakeParts6_[i], 4);

		m_layer[6]->addChild(MaterialParts1_[i], 4);
		m_layer[6]->addChild(MaterialParts2_[i], 4);
		m_layer[6]->addChild(MaterialParts3_[i], 4);
		m_layer[6]->addChild(MaterialParts4_[i], 4);
		m_layer[6]->addChild(MaterialParts5_[i], 4);
		m_layer[6]->addChild(MaterialParts6_[i], 4);



	}


	

	popup = false;

	Sprite* background1 = Sprite::create("hm/item/2.png");
	background1->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	background1->setScale(winSize.width / background1->getContentSize().width);			//배경1
	this->addChild(background1, 2);

	Sprite* background2 = Sprite::create("hm/item/3.png");
	background2->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	background2->setScale(winSize.width / background1->getContentSize().width);			//배경2
	this->addChild(background2);

	Sprite* wpgPage = Sprite::create("hm/item/wpg.png");	//수압총 페이지
	wpgPage->setPosition(350, 300);
	wpgPage->setScale(0.9);
	m_layer[0]->addChild(wpgPage, 2);

	Sprite* mgPage = Sprite::create("hm/item/mg.png");		//철갑형 수압총 페이지
	mgPage->setPosition(350, 300);
	mgPage->setScale(0.9);
	m_layer[1]->addChild(mgPage, 2);

	Sprite* sgPage = Sprite::create("hm/item/sg.png");		//확산형 수압총 페이지
	sgPage->setPosition(350, 300);
	sgPage->setScale(0.9);
	m_layer[2]->addChild(sgPage, 2);


	Sprite* raderPage = Sprite::create("hm/item/rader.png");		//레이더 페이지
	raderPage->setPosition(350, 300);
	raderPage->setScale(0.9);
	m_layer[3]->addChild(raderPage, 2);


	Sprite* enginePage = Sprite::create("hm/item/engine.png");		//동력 페이지
	enginePage->setPosition(350, 300);
	enginePage->setScale(0.9);
	m_layer[4]->addChild(enginePage, 2);


	Sprite* barrierPage = Sprite::create("hm/item/barrier.png");	//장갑 페이지
	barrierPage->setPosition(350, 300);
	barrierPage->setScale(0.9);
	m_layer[5]->addChild(barrierPage, 2);

	Sprite* makingPage = Sprite::create("hm/making/makeUI.png");
	makingPage->setPosition(winSize.width / 2, winSize.height / 2);		//제작 페이지
	m_layer[6]->addChild(makingPage, 3);

	Sprite* AttackSpeed = Sprite::create("hm/making/attackspeed.png");		//연사력
	AttackSpeed->setPosition(300, 220);
	m_layer[6]->addChild(AttackSpeed, 4);

	Sprite* Range = Sprite::create("hm/making/range.png");			//범위
	Range->setPosition(300, 190);
	m_layer[6]->addChild(Range, 4);

	Sprite* Damage = Sprite::create("hm/making/damage.png");				//데미지
	Damage->setPosition(300, 160);
	m_layer[6]->addChild(Damage, 4);

	m_Sprite[0] = Sprite::create();
	m_Sprite[0]->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2 + 15);		//제작 성공 재료
	m_Sprite[0]->setOpacity(0);
	m_Sprite[0]->setScale(1.7);
	m_layer[7]->addChild(m_Sprite[0], 6);

	m_Sprite[1] = Sprite::create("hm/making/success.png");
	m_Sprite[1]->setPosition(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2);		//제작 성공 틀
	m_Sprite[1]->setOpacity(0);
	m_layer[7]->addChild(m_Sprite[1], 5);

	auto wpgB = MenuItemImage::create("hm/item/slv8.png", "hm/item/slv8.png", CC_CALLBACK_1(StorageScene::Go_Rapid, this));
	wpgB->setPosition(790, 120);

	auto raderB = MenuItemImage::create("hm/item/ulv4.png", "hm/item/ulv4.png", CC_CALLBACK_1(StorageScene::Go_Rader, this));
	raderB->setPosition(915, 120);

	auto engineB = MenuItemImage::create("hm/item/dlv8.png", "hm/item/dlv8.png", CC_CALLBACK_1(StorageScene::Go_Engine, this));
	engineB->setPosition(1040, 120);

	auto barrierB = MenuItemImage::create("hm/item/jlv2.png", "hm/item/jlv2.png", CC_CALLBACK_1(StorageScene::Go_Barrier, this));
	barrierB->setPosition(1165, 120);

	auto backB = MenuItemImage::create("hm/arrow.png", "hm/arrow.png", CC_CALLBACK_1(StorageScene::Go_Back, this));
	backB->setScale(3);
	backB->setPosition(50, 660);

	auto MenU1 = Menu::create(wpgB, raderB, engineB, barrierB, backB, NULL);
	MenU1->setPosition(Vec2::ZERO);
	this->addChild(MenU1, 2);


	MenuItemImage* PL1_[15];//연사형 수압총 버튼들
	for (int i = 0; i < 15; i++)
	{
		sprintf(str, "hm/item/slv%d.png", i + 1);
		PL1_[i] = MenuItemImage::create(str, str, CC_CALLBACK_1(StorageScene::PL1, this));
		PL1_[i]->setTag(100 + i);	//100, 101, 102, 103 .... 114, 115
	}
	auto metalArrow = MenuItemImage::create("hm/item/metal.png", "hm/item/metal.png", CC_CALLBACK_1(StorageScene::Go_Metal, this));
	metalArrow->setPosition(550, 520);

	PL1_[0]->setPosition(210, 430);	PL1_[1]->setPosition(305, 430); PL1_[2]->setPosition(400, 430); PL1_[3]->setPosition(495, 430);
	PL1_[4]->setPosition(210, 335); PL1_[5]->setPosition(305, 335); PL1_[6]->setPosition(400, 335); PL1_[7]->setPosition(495, 335);
	PL1_[8]->setPosition(210, 240); PL1_[9]->setPosition(305, 240); PL1_[10]->setPosition(400, 240); PL1_[11]->setPosition(495, 240);
	PL1_[12]->setPosition(210, 150); PL1_[13]->setPosition(305, 150); PL1_[14]->setPosition(400, 150);
	auto MenU2 = Menu::create(metalArrow, PL1_[0], PL1_[1], PL1_[2], PL1_[3], PL1_[4], PL1_[5], PL1_[6], PL1_[7], PL1_[8], PL1_[9], PL1_[10], PL1_[11], PL1_[12], PL1_[13], PL1_[14], NULL);
	MenU2->setPosition(Vec2::ZERO);
	m_layer[0]->addChild(MenU2, 2);


	MenuItemImage* PL2_[15];//철갑형 수압총 버튼들
	for (int i = 0; i < 15; i++)
	{
		sprintf(str, "hm/item/glv%d.png", i + 1);
		PL2_[i] = MenuItemImage::create(str, str, CC_CALLBACK_1(StorageScene::PL2, this));
		PL2_[i]->setTag(200 + i);	//200, 201, 202, 203 ......214, 215
	}
	auto spreadArrow = MenuItemImage::create("hm/item/spread.png", "hm/item/spread.png", CC_CALLBACK_1(StorageScene::Go_Spread, this));
	spreadArrow->setPosition(550, 520);
	PL2_[0]->setPosition(210, 430);	PL2_[1]->setPosition(305, 430); PL2_[2]->setPosition(400, 430); PL2_[3]->setPosition(495, 430);
	PL2_[4]->setPosition(210, 335); PL2_[5]->setPosition(305, 335); PL2_[6]->setPosition(400, 335); PL2_[7]->setPosition(495, 335);
	PL2_[8]->setPosition(210, 240); PL2_[9]->setPosition(305, 240); PL2_[10]->setPosition(400, 240); PL2_[11]->setPosition(495, 240);
	PL2_[12]->setPosition(210, 150); PL2_[13]->setPosition(305, 150); PL2_[14]->setPosition(400, 150);
	auto MenU3 = Menu::create(spreadArrow, PL2_[0], PL2_[1], PL2_[2], PL2_[3], PL2_[4], PL2_[5], PL2_[6], PL2_[7], PL2_[8], PL2_[9], PL2_[10], PL2_[11], PL2_[12], PL2_[13], PL2_[14], NULL);
	MenU3->setPosition(Vec2::ZERO);
	m_layer[1]->addChild(MenU3, 2);


	MenuItemImage* PL3_[15];//확산형 수압총 버튼들
	for (int i = 0; i < 15; i++)
	{
		sprintf(str, "hm/item/hlv%d.png", i + 1);
		PL3_[i] = MenuItemImage::create(str, str, CC_CALLBACK_1(StorageScene::PL3, this));
		PL3_[i]->setTag(300 + i);	//300, 301, 302, 303.....314, 315
	}
	auto rapidArrow = MenuItemImage::create("hm/item/rapid.png", "hm/item/rapid.png", CC_CALLBACK_1(StorageScene::Go_Rapid, this));
	rapidArrow->setPosition(550, 520);
	PL3_[0]->setPosition(210, 430);	PL3_[1]->setPosition(305, 430); PL3_[2]->setPosition(400, 430); PL3_[3]->setPosition(495, 430);
	PL3_[4]->setPosition(210, 335); PL3_[5]->setPosition(305, 335); PL3_[6]->setPosition(400, 335); PL3_[7]->setPosition(495, 335);
	PL3_[8]->setPosition(210, 240); PL3_[9]->setPosition(305, 240); PL3_[10]->setPosition(400, 240); PL3_[11]->setPosition(495, 240);
	PL3_[12]->setPosition(210, 150); PL3_[13]->setPosition(305, 150); PL3_[14]->setPosition(400, 150);
	auto MenU4 = Menu::create(rapidArrow, PL3_[0], PL3_[1], PL3_[2], PL3_[3], PL3_[4], PL3_[5], PL3_[6], PL3_[7], PL3_[8], PL3_[9], PL3_[10], PL3_[11], PL3_[12], PL3_[13], PL3_[14], NULL);
	MenU4->setPosition(Vec2::ZERO);
	m_layer[2]->addChild(MenU4, 2);


	MenuItemImage* PL4_[15];//동력 버튼들
	for (int i = 0; i < 15; i++)
	{
		sprintf(str, "hm/item/ulv%d.png", i + 1);
		PL4_[i] = MenuItemImage::create(str, str, CC_CALLBACK_1(StorageScene::PL4, this));
		PL4_[i]->setTag(400 + i);	//400, 401, 402, 403....414, 415
	}
	PL4_[0]->setPosition(210, 430);	PL4_[1]->setPosition(305, 430); PL4_[2]->setPosition(400, 430); PL4_[3]->setPosition(495, 430);
	PL4_[4]->setPosition(210, 335); PL4_[5]->setPosition(305, 335); PL4_[6]->setPosition(400, 335); PL4_[7]->setPosition(495, 335);
	PL4_[8]->setPosition(210, 240); PL4_[9]->setPosition(305, 240); PL4_[10]->setPosition(400, 240); PL4_[11]->setPosition(495, 240);
	PL4_[12]->setPosition(210, 150); PL4_[13]->setPosition(305, 150); PL4_[14]->setPosition(400, 150);
	auto MenU5 = Menu::create(PL4_[0], PL4_[1], PL4_[2], PL4_[3], PL4_[4], PL4_[5], PL4_[6], PL4_[7], PL4_[8], PL4_[9], PL4_[10], PL4_[11], PL4_[12], PL4_[13], PL4_[14], NULL);
	MenU5->setPosition(Vec2::ZERO);
	m_layer[3]->addChild(MenU5, 2);

	MenuItemImage* PL5_[15];//장갑 버튼들
	for (int i = 0; i < 15; i++)
	{
		sprintf(str, "hm/item/dlv%d.png", i + 1);
		PL5_[i] = MenuItemImage::create(str, str, CC_CALLBACK_1(StorageScene::PL5, this));
		PL5_[i]->setTag(500 + i);	//500, 501, 502, 503.....514, 515
	}
	PL5_[0]->setPosition(210, 430);	PL5_[1]->setPosition(305, 430); PL5_[2]->setPosition(400, 430); PL5_[3]->setPosition(495, 430);
	PL5_[4]->setPosition(210, 335); PL5_[5]->setPosition(305, 335); PL5_[6]->setPosition(400, 335); PL5_[7]->setPosition(495, 335);
	PL5_[8]->setPosition(210, 240); PL5_[9]->setPosition(305, 240); PL5_[10]->setPosition(400, 240); PL5_[11]->setPosition(495, 240);
	PL5_[12]->setPosition(210, 150); PL5_[13]->setPosition(305, 150); PL5_[14]->setPosition(400, 150);
	auto MenU6 = Menu::create(PL5_[0], PL5_[1], PL5_[2], PL5_[3], PL5_[4], PL5_[5], PL5_[6], PL5_[7], PL5_[8], PL5_[9], PL5_[10], PL5_[11], PL5_[12], PL5_[13], PL5_[14], NULL);
	MenU6->setPosition(Vec2::ZERO);
	m_layer[4]->addChild(MenU6, 2);

	MenuItemImage* PL6_[15];//동력 버튼들
	for (int i = 0; i < 15; i++)
	{
		sprintf(str, "hm/item/jlv%d.png", i + 1);
		PL6_[i] = MenuItemImage::create(str, str, CC_CALLBACK_1(StorageScene::PL6, this));
		PL6_[i]->setTag(600 + i);
	}
	PL6_[0]->setPosition(210, 430);	PL6_[1]->setPosition(305, 430); PL6_[2]->setPosition(400, 430); PL6_[3]->setPosition(495, 430);
	PL6_[4]->setPosition(210, 335); PL6_[5]->setPosition(305, 335); PL6_[6]->setPosition(400, 335); PL6_[7]->setPosition(495, 335);
	PL6_[8]->setPosition(210, 240); PL6_[9]->setPosition(305, 240); PL6_[10]->setPosition(400, 240); PL6_[11]->setPosition(495, 240);
	PL6_[12]->setPosition(210, 150); PL6_[13]->setPosition(305, 150); PL6_[14]->setPosition(400, 150);
	auto MenU7 = Menu::create(PL6_[0], PL6_[1], PL6_[2], PL6_[3], PL6_[4], PL6_[5], PL6_[6], PL6_[7], PL6_[8], PL6_[9], PL6_[10], PL6_[11], PL6_[12], PL6_[13], PL6_[14], NULL);
	MenU7->setPosition(Vec2::ZERO);
	m_layer[5]->addChild(MenU7, 2);





	auto makeB = MenuItemImage::create("hm/making/makebutton.png", "hm/making/makebutton.png", CC_CALLBACK_1(StorageScene::make, this));	//제작하기
	makeB->setPosition(685, 200);

	auto cancelB = MenuItemImage::create("hm/making/cancelbutton.png", "hm/making/cancelbutton.png", CC_CALLBACK_1(StorageScene::cancel, this));	//취소하기
	cancelB->setScale(0.9);
	cancelB->setPosition(950, 200);

	auto MenU8 = Menu::create(makeB, cancelB, NULL);
	MenU8->setPosition(Vec2::ZERO);
	m_layer[6]->addChild(MenU8, 3);


	//	auto startL = LabelBMFont::create("1234567890", "fonts/undeadfont.fnt");		//폰트확인 예시(제작)
	//	startL->setPosition(640, 320);
	//	startL->setColor(Color3B::WHITE);
	//	this->addChild(startL, 10);

	//	auto dlatl = LabelTTF::create("1234567890", "Arial", 50);		//폰트확인 예시(기본)
	//	dlatl->setPosition(640, 370);
	//	dlatl->setColor(Color3B::BLACK);
	//	this->addChild(dlatl, 3);

	m_label[0] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");	//파츠 레벨
	m_label[0]->setScale(1.4);
	m_layer[6]->addChild(m_label[0], 4);

	m_label[1] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");		//파츠 제작하는데 드는 비용
	m_label[1]->setScale(1.4);
	m_layer[6]->addChild(m_label[1], 4);

	m_label[2] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");		//재료1 필요개수
	m_label[2]->setScale(1.4);
	m_layer[6]->addChild(m_label[2], 4);
	//
	m_label[3] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");		//재료2 필요개수
	m_label[3]->setScale(1.4);
	m_layer[6]->addChild(m_label[3], 4);
	//
	m_label[4] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");		//재료1 보유개수
	m_label[4]->setScale(1.4);
	m_layer[6]->addChild(m_label[4], 4);
	//
	m_label[5] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");		//재료2 보유개수
	m_label[5]->setScale(1.4);
	m_layer[6]->addChild(m_label[5], 4);
	//
	m_label[6] = LabelBMFont::create(" ", "fonts/undeadfont.fnt");		//재료파츠 부가설명
	m_label[6]->setScale(1.4);
	m_layer[6]->addChild(m_label[6], 4);




	//start라벨 깜빡깜빡
	//	FadeIn* action_0 = FadeIn::create(1.3f);
	//	FadeOut* action_1 = FadeOut::create(1.3f);
	//	Sequence* sequence = Sequence::create(action_1, action_0, NULL);
	//	auto re = RepeatForever::create(sequence);
	//	startL->runAction(re);

	for (int i = 0; i < 15; i++)
	{
		MaterialParts1_[i]->setPosition(600, 400);		//재료파츠
		MaterialParts2_[i]->setPosition(600, 400);
		MaterialParts3_[i]->setPosition(600, 400);
		MaterialParts4_[i]->setPosition(600, 400);
		MaterialParts5_[i]->setPosition(600, 400);
		MaterialParts6_[i]->setPosition(600, 400);

		MakeParts1_[i]->setPosition(350, 400);		//만들파츠
		MakeParts1_[i]->setScale(2);

		MakeParts2_[i]->setPosition(350, 400);
		MakeParts2_[i]->setScale(2);

		MakeParts3_[i]->setPosition(350, 400);
		MakeParts3_[i]->setScale(2);

		MakeParts4_[i]->setPosition(350, 400);
		MakeParts4_[i]->setScale(2);

		MakeParts5_[i]->setPosition(350, 400);
		MakeParts5_[i]->setScale(2);

		MakeParts6_[i]->setPosition(350, 400);
		MakeParts6_[i]->setScale(2);
	}

	schedule(schedule_selector(StorageScene::Update), 0.0f);

	return true;

}

void StorageScene::Update(float dt)
{
	/*
	m_label[0] = LabelTTF::create("asdfsdfa", "Arial", 100);
	m_label[0]->setPosition(winSize.width / 2, winSize.height / 2);
	m_label[0]->setVisible(false);
	m_label[0]->setTag(55);
	m_layer[6]->addChild(m_label[0]);
	*/
	string gold = UserDefault::getInstance()->getStringForKey("gold");

	m_label[7]->setString(gold);

}

/**
@brief : 메뉴 누르면 만들어지는 버튼 함수 생성
*/
void StorageScene::menuCloseCallback(Ref* pSender){}

void StorageScene::Go_Rapid(Ref* pSender)
{
	removeChildByTag(55);


	for (int i = 0; i < 6; i++)
		m_layer[i]->setVisible(false);

	m_layer[0]->setVisible(true);


}
void StorageScene::Go_Metal(Ref* pSender)
{
	removeChildByTag(55);

	for (int i = 0; i < 6; i++)
		m_layer[i]->setVisible(false);

	m_layer[1]->setVisible(true);

}
void StorageScene::Go_Spread(Ref* pSender)
{
	removeChildByTag(55);
	for (int i = 0; i < 6; i++)
		m_layer[i]->setVisible(false);

	m_layer[2]->setVisible(true);

}
void StorageScene::Go_Rader(Ref* pSender)
{
	removeChildByTag(55);

	for (int i = 0; i < 6; i++)
		m_layer[i]->setVisible(false);

	m_layer[3]->setVisible(true);

}
void StorageScene::Go_Engine(Ref* pSender)
{
	removeChildByTag(55);
	for (int i = 0; i < 6; i++)
		m_layer[i]->setVisible(false);

	m_layer[4]->setVisible(true);

}
void StorageScene::Go_Barrier(Ref* pSender)
{
	removeChildByTag(55);

	for (int i = 0; i < 6; i++)
		m_layer[i]->setVisible(false);

	m_layer[5]->setVisible(true);

}
void StorageScene::Go_Back(Ref* psEnder)
{
	MapCode = 1;
	Scene *scene = BlackScene::createScene();
	scene = TransitionCrossFade::create(0.3f, scene);
	Director::sharedDirector()->replaceScene(scene);
}

void StorageScene::PL1(Ref* pSender)//연사형 수압총
{
	if (popup == true) {
		return;
	}

	int _nT = ((Node *)pSender)->getTag();		//태그값을 _nT에 넣어준다
	for (j[0] = 1; j[0] < 15; j[0]++)
	{
		if (_nT == j[0] + 100)
		{

			mm = _nT;
			sprintf(str, "%d", j[0] + 1);
			m_label[0]->setString(str);					//파츠레벨
			m_label[0]->setPosition(425, 300);

			sprintf(str, "%d", (int)(500 * powf(1.2, j[0] - 1)));//제작 비용
			m_label[1]->setString(str);
			m_label[1]->setPosition(800, 300);

			sprintf(str, "/  %d", (int)(300 * powf(1.2, j[0] - 1)));	//첫번째 재료(마나피) 필요갯수
			m_label[2]->setString(str);
			m_label[2]->setScale(0.5);
			m_label[2]->setPosition(780, 370);

			sprintf(str, "/  %d", (int)(300 * powf(1.2, j[0] - 1)));		//두번째 재료(크내폰) 필요갯수
			m_label[3]->setString(str);
			m_label[3]->setScale(0.5);
			m_label[3]->setPosition(930, 370);

			sprintf(str, "%dLV part ", j[0]);								//재료파츠 
			m_label[6]->setString(str);
			m_label[6]->setScale(0.5);
			m_label[6]->setPosition(600, 370);

			string zxcv1 = UserDefault::getInstance()->getStringForKey("material_6");
			int asdf1 = UserDefault::getInstance()->getIntegerForKey("material_6");
			m_label[4]->setString(zxcv1);// 유저 디폴트 써서 현재 보유 첫번째 재료 갯수 쓰기
			m_label[4]->setScale(0.5);
			m_label[4]->setPosition(750, 370);

			string zxcv2 = UserDefault::getInstance()->getStringForKey("material_5");
			int asdf2 = UserDefault::getInstance()->getIntegerForKey("material_5");
			m_label[5]->setString(zxcv2);//두번째 재료 보유갯수 쓰기
			m_label[5]->setScale(0.5);
			m_label[5]->setPosition(900, 370);
			log("%d", asdf2);
			if ((300 * powf(1.2, j[0] - 1)) > asdf1)
				m_label[4]->setColor(Color3B::RED);
			else
			{
				m_label[4]->setColor(Color3B::WHITE);
			}

			if ((300 * powf(1.2, j[0] - 1)) > asdf2)
				m_label[5]->setColor(Color3B::RED);
			else
			{
				m_label[5]->setColor(Color3B::WHITE);
			}

			for (int i = 0; i < 6; i++)
				UPlvL[i]->setVisible(false);
			for (int i = 0; i < 8; i++)
				m_material[i]->setVisible(false);
			for (int i = 0; i < 15; i++)
			{
				MakeParts1_[i]->setVisible(false);
				MakeParts2_[i]->setVisible(false);
				MakeParts3_[i]->setVisible(false);
				MakeParts4_[i]->setVisible(false);
				MakeParts5_[i]->setVisible(false);
				MakeParts6_[i]->setVisible(false);

				MaterialParts1_[i]->setVisible(false);
				MaterialParts2_[i]->setVisible(false);
				MaterialParts3_[i]->setVisible(false);
				MaterialParts4_[i]->setVisible(false);
				MaterialParts5_[i]->setVisible(false);
				MaterialParts6_[i]->setVisible(false);
			}

			UPlvL[0]->setVisible(true);
			m_material[6]->setPosition(750, 400);			//마나피
			m_material[6]->setVisible(true);
			m_material[5]->setPosition(900, 400);			//크네폰
			m_material[5]->setVisible(true);

			MaterialParts1_[j[0] - 1]->setVisible(true);		//재료파츠

			MakeParts1_[j[0]]->setScale(2);
			MakeParts1_[j[0]]->setVisible(true);		//만들파츠

			for (int i = 0; i < 15; i++)
			{

				for (int i = 0; i < 3; i++)
					bar[0][i]->setVisible(true);
				for (int i = 0; i < 5; i++)
					bar[1][i]->setVisible(true);
				for (int i = 0; i < 2; i++)
					bar[2][i]->setVisible(true);
				m_layer[6]->setVisible(true);

				popup = true;

				break;
			}
		}
	}
	/*	case 100:////////////////////////////////////////
	for (int i = 0; i < 8; i++)
	m_material[i]->setVisible(false);
	for (int i = 0; i < 15;i++)
	MakeParts_[i]->setVisible(false);
	m_layer[6]->setVisible(true);
	break;

	case 101://///////////////////////////////////////

	m_label[0]->setString("2");					//파츠레벨
	m_label[1]->setString("10000");				//제작 비용
	for (int i = 0; i < 5; i++)
	{
	bar[0][i]->setVisible(false);
	bar[1][i]->setVisible(false);
	bar[2][i]->setVisible(false);
	}

	for (int i = 0; i < 8; i++)
	m_material[i]->setVisible(false);
	for (int i = 0; i < 15; i++)
	{
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	}

	UPlvL[0]->setVisible(true);
	m_material[7]->setPosition(900, 400);			//100개 소모
	m_material[7]->setVisible(true);
	m_material[6]->setPosition(750, 400);			//30개 소모
	m_material[6]->setVisible(true);
	//for (int i = 0; i < 15; i++)
	//{
	//	MakeParts_[i]->setPosition(600, 400);		//재료파츠
	//	MakeParts_[i]->setVisible(true);

	//	MakeParts_[i+1]->setPosition(350, 400);		//만들파츠
	//	MakeParts_[i+1]->setScale(2);
	//	MakeParts_[i+1]->setVisible(true);
	//}
	for (int i = 0; i < 3; i++)
	bar[0][i]->setVisible(true);
	for (int i = 0; i < 5; i++)
	bar[1][i]->setVisible(true);
	for (int i = 0; i < 2; i++)
	bar[2][i]->setVisible(true);
	m_layer[6]->setVisible(true);
	break;

	case 102://///////////////////////////////////////////////
	m_label[0]->setString("3");
	m_label[1]->setString("50000");

	for (int i = 0; i < 5; i++)
	{
	bar[0][i]->setVisible(false);
	bar[1][i]->setVisible(false);
	bar[2][i]->setVisible(false);
	}

	for (int i = 0; i < 8; i++)
	m_material[i]->setVisible(false);
	for (int i = 0; i < 15; i++)
	{
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	}

	UPlvL[0]->setVisible(true);
	m_material[7]->setPosition(900, 400);			//300개 소모
	m_material[7]->setVisible(true);
	m_material[6]->setPosition(750, 400);			//40개 소모
	m_material[6]->setVisible(true);
	MakeParts_[1]->setPosition(600, 400);		//재료파츠
	MakeParts_[1]->setScale(1.3);
	MakeParts_[1]->setVisible(true);

	MakeParts_[2]->setPosition(350, 400);		//만들파츠
	MakeParts_[2]->setScale(2);
	MakeParts_[2]->setVisible(true);
	for (int i = 0; i < 3; i++)
	bar[0][i]->setVisible(true);
	for (int i = 0; i < 5;i++)
	bar[1][i]->setVisible(true);
	for (int i = 0; i < 2;i++)
	bar[2][i]->setVisible(true);
	m_layer[6]->setVisible(true);

	break;

	case 103:////////////////////////////////////////////
	m_label[0]->setString("4");
	m_label[1]->setString("100000");

	for (int i = 0; i < 5; i++)
	{
	bar[0][i]->setVisible(false);
	bar[1][i]->setVisible(false);
	bar[2][i]->setVisible(false);
	}

	for (int i = 0; i < 8; i++)
	m_material[i]->setVisible(false);
	for (int i = 0; i < 15; i++)
	{
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	MakeParts_[i]->setVisible(false);
	}

	UPlvL[0]->setVisible(true);
	m_material[7]->setPosition(900, 400);			//400개 소모
	m_material[7]->setVisible(true);
	m_material[6]->setPosition(750, 400);			//60개 소모
	m_material[6]->setVisible(true);
	MakeParts_[2]->setPosition(600, 400);		//재료파츠
	MakeParts_[2]->setScale(1.3);
	MakeParts_[2]->setVisible(true);

	MakeParts_[3]->setPosition(350, 400);		//만들파츠
	MakeParts_[3]->setScale(2);
	MakeParts_[3]->setVisible(true);
	for (int i = 0; i < 3; i++)
	bar[0][i]->setVisible(true);
	for (int i = 0; i < 5; i++)
	bar[1][i]->setVisible(true);
	for (int i = 0; i < 2; i++)
	bar[2][i]->setVisible(true);
	m_layer[6]->setVisible(true);
	break;

	case 104:

	break;

	case 105:
	break;

	case 106:
	break;

	case 107:
	break;

	case 108:
	break;

	case 109:
	break;

	case 110:
	break;

	case 111:
	break;
	///////////////////////
	case 112:
	break;

	case 113:
	break;

	case 114:
	break;

	*/


	//this->removeChildByTag(55);



}
void StorageScene::PL2(Ref* pSender)//철갑형 수압총
{
	if (popup == true) {
		return;
	}
	int _nT = ((Node *)pSender)->getTag();
	for (j[1] = 1; j[1] < 15; j[1]++)
	{
		if (_nT == j[1] + 200)
		{
			mm = _nT;

			sprintf(str, "%d", j[1] + 1);
			m_label[0]->setString(str);					//파츠레벨
			m_label[0]->setPosition(430, 280);

			sprintf(str, "%d", (int)(500 * powf(1.2, j[1] - 1)));//제작 비용
			m_label[1]->setString(str);
			m_label[1]->setPosition(800, 300);

			sprintf(str, "/  %d", (int)(300 * powf(1.2, j[1] - 1)));	//첫번째 재료(마나피) 필요갯수
			m_label[2]->setString(str);
			m_label[2]->setScale(0.5);
			m_label[2]->setPosition(780, 370);

			sprintf(str, "/  %d", (int)(40 * powf(1.2, j[1] - 1)));		//두번째 재료(솔라) 필요갯수
			m_label[3]->setString(str);
			m_label[3]->setScale(0.5);
			m_label[3]->setPosition(930, 370);

			sprintf(str, "%dLV part ", j[1]);								//재료파츠 
			m_label[6]->setString(str);
			m_label[6]->setScale(0.5);
			m_label[6]->setPosition(600, 370);

			string zxcv1 = UserDefault::getInstance()->getStringForKey("material_6");
			int asdf1 = UserDefault::getInstance()->getIntegerForKey("material_6");
			m_label[4]->setString(zxcv1);// 유저 디폴트 써서 현재 보유 첫번째 재료 갯수 쓰기
			m_label[4]->setScale(0.5);
			m_label[4]->setPosition(750, 370);

			string zxcv2 = UserDefault::getInstance()->getStringForKey("material_7");
			int asdf2 = UserDefault::getInstance()->getIntegerForKey("material_7");
			m_label[5]->setString(zxcv2);//두번째 재료 보유갯수 쓰기
			m_label[5]->setScale(0.5);
			m_label[5]->setPosition(900, 370);

			if ((300 * powf(1.2, j[1] - 1)) > asdf1)
				m_label[4]->setColor(Color3B::RED);
			else
			{
				m_label[4]->setColor(Color3B::WHITE);
			}

			if ((40 * powf(1.2, j[1] - 1)) > asdf2)
				m_label[5]->setColor(Color3B::RED);
			else
			{
				m_label[5]->setColor(Color3B::WHITE);
			}

			for (int i = 0; i < 6; i++)
				UPlvL[i]->setVisible(false);
			for (int i = 0; i < 8; i++)
				m_material[i]->setVisible(false);
			for (int i = 0; i < 15; i++)
			{
				MakeParts1_[i]->setVisible(false);
				MakeParts2_[i]->setVisible(false);
				MakeParts3_[i]->setVisible(false);
				MakeParts4_[i]->setVisible(false);
				MakeParts5_[i]->setVisible(false);
				MakeParts6_[i]->setVisible(false);

				MaterialParts1_[i]->setVisible(false);
				MaterialParts2_[i]->setVisible(false);
				MaterialParts3_[i]->setVisible(false);
				MaterialParts4_[i]->setVisible(false);
				MaterialParts5_[i]->setVisible(false);
				MaterialParts6_[i]->setVisible(false);
			}

			UPlvL[1]->setVisible(true);
			m_material[6]->setPosition(750, 400);			//마나피
			m_material[6]->setVisible(true);
			m_material[7]->setPosition(900, 400);			//솔라
			m_material[7]->setVisible(true);

			MaterialParts2_[j[1] - 1]->setVisible(true);		//재료파츠

			MakeParts2_[j[1]]->setVisible(true);		//만들파츠

			for (int i = 0; i < 15; i++)
			{


				for (int i = 0; i < 5; i++)
					bar[0][i]->setVisible(true);
				bar[1][0]->setVisible(true);
				for (int i = 0; i < 2; i++)
					bar[2][i]->setVisible(true);
				m_layer[6]->setVisible(true);
				break;
			}
		}
	}

}
void StorageScene::PL3(Ref* pSender)//확산형 수압총
{
	if (popup == true) {
		return;
	}
	int _nT = ((Node *)pSender)->getTag();

	for (j[2] = 1; j[2] < 15; j[2]++)
	{
		if (_nT == j[2] + 300)
		{

			mm = _nT;

			sprintf(str, "%d", j[2] + 1);
			m_label[0]->setString(str);					//파츠레벨
			m_label[0]->setPosition(430, 300);

			sprintf(str, "%d", (int)(500 * powf(1.2, j[2] - 1)));//제작 비용
			m_label[1]->setString(str);
			m_label[1]->setPosition(800, 300);

			sprintf(str, "/  %d", (int)(300 * powf(1.2, j[2] - 1)));	//첫번째 재료(마나피) 필요갯수
			m_label[2]->setString(str);
			m_label[2]->setScale(0.5);
			m_label[2]->setPosition(780, 370);

			sprintf(str, "/  %d", (int)(80 * powf(1.2, j[2] - 1)));		//두번째 재료(크내폰) 필요갯수
			m_label[3]->setString(str);
			m_label[3]->setScale(0.5);
			m_label[3]->setPosition(930, 370);

			sprintf(str, "%dLV part ", j[2]);								//재료파츠 
			m_label[6]->setString(str);
			m_label[6]->setScale(0.5);
			m_label[6]->setPosition(600, 370);

			string zxcv1 = UserDefault::getInstance()->getStringForKey("material_3");
			int asdf1 = UserDefault::getInstance()->getIntegerForKey("material_3");
			m_label[4]->setString(zxcv1);// 유저 디폴트 써서 현재 보유 첫번째 재료 갯수 쓰기
			m_label[4]->setScale(0.5);
			m_label[4]->setPosition(750, 370);

			string zxcv2 = UserDefault::getInstance()->getStringForKey("material_2");
			int asdf2 = UserDefault::getInstance()->getIntegerForKey("material_2");
			m_label[5]->setString(zxcv2);//두번째 재료 보유갯수 쓰기
			m_label[5]->setScale(0.5);
			m_label[5]->setPosition(900, 370);

			if ((300 * powf(1.2, j[2] - 1)) > asdf1)
				m_label[4]->setColor(Color3B::RED);
			else
			{
				m_label[4]->setColor(Color3B::WHITE);
			}

			if ((80 * powf(1.2, j[5] - 1)) > asdf2)
				m_label[5]->setColor(Color3B::RED);
			else
			{
				m_label[5]->setColor(Color3B::WHITE);
			}

			for (int i = 0; i < 6; i++)
				UPlvL[i]->setVisible(false);
			for (int i = 0; i < 8; i++)
				m_material[i]->setVisible(false);
			for (int i = 0; i < 15; i++)
			{
				MakeParts1_[i]->setVisible(false);
				MakeParts2_[i]->setVisible(false);
				MakeParts3_[i]->setVisible(false);
				MakeParts4_[i]->setVisible(false);
				MakeParts5_[i]->setVisible(false);
				MakeParts6_[i]->setVisible(false);

				MaterialParts1_[i]->setVisible(false);
				MaterialParts2_[i]->setVisible(false);
				MaterialParts3_[i]->setVisible(false);
				MaterialParts4_[i]->setVisible(false);
				MaterialParts5_[i]->setVisible(false);
				MaterialParts6_[i]->setVisible(false);
			}

			UPlvL[2]->setVisible(true);
			m_material[6]->setPosition(750, 400);			//마나피
			m_material[6]->setVisible(true);
			m_material[4]->setPosition(900, 400);			//지프틴
			m_material[4]->setVisible(true);

			MaterialParts3_[j[2] - 1]->setVisible(true);		//재료파츠

			MakeParts3_[j[2]]->setVisible(true);		//만들파츠

			for (int i = 0; i < 15; i++)
			{


				for (int i = 0; i < 2; i++)
					bar[0][i]->setVisible(true);
				for (int i = 0; i < 3; i++)
					bar[1][i]->setVisible(true);
				for (int i = 0; i < 5; i++)
					bar[2][i]->setVisible(true);
				m_layer[6]->setVisible(true);
				popup = true;
				break;
			}
		}
	}




}
void StorageScene::PL4(Ref* pSender)//레이더(음파탐지기)
{
	if (popup == true) {
		return;
	}

	int _nT = ((Node *)pSender)->getTag();
	for (j[3] = 1; j[3] < 15; j[3]++)
	{
		if (_nT == j[3] + 400)
		{
			mm = _nT;

			sprintf(str, "%d", j[3] + 1);
			m_label[0]->setString(str);				//파츠레벨
			m_label[0]->setPosition(465, 300);

			sprintf(str, "%d", (int)(500 * powf(1.2, j[3] - 1)));//제작 비용
			m_label[1]->setString(str);
			m_label[1]->setPosition(800, 300);

			sprintf(str, "/  %d", (int)(160 * powf(1.2, j[3] - 1)));	//첫번째 재료(마나피) 필요갯수
			m_label[2]->setString(str);
			m_label[2]->setScale(0.5);
			m_label[2]->setPosition(780, 370);

			sprintf(str, "/  %d", (int)(300 * powf(1.2, j[3] - 1)));		//두번째 재료(크내폰) 필요갯수
			m_label[3]->setString(str);
			m_label[3]->setScale(0.5);
			m_label[3]->setPosition(930, 370);

			sprintf(str, "%dLV part ", j[3]);								//재료파츠 
			m_label[6]->setString(str);
			m_label[6]->setScale(0.5);
			m_label[6]->setPosition(600, 370);

			string zxcv1 = UserDefault::getInstance()->getStringForKey("material_6");
			int asdf1 = UserDefault::getInstance()->getIntegerForKey("material_6");
			m_label[4]->setString(zxcv1);// 유저 디폴트 써서 현재 보유 첫번째 재료 갯수 쓰기
			m_label[4]->setScale(0.5);
			m_label[4]->setPosition(750, 370);

			string zxcv2 = UserDefault::getInstance()->getStringForKey("material_5");
			int asdf2 = UserDefault::getInstance()->getIntegerForKey("material_5");
			m_label[5]->setString(zxcv2);//두번째 재료 보유갯수 쓰기
			m_label[5]->setScale(0.5);
			m_label[5]->setPosition(900, 370);

			if ((160 * powf(1.2, j[3] - 1)) > asdf1)
				m_label[4]->setColor(Color3B::RED);
			else
			{
				m_label[4]->setColor(Color3B::WHITE);
			}

			if ((300 * powf(1.2, j[3] - 1)) > asdf2)
				m_label[5]->setColor(Color3B::RED);
			else
			{
				m_label[5]->setColor(Color3B::WHITE);
			}

			for (int i = 0; i < 6; i++)
				UPlvL[i]->setVisible(false);
			for (int i = 0; i < 8; i++)
				m_material[i]->setVisible(false);
			for (int i = 0; i < 15; i++)
			{
				MakeParts1_[i]->setVisible(false);
				MakeParts2_[i]->setVisible(false);
				MakeParts3_[i]->setVisible(false);
				MakeParts4_[i]->setVisible(false);
				MakeParts5_[i]->setVisible(false);
				MakeParts6_[i]->setVisible(false);

				MaterialParts1_[i]->setVisible(false);
				MaterialParts2_[i]->setVisible(false);
				MaterialParts3_[i]->setVisible(false);
				MaterialParts4_[i]->setVisible(false);
				MaterialParts5_[i]->setVisible(false);
				MaterialParts6_[i]->setVisible(false);
			}

			UPlvL[3]->setVisible(true);
			m_material[3]->setPosition(750, 400);			//엠타
			m_material[3]->setVisible(true);
			m_material[2]->setPosition(900, 400);			//플론
			m_material[2]->setVisible(true);

			MaterialParts4_[j[3] - 1]->setVisible(true);		//재료파츠

			MakeParts4_[j[3]]->setVisible(true);		//만들파츠

			for (int i = 0; i < 15; i++)
			{


				for (int i = 0; i < 5; i++)
					bar[0][i]->setVisible(true);
				bar[1][0]->setVisible(true);
				for (int i = 0; i < 2; i++)
					bar[2][i]->setVisible(true);
				m_layer[6]->setVisible(true);
				popup = true;
				break;
			}
		}
	}

}
void StorageScene::PL5(Ref* pSender)//장갑
{
	if (popup == true) {
		return;
	}
	int _nT = ((Node *)pSender)->getTag();
	for (j[4] = 1; j[4] < 15; j[4]++)
	{
		if (_nT == j[4] + 500)
		{
			mm = _nT;


			sprintf(str, "%d", j[4] + 1);
			m_label[0]->setString(str);					//파츠레벨
			m_label[0]->setPosition(410, 300);

			sprintf(str, "%d", (int)(500 * powf(1.2, j[4] - 1)));//제작 비용
			m_label[1]->setString(str);
			m_label[1]->setPosition(800, 300);

			sprintf(str, "/  %d", (int)(80 * powf(1.2, j[4] - 1)));	//첫번째 재료(마나피) 필요갯수
			m_label[2]->setString(str);
			m_label[2]->setScale(0.5);
			m_label[2]->setPosition(780, 370);

			sprintf(str, "/  %d", (int)(5 * powf(1.2, j[4] - 1)));		//두번째 재료(크내폰) 필요갯수
			m_label[3]->setString(str);
			m_label[3]->setScale(0.5);
			m_label[3]->setPosition(930, 370);

			sprintf(str, "%dLV part ", j[4]);								//재료파츠 
			m_label[6]->setString(str);
			m_label[6]->setScale(0.5);
			m_label[6]->setPosition(600, 370);

			string zxcv1 = UserDefault::getInstance()->getStringForKey("material_1");
			int asdf1 = UserDefault::getInstance()->getIntegerForKey("material_1");
			m_label[4]->setString(zxcv1);// 유저 디폴트 써서 현재 보유 첫번째 재료 갯수 쓰기
			m_label[4]->setScale(0.5);
			m_label[4]->setPosition(750, 370);

			string zxcv2 = UserDefault::getInstance()->getStringForKey("material_0");
			int asdf2 = UserDefault::getInstance()->getIntegerForKey("material_0");
			m_label[5]->setString(zxcv2);//두번째 재료 보유갯수 쓰기
			m_label[5]->setScale(0.5);
			m_label[5]->setPosition(900, 370);

			if ((80 * powf(1.2, j[4] - 1)) > asdf1)
				m_label[4]->setColor(Color3B::RED);
			else
			{
				m_label[4]->setColor(Color3B::WHITE);
			}

			if ((5 * powf(1.2, j[4] - 1)) > asdf2)
				m_label[5]->setColor(Color3B::RED);
			else
			{
				m_label[5]->setColor(Color3B::WHITE);
			}

			for (int i = 0; i < 6; i++)
				UPlvL[i]->setVisible(false);
			for (int i = 0; i < 8; i++)
				m_material[i]->setVisible(false);
			for (int i = 0; i < 15; i++)
			{
				MakeParts1_[i]->setVisible(false);
				MakeParts2_[i]->setVisible(false);
				MakeParts3_[i]->setVisible(false);
				MakeParts4_[i]->setVisible(false);
				MakeParts5_[i]->setVisible(false);
				MakeParts6_[i]->setVisible(false);

				MaterialParts1_[i]->setVisible(false);
				MaterialParts2_[i]->setVisible(false);
				MaterialParts3_[i]->setVisible(false);
				MaterialParts4_[i]->setVisible(false);
				MaterialParts5_[i]->setVisible(false);
				MaterialParts6_[i]->setVisible(false);
			}

			UPlvL[4]->setVisible(true);
			m_material[1]->setPosition(750, 400);			//블랙스틸
			m_material[1]->setVisible(true);
			m_material[0]->setPosition(900, 400);			//드레이븐
			m_material[0]->setVisible(true);

			MaterialParts5_[j[4] - 1]->setVisible(true);		//재료파츠

			MakeParts5_[j[4]]->setVisible(true);		//만들파츠

			for (int i = 0; i < 15; i++)
			{


				for (int i = 0; i < 5; i++)
					bar[0][i]->setVisible(true);
				bar[1][0]->setVisible(true);
				for (int i = 0; i < 2; i++)
					bar[2][i]->setVisible(true);
				m_layer[6]->setVisible(true);
				popup = true;
				break;
			}
		}
	}

}
void StorageScene::PL6(Ref* pSender)//동력
{
	if (popup == true) {
		return;
	}
	int _nT = ((Node *)pSender)->getTag();
	for (j[5] = 1; j[5] < 15; j[5]++)
	{
		if (_nT == j[5] + 600)
		{

			mm = _nT;


			sprintf(str, "%d", j[5] + 1);
			m_label[0]->setString(str);					//파츠레벨
			m_label[0]->setPosition(410, 300);

			sprintf(str, "%d", (int)(500 * powf(1.2, j[5] - 1)));//제작 비용
			m_label[1]->setString(str);
			m_label[1]->setPosition(800, 300);

			sprintf(str, "/  %d", (int)(300 * powf(1.2, j[5] - 1)));	//첫번째 재료(크내폰) 필요갯수
			m_label[2]->setString(str);
			m_label[2]->setScale(0.5);
			m_label[2]->setPosition(780, 370);

			sprintf(str, "/  %d", (int)(300 * powf(1.2, j[5] - 1)));		//두번째 재료(플론) 필요갯수
			m_label[3]->setString(str);
			m_label[3]->setScale(0.5);
			m_label[3]->setPosition(930, 370);

			sprintf(str, "%dLV part ", j[5]);								//재료파츠 
			m_label[6]->setString(str);
			m_label[6]->setScale(0.5);
			m_label[6]->setPosition(600, 370);

			string zxcv1 = UserDefault::getInstance()->getStringForKey("material_5");
			int asdf1 = UserDefault::getInstance()->getIntegerForKey("material_5");
			m_label[4]->setString(zxcv1);// 유저 디폴트 써서 현재 보유 첫번째 재료 갯수 쓰기
			m_label[4]->setScale(0.5);
			m_label[4]->setPosition(750, 370);

			string zxcv2 = UserDefault::getInstance()->getStringForKey("material_2");
			int asdf2 = UserDefault::getInstance()->getIntegerForKey("material_2");
			m_label[5]->setString(zxcv2);//두번째 재료 보유갯수 쓰기
			m_label[5]->setScale(0.5);
			m_label[5]->setPosition(900, 370);

			if ((300 * powf(1.2, j[5] - 1)) > asdf1)
				m_label[4]->setColor(Color3B::RED);
			else
			{
				m_label[4]->setColor(Color3B::WHITE);
			}

			if ((300 * powf(1.2, j[5] - 1)) > asdf2)
				m_label[5]->setColor(Color3B::RED);
			else
			{
				m_label[5]->setColor(Color3B::WHITE);
			}

			for (int i = 0; i < 6; i++)
				UPlvL[i]->setVisible(false);
			for (int i = 0; i < 8; i++)
				m_material[i]->setVisible(false);
			for (int i = 0; i < 15; i++)
			{
				MakeParts1_[i]->setVisible(false);
				MakeParts2_[i]->setVisible(false);
				MakeParts3_[i]->setVisible(false);
				MakeParts4_[i]->setVisible(false);
				MakeParts5_[i]->setVisible(false);
				MakeParts6_[i]->setVisible(false);

				MaterialParts1_[i]->setVisible(false);
				MaterialParts2_[i]->setVisible(false);
				MaterialParts3_[i]->setVisible(false);
				MaterialParts4_[i]->setVisible(false);
				MaterialParts5_[i]->setVisible(false);
				MaterialParts6_[i]->setVisible(false);
			}

			UPlvL[5]->setVisible(true);
			m_material[5]->setPosition(750, 400);			//크네폰
			m_material[5]->setVisible(true);
			m_material[2]->setPosition(900, 400);			//플론
			m_material[2]->setVisible(true);

			MaterialParts6_[j[5] - 1]->setVisible(true);		//재료파츠

			MakeParts6_[j[5]]->setVisible(true);		//만들파츠

			for (int i = 0; i < 15; i++)
			{


				for (int i = 0; i < 5; i++)
					bar[0][i]->setVisible(true);
				bar[1][0]->setVisible(true);
				for (int i = 0; i < 2; i++)
					bar[2][i]->setVisible(true);
				m_layer[6]->setVisible(true);
				popup = true;
				break;
			}
		}
	}


}

void StorageScene::make(Ref* pSender)
{
	log("%d", mm);

	nowSubmarinFrame = 4;
	UserDefault::getInstance()->setIntegerForKey("SubmarinFrame", nowSubmarinFrame);
	UserDefault::getInstance()->flush();

	if (99 < mm && mm < 116)
	{
		sprintf(str, "hm/item/slv%d.png", mm - 99);
		m_Sprite[0]->setTexture(str);
	}
	else if (199 < mm && mm < 216)
	{
		sprintf(str, "hm/item/glv%d.png", mm - 199);
		m_Sprite[0]->setTexture(str);
	}
	else if (299 < mm && mm < 316)
	{
		sprintf(str, "hm/item/hlv%d.png", mm - 299);
		m_Sprite[0]->setTexture(str);

	}
	else if (399 < mm && mm < 416)
	{
		sprintf(str, "hm/item/ulv%d.png", mm - 399);
		m_Sprite[0]->setTexture(str);

	}
	else if (499 < mm && mm < 516)
	{
		sprintf(str, "hm/item/dlv%d.png", mm - 499);
		m_Sprite[0]->setTexture(str);
	}
	else if (599 < mm && mm < 616)
	{
		sprintf(str, "hm/item/jlv%d.png", mm - 599);
		m_Sprite[0]->setTexture(str);
	}
	m_layer[7]->setVisible(true);

	FadeIn* action_1 = FadeIn::create(2.0f);
	FadeOut* action_2 = FadeOut::create(1.0f);
	auto action_3 = CallFunc::create(CC_CALLBACK_0(StorageScene::closeLayer6, this));
	auto reload = CallFunc::create(CC_CALLBACK_0(StorageScene::SceneReload, this));

	Sequence* se1 = Sequence::create(action_1, action_2, action_3, reload, NULL);


	m_Sprite[0]->runAction(se1);
	m_Sprite[1]->runAction(se1->clone());
}
void StorageScene::cancel(Ref* pSender)
{
	removeChildByTag(55);

	m_layer[6]->setVisible(false);
	m_layer[7]->setVisible(false);
	for (int i = 0; i < 5; i++)
	{
		bar[0][i]->setVisible(false);
		bar[1][i]->setVisible(false);
		bar[2][i]->setVisible(false);
	}

	popup = false;

}
bool StorageScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point location = touch->getLocation();

	log("x = %f       y = %f", location.x, location.y);
	return true;
}
void StorageScene::onTouchMoved(Touch *touch, Event *unused_event){}
void StorageScene::onTouchEnded(Touch *touch, Event *unused_event){}
//void Storage::onTouchCancelled(Touch *touch, Event *unused_event){}
//void Storage::onTouchesBegan(const  vector<Touch*>& touches, Event *unused_event){}
//void Storage::onTouchesMoved(const  vector<Touch*>& touches, Event *unused_event){}
//void Storage::onTouchesEnded(const  vector<Touch*>& touches, Event *unused_event){}
//void Storage::onTouchesCancelled(const  vector<Touch*>&touches, Event *unused_event){}
void StorageScene::closeLayer6()
{
	m_layer[7]->setVisible(false);
}
void StorageScene::SceneReload()
{
	Director::getInstance()->replaceScene(StorageScene::createScene());
}