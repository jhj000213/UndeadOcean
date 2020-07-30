#pragma once 
#include "stdafx.h"

class FishHead_Roar : public Node
{
private:
	Sprite * Mother;
	Sprite * Shild;
	Sprite * SollisionPoint;
	Layer * MonLayer;

	Vector<FishHead_Roar*> *p;
	Vector<FishHead_Rain*> *tp;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	bool del;
	int nowFrame;
	int loop;

	Label * la;
public:
	int M_HP;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer, Vector<FishHead_Roar*> *vec, Vector<FishHead_Rain*> *tvec);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();
	void makeRain();

	static FishHead_Roar * m_create(Vec2 CPos, Layer * layer, Vector<FishHead_Roar*> *vec, Vector<FishHead_Rain*> *tvec)
	{
		auto ref = new FishHead_Roar();
		ref->m_init(CPos, layer, vec, tvec);
		ref->autorelease();

		return ref;
	}
};