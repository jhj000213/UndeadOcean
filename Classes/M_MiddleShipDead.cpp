#include "stdafx.h"

#define MAX_TIME 0.15f
void M_MiddleShipDead::m_init(Vec2 Pos, Layer * layer)
{
	Mother = Sprite::create("enemy/aghi/agi_hitpoint.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	

	Aghi = Sprite::create("enemy/middleship/dead/dragondead0.png");
	Aghi->setPosition(Vec2(0, 0));
	Mother->addChild(Aghi);


	Dead = false;
	m_time = MAX_TIME;
	changeFrame = false;
	nowFrame = 0;
}

void M_MiddleShipDead::m_update(float dt)
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
				nowFrame = 0;
				//Aghi->setOpacity(0);
				Dead = true;
			}

			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;

			char str[256];
			sprintf(str, "enemy/middleship/dead/dragondead%d.png", nowFrame);
			Aghi->setTexture(str);

		}
	}
	
}