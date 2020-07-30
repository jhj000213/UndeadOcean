#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f
#define SHOOT_DELAY 5.6f
#define DANGER_TIME 1.6f
void M_Japonica::m_init(Vec2 Pos, Layer * layer, Vector<MonsterRazer*> *p)
{
	M_HP = 140;
	Mother = Sprite::create("enemy/japonica/japonicahit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setScale(0.7);
	Mother->setPosition(Pos);
	this->addChild(Mother,15);

	//m_HPbar = MonsterHP::m_create(Vec2(-10, 100), Mother, 140);
	//Mother->addChild(m_HPbar);

	Japo = Sprite::create("enemy/japonica/japonica0.png");
	Japo->setPosition(Vec2(110, 30));
	Mother->addChild(Japo);

	auto ac = MoveBy::create(0.7f, Vec2(-400, 0));

	//auto seq = Sequence::create(ac, DelayTime::create(2.5f),  NULL);

	Mother->runAction(ac);

	MomL = layer;
	vec = p;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_shootdelaytime = 2.0f;
	m_shootingtime = 1.0f;
	m_dangerTime = DANGER_TIME;
	m_hit = false;
	changeFrame = false;
	danger = false;
	nowFrame = 0;
	shootnowFrame = 0;
}

void M_Japonica::m_update(float dt)
{
	//m_HPbar->hp_update(M_HP);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;

	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 8)//프레임 수
			nowFrame = 0;
		changeFrame = true;
	}

	m_shootdelaytime -= dt;

	if (m_shootdelaytime <= 0.0f)
	{
		shoot = true;
		danger = true;
		m_shootdelaytime = SHOOT_DELAY;
		MonsterRazer * MR = MonsterRazer::m_create(Vec2(Mother->getPositionX()-50,Mother->getPositionY()), 2,true);
		this->addChild(MR,10);
		vec->pushBack(MR);

		auto seq = Sequence::create(DelayTime::create(4.0f), RemoveSelf::create(), NULL);
		MR->runAction(seq);
	}

	if (danger == true)
		m_dangerTime -= dt;

	if (m_dangerTime <= 0.0f)
		danger == false;

	if (shoot == true)
	{
		m_shootingtime -= dt;
	}
		

	if (m_shootingtime <= 0.0f)
	{
		shoot = false;
		m_shootingtime = 1.0f;

	}
		

	if (changeFrame == true)
	{
		changeFrame = false;
		if (shoot == true && danger == false)
		{
			char str[256];
			sprintf(str, "enemy/japonica/sparkjaponica%d.png", shootnowFrame);
			Japo->setTexture(str);
			shootnowFrame++;
			if (shootnowFrame == 2)
				shootnowFrame = 0;
		}
		else if (m_hit == true && m_delaytime <= 0.0f)
		{
			m_delaytime = DELAY_TIME;
			m_hit = false;

			char str[256];
			sprintf(str, "enemy/japonica/japonicawhite%d.png", nowFrame);
			//Aghi->setTexture(str);

			Sprite * h = Sprite::create(str);
			h->setPosition(Japo->getPosition());
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
			sprintf(str, "enemy/japonica/japonica%d.png", nowFrame);
			Japo->setTexture(str);
			
		}
	}
}

void M_Japonica::m_sollision()
{
	m_hit = true;
}

bool M_Japonica::m_sollisionCheck()
{

	return true;
}

Rect M_Japonica::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_Japonica::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

Vec2 M_Japonica::m_getPosition()
{
	return Mother->getPosition();
}