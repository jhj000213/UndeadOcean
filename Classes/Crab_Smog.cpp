#include "stdafx.h"

#define MAX_TIME 0.1f
void Crab_Smog::m_init(Vec2 Pos, Layer * layer, Vector<Crab_Smog*> *vec, Vector<Crab_Thorn*> *tvec)
{
	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setPosition(Pos);
	this->addChild(Mother);


	Shild = Sprite::create("enemy/crab/smoke/smog0.png");
	Shild->setPosition(Vec2(180, 390));
	Mother->addChild(Shild);

	MonLayer = layer;
	tp = tvec;
	p = vec;
	m_time = MAX_TIME;
	m_hit = false;
	changeFrame = false;
	del = false;
	nowFrame = 0;
	loop = 0;
}

void Crab_Smog::m_update(float dt)
{
	if (del == false)
	{
		//log("%f", Mother->getPositionX());
		m_time -= dt;
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 3 && loop <= 4)
			{
				loop++;
				nowFrame = 1;
			}
			if (nowFrame == 11)//프레임 수
			{
				nowFrame = 10;
				makeThorn();
				Shild->setOpacity(0);
				del = true;
				//removeself();

			}

			changeFrame = true;
		}
		if (changeFrame == true && del == false)
		{
			changeFrame = false;

			char str[256];
			sprintf(str, "enemy/crab/smoke/smog%d.png", nowFrame);
			Shild->setTexture(str);

		}
	}
	
}

void Crab_Smog::m_sollision()
{
	m_hit = true;
}

bool Crab_Smog::m_sollisionCheck()
{

	return true;
}

Rect Crab_Smog::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void Crab_Smog::m_Dmg(int dmg)
{

}
void Crab_Smog::removeself()
{
	p->eraseObject(this);
}

Vec2 Crab_Smog::m_getPosition()
{
	return Mother->getPosition();
}

void Crab_Smog::makeThorn()
{
	Crab_Thorn * gashi = Crab_Thorn::m_create(Vec2(1080,0), tp);
	MonLayer->addChild(gashi);
	tp->pushBack(gashi);

	auto ac = Sequence::create(DelayTime::create(2.2f), RemoveSelf::create(), NULL);
	gashi->runAction(ac);
}