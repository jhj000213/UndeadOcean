#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void Crab_Wave::m_init(Vec2 Pos, Vector<Crab_Wave*> *vec)
{
	Mother = Sprite::create("enemy/crab/wave/wavehit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0));
	Mother->setScale(0.75);
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	Wave = Sprite::create("enemy/crab/wave/wave0.png");
	Wave->setPosition(Vec2(300, 300));
	Mother->addChild(Wave);

	auto ac = MoveBy::create(1.0f, Vec2(-1280, 0));
	auto ac2 = CallFunc::create(CC_CALLBACK_0(Crab_Wave::removeself, this));
	auto seq = Sequence::create(ac, ac2, RemoveSelf::create(), NULL);

	Mother->runAction(seq);
	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
}

void Crab_Wave::m_update(float dt)
{
	m_time -= dt;
	m_delaytime -= dt;
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

		char str[256];
		sprintf(str, "enemy/crab/wave/wave%d.png", nowFrame);
		Wave->setTexture(str);
		
	}
}

void Crab_Wave::m_sollision()
{
}

bool Crab_Wave::m_sollisionCheck()
{
	return true;
}

Rect Crab_Wave::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY(),
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void Crab_Wave::m_Dmg(int dmg)
{
	M_HP -= dmg;
}
void Crab_Wave::removeself()
{
	p->eraseObject(this);
}

Vec2 Crab_Wave::m_getPosition()
{
	return Mother->getPosition();
}