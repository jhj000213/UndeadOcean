#include "stdafx.h"

void MonsterHP::hp_init(Vec2 Pos, Node * mother,int maxhp)
{
	MaxHP = maxhp;

	HPBox = Sprite::create("enemy/hp_box.png");
	HPBox->setAnchorPoint(Vec2(0, 0));
	HPBox->setPosition(Pos);
	mother->addChild(HPBox,500);

	HPLine = Sprite::create("enemy/hp_bar.png");
	HPLine->setAnchorPoint(Vec2(0, 0));
	HPLine->setPosition(Pos.x + 20, Pos.y + 15);
	mother->addChild(HPLine,501);
}

void MonsterHP::hp_update(float nowHP)
{
	float sc = nowHP / MaxHP;
	HPLine->setScaleX(sc);
}