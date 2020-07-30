#include "stdafx.h"

#define MAX_TIME 0.1f
#define DELAY_TIME 0.45f;
void FishHead_Rain::m_init(Layer * layer, Vector<FishHead_Rain*> *vec)
{
	AudioEngine::play2d("sound/effect/fishhead_rain.mp3", false, Volume);

	Mother = Sprite::create("enemy/fishhead/rain/stornhit.png");
	Mother->setAnchorPoint(Vec2(0, 0));
	Mother->setOpacity(0);
	Mother->setPosition(0, 1280);
	layer->addChild(Mother, 100);

	Wave = Sprite::create("enemy/fishhead/rain/storn.png");
	Wave->setAnchorPoint(Vec2(0, 0));
	Wave->setPosition(Vec2(0, 0));
	layer->addChild(Wave, 0);

	Eff = Sprite::create("enemy/fishhead/rain/rainboom0.png");
	Eff->setAnchorPoint(Vec2(0.5, 0));
	Eff->setOpacity(200);
	Eff->setPosition(Vec2(345, -30));
	layer->addChild(Eff,150);

	auto seqq = Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), NULL);
	Eff->runAction(seqq);

	auto ac = MoveBy::create(0.5f, Vec2(0, -1280));
	auto seq = Sequence::create(ac,DelayTime::create(1.2f),MoveBy::create(0.2f,Vec2(0,-720)),DelayTime::create(0.3f),RemoveSelf::create(), NULL);
	Mother->runAction(seq);

	auto move = MoveBy::create(2.0f, Vec2(0, -4813));
	auto ac1 = CallFunc::create(CC_CALLBACK_0(FishHead_Rain::removeself, this));
	auto seq1 = Sequence::create(move, ac1, RemoveSelf::create(), NULL);
	Wave->runAction(seq1);

	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	del = false;
	nowFrame = 0;
}

void FishHead_Rain::m_update(float dt)
{
	m_time -= dt;
	m_delaytime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 2)//프레임 수
		{
			nowFrame = 0;
			
		}

		changeFrame = true;
	}
	if (changeFrame == true)
	{

		char str[256];
		sprintf(str, "enemy/fishhead/rain/rainboom%d.png", nowFrame);
		Eff->setTexture(str);

	}
	
}

void FishHead_Rain::m_sollision()
{
}

bool FishHead_Rain::m_sollisionCheck()
{
	return true;
}

Rect FishHead_Rain::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX(),
		Mother->getPositionY(),
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void FishHead_Rain::m_Dmg(int dmg)
{

}
void FishHead_Rain::removeself()
{
	p->eraseObject(this);
	del = true;
}

Vec2 FishHead_Rain::m_getPosition()
{
	return Mother->getPosition();
}