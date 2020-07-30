#include "stdafx.h"

#define MAX_TIME 0.15f
void Crab_Dead::m_init(Vec2 Pos, Layer * layer)
{
	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(1, 0));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	layer->addChild(Mother);



	Spr = Sprite::create("enemy/crab/dead/dead0.png");
	Spr->setAnchorPoint(Vec2(1, 0));
	Spr->setPosition(Vec2(200, -250));
	Mother->addChild(Spr);


	auto ac1 = MoveBy::create(1.0f, Vec2(0, -150));
	Mother->runAction(EaseIn::create(ac1, 2.0));


	Dead = false;
	m_time = MAX_TIME;
	changeFrame = false;
	nowFrame = 0;
}

void Crab_Dead::m_update(float dt)
{
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	if (Dead == false)
	{
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 13)//프레임 수
			{
				nowFrame = 12;
				//Aghi->setOpacity(0);
				Dead = true;
			}

			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;

			char str[256];
			sprintf(str, "enemy/crab/dead/dead%d.png", nowFrame);
			Spr->setTexture(str);

		}
	}

}