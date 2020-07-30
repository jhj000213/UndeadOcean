#include "stdafx.h"

void cSubmarine::init(Node* base)
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("sh/submarin_normal.plist");

	Base = base;
	pointX = D_DESIGN_WIDTH/2;
	pointY = 300;

	sprSubmarine = Sprite::createWithSpriteFrameName("0.png");

	Vector<SpriteFrame*>aniFrames;

	char str[100] = { 0, };
	for (int i = 0; i < 3; i++)
	{
		sprintf(str, "%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		aniFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(aniFrames, 0.05f);
	auto animate = Animate::create(animation);

	sprSubmarine->setPosition(Vec2(pointX, pointY));
	base->addChild(sprSubmarine);
	sprSubmarine->runAction(RepeatForever::create(animate));
	sprSubmarine->setFlippedX(true);

	SubmarinePoint = Sprite::create("sh/submarin_point.png");
	SubmarinePoint->setPosition(Vec2(pointX, pointY));
	SubmarinePoint->setOpacity(0);
	base->addChild(SubmarinePoint);

	isMove = false;
}

bool cSubmarine::touchBegan(Vec2 tp, int index)
{
	touchIndex = index;

	if (tp.x<D_DESIGN_WIDTH/2 )
	{
		isMove = true;
		return true;
	}
	return false;

}

void cSubmarine::touchMove(Vec2 tp, int index)
{
	if (isMove && touchIndex == index)
	{
		pointY = tp.y;
		move();
	}
}

void cSubmarine::touchEnd(Vec2 tp, int index)
{
	if (isMove && touchIndex == index)
	{
		pointY = tp.y;
		move();
	}
	isMove = false;

	
}


void cSubmarine::move()
{
	float subY = sprSubmarine->getPositionY();

	if (pointY > D_DESIGN_HEIGHT) pointY = D_DESIGN_HEIGHT;
	if (pointY < 0)pointY = 0;

	if (pointY - 5 < subY && subY< pointY + 5)
	{
		return;
	}
	if (pointY > subY)
	{
		sprSubmarine->setPositionY(subY+5);
	}
	if(pointY < subY)
	{
		sprSubmarine->setPositionY(subY-5);
	}
	SubmarinePoint->setPosition( sprSubmarine->getPosition());
	
}

void cSubmarine::damage()
{	
	sprSubmarine->runAction(Sequence::create(FadeTo::create(0.2f, 0), FadeTo::create(0.2f, 255), NULL));
}

