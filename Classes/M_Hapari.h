#pragma once 
#include "stdafx.h"

class M_Hapari : public Node
{
private:
	Sprite * Mother;
	Sprite * Hapari;
	Sprite * SollisionPoint;
	Layer * MonLayer;
	MonsterHP * m_HPbar;

	Vector<MonsterMissail*> *p;
	Vector<M_Hapari*> *hp;

	float m_shotDelayTime;
	float m_shotCoolTime;
	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;
	int HI;

	Label * la;
public:
	//Vector<MonsterMissail*> v_MonMissail;
	int M_HP;
	void m_update(float dt,Vec2 Pos);
	void m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, int hapariinfo, Vector<M_Hapari*> *hvec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void m_Shoot(Vec2 Pos);
	void removeself();
	Vec2 m_getPosition();

	static M_Hapari * m_create(Vec2 CPos, Layer * layer, Vector<MonsterMissail*> *vec, int hapariinfo,Vector<M_Hapari*> *hvec)
	{
		auto ref = new M_Hapari();
		ref->m_init(CPos, layer,vec,hapariinfo,hvec);
		ref->autorelease();

		return ref;
	}
};