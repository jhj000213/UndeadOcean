#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f
#define BUBBLE_TIME 3.5f
#define PAT_DELAY_TIME 4.5f
void M_FishHead::m_init(Vec2 Pos, Layer * layer, Vector<M_FishHead*> *vec, Vector<FishHead_Roar*> *rop, Vector<MonsterRazer*> *Rp, Vector<FishHead_Hurricane*> *hpo, Vector<FishHead_Crash*> *hc, Vector<FishHead_Rain*> *rp)
{
	M_HP = 4500;
	Mother = Sprite::create("enemy/fishhead/normal/fishheadhit.png");
	Mother->setAnchorPoint(Vec2(1, 0));
	Mother->setScale(0.7f);
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	m_HPbar = MonsterHP::m_create(Vec2(925, 360), this, 4500);//작게
	Mother->addChild(m_HPbar);

	Aghi = Sprite::create("enemy/fishhead/normal/fishhead0.png");
	Aghi->setAnchorPoint(Vec2(1, 0));
	Aghi->setPosition(Vec2(980, 0));
	Mother->addChild(Aghi);


	auto ac1 = MoveBy::create(2.0f, Vec2(-200, 720));
	auto seq = Sequence::create(EaseOut::create(ac1, 4.5f), NULL);
	Mother->runAction(seq);

	HeadPos = Vec2(Mother->getPositionX()-300, Mother->getPositionY());
	MonLayer = layer;
	cvec = hc;
	rvec = rp;
	v_hurricane = hpo;
	v_roar = rop;
	p = vec;
	v_monr = Rp;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	hitBoom = false;
	hitc = false;
	nowPat = 0;
	BubbleTime = 0.0f;
	m_pattime = PAT_DELAY_TIME;
	nowFrame = 0;
	loop = 0;
}

void M_FishHead::m_update(float dt,int patt)
{
	m_pattime -= dt;

	if (m_pattime <= 0.0f)
	{
		m_Pattun(patt);//
		m_pattime = PAT_DELAY_TIME;
	}
	if (hitBoom == true && hitc == false)
	{
		hitc = true;
		auto ac = CallFunc::create(CC_CALLBACK_0(M_FishHead::setbool, this));
		auto seq = Sequence::create(DelayTime::create(1.6f), ac, NULL);

		this->runAction(seq);
	}

	HeadPos = Vec2(Mother->getPositionX() - 300, Mother->getPositionY() + Mother->boundingBox().size.height / 2);
	m_HPbar->hp_update(M_HP);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;

	BubbleTime -= dt;
	if (BubbleTime <= 0.0f)
	{
		BubbleTime = 3.2f;
		MakeBubble();
	}

	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		if (v_Pat.empty() == false)
		{
			nowFrame = v_Pat.front();
			v_Pat.erase(v_Pat.begin());
		}
		else
		{
			nowFrame++;
			if (nowFrame >= 2)//프레임 수
			{
				nowFrame = 0;
			}
		}
		changeFrame = true;
	}
	if (changeFrame == true)
	{
		changeFrame = false;
		if (m_hit == true && m_delaytime <= 0.0f)
		{
			m_delaytime = DELAY_TIME;
			m_hit = false;

			char str[256];
			sprintf(str, "enemy/fishhead/normal/fishheadwhite%d.png", nowFrame);
			//Aghi->setTexture(str);

			Sprite * h = Sprite::create(str);
			h->setAnchorPoint(Vec2(1, 0));
			h->setPosition(Aghi->getPosition());
			Mother->addChild(h);
			auto ac = FadeOut::create(0.3f);
			auto seq = Sequence::create(ac, RemoveSelf::create(), NULL);
			h->runAction(seq);

			auto mo1 = MoveBy::create(0.05f, Vec2(4, 0));
			auto mo2 = MoveBy::create(0.05f, Vec2(-8, 0));
			auto mo3 = MoveBy::create(0.05f, Vec2(8, 0));
			auto mo4 = MoveBy::create(0.05f, Vec2(-4, 0));
			auto moseq = Sequence::create(mo1, mo2, mo3, mo4, NULL);
			Mother->runAction(moseq);
		}
		else
		{
			char str[256];
			sprintf(str, "enemy/fishhead/normal/fishhead%d.png", nowFrame);
			Aghi->setTexture(str);
		}
	}
}

void M_FishHead::m_Pattun(int path)
{

	int patnum;

	patnum = (rand() % 4) + 1;
	//patnum = path;
	//patnum = 4;
	log("%d", patnum);
	if (patnum == 1)//Hurricane
	{
		FishHead_Hurricane * Make = FishHead_Hurricane::m_create(HeadPos, MonLayer, v_hurricane, cvec);
		Mother->addChild(Make);
		v_hurricane->pushBack(Make);

		
		auto seq = Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), NULL);
		Make->runAction(seq);


		v_Pat.push_back(2);
		v_Pat.push_back(3);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);

		v_Pat.push_back(2);
		v_Pat.push_back(1);
		v_Pat.push_back(0);
	}
	if (patnum == 2)//Roar
	{
		FishHead_Roar * Make = FishHead_Roar::m_create(Vec2(0, 0), MonLayer, v_roar, rvec);
		Mother->addChild(Make);
		v_roar->pushBack(Make);


		auto seq = Sequence::create(DelayTime::create(2.0f), RemoveSelf::create(), NULL);
		Make->runAction(seq);


		v_Pat.push_back(2);
		v_Pat.push_back(3);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
		v_Pat.push_back(4);
	}
	if (patnum == 3)//breath
	{
		MonsterRazer * MR = MonsterRazer::m_create(Vec2(HeadPos.x-170,HeadPos.y+100), 4, true);
		this->addChild(MR, 10);
		v_monr->pushBack(MR);

		auto seq = Sequence::create(DelayTime::create(4.0f), RemoveSelf::create(), NULL);
		MR->runAction(seq);

		v_Pat.push_back(0);
		v_Pat.push_back(1);
		v_Pat.push_back(0);
		v_Pat.push_back(1);
		v_Pat.push_back(3);
		v_Pat.push_back(4);
		v_Pat.push_back(3);
		v_Pat.push_back(4);
		v_Pat.push_back(3);
		v_Pat.push_back(4);
		v_Pat.push_back(3);
	}
	if (patnum == 4)
	{
		Sprite * Ani = Sprite::create();
		Ani->setPosition(Vec2(700, 260));
		MonLayer->addChild(Ani, 1000);

		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 1; i < 6; i++)
		{
			sprintf(str1, "chohmpa%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


		Ani->runAction(seq);

		MakeHapari = true;
	}

}

void M_FishHead::m_sollision()
{
	m_hit = true;
}

bool M_FishHead::m_sollisionCheck()
{

	return true;
}

Rect M_FishHead::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width,
		Mother->getPositionY(),
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_FishHead::m_Dmg(int dmg)
{
	M_HP -= dmg;
}
void M_FishHead::removeself()
{
	p->eraseObject(this);
}

Vec2 M_FishHead::m_getPosition()
{
	return Mother->getPosition();
}

void M_FishHead::MakeBubble()
{
	Sprite * bub = Sprite::create();
	bub->setPosition(Vec2(-450, -50));
	Mother->addChild(bub, 1000);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 0; i < 7; i++)
	{
		sprintf(str1, "bub%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	bub->runAction(seq);
}

void M_FishHead::setbool()
{
	hitBoom = false;
	hitc = false;
}
