#pragma once 
#include "stdafx.h"

class FishHead_Hurricane : public Node
{
private:
	Sprite * Mother;
	Sprite * Wave;
	Sprite * SollisionPoint;
	Layer * MonLayer;

	Vec2 HeadPos;

	Vector<FishHead_Hurricane*> *p;
	Vector<FishHead_Crash*> *wvec;

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
	void m_init(Vec2 Pos, Layer * layer, Vector<FishHead_Hurricane*> *vec, Vector<FishHead_Crash*> *wp);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	void m_makeCrash();

	static FishHead_Hurricane * m_create(Vec2 CPos, Layer * layer, Vector<FishHead_Hurricane*> *vec, Vector<FishHead_Crash*> *w)
	{
		auto ref = new FishHead_Hurricane();
		ref->m_init(CPos, layer, vec, w);
		ref->autorelease();

		return ref;
	}
};