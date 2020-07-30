#pragma once
#include "stdafx.h"

class MyTorpedo : public Node
{
private:

	Sprite * s_boom;
	int MissailNum;
	bool BoomOn = false;
	Layer * ILayer;
	bool wasboom;


	Vector<TorpedoBoom*> *p;
	Vector<MyTorpedo*> *mp;
public:
	Sprite * Missail;

	void m_init(Vec2 Pos, Layer * layer,Vector<MyTorpedo*> *tp, Vector<TorpedoBoom*> *bp,int info);
	float m_getPositionX();
	void m_createBoom();
	bool m_torSollisionCheck();
	void m_torRelease();
	void m_boomEffect();
	Rect m_getRect();
	void m_setPosition(Vec2 Pos);
	void removeself();


	static MyTorpedo * m_create(Vec2 CPos, Layer * layer, Vector<MyTorpedo*> *tp, Vector<TorpedoBoom*> *bp, int info)
	{
		auto ref = new MyTorpedo();
		ref->m_init(CPos, layer,tp,bp,info);
		ref->autorelease();

		return ref;
	}
};