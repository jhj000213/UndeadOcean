#pragma once 
#include "stdafx.h"

class Crab_EarseQuake : public Node
{
private:
	Sprite * Mother;
	Sprite * Shild;
	Sprite * SollisionPoint;
	Layer * MonLayer;

	Vector<Crab_EarseQuake*> *p;
	Vector<Crab_Wave*> *wp;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	bool del;
	int nowFrame;


	Label * la;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer, Vector<Crab_EarseQuake*> *vec, Vector<Crab_Wave*> *wp);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	void m_makeWave();

	static Crab_EarseQuake * m_create(Vec2 CPos, Layer * layer, Vector<Crab_EarseQuake*> *vec, Vector<Crab_Wave*> *w)
	{
		auto ref = new Crab_EarseQuake();
		ref->m_init(CPos, layer, vec,w);
		ref->autorelease();

		return ref;
	}
};