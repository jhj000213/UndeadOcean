#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f
#define FEVER_TIME 3.0f
#define SHOT_DELAY_TIME 1.0f
void MiddleShip_Boom::m_init(Vec2 Pos, Layer * layer,Vector<MonsterMissail*> *vec)
{

	Mother = Sprite::create("enemy/middleship/boom/bhitpoint.png");
	Mother->setAnchorPoint(Vec2(0, 0.5));
	Mother->setScale(0.5);
	Mother->setOpacity(0);
	Mother->setPosition(Vec2(Pos.x, Pos.y + 50));
	//m_layer = layer;
	this->addChild(Mother);
	M_HP = 280;

	S_Boom = Sprite::create("enemy/middleship/boom/b0.png");
	S_Boom->setPosition(Vec2(90,100));
	Mother->addChild(S_Boom);
/*
	m_HPbar = MonsterHP::m_create(Vec2(-40, 190), Mother, 280);
	Mother->addChild(m_HPbar);*/

	
	auto ac1 = MoveBy::create(1.0f, Vec2(-500, 0));
	//auto ac2 = Sequence::create(ac1, RemoveSelf::create(), NULL);
	Mother->runAction(EaseOut::create(ac1,3.0f));
	MonLayer = layer;
	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_fevertime = FEVER_TIME;
	m_shotdelaytime = SHOT_DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	Shoot = false;
	ang = false;
	nowFrame = 0;
}


void MiddleShip_Boom::m_update(float dt)
{
	//m_HPbar->hp_update(M_HP);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	m_shotdelaytime -= dt;
	if (m_hit == true && m_delaytime <= 0.0f)
	{
		m_delaytime = DELAY_TIME;
		m_hit = false;

		char str[256];
		sprintf(str, "enemy/middleship/boom/b6.png", nowFrame);
		//Aghi->setTexture(str);

		Sprite * h = Sprite::create(str);
		h->setPosition(S_Boom->getPosition());
		Mother->addChild(h);
		auto ac = FadeOut::create(0.3f);
		auto seq = Sequence::create(ac, RemoveSelf::create(), NULL);
		h->runAction(seq);

		/*auto mo1 = MoveBy::create(0.05f, Vec2(4, 0));
		auto mo2 = MoveBy::create(0.05f, Vec2(-8, 0));
		auto mo3 = MoveBy::create(0.05f, Vec2(8, 0));
		auto mo4 = MoveBy::create(0.05f, Vec2(-4, 0));
		auto moseq = Sequence::create(mo1, mo2, mo3, mo4, NULL);
		Mother->runAction(moseq);*/
	}
	if (Shoot == false)
	{
		m_fevertime -= dt;
		if (m_fevertime <= 0.0f)
		{
			Shoot = true;
		}
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
			

			{
				char str[256];
				sprintf(str, "enemy/middleship/boom/b%d.png", nowFrame);
				S_Boom->setTexture(str);
			}
		}
	}
	if (Shoot == true)
	{
		S_Boom->setTexture("enemy/middleship/boom/b4.png");
		if (m_shotdelaytime <= 0.0f)
		{
			m_shoot(dt);
			m_shotdelaytime = SHOT_DELAY_TIME;
		}
		
	
	}
	
}


float MiddleShip_Boom::m_getPositionX()
{

	return Mother->getPositionX();
}

void MiddleShip_Boom::m_setPosition(Vec2 Pos)
{
	Mother->setPosition(Pos);
}

Rect MiddleShip_Boom::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void MiddleShip_Boom::m_boomEffect()
{
	int x = rand() % 20;
	int y = rand() % 10;

	Sprite * n_boom = Sprite::create();
	n_boom->setScale(0.4);
	n_boom->setPosition(Vec2(Mother->getPosition().x + x, Mother->getPosition().y + y));
	this->addChild(n_boom);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 6; i++)
	{
		sprintf(str1, "airgun_boom_%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);
	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);

	n_boom->runAction(seq);
}

Vec2 MiddleShip_Boom::m_getPosition()
{
	return Mother->getPosition();
}

void MiddleShip_Boom::m_shoot(float dt)
{
	for (int i = 0; i < 8; i++)
	{
		MonsterMissail * Missail = MonsterMissail::m_create(Vec2(Mother->getPosition().x+50, Mother->getPosition().y), this, Vec2(0, 0), 2, i);
		MonLayer->addChild(Missail);
		p->pushBack(Missail);
	}
}

void MiddleShip_Boom::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void MiddleShip_Boom::m_sollision()
{
	m_hit = true;
}