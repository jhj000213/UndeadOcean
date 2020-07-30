#pragma once 
#include "stdafx.h"

class M_CrabShildMake : public Node
{
private:
	Sprite * Mother;
	Sprite * Shild;
	Sprite * SollisionPoint;


	Vector<M_CrabShildMake*> *p;
	Vector<M_CrabShild*> *sp;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	bool del;
	int nowFrame;

	Layer * MonLayer;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos,Layer * layer,  Vector<M_CrabShildMake*> *vec,Vector<M_CrabShild*> *svec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();
	void m_makeShild();

	static M_CrabShildMake * m_create(Vec2 CPos, Layer * layer, Vector<M_CrabShildMake*> *vec, Vector<M_CrabShild*> *svec)
	{
		auto ref = new M_CrabShildMake();
		ref->m_init(CPos, layer, vec,svec);
		ref->autorelease();

		return ref;
	}
};