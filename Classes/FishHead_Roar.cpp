#include "stdafx.h"

#define MAX_TIME 0.1f
void FishHead_Roar::m_init(Vec2 Pos, Layer * layer, Vector<FishHead_Roar*> *vec, Vector<FishHead_Rain*> *tvec)
{
	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(0,0));
	Mother->setPosition(Pos);
	layer->addChild(Mother,100);

	AudioEngine::play2d("sound/effect/fishhead_roar.mp3", false, Volume);


	Shild = Sprite::create("enemy/fishhead/roar/roar0.png");
	Shild->setAnchorPoint(Vec2(0, 0));
	Shild->setPosition(Vec2(0, 0));
	layer->addChild(Shild,100);

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

void FishHead_Roar::m_update(float dt)
{
	if (del == false)
	{
		//log("%f", Mother->getPositionX());
		m_time -= dt;
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;

			if (nowFrame == 12)//프레임 수
			{
				nowFrame = 11;
				makeRain();
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
			sprintf(str, "enemy/fishhead/roar/roar%d.png", nowFrame);
			Shild->setTexture(str);

		}
	}

}

void FishHead_Roar::m_sollision()
{
	m_hit = true;
}

bool FishHead_Roar::m_sollisionCheck()
{

	return true;
}

Rect FishHead_Roar::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void FishHead_Roar::m_Dmg(int dmg)
{

}
void FishHead_Roar::removeself()
{
	p->eraseObject(this);
}

Vec2 FishHead_Roar::m_getPosition()
{
	return Mother->getPosition();
}

void FishHead_Roar::makeRain()
{
	FishHead_Rain * gashi = FishHead_Rain::m_create(MonLayer, tp);
	MonLayer->addChild(gashi);
	tp->pushBack(gashi);

	auto ac = Sequence::create(DelayTime::create(2.2f), RemoveSelf::create(), NULL);
	gashi->runAction(ac);
}