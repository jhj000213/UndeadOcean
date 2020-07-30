#pragma once
#include "stdafx.h"

class MonsterHP : public Node
{
private:
	float MaxHP;
public:
	Sprite * HPBox;
	Sprite * HPLine;


	void hp_init(Vec2 Pos, Node * mother,int maxhp);
	float hp_getPositionX();
	void hp_setPosition(Vec2 Pos);
	Rect hp_getRect();
	void hp_update(float nowHP);

	static MonsterHP * m_create(Vec2 CPos, Node * mother,int maxhp)
	{
		auto ref = new MonsterHP();
		ref->hp_init(CPos, mother,maxhp);
		ref->autorelease();

		return ref;
	}
};