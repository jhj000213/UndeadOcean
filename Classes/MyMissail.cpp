#include "stdafx.h"

void MyMissail::m_init(Vec2 Pos, Layer * layer,int info)
{

	Missail = Sprite::create("submarin/airgun/airgun.png");
	Missail->setAnchorPoint(Vec2(0, 0.5));
	Missail->setScale(0.65);
	Missail->setPosition(Pos);
	m_layer = layer;
	m_layer->addChild(Missail);

	
	if (info == 1)
	{
		auto ac1 = MoveBy::create(1.0f, Vec2(1480, 0));
		auto ac2 = Sequence::create(ac1, NULL);
		Missail->runAction(ac2);
	}
	else if (info == 2)
	{
		Missail->setRotation(-15);
		auto ac1 = MoveBy::create(1.2f, Vec2(1480, 300));
		auto ac2 = Sequence::create(ac1, NULL);
		Missail->runAction(ac2);
	}
	else if (info == 3)
	{
		Missail->setRotation(15);
		auto ac1 = MoveBy::create(1.0f, Vec2(1480, -300));
		auto ac2 = Sequence::create(ac1, NULL);
		Missail->runAction(ac2);
	}
}

float MyMissail::m_getPositionX()
{

	return Missail->getPositionX();
}

void MyMissail::m_setPosition(Vec2 Pos)
{
	Missail->setPosition(Pos);
}

Rect MyMissail::m_getRect()
{
	Rect mrect = Rect(
		Missail->getPositionX() - Missail->boundingBox().size.width / 2,
		Missail->getPositionY() - Missail->boundingBox().size.height / 2,
		Missail->boundingBox().size.width,
		Missail->boundingBox().size.height);
	return mrect;
}

void MyMissail::m_boomEffect()
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