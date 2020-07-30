#include "stdafx.h"

#define MAX_TIME 0.13f
#define DELAY_TIME 0.45f
#define COOL_TIME 2.3f
void M_MiniOb::m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec,Vector<M_MiniOb*> *hvec,int in)
{
	M_HP = 110;
	Mother = Sprite::create("enemy/middleship/miniob/juggernautsmallsizehit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	Mother->setScale(0.6);
	this->addChild(Mother);
	MonLayer = layer;
	//m_HPbar = MonsterHP::m_create(Vec2(-60, 100), Mother, 150);
	//Mother->addChild(m_HPbar);

	MiniOb = Sprite::create("enemy/middleship/miniob/juggernautsmallsize0.png");
	MiniOb->setPosition(Vec2(85, 50));
	Mother->addChild(MiniOb);

	if (in == 1)
	{
		auto ac = MoveBy::create(1.0f, Vec2(0, -100));//이지액션 먹임,밑으로
		auto ac1 = MoveBy::create(1.0f, Vec2(-50, 0));
		auto ac2 = MoveBy::create(4.0f, Vec2(-1280, 0));
		auto spa = Spawn::create(EaseOut::create(ac, 2.5f), EaseOut::create(ac1, 2.5f), NULL);
		auto ac3 = CallFunc::create(CC_CALLBACK_0(M_MiniOb::removeself, this));
		auto seq = Sequence::create(spa, DelayTime::create(2.0f), ac2,ac3, NULL);
		Mother->runAction(seq);
	}
	else if (in == 2)
	{
		auto ac = MoveBy::create(5.0f, Vec2(-1480, 0));
		auto ac3 = CallFunc::create(CC_CALLBACK_0(M_MiniOb::removeself, this));
		auto seq = Sequence::create(ac,ac3, NULL);

		Mother->runAction(seq);
	}
	

	mp = hvec;
	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
	m_shotCoolTime = COOL_TIME;

}

void M_MiniOb::m_update(float dt, Vec2 Pos)
{

	//m_HPbar->hp_update(M_HP);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	m_shotCoolTime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 3)//프레임 수
			nowFrame = 0;
		changeFrame = true;
	}
	if (changeFrame == true)
	{
		changeFrame = false;
		if (m_hit == true && m_delaytime <= 0.0f)
		{
			m_delaytime = DELAY_TIME;
			m_hit = false;

			char str[256];
			sprintf(str, "enemy/middleship/miniob/juggernautsmallsizewhite%d.png", nowFrame);
			//Aghi->setTexture(str);

			Sprite * h = Sprite::create(str);
			h->setPosition(MiniOb->getPosition());
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
			sprintf(str, "enemy/middleship/miniob/juggernautsmallsize%d.png", nowFrame);
			MiniOb->setTexture(str);
		}
	}

	if (m_shotCoolTime <= 0.0f)
	{
		m_Shoot(Pos);
		m_shotCoolTime = COOL_TIME;
	}
	MobPos = Mother->getPosition();
}

void M_MiniOb::m_sollision()
{
	m_hit = true;
}

bool M_MiniOb::m_sollisionCheck()
{

	return true;
}

Rect M_MiniOb::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_MiniOb::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void M_MiniOb::m_Shoot(Vec2 Pos)
{
	MonsterMissail * Missail = MonsterMissail::m_create(Mother->getPosition(), MonLayer, Pos, 4, 0);
	MonLayer->addChild(Missail);
	p->pushBack(Missail);
}

void M_MiniOb::removeself()
{
	mp->eraseObject(this);
}

Vec2 M_MiniOb::m_getPosition()
{
	return Mother->getPosition();
}