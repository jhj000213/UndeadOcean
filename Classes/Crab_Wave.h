#pragma once 
#include "stdafx.h"

class Crab_Wave : public Node
{
private:
	Sprite * Mother;
	Sprite * Wave;
	Sprite * SollisionPoint;

	MonsterHP * m_HPbar;

	Vector<Crab_Wave*> *p;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;


	Label * la;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos,  Vector<Crab_Wave*> *vec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	static Crab_Wave * m_create(Vec2 CPos, Vector<Crab_Wave*> *vec)
	{
		auto ref = new Crab_Wave();
		ref->m_init(CPos,  vec);
		ref->autorelease();

		return ref;
	}
};