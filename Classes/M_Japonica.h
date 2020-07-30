#pragma once 
#include "stdafx.h"

class M_Japonica : public Node
{
private:
	Sprite * Mother;
	Sprite * Japo;
	Sprite * SollisionPoint;
	Layer * MomL;
	MonsterHP * m_HPbar;

	Vector<MonsterRazer*> *vec;
	float m_time;
	float m_delaytime;
	float m_shootdelaytime;
	float m_shootingtime;
	float m_dangerTime;
	bool danger;
	bool m_hit;
	bool changeFrame;
	int nowFrame;
	int shootnowFrame;
	bool shoot;

	Label * la;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer,Vector<MonsterRazer*> *p);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	Vec2 m_getPosition();

	static M_Japonica * m_create(Vec2 CPos, Layer * layer, Vector<MonsterRazer*> *p)
	{
		auto ref = new M_Japonica();
		ref->m_init(CPos, layer,p);
		ref->autorelease();

		return ref;
	}
};