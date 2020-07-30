#pragma once 
#include "stdafx.h"

class M_middleShip : public Node
{
private:

	Sprite * middleShip;
	Sprite * SollisionPoint;
	Layer * MonLayer;
	MonsterHP * m_HPbar;
	
	Vector<MonsterMissail*> *p;
	Vector<M_MiniOb*> *mp;
	float m_time;
	float m_delaytime;
	float m_patdelaytime;
	int moveup;
	bool m_hit;
	bool changeFrame;
	bool hitc;
	int nowFrame;
	int UP;
	int MN;

	float BubbleTime;

	Label * la;
public:
	Sprite * Mother;
	Vector<MiddleShip_Boom*> v_MSB;
	int M_HP;
	bool hitBoom;
	void m_update(float dt,int path);
	void m_init(Vec2 Pos, Layer * layer,Vector<MonsterMissail*> *vec,Vector<M_MiniOb*> *mv);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void m_hachiAni();

	void MakeBubble();

	void m_Pattun(int path);
	void m_SprinkleShot();

	void setbool();

	static M_middleShip * m_create(Vec2 CPos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<M_MiniOb*> *mv)
	{
		auto ref = new M_middleShip();
		ref->m_init(CPos, layer,vec,mv);
		ref->autorelease();

		return ref;
	}
};