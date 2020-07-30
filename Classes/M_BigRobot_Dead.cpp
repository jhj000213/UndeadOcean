#include "stdafx.h"

#define MAX_TIME 0.15f
void M_BigRobot_Dead::m_init(Vec2 Pos, Layer * layer)
{
	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);



	Spr = Sprite::create("enemy/bigrobot/dead/middead0.png");
	Spr->setPosition(Vec2(0, 0));
	Mother->addChild(Spr);

	GLayer = layer;
	Dead = false;
	m_time = MAX_TIME;
	changeFrame = false;
	nowFrame = 0;
}

void M_BigRobot_Dead::m_update(float dt)
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
			if (nowFrame == 9)
			{
				Sprite * White = Sprite::create("enemy/bigrobot/dead/white.png");
				White->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2)); 
				White->setOpacity(0);
				GLayer->addChild(White,9999);

				auto ac = FadeIn::create(0.4f);
				auto ac1 = FadeOut::create(0.3f);
				auto seq = Sequence::create(ac, ac1,RemoveSelf::create(), NULL);
				White->runAction(seq);
			}

			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;

			char str[256];
			sprintf(str, "enemy/bigrobot/dead/middead%d.png", nowFrame);
			Spr->setTexture(str);

		}
	}

}