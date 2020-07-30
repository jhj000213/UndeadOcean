#include "stdafx.h"

#define MAX_TIME 0.15f
void ShildBreak::m_init(Vec2 Pos, Layer * layer)
{
	Mother = Sprite::create();
	Mother->setScale(0.8f);
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);



	Spr = Sprite::create("enemy/crab/shildbreak/shieldbreak0.png");
	Spr->setPosition(Vec2(0, 0));
	Mother->addChild(Spr);


	Dead = false;
	m_time = MAX_TIME;
	changeFrame = false;
	nowFrame = 0;
}

void ShildBreak::m_update(float dt)
{
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	if (Dead == false)
	{
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 12)//프레임 수
			{
				nowFrame = 11;
				Spr->setOpacity(0);
				Dead = true;
			}

			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;

			char str[256];
			sprintf(str, "enemy/crab/shildbreak/shieldbreak%d.png", nowFrame);
			Spr->setTexture(str);

		}
	}

}