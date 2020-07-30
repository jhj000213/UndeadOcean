#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void FishHead_Hurricane::m_init(Vec2 Pos, Layer * layer, Vector<FishHead_Hurricane*> *vec, Vector<FishHead_Crash*> *wp)
{
	AudioEngine::play2d("sound/effect/fishhead_hurricane.mp3");

	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(1, 0.5));
	Mother->setScale(0.6f);
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	Wave = Sprite::create("enemy/fishhead/hurricane/hurricane0.png");
	Wave->setAnchorPoint(Vec2(1, 0.5));
	Wave->setPosition(Vec2(-1500, 700));
	Mother->addChild(Wave);

	auto ac1 = CallFunc::create(CC_CALLBACK_0(FishHead_Hurricane::m_makeCrash, this));
	auto ac2 = CallFunc::create(CC_CALLBACK_0(FishHead_Hurricane::removeself, this));
	auto seq = Sequence::create(DelayTime::create(1.5f), ac1,ac2, RemoveSelf::create(), NULL);

	Mother->runAction(seq);

	MonLayer = layer;
	HeadPos = Pos;
	p = vec;
	wvec = wp;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
}

void FishHead_Hurricane::m_update(float dt)
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
		sprintf(str, "enemy/fishhead/hurricane/hurricane%d.png", nowFrame);
		Wave->setTexture(str);

	}
}

void FishHead_Hurricane::m_sollision()
{
}

bool FishHead_Hurricane::m_sollisionCheck()
{
	return true;
}

Rect FishHead_Hurricane::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY(),
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void FishHead_Hurricane::m_Dmg(int dmg)
{
	M_HP -= dmg;
}
void FishHead_Hurricane::removeself()
{
	p->eraseObject(this);
}

Vec2 FishHead_Hurricane::m_getPosition()
{
	return Mother->getPosition();
}

void FishHead_Hurricane::m_makeCrash()
{
	FishHead_Crash * crash = FishHead_Crash::m_create(Vec2(HeadPos.x-160,HeadPos.y+40),MonLayer, wvec);
	this->addChild(crash);
	wvec->pushBack(crash);

	auto seq = Sequence::create(DelayTime::create(1.0f), RemoveSelf::create(), NULL);
	crash->runAction(seq);
}