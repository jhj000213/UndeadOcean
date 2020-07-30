#pragma once 
#include "stdafx.h"

class FishHead_Rain : public Node
{
private:
	Sprite * Mother;
	Sprite * Wave;
	Sprite * Eff;
	Sprite * SollisionPoint;


	MonsterHP * m_HPbar;

	Vector<FishHead_Rain*> *p;

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
	void m_init(Layer * layer, Vector<FishHead_Rain*> *vec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();

	static FishHead_Rain * m_create(Layer * layer, Vector<FishHead_Rain*> *vec)
	{
		auto ref = new FishHead_Rain();
		ref->m_init(layer, vec);
		ref->autorelease();

		return ref;
	}
};