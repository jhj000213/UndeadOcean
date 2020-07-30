#pragma once 
#include "stdafx.h"

class Robot_Missail : public Node
{
private:
	Sprite * Mother;
	Sprite * Wave;
	Sprite * SollisionPoint;


	MonsterHP * m_HPbar;

	Vector<Robot_Missail*> *p;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;

	int nowFrame;


	Label * la;
public:	
	bool del;
	int M_HP;
	void m_update(float dt);
	void m_init(Layer * layer, Vector<Robot_Missail*> *vec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	static Robot_Missail * m_create(Layer * layer, Vector<Robot_Missail*> *vec)
	{
		auto ref = new Robot_Missail();
		ref->m_init(layer, vec);
		ref->autorelease();

		return ref;
	}
};