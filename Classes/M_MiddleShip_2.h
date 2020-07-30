#pragma once 
#include "stdafx.h"

class M_MiddleShip_2 : public Node
{
private:
	Sprite * Mother;
	Sprite * middleShip;
	Sprite * SollisionPoint;
	Layer * MonLayer;
	MonsterHP * m_HPbar;
	Vec2 HeadPos;

	Vector<MonsterMissail*> *p;
	Vector<MonsterRazer*> *mp;
	float m_time;
	float m_delaytime;
	float m_patdelaytime;
	bool m_hit;
	bool changeFrame;
	bool hitc;
	int nowFrame;
	int moveup;

	float BubbleTime;
	
	Label * la;
public:
	bool Changeing;
	int M_HP;
	bool hitBoom;
	void m_update(float dt,int path);
	void m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec,Vector<MonsterRazer*> *mv);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	Vec2 m_getPosition();

	void m_Pattun(int path);
	void m_SprinkleShot1();
	void m_SprinkleShot2();

	void MakeBubble();

	void setbool();

	static M_MiddleShip_2 * m_create(Vec2 CPos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<MonsterRazer*> *mv)
	{
		auto ref = new M_MiddleShip_2();
		ref->m_init(CPos, layer, vec,mv);
		ref->autorelease();

		return ref;
	}
};