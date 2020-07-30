#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void Crab_EarseQuake::m_init(Vec2 Pos, Layer * layer, Vector<Crab_EarseQuake*> *vec,Vector<Crab_Wave*> *w)
{
	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(125);
	Mother->setPosition(Pos);
	this->addChild(Mother);


	Shild = Sprite::create("enemy/crab/punch/punch0.png");
	Shild->setPosition(Vec2(50, 50));
	Mother->addChild(Shild);

	MonLayer = layer;
	wp = w;
	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	del = false;
	nowFrame = 0;
}

void Crab_EarseQuake::m_update(float dt)
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
			if (nowFrame == 6)
			{

				m_makeWave();

			}
			if (nowFrame == 9)//프레임 수
			{
				nowFrame = 8;
				del = true;
				//Shild->setOpacity(0);
				//removeself();
			}

			changeFrame = true;
		}
		if (changeFrame == true&&del==false)
		{
			changeFrame = false;

			char str[256];
			sprintf(str, "enemy/crab/punch/punch%d.png", nowFrame);
			Shild->setTexture(str);

		}
	}
	
}

void Crab_EarseQuake::m_sollision()
{
	m_hit = true;
}

bool Crab_EarseQuake::m_sollisionCheck()
{

	return true;
}

Rect Crab_EarseQuake::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void Crab_EarseQuake::m_Dmg(int dmg)
{

}
void Crab_EarseQuake::removeself()
{
	p->eraseObject(this);
	Mother->removeChild(Shild,true);
}

Vec2 Crab_EarseQuake::m_getPosition()
{
	return Mother->getPosition();
}

void Crab_EarseQuake::m_makeWave()
{
	Crab_Wave * wave = Crab_Wave::m_create(Vec2(1000,0), wp);
	MonLayer->addChild(wave);
	wp->pushBack(wave);

	auto seq = Sequence::create(DelayTime::create(1.2f), RemoveSelf::create(), NULL);
	wave->runAction(seq);
}