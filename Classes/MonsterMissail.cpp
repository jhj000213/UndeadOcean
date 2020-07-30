#include "stdafx.h"

void MonsterMissail::m_init(Vec2 Pos, Node * layer,Vec2 SPos,int MissailInfo,int radiarr)
{
	float scale = 0.65;
	Missail = Sprite::create();
	//Missail->setAnchorPoint(Vec2(0, 0.5));
	Missail->setScale(scale);
	
	Missail->setPosition(Pos);
	//m_layer = layer;
	this->addChild(Missail,100);

	m_MissailInfo = MissailInfo;

	if (m_MissailInfo == 1)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 1; i < 5; i++)
		{
			sprintf(str1, "shoot%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.15f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Missail->runAction(CCRepeatForever::create(seq));
		MissailWidth = 35.0f*scale;
		/*auto ac1 = MoveTo::create(3.0f, SubPos);
		auto ac2 = Sequence::create(ac1,  NULL);
		Missail->runAction(ac2);*/

		radi = atan2((Missail->getPositionY() - SPos.y), (Missail->getPositionX() - SPos.x));
		dis = 350.0f;
		
	}
	else if (m_MissailInfo == 2)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 1; i < 5; i++)
		{
			sprintf(str1, "bullet%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.15f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Missail->runAction(CCRepeatForever::create(seq));
		MissailWidth = 20.0f*scale;
		/*auto ac1 = MoveTo::create(3.0f, SubPos);
		auto ac2 = Sequence::create(ac1,  NULL);
		Missail->runAction(ac2);*/

		
		double radia[8] = {
			atan2(0, 1),
			atan2(1, 1),
			atan2(1, 0),
			atan2(1, -1),
			atan2(0, -1),
			atan2(-1, -1),
			atan2(-1, 0),
			atan2(-1, 1), };
		radi = radia[radiarr];
		dis = 350.0f;

	}
	else if (m_MissailInfo == 3)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 1; i < 5; i++)
		{
			sprintf(str1, "bullet%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.15f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Missail->runAction(CCRepeatForever::create(seq));
		MissailWidth = 20.0f*scale;
		/*auto ac1 = MoveTo::create(3.0f, SubPos);
		auto ac2 = Sequence::create(ac1,  NULL);
		Missail->runAction(ac2);*/


		double radia[5] = {
			atan2(4, 9),//40
			atan2(2,9),//20
			atan2(0,1),//270
			atan2(-2, 9),//-20
			atan2(-4, 9) };//-40
		radi = radia[radiarr];
		dis = 650.0f;

	}
	else if (m_MissailInfo == 4)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 1; i < 5; i++)
		{
			sprintf(str1, "bullet%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.15f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Missail->runAction(CCRepeatForever::create(seq));
		MissailWidth = 20.0f*scale;
		/*auto ac1 = MoveTo::create(3.0f, SubPos);
		auto ac2 = Sequence::create(ac1,  NULL);
		Missail->runAction(ac2);*/

		radi = atan2((Missail->getPositionY() - SPos.y), (Missail->getPositionX() - SPos.x));
		dis = 400.0f;

	}
	else if (m_MissailInfo == 5)
	{
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 1; i < 5; i++)
		{
			sprintf(str1, "bullet%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.15f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Missail->runAction(CCRepeatForever::create(seq));
		MissailWidth = 20.0f*scale;
		/*auto ac1 = MoveTo::create(3.0f, SubPos);
		auto ac2 = Sequence::create(ac1,  NULL);
		Missail->runAction(ac2);*/


		double radia[4] = {
			atan2(3, 9),//40
			atan2(1, 9),//20
			atan2(-1, 9),//270
			atan2(-3, 9),//-20
		};
		radi = radia[radiarr];
		dis = 500.0f;
	}
	else if (m_MissailInfo == 6)
	{
		radi = atan2((Missail->getPositionY() - SPos.y), (Missail->getPositionX() - SPos.x));

		Missail->setTexture("enemy/crab/missail/dok.png");
		Missail->setRotation(radi*-180 / 3.14);

		MissailWidth = 32.5*scale;

		
		dis = 1500.0f;

	}

	// radia[0], radia[1];

	SpeedX = (cos(radi) * dis);
	SpeedY = (sin(radi) * dis);
}

void MonsterMissail::m_update(float dt)
{
	float X = SpeedX * dt;
	float Y = SpeedY * dt;
	if (m_MissailInfo == 1)
	{
		//float num = atan2(360, -1000);
		Vec2 NPos = Missail->getPosition();
		Missail->setPosition(Vec2(NPos.x -= X, NPos.y -= Y));
	}
	else if (m_MissailInfo == 2)
	{
		Vec2 NPos = Missail->getPosition();
		Missail->setPosition(Vec2(NPos.x -= X, NPos.y -= Y));
	}
	else if (m_MissailInfo == 3)
	{
		Vec2 NPos = Missail->getPosition();
		Missail->setPosition(Vec2(NPos.x -= X, NPos.y -= Y));
	}
	else if (m_MissailInfo == 4)
	{
		//float num = atan2(360, -1000);
		Vec2 NPos = Missail->getPosition();
		Missail->setPosition(Vec2(NPos.x -= X, NPos.y -= Y));
	}
	else if (m_MissailInfo == 5)
	{
		Vec2 NPos = Missail->getPosition();
		Missail->setPosition(Vec2(NPos.x -= X, NPos.y -= Y));
	}
	else if (m_MissailInfo == 6)
	{
		Vec2 NPos = Missail->getPosition();
		Missail->setPosition(Vec2(NPos.x -= X, NPos.y -= Y));
	}
}

float MonsterMissail::m_getPositionX()
{

	return Missail->getPositionX();
}

void MonsterMissail::m_setPosition(Vec2 Pos)
{
	Missail->setPosition(Pos);
}

Rect MonsterMissail::m_getRect()
{
	Rect mrect = Rect(
		Missail->getPositionX() - Missail->boundingBox().size.width / 2,
		Missail->getPositionY() - Missail->boundingBox().size.height / 2,
		Missail->boundingBox().size.width,
		Missail->boundingBox().size.height);
	return mrect;
}

void MonsterMissail::m_boomEffect()
{
	int x = rand() % 20;
	int y = rand() % 10;

	Sprite * n_boom = Sprite::create();
	n_boom->setScale(0.4);
	n_boom->setPosition(Vec2(Missail->getPosition().x + x, Missail->getPosition().y + y));
	m_layer->addChild(n_boom);

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

Vec2 MonsterMissail::m_getPosition()
{
	return Missail->getPosition();
}