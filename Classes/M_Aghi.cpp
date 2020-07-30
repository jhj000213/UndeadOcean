#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void M_Aghi::m_init(Vec2 Pos, Layer * layer,Vector<M_Aghi*> *vec)
{
	M_HP = 100;
	Mother = Sprite::create("enemy/aghi/agi_hitpoint.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setScale(0.6f);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	//m_HPbar = MonsterHP::m_create(Vec2(-55, 100), Mother, 100);//작게
	//Mother->addChild(m_HPbar);

	Aghi = Sprite::create("enemy/aghi/agi0.png");
	Aghi->setPosition(Vec2(50,50));
	Mother->addChild(Aghi);

	auto ac = MoveBy::create(0.7f, Vec2(-560, 0));
	auto ac1 = MoveBy::create(2.0f, Vec2(-1600, 0));
	auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Aghi::removeself, this));
	auto seq = Sequence::create(EaseOut::create(ac, 2.5f), DelayTime::create(2.5f), EaseIn::create(ac1,2.5), ac2,RemoveSelf::create(),NULL);

	Mother->runAction(seq);                                                                                                                 
	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
}

void M_Aghi::m_update(float dt)
{
	//m_HPbar->hp_update(M_HP);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 4)//프레임 수
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
			sprintf(str, "enemy/aghi/agiwhite%d.png", nowFrame);
			//Aghi->setTexture(str);

			Sprite * h = Sprite::create(str);
			h->setPosition(Aghi->getPosition());
			Mother->addChild(h);
			auto ac = FadeOut::create(0.3f);
			auto seq = Sequence::create(ac, RemoveSelf::create(), NULL);
			h->runAction(seq);

			auto mo1 = MoveBy::create(0.05f, Vec2(4,0));
			auto mo2 = MoveBy::create(0.05f, Vec2(-8,0));
			auto mo3 = MoveBy::create(0.05f, Vec2(8,0));
			auto mo4 = MoveBy::create(0.05f, Vec2(-4, 0));
			auto moseq = Sequence::create(mo1, mo2, mo3,mo4, NULL);
			Mother->runAction(moseq);
		}
		else
		{
			char str[256];
			sprintf(str, "enemy/aghi/agi%d.png", nowFrame);
			Aghi->setTexture(str);
		}
	}
}

void M_Aghi::m_sollision()
{
	m_hit = true;
}

bool M_Aghi::m_sollisionCheck()
{
	
	return true;
}

Rect M_Aghi::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_Aghi::m_Dmg(int dmg)
{
	M_HP -= dmg;
}
void M_Aghi::removeself()
{
	p->eraseObject(this);
}

Vec2 M_Aghi::m_getPosition()
{
	return Mother->getPosition();
}