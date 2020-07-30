#pragma once
#include "stdafx.h"

class MySubmarin : public Node
{
private:
	
	float s_MovingTime;


	Sprite * Sub;
	Sprite * Frame;

	Vector<TorpedoBoom*> *p;
	
	Layer * GLayer;

	float ShootDelayTime;
	float ShootCoolTime;
	float TorpedoCoolTime;
	float HitTime;

	float BubbleTime;

	int HP;
	int Level;
	int Damege;
	int AirgunInfo;
	bool Strong;

public:
	Sprite * Hack;
	float HackWidth;
	int MissailDamege;
	int TorpedoDamege;
	bool s_Moving;
	void n_init(Vec2 CPos, Layer * layer, Vector<TorpedoBoom*> *bp, int airguninfo);
	void n_update(float dt);
	void s_setPosition(Vec2 Pos);
	void s_setPositionX(float dx);
	void s_setPositionY(float dy);
	void s_airShoot(Vec2 Pos,int info);
	bool s_Torpedo();
	bool s_ScreenSollisionX(float Pos);
	bool s_ScreenSollisionY(float Pos);
	Rect s_getRect();
	void s_hitting();
	bool s_getStrong();
	void s_setStrong();

	void MakeBubble();

	
	Vec2 s_getPosition();

	Vector<MyMissail*> AirGun;
	Vector<MyTorpedo*> v_Torpedo;

	float s_Speed;

	static MySubmarin * n_create(Vec2 CPos, Layer * layer, Vector<TorpedoBoom*> *bp, int airguninfo)
	{
		auto ref = new MySubmarin();
		ref->n_init(CPos,layer,bp,airguninfo);
		ref->autorelease();

		return ref;
	}
};