#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void FishHead_Crash::m_init(Vec2 Pos,Layer * layer, Vector<FishHead_Crash*> *vec)
{
	AudioEngine::play2d("sound/effect/fishhead_crash.mp3");

	Mother = Sprite::create("enemy/fishhead/crash/crashhit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setScale(0.7f);
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	layer->addChild(Mother,150);

	Wave = Sprite::create("enemy/fishhead/crash/crash0.png");
	Wave->setPosition(Vec2(300, 300));
	Mother->addChild(Wave);


	auto ac2 = CallFunc::create(CC_CALLBACK_0(FishHead_Crash::removeself, this));
	auto seq = Sequence::create(DelayTime::create(1.0f), ac2, RemoveSelf::create(), NULL);

	Mother->runAction(seq);

	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
}

void FishHead_Crash::m_update(float dt)
{
	m_time -= dt;
	m_delaytime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 4)//프레임 수
		{
			nowFrame = 0;
			Wave->setOpacity(0);
		}
			
		changeFrame = true;
	}
	if (changeFrame == true)
	{

		char str[256];
		sprintf(str, "enemy/fishhead/crash/crash%d.png", nowFrame);
		Wave->setTexture(str);

	}
}

void FishHead_Crash::m_sollision()
{
}

bool FishHead_Crash::m_sollisionCheck()
{
	return true;
}

Rect FishHead_Crash::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY(),
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void FishHead_Crash::m_Dmg(int dmg)
{
	M_HP -= dmg;
}
void FishHead_Crash::removeself()
{
	p->eraseObject(this);
}

Vec2 FishHead_Crash::m_getPosition()
{
	return Mother->getPosition();
}