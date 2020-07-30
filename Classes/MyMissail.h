#pragma once
#include "stdafx.h"

class MyMissail : public Node
{
private:
	


	Layer * m_layer;

public:
	Sprite * Missail;


	void m_init(Vec2 Pos, Layer * layer, int info);
	float m_getPositionX();
	void m_setPosition(Vec2 Pos);
	Rect m_getRect();
	void m_boomEffect();

	static MyMissail * m_create(Vec2 CPos, Layer * layer, int info)
	{
		auto ref = new MyMissail();
		ref->m_init(CPos, layer,info);
		ref->autorelease();

		return ref;
	}
};