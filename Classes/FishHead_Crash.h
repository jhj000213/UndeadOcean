#pragma once 
#include "stdafx.h"

class FishHead_Crash : public Node
{
private:
	Sprite * Mother;
	Sprite * Wave;
	Sprite * SollisionPoint;

	//Layer * MonLayer;

	Vector<FishHead_Crash*> *p;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;


	Label * la;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer, Vector<FishHead_Crash*> *vec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	static FishHead_Crash * m_create(Vec2 CPos, Layer * layer, Vector<FishHead_Crash*> *vec)
	{
		auto ref = new FishHead_Crash();
		ref->m_init(CPos,layer, vec);
		ref->autorelease();

		return ref;
	}
};