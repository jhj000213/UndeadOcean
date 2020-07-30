#include "stdafx.h"

#define MAX_TIME 0.10f
#define DELAY_TIME 0.45f;
void Crab_Thorn::m_init(Vec2 Pos, Vector<Crab_Thorn*> *vec)
{
	Mother = Sprite::create("enemy/crab/thorn/wavehit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	Wave = Sprite::create("enemy/crab/thorn/gashi0.png");
	Wave->setAnchorPoint(Vec2(0, 0));
	Wave->setPosition(Vec2(0,0));
	this->addChild(Wave,1);

	auto ac = MoveBy::create(2.0f, Vec2(-1080, 0));
	auto ac2 = CallFunc::create(CC_CALLBACK_0(Crab_Thorn::removeself, this));
	auto seq = Sequence::create(ac, ac2, RemoveSelf::create(), NULL);

	Mother->runAction(seq);
	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;

	AudioEngine::play2d("sound/effect/crab_thorn.mp3", false, Volume);
}

void Crab_Thorn::m_update(float dt)
{
	m_time -= dt;
	m_delaytime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 20)//프레임 수
		{
			nowFrame = 19;
			Wave->setOpacity(0);
		}
			
		changeFrame = true;
	}
	if (changeFrame == true)
	{

		char str[256];
		sprintf(str, "enemy/crab/thorn/gashi%d.png", nowFrame);
		Wave->setTexture(str);

	}
}

void Crab_Thorn::m_sollision()
{
}

bool Crab_Thorn::m_sollisionCheck()
{
	return true;
}

Rect Crab_Thorn::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY(),
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void Crab_Thorn::m_Dmg(int dmg)
{
	M_HP -= dmg;
}
void Crab_Thorn::removeself()
{
	p->eraseObject(this);
}

Vec2 Crab_Thorn::m_getPosition()
{
	return Mother->getPosition();
}