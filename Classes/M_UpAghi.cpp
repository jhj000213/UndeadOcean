#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void M_UpAghi::m_init(Vec2 Pos, Layer * layer,Vector<M_UpAghi*> *hvec)
{
	M_HP = 30;
	Mother = Sprite::create("enemy/upaghi/agihit.png");
	Mother->setRotation(90);
	Mother->setScale(0.7);
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	Danger = Sprite::create("enemy/upaghi/danger.png");
	Danger->setAnchorPoint(Vec2(0.5, 0));
	Danger->setPosition(Vec2(Pos.x, 0));
	layer->addChild(Danger);

	//m_HPbar = MonsterHP::m_create(Vec2(-10, 100), Mother, 30);
	//Mother->addChild(m_HPbar);

	Aghi = Sprite::create("enemy/upaghi/agi0.png");
	Aghi->setPosition(Vec2(150, 45));
	Mother->addChild(Aghi);


	auto ac = MoveBy::create(0.7f, Vec2(0, 1100));
	auto ac1 = CallFunc::create(CC_CALLBACK_0(M_UpAghi::MakeEffect, this));
	auto ac2 = CallFunc::create(CC_CALLBACK_0(M_UpAghi::removeself,this));
	auto sp = Spawn::create(ac, ac1, NULL);
	auto seq = Sequence::create(DelayTime::create(2.0f), sp,ac2, RemoveSelf::create(),NULL);
	Mother->runAction(seq);

	auto al = FadeIn::create(0.25f);
	auto al2 = FadeOut::create(0.25f);
	auto seq3 = Sequence::create(al, al2, DelayTime::create(1.0f), al, al2,RemoveSelf::create(), NULL);
	Danger->runAction(seq3);

	EPos = Pos;
	MomL = layer;
	p = hvec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
}

void M_UpAghi::m_update(float dt)
{
	//m_HPbar->hp_update(M_HP);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 4)//프레임 수
			nowFrame = 0;
		changeFrame = true;
	}
	if (changeFrame == true)
	{
		changeFrame = false;
		if (m_hit == true && m_delaytime <= 0.0f)
		{
			m_delaytime = DELAY_TIME;
			m_hit = false;

			char str[256];
			sprintf(str, "enemy/upaghi/agiwhite%d.png", nowFrame);
			//Aghi->setTexture(str);

			Sprite * h = Sprite::create(str);
			h->setPosition(Aghi->getPosition());
			Mother->addChild(h);
			auto ac = FadeOut::create(0.3f);
			auto seq = Sequence::create(ac, RemoveSelf::create(), NULL);
			h->runAction(seq);

			auto mo1 = MoveBy::create(0.05f, Vec2(4, 0));
			auto mo2 = MoveBy::create(0.05f, Vec2(-8, 0));
			auto mo3 = MoveBy::create(0.05f, Vec2(8, 0));
			auto mo4 = MoveBy::create(0.05f, Vec2(-4, 0));
			auto moseq = Sequence::create(mo1, mo2, mo3, mo4, NULL);
			Mother->runAction(moseq);
		}
		else
		{
			char str[256];
			sprintf(str, "enemy/upaghi/agi%d.png", nowFrame);
			Aghi->setTexture(str);
		}
	}
}

void M_UpAghi::m_sollision()
{
	m_hit = true;
}

bool M_UpAghi::m_sollisionCheck()
{

	return true;
}

Rect M_UpAghi::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_UpAghi::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void M_UpAghi::MakeEffect()
{
	Sprite * Effect = Sprite::create();

	Effect->setPosition(Vec2(EPos.x, EPos.y+300));

	MomL->addChild(Effect,500);
	
	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 6; i++)
	{
		sprintf(str1, "e%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.11f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	Effect->runAction(seq);
}

void M_UpAghi::removeself()
{
	p->eraseObject(this);
}

Vec2 M_UpAghi::m_getPosition()
{
	return Mother->getPosition();
}