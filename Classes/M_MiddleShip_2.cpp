#include "stdafx.h"

#define MAX_TIME 0.10f
#define DELAY_TIME 0.45f
#define PAT_DELAY_TIME 3.5f
void M_MiddleShip_2::m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<MonsterRazer*> *mv)
{
	M_HP = 1500;

	Mother = Sprite::create("enemy/middleship/dragon/dragonhit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	m_HPbar = MonsterHP::m_create(Vec2(150, 200), Mother, 1500);
	Mother->addChild(m_HPbar);

	middleShip = Sprite::create("enemy/middleship/change/midiumchange0.png");
	middleShip->setPosition(Vec2(280, 85));
	Mother->addChild(middleShip);

	HeadPos = Vec2(Mother->getPosition().x-100,Mother->getPosition().y+50);
	MonLayer = layer;
	p = vec;
	mp = mv;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_patdelaytime = PAT_DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	Changeing = true;
	hitBoom = false;
	nowFrame = 0;
	moveup = -1;
}

void M_MiddleShip_2::m_update(float dt,int path)
{
	m_HPbar->hp_update(M_HP);

	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	m_patdelaytime -= dt;

	
	BubbleTime -= dt;
	if (BubbleTime <= 0.0f)
	{
		BubbleTime = 3.1f;
		MakeBubble();
	}


	if (mp->empty() == false)
	{
		for (MonsterRazer * MR : *mp)
		{
			if (MR->m_getRazerInfo() == 1)
			{
				MR->m_setPosition(HeadPos);
			}
		}
	}

	if (hitBoom == true && hitc == false)
	{
		hitc = true;
		auto ac = CallFunc::create(CC_CALLBACK_0(M_MiddleShip_2::setbool, this));
		auto seq = Sequence::create(DelayTime::create(1.6f), ac, NULL);

		this->runAction(seq);
	}
	
	if (Changeing == false)
	{
		float PosY = Mother->getPositionY();
		if (Mother->getPositionY() + Mother->boundingBox().size.height / 2 >= 700)
			moveup = -1;
		if (Mother->getPositionY() - Mother->boundingBox().size.height / 2 <= 0)
			moveup = 1;
		Mother->setPositionY(PosY + 40 * dt * moveup);

		HeadPos = Vec2(Mother->getPosition().x - 100, Mother->getPosition().y + 50);

		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 17)//프레임 수
				nowFrame = 0;
			changeFrame = true;
		}
		if (m_patdelaytime <= 0.0f)
		{
			m_Pattun(path);//
			m_patdelaytime = PAT_DELAY_TIME;
		}

		if (changeFrame == true)
		{
			changeFrame = false;
			if (m_hit == true && m_delaytime <= 0.0f)
			{
				m_delaytime = DELAY_TIME;
				m_hit = false;

				char str[256];
				sprintf(str, "enemy/middleship/dragon/dragonwhite.png");
				//Aghi->setTexture(str);

				Sprite * h = Sprite::create(str);
				h->setPosition(middleShip->getPosition());
				Mother->addChild(h);
				auto ac = FadeOut::create(0.3f);
				auto seq = Sequence::create(ac, RemoveSelf::create(), NULL);
				h->runAction(seq);

				auto mo1 = MoveBy::create(0.05f, Vec2(4, 0));
				auto mo2 = MoveBy::create(0.05f, Vec2(-8, 0));
				auto mo3 = MoveBy::create(0.05f, Vec2(8, 0));
				auto mo4 = MoveBy::create(0.05f, Vec2(-4, 0));
				auto moseq = Sequence::create(mo1, mo2, mo3, mo4, NULL);
				Mother->runAction(moseq);
			}
			else
			{
				char str[256];
				sprintf(str, "enemy/middleship/dragon/dragon%d.png", nowFrame);
				middleShip->setTexture(str);
			}
		}
	}
	else
	{
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 24)//프레임 수
			{
				Changeing = false;
				nowFrame = 0;
			}
				
			changeFrame = true;
		}
		if (changeFrame == true && Changeing == true)
		{
			changeFrame = false;
			
			char str[256];
			sprintf(str, "enemy/middleship/change/midiumchange%d.png", nowFrame);
			middleShip->setTexture(str);

		}
	}

}

void M_MiddleShip_2::m_sollision()
{
	m_hit = true;
}

bool M_MiddleShip_2::m_sollisionCheck()
{

	return true;
}

Rect M_MiddleShip_2::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_MiddleShip_2::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void M_MiddleShip_2::m_Pattun(int path)
{
	int patnum;


	//patnum = path;
	//patnum = 1;
	patnum = (rand() % 4) + 1;
	if (patnum == 1)
	{
		auto ac1 = CallFuncN::create(CC_CALLBACK_0(M_MiddleShip_2::m_SprinkleShot1, this));
		auto ac2 = CallFuncN::create(CC_CALLBACK_0(M_MiddleShip_2::m_SprinkleShot2, this));

		auto seq = Sequence::create(ac1, DelayTime::create(0.4f), ac2, NULL);
		this->runAction(seq);
	}
	else if (patnum == 2)
	{
		Vec2 Pos = Mother->getPosition();

		auto ac1 = MoveTo::create(0.5f, Vec2(1050, 620));
		auto ac2 = MoveTo::create(1.0f, Vec2(1050, 100));
		auto ac3 = MoveTo::create(0.7f, Vec2(Pos.x,Pos.y/2+100));

		auto seq = Sequence::create(EaseOut::create(ac1,2.5f), DelayTime::create(0.76), ac2,EaseOut::create(ac3,2.5f), NULL);
		Mother->runAction(seq);

		MonsterRazer * Razer = MonsterRazer::m_create(HeadPos, 1,true);
		this->addChild(Razer);
		mp->pushBack(Razer);
	}
	else if (patnum == 3)
	{
		Vec2 Pos = Mother->getPosition();

		auto ac1 = MoveTo::create(0.5f, Vec2(1050, 50));
		auto ac2 = MoveTo::create(1.0f, Vec2(1050, 620));
		auto ac3 = MoveTo::create(0.7f, Vec2(Pos.x, 600-Pos.y / 2 ));

		auto seq = Sequence::create(EaseOut::create(ac1, 2.5f), DelayTime::create(0.76), ac2, EaseOut::create(ac3, 2.5f), NULL);
		Mother->runAction(seq);

		MonsterRazer * Razer = MonsterRazer::m_create(HeadPos, 1,true);
		this->addChild(Razer);
		mp->pushBack(Razer);
	}
	else if (patnum == 4)
	{
		auto ac1 = CallFuncN::create(CC_CALLBACK_0(M_MiddleShip_2::m_SprinkleShot1, this));
		auto ac2 = CallFuncN::create(CC_CALLBACK_0(M_MiddleShip_2::m_SprinkleShot2, this));

		auto seq = Sequence::create(ac1, DelayTime::create(0.4f), ac2, NULL);
		this->runAction(seq);
	}
}

void M_MiddleShip_2::m_SprinkleShot1()
{

	for (int i = 0; i < 5; i++)
	{
		MonsterMissail * Missail = MonsterMissail::m_create(HeadPos, this, Vec2(0, 0), 3, i);
		MonLayer->addChild(Missail);
		p->pushBack(Missail);
	}
}

void M_MiddleShip_2::m_SprinkleShot2()
{

	for (int i = 0; i < 4; i++)
	{
		MonsterMissail * Missail = MonsterMissail::m_create(HeadPos, this, Vec2(0, 0), 5, i);
		MonLayer->addChild(Missail);
		p->pushBack(Missail);
	}
}

Vec2 M_MiddleShip_2::m_getPosition()
{
	return Mother->getPosition();
}

void M_MiddleShip_2::setbool()
{
	hitBoom = false;
	hitc = false;
}

void M_MiddleShip_2::MakeBubble()
{
	Sprite * bub = Sprite::create();
	bub->setPosition(Vec2(20, 80));
	bub->setScale(0.6f);
	Mother->addChild(bub, 1000);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 0; i < 7; i++)
	{
		sprintf(str1, "bub%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	bub->runAction(seq);




	Sprite * bub1 = Sprite::create();
	bub1->setPosition(Vec2(270, 20));
	Mother->addChild(bub1, 1000);

	Vector<SpriteFrame *>aniFrames11;
	char str11[256];
	for (int i = 0; i < 7; i++)
	{
		sprintf(str11, "bub%d.png", i);

		SpriteFrame * frame11 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str11);
		aniFrames11.pushBack(frame11);
	}
	Animation * ani1 = Animation::createWithSpriteFrames(aniFrames11, 0.1f, 1);

	Animate * animate1 = Animate::create(ani1);

	auto * seq1 = Sequence::create(animate1, RemoveSelf::create(), NULL);


	bub1->runAction(seq1);
}