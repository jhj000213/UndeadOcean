#pragma once 
#include "stdafx.h"

class TorpedoBoom : public Node
{
private:
	Sprite * Mother;
	Sprite * Wave;
	Sprite * SollisionPoint;

	MonsterHP * m_HPbar;

	Vector<TorpedoBoom*> *p;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;
	int BoomNum;


	Label * la;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos, Vector<TorpedoBoom*> *vec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	void boomeff();
	void boomeff_1();

	static TorpedoBoom * m_create(Vec2 CPos, Vector<TorpedoBoom*> *vec)
	{
		auto ref = new TorpedoBoom();
		ref->m_init(CPos, vec);
		ref->autorelease();

		return ref;
	}
};