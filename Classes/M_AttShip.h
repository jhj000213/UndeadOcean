#pragma once 
#include "stdafx.h"

class M_AttShip : public Node
{
private:
	Sprite * Mother;
	Sprite * MiniOb;
	Sprite * SollisionPoint;
	Layer * MonLayer;
	MonsterHP * m_HPbar;
	Vec2 MobPos;

	Vector<MonsterMissail*> *p;
	Vector<M_AttShip*> *mp;

	float m_shotDelayTime;
	float m_shotCoolTime;
	float m_time;
	float m_delaytime;
	bool m_hit;
	bool hitc;
	bool changeFrame;
	int nowFrame;


	Label * la;
public:
	//Vector<MonsterMissail*> v_MonMissail;
	int M_HP;
	
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<M_AttShip*> *hvec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void m_Shoot();
	void removeself();
	Vec2 m_getPosition();
	void setbool();
	bool hitBoom;
	static M_AttShip * m_create(Vec2 CPos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<M_AttShip*> *hvec)
	{
		auto ref = new M_AttShip();
		ref->m_init(CPos, layer, vec, hvec);
		ref->autorelease();

		return ref;
	}
};