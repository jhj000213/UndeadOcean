#pragma once 
#include "stdafx.h"

class M_Aghi : public Node
{
private:
	Sprite * Mother;
	Sprite * Aghi;
	Sprite * SollisionPoint;

	MonsterHP * m_HPbar;

	Vector<M_Aghi*> *p;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;
	

	Label * la;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer,Vector<M_Aghi*> *vec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	static M_Aghi * m_create(Vec2 CPos, Layer * layer, Vector<M_Aghi*> *vec)
	{
		auto ref = new M_Aghi();
		ref->m_init(CPos, layer,vec);
		ref->autorelease();

		return ref;
	}
};