#pragma once 
#include "stdafx.h"

class Crab_Smog : public Node
{
private:
	Sprite * Mother;
	Sprite * Shild;
	Sprite * SollisionPoint;
	Layer * MonLayer;

	Vector<Crab_Smog*> *p;
	Vector<Crab_Thorn*> *tp;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	bool del;
	int nowFrame;
	int loop;

	Label * la;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer, Vector<Crab_Smog*> *vec,Vector<Crab_Thorn*> *tvec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();
	void makeThorn();

	static Crab_Smog * m_create(Vec2 CPos, Layer * layer, Vector<Crab_Smog*> *vec, Vector<Crab_Thorn*> *tvec)
	{
		auto ref = new Crab_Smog();
		ref->m_init(CPos, layer, vec,tvec);
		ref->autorelease();

		return ref;
	}
};