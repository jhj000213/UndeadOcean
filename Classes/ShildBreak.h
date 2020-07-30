#pragma once 
#include "stdafx.h"

class ShildBreak : public Node
{
private:
	Sprite * Mother;
	Sprite * Spr;
	Sprite * SollisionPoint;


	float m_time;
	float m_delaytime;

	bool changeFrame;
	int nowFrame;


public:
	bool Dead;
	void m_update(float dt);
	void m_init(Vec2 Pos, Layer * layer);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();

	static ShildBreak * m_create(Vec2 CPos, Layer * layer)
	{
		auto ref = new ShildBreak();
		ref->m_init(CPos, layer);
		ref->autorelease();

		return ref;
	}
};