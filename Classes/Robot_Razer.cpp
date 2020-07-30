#include "stdafx.h"

#define MAX_TIME 0.13f
#define DELAY_TIME 0.45f
void Robot_Razer::m_init(Vec2 Pos, Layer * layer, Vector<MonsterRazer*> *vec, Vector<Robot_Razer*> *hvec, bool top)
{
	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	Mother->setScale(0.6);
	this->addChild(Mother);
	MonLayer = layer;


	MiniOb = Sprite::create();
	MiniOb->setPosition(Vec2(85, 50));
	Mother->addChild(MiniOb);

	//=
	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 0; i < 3; i++)
	{
		sprintf(str1, "midraizer%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, NULL);


	MiniOb->runAction(CCRepeatForever::create(seq));
	//
	HeadPos = Mother->getPosition();


	TopFrame = top;
	mp = hvec;
	p = vec;
	shootting = false;

}

void Robot_Razer::m_update(float dt,bool shoot)
{
	shootting = shoot;
	if (shootting ==true)
	{
		m_Shoot();
		shootting = false;
	}
	
	HeadPos = Vec2(Mother->getPositionX() , Mother->getPositionY()-15);
	//log("%f %f", HeadPos.x, HeadPos.y);
	if (p->empty() == false)
	{
		for (MonsterRazer * MR : *p)
		{
			if (MR->m_getRazerInfo() == 3 && MR->top == TopFrame)
			{
				MR->m_setPosition(HeadPos);
			}
		}
	}
}

void Robot_Razer::m_sollision()
{

}

bool Robot_Razer::m_sollisionCheck()
{

	return true;
}

Rect Robot_Razer::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void Robot_Razer::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void Robot_Razer::m_Shoot()
{

	Sprite * shot = Sprite::create();
	shot->setPosition(Vec2(MiniOb->getPosition()));
	Mother->addChild(shot,100);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 3; i < 6; i++)
	{
		sprintf(str1, "midraizer%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);


	Vector<SpriteFrame *>aniFrames11;
	char str11[256];
	for (int i = 0; i < 3; i++)
	{
		sprintf(str11, "midraizer%d.png", i);

		SpriteFrame * frame11 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str11);
		aniFrames11.pushBack(frame11);
	}
	Animation * ani1 = Animation::createWithSpriteFrames(aniFrames11, 0.1f, 1);

	Animate * animate1 = Animate::create(ani1);

	auto ac = CallFunc::create(CC_CALLBACK_0(Robot_Razer::m_setOpacity_shoot, this));
	auto ac1 = CallFunc::create(CC_CALLBACK_0(Robot_Razer::m_setOpacity_normal, this));
	auto seq = Sequence::create(ac, animate, DelayTime::create(3.5f), ac1, RemoveSelf::create(), NULL);
	auto seq1 = Sequence::create(ac, animate1, DelayTime::create(4.0f), ac1, NULL);

	if (TopFrame == true)
	{
		auto mov = MoveBy::create(1.0f, Vec2(70, 0));
		auto move1 = MoveBy::create(1.0f, Vec2(0, 250));

		auto call = CallFunc::create(CC_CALLBACK_0(Robot_Razer::m_razersound, this));

		auto down = MoveBy::create(0.5f, Vec2(0, -150));
		auto up = MoveBy::create(0.5f, Vec2(0, 150));

		auto mov1 = MoveBy::create(1.0f, Vec2(-70, 0));
		auto move2 = MoveBy::create(1.0f, Vec2(0, -250));


		auto updownseq = Sequence::create(down, up, NULL);
		auto se = Sequence::create(DelayTime::create(1.0f), call, updownseq, mov1, move2, NULL);
		auto sequ = Spawn::create(EaseIn::create(mov, 8.0), EaseIn::create(move1, 3.0),  se, seq, NULL);
		auto seqq = Spawn::create(EaseIn::create(mov, 8.0), EaseIn::create(move1, 3.0),       se, seq1, NULL);
		shot->runAction(sequ);
		Mother->runAction(seqq);
	}
	else
	{
		auto mov = MoveBy::create(1.0f, Vec2(70, 0));
		auto move1 = MoveBy::create(1.0f, Vec2(0, -250));

		auto down = MoveBy::create(0.5f, Vec2(0, -150));
		auto up = MoveBy::create(0.5f, Vec2(0, 150));

		auto mov1 = MoveBy::create(1.0f, Vec2(-70, 0));
		auto move2 = MoveBy::create(1.0f, Vec2(0, 250));

		auto updownseq = Sequence::create(up, down, NULL);
		auto se = Sequence::create(DelayTime::create(1.0f),updownseq, mov1, move2, NULL);
		auto sequ = Spawn::create(EaseIn::create(mov, 8.0), EaseIn::create(move1, 3.0),se, seq, NULL);
		auto seqq = Spawn::create(EaseIn::create(mov, 8.0), EaseIn::create(move1, 3.0), se, seq1, NULL);
		shot->runAction(sequ);
		Mother->runAction(seqq);
	}



	MonsterRazer * Missail = MonsterRazer::m_create(HeadPos, 3,TopFrame);
	this->addChild(Missail);
	p->pushBack(Missail);

	auto seq3 = Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL);
	Missail->runAction(seq3);
}

void Robot_Razer::removeself()
{
	mp->eraseObject(this);
}

Vec2 Robot_Razer::m_getPosition()
{
	return Mother->getPosition();
}

void Robot_Razer::m_setOpacity_normal()
{
	MiniOb->setOpacity(255);
}

void Robot_Razer::m_setOpacity_shoot()
{
	MiniOb->setOpacity(0);
}

void Robot_Razer::m_razersound()
{
	AudioEngine::play2d("sound/effect/bigrobot_razer.mp3", false, Volume);
}