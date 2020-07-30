#pragma once 
#include "stdafx.h"

class M_MiddleShipDead : public Node
{
private:
	Sprite * Mother;
	Sprite * Aghi;
	Sprite * SollisionPoint;

	MonsterHP * m_HPbar;



	float m_time;
	float m_delaytime;

	bool changeFrame;
	int nowFrame;


public:
	bool Dead;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();

	static M_MiddleShipDead * m_create(Vec2 CPos, Layer * layer)
	{
		auto ref = new M_MiddleShipDead();
		ref->m_init(CPos, layer);
		ref->autorelease();

		return ref;
	}
};