#include "stdafx.h"


void cBarricadeType1::initBarricade(Node* base)
{
	auto move = MoveBy::create(3, Vec2(D_DESIGN_WIDTH + 100, 0));
	auto move2 = MoveBy::create(3, Vec2(D_DESIGN_WIDTH + 100, 0));

	int random = rand() % 3 + 1;
	char stalactite[100];

	switch (random)
	{
	case 3:
		
		sprintf(stalactite, "sh/stage3peturn/peturn%d.png", random);

		sprBarricadeUp = Sprite::create(stalactite);
		sprBarricadeUp->setAnchorPoint(Vec2(0.5, 1));
		sprBarricadeUp->setPositionY(D_DESIGN_HEIGHT+10);

		//sprBarricadeDown = NULL;

		base->addChild(sprBarricadeUp, 9999);

		sprBarricadeUp->runAction(move);

		state = 1;

		break;

	case 4:

		sprintf(stalactite, "sh/stage3peturn/peturn%d.png", random);

		sprBarricadeDown = Sprite::create(stalactite);
		sprBarricadeDown->setAnchorPoint(Vec2(0.5, 0));
		sprBarricadeDown->setPositionY(-20);

		base->addChild(sprBarricadeDown, 9999);

		sprBarricadeDown->runAction(move);

		state = 2;

		break;

	default:

		char stalactite_up[100];
		char stalactite_down[100];
		sprintf(stalactite_up, "sh/stage3peturn/peturn%d.png", random);
		sprintf(stalactite_down, "sh/stage3peturn/peturn%d_1.png", random);

		sprBarricadeUp = Sprite::create(stalactite_up);
		sprBarricadeUp->setAnchorPoint(Vec2(0.5, 1));
		sprBarricadeUp->setPositionY(D_DESIGN_HEIGHT+20);

		sprBarricadeDown = Sprite::create(stalactite_down);
		sprBarricadeDown->setAnchorPoint(Vec2(0.5, 0));
		sprBarricadeDown->setPositionY(-20);

		base->addChild(sprBarricadeUp, 9999);
		base->addChild(sprBarricadeDown, 9999);

		sprBarricadeUp->runAction(move);
		sprBarricadeDown->runAction(move2);

		state = 3;
	}

	

}

bool cBarricadeType1::checkCollision(Rect boundingBox)
{
	if (state != 2)
	{
		Rect BarricadeBoundingBox1 = sprBarricadeUp->getBoundingBox();
		if (boundingBox.intersectsRect(BarricadeBoundingBox1))
		{
			return true;
		}
	}
	if (state != 1)
	{
		Rect BarricadeBoundingBox2 = sprBarricadeDown->getBoundingBox();
		if (boundingBox.intersectsRect(BarricadeBoundingBox2))
		{
			return true;
		}
	}

	return false;
}

bool cBarricadeType1::passBarricade()
{
	if (state!=2 && sprBarricadeUp->getPositionX() > D_DESIGN_WIDTH)
	{
		return true;
	}
	else if (state == 2 && sprBarricadeDown->getPositionX() > D_DESIGN_WIDTH)
	{
		return true;
	}

	return false;
}

void cBarricadeType1::remove(Node* base)
{
	base->removeChild(sprBarricadeDown, true);
	base->removeChild(sprBarricadeUp, true);
}

void cBarricadeType2::initBarricade(Node* base)
{
	srand(time(NULL));

	int random = rand() % D_DESIGN_HEIGHT;
	int size = (rand() % 1) + 1;

	auto move = MoveBy::create(3, Vec2(D_DESIGN_WIDTH + 100, 0));
	auto rotate = RepeatForever::create(RotateBy::create(1, 30));

	sprBarricade = Sprite::create("sh/rock.png");
	sprBarricade->setPositionY(random);
	sprBarricade->setScale(size);

	base->addChild(sprBarricade, 9999);

	sprBarricade->runAction(move);
	sprBarricade->runAction(rotate);
}

bool cBarricadeType2::checkCollision(Rect boundingBox)
{
	Rect BarricadeBoundingBox = sprBarricade->getBoundingBox();

	if (boundingBox.intersectsRect(BarricadeBoundingBox))
	{
		return true;
	}

	return false;
}

bool cBarricadeType2::passBarricade()
{
	if (sprBarricade->getPositionX() > D_DESIGN_WIDTH)
	{
		return true;
	}
	return false;
}

void cBarricadeType2::remove(Node* base)
{
	base->removeChild(sprBarricade, true);
}

void cBarricadeManager::makeBarricade(Node* base)
{
	Base = base;
}

void cBarricadeManager::randomSpawn()
{
	srand(time(NULL));

	int random = rand() % 2;

	if (random)
	{
		auto barc = new cBarricadeType1;

		barc->initBarricade(Base);

		barricade1.push_back(barc);
	}
	else
	{
		auto barc = new cBarricadeType2;

		barc->initBarricade(Base);

		barricade2.push_back(barc);
	}
}

bool cBarricadeManager::checkCollision(Rect boundingBox)
{

	for (int i = 0; i < barricade1.size(); i++)
	{
		auto barc = barricade1.at(i);
		if (barc->passBarricade())
		{
			barc->remove(Base);
			delete barc;

			barricade1.erase(barricade1.begin() + i);
		}
	}

	for (int i = 0; i < barricade2.size(); i++)
	{
		auto barc = barricade2.at(i);
		if (barc->passBarricade())
		{
			barc->remove(Base);
			delete barc;

			barricade2.erase(barricade2.begin() + i);
		}
	}

	for (auto barc : barricade1)
	{
		if (barc->checkCollision(boundingBox))
		{
			return true;
		}
	}

	for (auto barc : barricade2)
	{
		if (barc->checkCollision(boundingBox))
		{
			return true;
		}
	}

	return false;
}