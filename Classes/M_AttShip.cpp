#include "stdafx.h"

#define MAX_TIME 0.13f
#define DELAY_TIME 0.45f
#define COOL_TIME 3.5f
void M_AttShip::m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<M_AttShip*> *hvec)
{
	M_HP = 1000;
	Mother = Sprite::create("enemy/attship/normal/attshiphit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);
	MonLayer = layer;

	m_HPbar = MonsterHP::m_create(Vec2(40, 220), Mother, 1000);
	Mother->addChild(m_HPbar);

	MiniOb = Sprite::create("enemy/attship/normal/attship0.png");
	MiniOb->setPosition(Vec2(140, 100));
	Mother->addChild(MiniOb);

	auto ac = MoveBy::create(3.0f, Vec2(-550, 0));
	auto ac1 = MoveBy::create(4.0f, Vec2(0, 200));
	auto ac2 = MoveBy::create(4.0f, Vec2(0, -200));
	auto ac3 = MoveBy::create(5.0f, Vec2(-1400, 0));
	auto ac4 = CallFunc::create(CC_CALLBACK_0(M_AttShip::removeself, this));
	auto seq = Sequence::create(EaseOut::create(ac, 3.0f), ac1, ac2, ac1, ac2, ac3, ac4, NULL);
	Mother->runAction(seq);

	mp = hvec;
	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	hitBoom = false;
	hitc = false;
	nowFrame = 0;
	m_shotCoolTime = COOL_TIME;
}

void M_AttShip::m_update(float dt)
{

	m_HPbar->hp_update(M_HP);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	m_shotCoolTime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 10)//프레임 수
			nowFrame = 0;
		changeFrame = true;
	}
	if (hitBoom == true && hitc == false)
	{
		hitc = true;
		auto ac = CallFunc::create(CC_CALLBACK_0(M_AttShip::setbool, this));
		auto seq = Sequence::create(DelayTime::create(1.6f), ac, NULL);

		this->runAction(seq);
	}
	if (changeFrame == true)
	{
		changeFrame = false;
		if (m_hit == true && m_delaytime <= 0.0f)
		{
			m_delaytime = DELAY_TIME;
			m_hit = false;

			char str[256];
			sprintf(str, "enemy/attship/normal/attshipwhite.png");
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
			sprintf(str, "enemy/attship/normal/attship%d.png", nowFrame);
			MiniOb->setTexture(str);
		}
	}

	if (m_shotCoolTime <= 0.0f)
	{
		m_Shoot();
		m_shotCoolTime = COOL_TIME;
	}
	MobPos = Mother->getPosition();
}

void M_AttShip::m_sollision()
{
	m_hit = true;
}

bool M_AttShip::m_sollisionCheck()
{

	return true;
}

Rect M_AttShip::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_AttShip::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void M_AttShip::m_Shoot()
{
	for (int i = 0; i < 4; i++)
	{
		MonsterMissail * Missail = MonsterMissail::m_create(Vec2(Mother->getPositionX()-100, Mother->getPositionY()), this, Vec2(0, 0), 5, i);
		MonLayer->addChild(Missail);
		p->pushBack(Missail);
	}
}

void M_AttShip::removeself()
{
	mp->eraseObject(this);
}

Vec2 M_AttShip::m_getPosition()
{
	return Mother->getPosition();
}
void M_AttShip::setbool()
{
	hitBoom = false;
	hitc = false;
}
