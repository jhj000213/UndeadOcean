#pragma once 
#include "stdafx.h"

class M_UpAghi : public Node
{
private:
	Sprite * Mother;
	Sprite * Aghi;
	Sprite * SollisionPoint;
	Sprite * Danger;
	Vec2 EPos;
	MonsterHP * m_HPbar;


	Vector<M_UpAghi*> *p;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;

	Layer * MomL;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer,Vector<M_UpAghi*> *vec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void MakeEffect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	static M_UpAghi * m_create(Vec2 CPos, Layer * layer, Vector<M_UpAghi*> *vec)
	{
		auto ref = new M_UpAghi();
		ref->m_init(CPos, layer,vec);
		ref->autorelease();

		return ref;
	}
};