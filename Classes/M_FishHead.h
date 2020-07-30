#pragma once 
#include "stdafx.h"

class M_FishHead : public Node
{
private:
	Sprite * Mother;
	Sprite * Aghi;
	Sprite * SollisionPoint;

	Layer * MonLayer;
	Vec2 HeadPos;

	MonsterHP * m_HPbar;

	Vector<MonsterRazer*> *v_monr;
	Vector<M_FishHead*> *p;
	Vector<FishHead_Roar*> *v_roar;
	Vector<FishHead_Hurricane*> *v_hurricane;
	Vector<FishHead_Crash*> *cvec;
	Vector<FishHead_Rain*> *rvec;

	float m_time;
	float m_delaytime;
	float m_pattime;
	bool m_hit;
	bool changeFrame;
	int nowFrame;
	bool hitc;
	float BubbleTime;

	int loop;
	int nowPat;
	vector<int> v_Pat;


	Label * la;
public:
	bool MakeHapari;
	int M_HP;
	void m_update(float dt,int patt);
	void m_init(Vec2 Pos, Layer * layer, Vector<M_FishHead*> *vec, Vector<FishHead_Roar*> *rop, Vector<MonsterRazer*> *Rp, Vector<FishHead_Hurricane*> *hpo, Vector<FishHead_Crash*> *hc, Vector<FishHead_Rain*> *rp);
	bool m_sollisionCheck();
	void m_sollision();
	Rect m_getRect();
	void m_Dmg(int dme);
	void removeself();
	Vec2 m_getPosition();
	void m_Pattun(int path);
	void MakeBubble();
	void setbool();
	bool hitBoom;

	static M_FishHead * m_create(Vec2 Pos, Layer * layer, Vector<M_FishHead*> *vec, Vector<FishHead_Roar*> *rop, Vector<MonsterRazer*> *Rp, Vector<FishHead_Hurricane*> *hpo, Vector<FishHead_Crash*> *hc, Vector<FishHead_Rain*> *rp)
	{
		auto ref = new M_FishHead();
		ref->m_init(Pos, layer, vec,rop,Rp,hpo,hc,rp);
		ref->autorelease();

		return ref;
	}
};