#include "stdafx.h"

#define MAX_TIME 0.13f
#define DELAY_TIME 0.45f
#define COOL_TIME 2.0f
void M_Hapari::m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, int hapariinfo,Vector<M_Hapari*> *hvec)
{
	M_HP = 15;
	Mother = Sprite::create("enemy/hapari/hapari_hitpoint.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	Mother->setScale(0.6);
	this->addChild(Mother);
	MonLayer = layer;
	//m_HPbar = MonsterHP::m_create(Vec2(-80, 130), Mother, 15);//작게
	//Mother->addChild(m_HPbar);

	Hapari = Sprite::create("enemy/hapari/hapari0.png");
	Hapari->setPosition(Vec2(40, 50));
	Mother->addChild(Hapari);
	HI = hapariinfo;

	p = vec;
	hp = hvec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
	m_shotCoolTime = COOL_TIME;

	if (HI == 1)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(500, 0));
		auto ac2 = MoveBy::create(1.5f, Vec2(0, -360));
		auto ac3 = MoveBy::create(1.5f, Vec2(0, 360));

		auto ac4 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		
		auto seq = Sequence::create(EaseOut::create(ac2, 2.0), EaseIn::create(ac3, 2.0) , NULL);
		auto sp = Spawn::create(ac1, seq, NULL);
		
		auto seq1 = Sequence::create(sp, ac4,RemoveSelf::create(), NULL);
		Mother->runAction(seq1);
	}
	else if (HI == 2)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(720, -850));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 3)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(-720, -850));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 4)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(0, -850));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 5)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(-950, 0));
		auto ac3 = MoveBy::create(2.3f, Vec2(0, 700));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac3, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 6)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(720, 850));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 7)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(-500, 0));
		auto ac2 = MoveBy::create(1.5f, Vec2(0, 360));
		auto ac3 = MoveBy::create(1.5f, Vec2(0, -360));
		auto ac4 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));

		auto seq = Sequence::create(EaseOut::create(ac2, 2.0), EaseIn::create(ac3, 2.0), NULL);
		auto sp = Spawn::create(ac1, seq, NULL);

		auto seq1 = Sequence::create(sp, ac4, RemoveSelf::create(), NULL);
		Mother->runAction(seq1);
	}
	else if (HI == 8)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(-720, -850));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 9)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(0, 850));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 10)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(-950, 0));
		auto ac3 = MoveBy::create(2.3f, Vec2(0, -700));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac3, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 11)
	{
		auto ac1 = MoveBy::create(4.6f, Vec2(-1400, 0));
		auto ac2 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));
		auto seq = Sequence::create(ac1, ac2, RemoveSelf::create(), NULL);
		Mother->runAction(seq);
	}
	else if (HI == 12)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(-500, 0));
		auto ac2 = MoveBy::create(1.5f, Vec2(0, -360));
		auto ac3 = MoveBy::create(1.5f, Vec2(0, 360));

		auto ac4 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));

		auto seq = Sequence::create(EaseOut::create(ac2, 2.0), EaseIn::create(ac3, 2.0), NULL);
		auto sp = Spawn::create(ac1, seq, NULL);

		auto seq1 = Sequence::create(sp, ac4, RemoveSelf::create(), NULL);
		Mother->runAction(seq1);
	}
	else if (HI == 13)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(500, 0));
		auto ac2 = MoveBy::create(1.5f, Vec2(0, 360));
		auto ac3 = MoveBy::create(1.5f, Vec2(0, -360));
		auto ac4 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));

		auto seq = Sequence::create(EaseOut::create(ac2, 2.0), EaseIn::create(ac3, 2.0), NULL);
		auto sp = Spawn::create(ac1, seq, NULL);

		auto seq1 = Sequence::create(sp, ac4, RemoveSelf::create(), NULL);
		Mother->runAction(seq1);
	}
	else if (HI == 14)
	{
		auto ac1 = MoveBy::create(3.0f, Vec2(0, 850));
		auto ac2 = MoveBy::create(0.75f, Vec2(-500, 0));
		auto ac3 = MoveBy::create(0.75f, Vec2(500, 0));
		auto ac4 = CallFunc::create(CC_CALLBACK_0(M_Hapari::removeself, this));

		auto seq = Sequence::create(ac2, ac3, ac2, ac3, NULL);
		auto sp = Spawn::create(ac1, seq, NULL);

		auto seq1 = Sequence::create(sp, ac4, RemoveSelf::create(), NULL);
		Mother->runAction(seq1);
	}
}

void M_Hapari::m_update(float dt,Vec2 Pos)
{

	//m_hpbar->hp_update(m_hp);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	m_shotCoolTime -= dt;
	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 3)//프레임 수
			nowFrame = 0;
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
			sprintf(str, "enemy/hapari/hapari_white%d.png", nowFrame);
			//Aghi->setTexture(str);

			Sprite * h = Sprite::create(str);
			h->setPosition(Hapari->getPosition());
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
			sprintf(str, "enemy/hapari/hapari%d.png", nowFrame);
			Hapari->setTexture(str);
		}
	}

	if (m_shotCoolTime <= 0.0f)
	{
		m_Shoot(Pos);
		m_shotCoolTime = COOL_TIME;
	}
}

void M_Hapari::m_sollision()
{
	m_hit = true;
}

bool M_Hapari::m_sollisionCheck()
{

	return true;
}

Rect M_Hapari::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_Hapari::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void M_Hapari::m_Shoot(Vec2 Pos)
{
	AudioEngine::play2d("sound/effect/hapari_shoot.mp3", false, EffVolume);

	MonsterMissail * Missail = MonsterMissail::m_create(Mother->getPosition(), MonLayer, Pos, 1, 0);
	MonLayer->addChild(Missail);
	p->pushBack(Missail);
}

void M_Hapari::removeself()
{
	hp->eraseObject(this);
}

Vec2 M_Hapari::m_getPosition()
{
	return Mother->getPosition();
}