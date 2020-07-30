#pragma once 
#include "stdafx.h"

class Robot_Razer : public Node
{
private:
	Sprite * Mother;
	Sprite * MiniOb;
	Sprite * Shoot_R;
	Sprite * SollisionPoint;
	Layer * MonLayer;
	MonsterHP * m_HPbar;
	Vec2 MobPos;
	Vec2 HeadPos;

	Vector<MonsterRazer*> *p;
	Vector<Robot_Razer*> *mp;

	float m_shotDelayTime;

	float m_time;
	float m_delaytime;
	bool changeFrame;
	int nowFrame;

	bool shootting;
	bool TopFrame;

public:
	//Vector<MonsterMissail*> v_MonMissail;
	int M_HP;
	void m_update(float dt,bool shoot);
	void m_init(Vec2 Pos, Layer * layer, Vector<MonsterRazer*> *vec, Vector<Robot_Razer*> *hvec,bool top);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void m_Shoot();
	void removeself();
	Vec2 m_getPosition();
	void m_setOpacity_normal();
	void m_setOpacity_shoot();

	void m_razersound();

	static Robot_Razer * m_create(Vec2 CPos, Layer * layer, Vector<MonsterRazer*> *vec, Vector<Robot_Razer*> *hvec, bool top)
	{
		auto ref = new Robot_Razer();
		ref->m_init(CPos, layer, vec, hvec,top);
		ref->autorelease();

		return ref;
	}
};