#pragma once
#include "stdafx.h"

class MonsterRazer : public Node
{
private:
	Layer * m_layer;

	float m_time;
	float m_delaytime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;
	int m_RazerInfo;
	bool solli;
	int loop;
	bool shootsound;

	vector<int> hit;
public:
	Sprite * Mother;
	Sprite * Razer;
	bool del;
	bool top;

	void m_init(Vec2 SPos, int RazerInfo, bool t);
	float m_getPositionX();
	Vec2 m_getPosition();
	void m_setPosition(Vec2 Pos);
	Rect m_getRect();
	void m_boomEffect();
	void m_update(float dt);
	bool m_sollisionCheck();
	int m_getRazerInfo();

	static MonsterRazer * m_create(Vec2 SPos,int MI, bool tr)
	{
		auto ref = new MonsterRazer();
		ref->m_init(SPos, MI,tr);
		ref->autorelease();

		return ref;
	}
};