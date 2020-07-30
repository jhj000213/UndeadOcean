#pragma once 
#include "stdafx.h"

class M_Crab : public Node
{
private:
	Sprite * Mother;
	Sprite * BodyMother;
	Sprite * BackMother;
	Sprite * FrontMother;
	Sprite * Crab;
	Sprite * BigHand;
	Sprite * SmallHand;
	Sprite * LeftLeg;
	Sprite * RightLeg;
	Vec2 SubPos;

	MonsterHP * m_HPbar;

	Vector<M_Crab*> *p;
	Vector<M_CrabShild*> *sp;
	Vector<MonsterMissail*> *mVec;
	Vector<Crab_Wave*> *wp;
	Vector<M_CrabShildMake*> v_shildmake;
	Vector<Crab_Smog*> v_smog;
	Vector<Crab_EarseQuake*> v_earsequake;
	Vector<Crab_Thorn*> *tp;

	float m_time;
	float m_delaytime;
	float m_pattuntime;
	bool m_bodyhit;
	bool m_leghit;
	bool m_handhit;
	bool changeFrame;
	bool hitc;
	int nowFrame;
	int nowLegFrame;
	int nowHandFrame;


	Layer * MonLayer;
public:
	int M_Body_HP;
	int M_Hand_HP;
	int M_Leg_HP;
	bool HandDead;
	bool LegDead;
	bool MakeHapari;
	bool CanMove;
	bool hitBoom;
	void m_update(float dt,Vec2 Pos,int path);
	void m_init(Vec2 Pos, Layer * layer, Vector<M_Crab*> *vec, Vector<M_CrabShild*> *svec, Vector<MonsterMissail*> *mvec, Vector<Crab_Wave*> *w, Vector<Crab_Thorn*> *tvec);
	bool m_sollisionCheck();


	void m_Pattun(int path);
	void m_shoot();

	void m_bodysollision();
	void m_handsollision();
	void m_legsollision();

	Rect m_getBodyRect();
	Rect m_getHandRect();
	Rect m_getLegRect();

	void m_Body_Dmg(int dme);
	void m_Hand_Dmg(int dme);
	void m_Leg_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();
	void m_setOpacity();
	void m_setOpacityLaw();
	void m_setOpacity_T();
	void m_setOpacityLaw_T();

	void m_removeBigHand();
	void m_removeSmallHand();
	void m_removeSmog();

	void m_BoomHand();
	void m_BoomLeg();

	void setbool();

	static M_Crab * m_create(Vec2 CPos, Layer * layer, Vector<M_Crab*> *vec, Vector<M_CrabShild*> *svec, Vector<MonsterMissail*> *mvec, Vector<Crab_Wave*> *w, Vector<Crab_Thorn*> *tvec)
	{
		auto ref = new M_Crab();
		ref->m_init(CPos, layer, vec,svec,mvec,w,tvec);
		ref->autorelease();

		return ref;
	}
};