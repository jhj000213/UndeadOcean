#include "stdafx.h"

#define MAX_TIME 0.15f
void FishHead_Dead::m_init(Vec2 Pos, Layer * layer)
{
	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(1, 0));
	Mother->setOpacity(0);
	Mother->setScale(0.7f);
	Mother->setPosition(Pos);
	this->addChild(Mother);



	Spr = Sprite::create("enemy/fishhead/dead/dead0.png");
	Spr->setAnchorPoint(Vec2(1, 0));
	Spr->setPosition(Vec2(0, 0));
	Mother->addChild(Spr);


	Dead = false;
	m_time = MAX_TIME;
	changeFrame = false;
	nowFrame = 0;
}

void FishHead_Dead::m_update(float dt)
{
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	if (Dead == false)
	{
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 9)//프레임 수
			{
				nowFrame = 8;
				auto ac = FadeOut::create(1.0f);
				Spr->runAction(ac);
				Dead = true;
			}

			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;

			char str[256];
			sprintf(str, "enemy/fishhead/dead/dead%d.png", nowFrame);
			Spr->setTexture(str);

		}
	}

}