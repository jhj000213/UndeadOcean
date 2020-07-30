#pragma once
#include "stdafx.h"

class MonsterMissail : public Node
{
private:
	Layer * m_layer;

	float dis;
	float SpeedX;
	float SpeedY;
	int m_MissailInfo;
	double radi;
public:
	Sprite * Missail;
	float MissailWidth;

	void m_init(Vec2 Pos, Node * layer,Vec2 SPos, int MissailInfo,int radiarr);
	float m_getPositionX();
	Vec2 m_getPosition();
	void m_setPosition(Vec2 Pos);
	Rect m_getRect();
	void m_boomEffect();
	void m_update(float dt);

	static MonsterMissail * m_create(Vec2 CPos, Node * layer, Vec2 SPos, int MI,int radiarr)
	{
		auto ref = new MonsterMissail();
		ref->m_init(CPos, layer,SPos,MI,radiarr);
		ref->autorelease();

		return ref;
	}
};