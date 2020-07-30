#include "stdafx.h"

void MyTorpedo::m_init(Vec2 Pos, Layer * layer, Vector<MyTorpedo*> *tp, Vector<TorpedoBoom*> *bp,int info)
{
	if (info == 1)
	{
		Missail = Sprite::create("submarin/missail_black.png");
		Missail->setAnchorPoint(Vec2(0.5, 0.5));
		Missail->setScale(1.4);
		Missail->setPosition(Pos);
		layer->addChild(Missail);
		ILayer = layer;
	}
	else if (info == 4)
	{
		Missail = Sprite::create("submarin/missail_2.png");
		Missail->setAnchorPoint(Vec2(0.5, 0.5));
		Missail->setScale(1.4);
		Missail->setPosition(Pos);
		layer->addChild(Missail);
		ILayer = layer;
	}
	



	auto ac1 = MoveBy::create(0.5f, Vec2(-75, -125));
	auto esac = EaseOut::create(ac1, 3.0);
	auto ac2 = MoveBy::create(0.7, Vec2(D_DESIGN_WIDTH / 2, 20));
	auto esac2 = EaseIn::create(ac2, 2.0);
	auto ac3 = CallFunc::create(CC_CALLBACK_0(MyTorpedo::m_createBoom,this));
	auto ac4 = CallFunc::create(CC_CALLBACK_0(MyTorpedo::removeself, this));
	auto seq = Sequence::create(esac, esac2, ac3, ac4, RemoveSelf::create(), NULL);
	Missail->runAction(seq);

	wasboom = false;
	p = bp;
	mp = tp;
}

float MyTorpedo::m_getPositionX()
{
	return Missail->getPositionX();
}

void MyTorpedo::m_createBoom()
{
	if (wasboom == false)
	{
		m_boomEffect();
		wasboom = true;
	}
}

bool MyTorpedo::m_torSollisionCheck()
{
	return true;
}

Rect MyTorpedo::m_getRect()
{
	Rect mrect = Rect(
		Missail->getPositionX() - Missail->boundingBox().size.width / 2,
		Missail->getPositionY() - Missail->boundingBox().size.height / 2,
		Missail->boundingBox().size.width,
		Missail->boundingBox().size.height);
	return mrect;
}

void MyTorpedo::m_setPosition(Vec2 Pos)
{
	Missail->setPosition(Pos);
}

void MyTorpedo::m_boomEffect()
{
	TorpedoBoom * Boom = TorpedoBoom::m_create(Missail->getPosition(), p);
	ILayer->addChild(Boom,1100);
	p->pushBack(Boom);

	auto seq = Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), NULL);
	Boom->runAction(seq);
}

void MyTorpedo::removeself()
{
	mp->eraseObject(this);
}