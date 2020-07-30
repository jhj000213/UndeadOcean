#pragma once 
#include "stdafx.h"

class M_BigRobot : public Node
{
private:

	Sprite * middleShip;
	Sprite * SollisionPoint;
	Layer * MonLayer;
	MonsterHP * m_HPbar;

	Vector<MonsterMissail*> *p;
	Vector<MonsterRazer*> *mp;
	Vector<Robot_Missail*> *rp;
	float m_time;
	float m_delaytime;
	float m_patdelaytime;
	int moveup;
	bool m_hit;
	bool changeFrame;
	bool RazerShoot;
	bool hitc;
	int nowFrame;
	int UP;
	int MN;
	int pat3num;
	int pat3p;
	int loo;

	float BubbleTime;

	Label * la;
public:
	Sprite * Mother;
	Vector<Robot_Razer*> v_RobotRazer;
	int M_HP;
	bool hitBoom;
	void m_update(float dt,int path);
	void m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<MonsterRazer*> *mv, Vector<Robot_Missail*> *rv);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	Vec2 m_getPosition();
	void setbool();

	void MakeBubble();

	void m_Pattun(int path);
	void m_SprinkleShot();
	~M_BigRobot();


	static M_BigRobot * m_create(Vec2 CPos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<MonsterRazer*> *mv, Vector<Robot_Missail*> *rv)
	{
		auto ref = new M_BigRobot();
		ref->m_init(CPos, layer, vec, mv,rv);
		ref->autorelease();

		return ref;
	}
};