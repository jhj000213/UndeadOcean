#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void M_CrabShild::m_init(Vec2 Pos, Layer * layer, Vector<M_CrabShild*> *vec)
{
	M_HP = 500;
	Mother = Sprite::create("enemy/crab/barrier/shildhit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);


	Shild = Sprite::create("enemy/crab/barrier/shild0.png");
	Shild->setPosition(Vec2(100, 300));
	Mother->addChild(Shild);


	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
}

void M_CrabShild::m_update(float dt)
{
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 5)//프레임 수
		{
			nowFrame = 4;
		}

		changeFrame = true;
	}
	if (changeFrame == true)
	{
		changeFrame = false;

		char str[256];
		sprintf(str, "enemy/crab/barrier/shild%d.png", nowFrame);
		Shild->setTexture(str);
	}
	if (M_HP <= 0)
	{
		removeself();
	}
}

void M_CrabShild::m_sollision()
{
	m_hit = true;
}

bool M_CrabShild::m_sollisionCheck()
{

	return true;
}

Rect M_CrabShild::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_CrabShild::m_Dmg(int dmg)
{
	M_HP -= dmg;
}
void M_CrabShild::removeself()
{
	p->eraseObject(this);
}

Vec2 M_CrabShild::m_getPosition()
{
	return Mother->getPosition();
}