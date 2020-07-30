#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void M_CrabShildMake::m_init(Vec2 Pos, Layer * layer,Vector<M_CrabShildMake*> *vec, Vector<M_CrabShild*> *svec)
{
	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(125);
	Mother->setPosition(Pos);
	this->addChild(Mother);


	Shild = Sprite::create("enemy/crab/shildmake/shildmake0.png");
	Shild->setPosition(Vec2(50, 50));
	Mother->addChild(Shild);

	MonLayer = layer;
	sp = svec;
	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	del = false;
	nowFrame = 0;
}

void M_CrabShildMake::m_update(float dt)
{
	if (del == false)
	{
		//log("%f", Mother->getPositionX());
		m_time -= dt;
		m_delaytime -= dt;
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 7)//프레임 수
			{
				nowFrame = 6;
				m_makeShild();
				del = true;
				//removeself();
				
				//Shild->setOpacity(0);
				
			}

			changeFrame = true;
		}
		if (changeFrame == true && del == false)
		{
			changeFrame = false;

			char str[256];
			sprintf(str, "enemy/crab/shildmake/shildmake%d.png", nowFrame);
			Shild->setTexture(str);
		}
	}

}

void M_CrabShildMake::m_sollision()
{
	m_hit = true;
}

bool M_CrabShildMake::m_sollisionCheck()
{

	return true;
}

Rect M_CrabShildMake::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_CrabShildMake::m_Dmg(int dmg)
{

}
void M_CrabShildMake::removeself()
{
	p->eraseObject(this);
	Mother->removeChild(Shild,true);
}

Vec2 M_CrabShildMake::m_getPosition()
{
	return Mother->getPosition();
}

void M_CrabShildMake::m_makeShild()
{
	M_CrabShild * Shild = M_CrabShild::m_create(Vec2(700,360), MonLayer, sp);
	MonLayer->addChild(Shild);
	sp->pushBack(Shild);
}