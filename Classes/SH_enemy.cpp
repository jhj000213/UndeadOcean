#include "stdafx.h"

void cBullet::initenemy(Node* base)
{
	auto cache = SpriteFrameCache::getInstance();

	srand(time(NULL));
	sprBullet = Sprite::createWithSpriteFrameName("bullet0.png");
	sprBullet->setPositionX(D_DESIGN_WIDTH+20);

	Vector<SpriteFrame*>aniFrames;

	char str[100] = { 0, };
	for (int i = 0; i < 5; i++)
	{
		sprintf(str, "bullet%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		aniFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(aniFrames, 0.2f);
	auto animate = Animate::create(animation);

	base->addChild(sprBullet);
	sprBullet->runAction(RepeatForever::create(animate));
}


//////////////////
void cBulletmanager::makeBullet(Node* base)
{
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("sh/bullet.plist");

	Base = base;
}

void cBulletmanager::schedule()
{
	cBullet* bullet = new cBullet;
	
	bullet->initenemy(Base);
	
	vBullet.push_back(bullet);

	auto shoot = MoveTo::create(3,Vec2(D_DESIGN_WIDTH+10 , bullet->sprBullet->getPositionY() ) );

	bullet->sprBullet->runAction(shoot);
}

//패턴

void cBulletmanager::trace(int number, Vec2 subpos)
{
	int posy_2;

	for (int i = 1; i <= number; i++)
	{
		srand(time(NULL));
		int posy = rand() % D_DESIGN_HEIGHT;

		cBullet* bullet = new cBullet;
		bullet->initenemy(Base);
		vBullet.push_back(bullet);
		bullet->sprBullet->setPositionY(posy);

		if (subpos.y < posy)
		{
			posy_2 = subpos.y - (((posy - subpos.y)*2));
		}
		else
		{
			posy_2 = subpos.y + (((subpos.y - posy)*2));
		}

		bullet->sprBullet->runAction(Sequence::create(DelayTime::create(i*0.05),
			MoveTo::create(1.3, Vec2(-10, posy_2)), NULL));
	}
}

void cBulletmanager::columnDown(int height, int number) //5번 패턴
{
	for (int i = 1; i <= height; i++)
	{
		for (int j = 0; j < number; j++)
		{
			cBullet* bullet = new cBullet;
			bullet->initenemy(Base);
			vBullet.push_back(bullet);
			bullet->sprBullet->setPositionY(i * D_DESIGN_HEIGHT/height);
			bullet->sprBullet->runAction(Sequence::create(DelayTime::create(i*0.2),DelayTime::create(j*0.05), 
				MoveTo::create(1.3, Vec2(-10, bullet->sprBullet->getPositionY())), NULL));
		}
	}
}

void cBulletmanager::columnUp(int height, int number) //5번 패턴
{
	int tim = 1;
	for (int i = height; i >= 1; i--)
	{
		for (int j = 0; j < number; j++)
		{
			cBullet* bullet = new cBullet;
			bullet->initenemy(Base);
			vBullet.push_back(bullet);
			bullet->sprBullet->setPositionY(i * D_DESIGN_HEIGHT / height);
			bullet->sprBullet->runAction(Sequence::create(DelayTime::create(tim*0.2), DelayTime::create(j*0.05),
				MoveTo::create(1.3, Vec2(-10, bullet->sprBullet->getPositionY())), NULL));
		}
		tim++;
	}
}


void cBulletmanager::spray(int height, int number)
{
	int tim = 1;
	bool half = false;
	int posy = D_DESIGN_HEIGHT / 2 + (height / 2 * 20);

	for (int i = height; i >= 1; i--)
	{
		for (int j = 0; j < number; j++)
		{
			float dy = (i * D_DESIGN_HEIGHT / height) - (D_DESIGN_HEIGHT / 2);
			float rad = atan2(dy, 0);
			float angle = -((rad * 180) / M_PI);

			cBullet* bullet = new cBullet;
			bullet->initenemy(Base);
			vBullet.push_back(bullet);
			bullet->sprBullet->setRotation(angle);
			bullet->sprBullet->setPositionY(posy);

			if (i <= height/2)
			{
				bullet->sprBullet->runAction(Sequence::create(DelayTime::create(tim*0.2), DelayTime::create(j*0.05),
					MoveTo::create(1.3, Vec2(-10, i * D_DESIGN_HEIGHT / height)), NULL));
			}
			else
			{
				
				bullet->sprBullet->runAction(Sequence::create(DelayTime::create(i*0.2), DelayTime::create(j*0.05),
					MoveTo::create(1.3, Vec2(-10, i * D_DESIGN_HEIGHT / height)), NULL));

				half = true;
			}
		}
		posy -= 20;
		if (half) tim++;
	}
}

void cBulletmanager::randomBullet(Vec2 subpos)
{
	srand(time(NULL));

	int random = rand() % 5;

	int height = rand() % 14+1;
	int number = rand() % 2 + 1;

	switch (random)
	{
	case 0:
		columnDown(10, number);//5번
		break;

	case 1:
		columnUp(10, number);//6번
		break;

	case 2:
		trace(number, subpos);//1번
		break;

	case 3:
		//x자 삭제
		//crossUp(height, number);
		//crossDown(height, number);
		break;

	case 4:
		spray(7, number);//2번
		break;
	}
}

bool cBulletmanager::checkCollision(Rect boundingBox)
{
	for (int i = 0; i < vBullet.size(); i++)
	{
		auto bullet = vBullet.at(i);

		//Rect bulletBoundingBox = bullet->sprBullet->getBoundingBox();
		if (boundingBox.containsPoint(bullet->sprBullet->getPosition()))
		{
			auto bullet = vBullet.at(i);
			remove(bullet);
			vBullet.erase(vBullet.begin() + i);

			return true;
		}
	}
	return false;
}

void cBulletmanager::passBullet()
{
	for (int i = 0; i < vBullet.size(); i++)
	{
		auto bullet = vBullet.at(i);
		if (bullet->sprBullet->getPositionX() < 0)
		{
			auto bullet = vBullet.at(i);
			remove(bullet);
			vBullet.erase(vBullet.begin() + i);
		}
	}
}

void cBulletmanager::remove(cBullet* bullet)
{
	Base->removeChild(bullet->sprBullet, true);
	delete bullet;
}
