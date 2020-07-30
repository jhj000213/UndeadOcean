#pragma once 
#include "stdafx.h"

class M_BigRobot_Dead : public Node
{
private:
	Sprite * Mother;
	Sprite * Spr;
	Sprite * SollisionPoint;


	float m_time;
	float m_delaytime;

	bool changeFrame;
	int nowFrame;
	Layer * GLayer;

public:
	bool Dead;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();

	static M_BigRobot_Dead * m_create(Vec2 CPos, Layer * layer)
	{
		auto ref = new M_BigRobot_Dead();
		ref->m_init(CPos, layer);
		ref->autorelease();

		return ref;
	}
};