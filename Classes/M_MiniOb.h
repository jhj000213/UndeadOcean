#pragma once 
#include "stdafx.h"

class M_MiniOb : public Node
{
private:
	Sprite * Mother;
	Sprite * MiniOb;
	Sprite * SollisionPoint;
	Layer * MonLayer;
	MonsterHP * m_HPbar;
	Vec2 MobPos;

	Vector<MonsterMissail*> *p;
	Vector<M_MiniOb*> *mp;

	float m_shotDelayTime;
	float m_shotCoolTime;
	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;


	Label * la;
public:
	//Vector<MonsterMissail*> v_MonMissail;
	int M_HP;
	void m_update(float dt, Vec2 Pos);
	void m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<M_MiniOb*> *hvec,int in);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void m_Shoot(Vec2 Pos);
	void removeself();
	Vec2 m_getPosition();

	static M_MiniOb * m_create(Vec2 CPos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<M_MiniOb*> *hvec,int in)
	{
		auto ref = new M_MiniOb();
		ref->m_init(CPos, layer, vec,hvec,in);
		ref->autorelease();

		return ref;
	}
};