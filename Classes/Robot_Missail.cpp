#include "stdafx.h"

#define MAX_TIME 0.1f
#define DELAY_TIME 0.45f;
void Robot_Missail::m_init(Layer * layer, Vector<Robot_Missail*> *vec)
{
	AudioEngine::play2d("sound/effect/bigrobot_missail.mp3", false, Volume);

	Mother = Sprite::create("enemy/bigrobot/missail/missailhit.png");
	Mother->setAnchorPoint(Vec2(0, 0));
	Mother->setOpacity(0);
	Mother->setPosition(0,1280);
	layer->addChild(Mother,100);

	Wave = Sprite::create("enemy/bigrobot/missail/missail0.png");
	Wave->setAnchorPoint(Vec2(0, 0));
	Wave->setPosition(Vec2(0,0));
	layer->addChild(Wave,100);

	auto ac = MoveBy::create(0.5f, Vec2(0,-1280));
	auto seq = Sequence::create(DelayTime::create(0.7f), ac, NULL);
	Mother->runAction(seq);

	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	del = false;
	nowFrame = 0;
}

void Robot_Missail::m_update(float dt)
{
	m_time -= dt;
	m_delaytime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 21)//프레임 수
		{
			nowFrame = 0;
			Wave->setOpacity(0);
			removeself();
		}

		if (nowFrame == 15)
		{
			AudioEngine::play2d("sound/effect/middleship_boom.mp3");
		}
			
		changeFrame = true;
	}
	if (changeFrame == true)
	{

		char str[256];
		sprintf(str, "enemy/bigrobot/missail/missail%d.png", nowFrame);
		Wave->setTexture(str);

	}
}

void Robot_Missail::m_sollision()
{
}

bool Robot_Missail::m_sollisionCheck()
{
	return true;
}

Rect Robot_Missail::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX(),
		Mother->getPositionY(),
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void Robot_Missail::m_Dmg(int dmg)
{
	M_HP -= dmg;
}
void Robot_Missail::removeself()
{
	p->eraseObject(this);
	del = true;
}

Vec2 Robot_Missail::m_getPosition()
{
	return Mother->getPosition();
}