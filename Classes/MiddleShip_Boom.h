#pragma once
#include "stdafx.h"

class MiddleShip_Boom : public Node
{
private:
	
	Sprite * S_Boom;
	Layer * MonLayer;
	MonsterHP * m_HPbar;
	Vector<MonsterMissail*> *p;
	float m_time;
	float m_delaytime;
	float m_fevertime;
	float m_shotdelaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;

	bool Shoot;
	bool ang;
public:
	Sprite * Mother;
	int M_HP;

	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer,Vector<MonsterMissail*> *vec);
	float m_getPositionX();
	Vec2 m_getPosition();
	void m_setPosition(Vec2 Pos);
	Rect m_getRect();
	void m_boomEffect();
	void m_shoot(float dt);
	void m_Dmg(int dme);
	void m_sollision();

	static MiddleShip_Boom * m_create(Vec2 CPos, Layer * layer,Vector<MonsterMissail*> *vec)
	{
		auto ref = new MiddleShip_Boom();
		ref->m_init(CPos, layer,vec);
		ref->autorelease();

		return ref;
	}
};