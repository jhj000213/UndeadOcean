#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f
#define PAT_DELAY_TIME 4.0f
void M_Crab::m_init(Vec2 Pos, Layer * layer, Vector<M_Crab*> *vec, Vector<M_CrabShild*> *svec, Vector<MonsterMissail*> *mvec, Vector<Crab_Wave*> *w, Vector<Crab_Thorn*> *tvec)
{
	M_Body_HP = 4000;
	M_Hand_HP = 1500;
	M_Leg_HP = 1500;

	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(125);
	Mother->setPosition(Pos);
	this->addChild(Mother);


	m_HPbar = MonsterHP::m_create(Vec2(-55, 300), Mother, 4000);//작게
	Mother->addChild(m_HPbar);

	BodyMother = Sprite::create("enemy/crab/body/bodyhit.png");
	BodyMother->setOpacity(0);
	BodyMother->setPosition(Vec2(0,0));
	Mother->addChild(BodyMother, 1);

	Crab = Sprite::create("enemy/crab/body/body.png");
	Crab->setPosition(Vec2(110,230));
	BodyMother->addChild(Crab);


	BackMother = Sprite::create("enemy/crab/body/handhit.png");
	BackMother->setOpacity(0);
	BackMother->setPosition(Vec2(-75,30));
	Mother->addChild(BackMother, 0);

	FrontMother = Sprite::create("enemy/crab/leg/leghit.png");
	FrontMother->setOpacity(0);
	FrontMother->setPosition(Vec2(-80,-180));
	Mother->addChild(FrontMother, 2);

	BigHand = Sprite::create("enemy/crab/body/bighand0.png");
	BigHand->setPosition(Vec2(230, 300));
	FrontMother->addChild(BigHand);

	SmallHand = Sprite::create("enemy/crab/body/smallhand0.png");
	SmallHand->setPosition(Vec2(200, 50));
	BackMother->addChild(SmallHand);

	LeftLeg = Sprite::create("enemy/crab/leg/left/leg0.png");
	LeftLeg->setPosition(Vec2(270, -170));
	BackMother->addChild(LeftLeg);

	RightLeg = Sprite::create("enemy/crab/leg/right/leg0.png");
	RightLeg->setPosition(Vec2(280, 100));
	FrontMother->addChild(RightLeg);

	MonLayer = layer;
	tp = tvec;
	wp = w;
	p = vec;
	sp = svec;
	mVec = mvec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_pattuntime = PAT_DELAY_TIME;

	m_bodyhit=false;
	m_leghit = false;
	m_handhit = false;
	HandDead = false;
	LegDead = false;
	MakeHapari = false;
	CanMove = true;
	hitBoom = false;
	changeFrame = false;
	nowFrame = 0;
	nowHandFrame = 0;
	nowLegFrame = 0;


	auto ac = MoveBy::create(3.0f, Vec2(-500, 0));
	Mother->runAction(ac);
}

void M_Crab::m_update(float dt,Vec2 Pos,int path)
{
	SubPos = Pos;
	bool hit = false;
	m_HPbar->hp_update(M_Body_HP);
	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	m_pattuntime -= dt;

	if (v_earsequake.empty() == false)
	{
		for (Crab_EarseQuake * S : v_earsequake)
		{
			S->m_update(dt);
			break;
		}
	}
	if (v_shildmake.empty() == false)
	{
		for (M_CrabShildMake * S : v_shildmake)
		{
			S->m_update(dt);
			break;
		}
	}
	if (v_smog.empty() == false)
	{
		for (Crab_Smog * S : v_smog)
		{
			S->m_update(dt);
			break;
		}
	}

	if (hitBoom == true && hitc == false)
	{
		hitc = true;
		auto ac = CallFunc::create(CC_CALLBACK_0(M_Crab::setbool, this));
		auto seq = Sequence::create(DelayTime::create(1.6f), ac, NULL);

		this->runAction(seq);
	}




	if (m_pattuntime <= 0.0f)
	{
		m_Pattun(path);//
		m_pattuntime = PAT_DELAY_TIME;
	}




	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		nowHandFrame++;
		nowLegFrame++;
		if (nowFrame == 4)//프레임 수
			nowFrame = 0;


		if (nowHandFrame == 4)//프레임 수
			nowHandFrame = 0;

		if (nowLegFrame == 4)//프레임 수
			nowLegFrame = 0;
		changeFrame = true;
	}
	if (changeFrame == true)
	{
		changeFrame = false;
		if (m_bodyhit == true && m_delaytime <= 0.0f)
		{
			m_bodyhit = false;
			hit = true;


			Sprite * h = Sprite::create("enemy/crab/body/bodywhite.png");
			h->setPosition(Crab->getPosition());
			BodyMother->addChild(h);
			auto ac = FadeOut::create(0.3f);
			auto seq = Sequence::create(ac, RemoveSelf::create(), NULL);
			h->runAction(seq);

			auto mo1 = MoveBy::create(0.05f, Vec2(4, 0));
			auto mo2 = MoveBy::create(0.05f, Vec2(-8, 0));
			auto mo3 = MoveBy::create(0.05f, Vec2(8, 0));
			auto mo4 = MoveBy::create(0.05f, Vec2(-4, 0));
			auto moseq = Sequence::create(mo1, mo2, mo3, mo4, NULL);
			BodyMother->runAction(moseq);
		}
		else
		{
			Crab->setTexture("enemy/crab/body/body.png");
		}

		if (m_handhit == true && m_delaytime <= 0.0f && HandDead==false)
		{
			m_handhit = false;
			hit = true;
			char str[256];
			sprintf(str, "enemy/crab/body/bighandwhite%d.png", nowHandFrame);

			Sprite * h = Sprite::create(str);
			h->setPosition(BigHand->getPosition());//-
			FrontMother->addChild(h);
			auto ac = FadeOut::create(0.3f);
			auto seq = Sequence::create(ac, RemoveSelf::create(), NULL);
			h->runAction(seq);


			char str1[256];
			sprintf(str1, "enemy/crab/body/smallhandwhite%d.png", nowHandFrame);

			Sprite * hh = Sprite::create(str1);
			hh->setPosition(SmallHand->getPosition());//-
			BackMother->addChild(hh);
			auto ac1 = FadeOut::create(0.3f);
			auto seq1 = Sequence::create(ac1, RemoveSelf::create(), NULL);
			hh->runAction(seq1);

			auto mo1 = MoveBy::create(0.05f, Vec2(4, 0));
			auto mo2 = MoveBy::create(0.05f, Vec2(-8, 0));
			auto mo3 = MoveBy::create(0.05f, Vec2(8, 0));
			auto mo4 = MoveBy::create(0.05f, Vec2(-4, 0));
			auto moseq = Sequence::create(mo1, mo2, mo3, mo4, NULL);
			BigHand->runAction(moseq);
			SmallHand->runAction(moseq);


			char str3[256];
			sprintf(str3, "enemy/crab/body/bighand%d.png", nowHandFrame);
			BigHand->setTexture(str3);

			char str4[256];
			sprintf(str4, "enemy/crab/body/smallhand%d.png", nowHandFrame);
			SmallHand->setTexture(str4);
		}
		else
		{
			char str[256];
			sprintf(str, "enemy/crab/body/bighand%d.png", nowHandFrame);
			BigHand->setTexture(str);

			char str1[256];
			sprintf(str1, "enemy/crab/body/smallhand%d.png", nowHandFrame);
			SmallHand->setTexture(str1);

		}

		if (m_leghit == true && m_delaytime <= 0.0f && LegDead == false)
		{
			m_leghit = false;
			hit = true;
			char str[256];
			sprintf(str, "enemy/crab/leg/right/legwhite%d.png", nowLegFrame);

			Sprite * h = Sprite::create(str);
			h->setPosition(RightLeg->getPosition());//-
			FrontMother->addChild(h);
			auto ac = FadeOut::create(0.3f);
			auto seq = Sequence::create(ac, RemoveSelf::create(), NULL);
			h->runAction(seq);


			char str1[256];
			sprintf(str1, "enemy/crab/leg/left/legwhite%d.png", nowLegFrame);

			Sprite * hh = Sprite::create(str1);
			hh->setPosition(LeftLeg->getPosition());//-
			BackMother->addChild(hh);
			auto ac1 = FadeOut::create(0.3f);
			auto seq1 = Sequence::create(ac1, RemoveSelf::create(), NULL);
			hh->runAction(seq1);

			auto mo1 = MoveBy::create(0.05f, Vec2(4, 0));
			auto mo2 = MoveBy::create(0.05f, Vec2(-8, 0));
			auto mo3 = MoveBy::create(0.05f, Vec2(8, 0));
			auto mo4 = MoveBy::create(0.05f, Vec2(-4, 0));
			auto moseq = Sequence::create(mo1, mo2, mo3, mo4, NULL);
			LeftLeg->runAction(moseq);
			RightLeg->runAction(moseq);

			char str3[256];
			sprintf(str3, "enemy/crab/leg/left/leg%d.png", nowLegFrame);
			LeftLeg->setTexture(str3);

			char str4[256];
			sprintf(str4, "enemy/crab/leg/right/leg%d.png", nowLegFrame);
			RightLeg->setTexture(str4);
		}
		else
		{
			char str[256];
			sprintf(str, "enemy/crab/leg/left/leg%d.png", nowLegFrame);
			LeftLeg->setTexture(str);

			char str1[256];
			sprintf(str1, "enemy/crab/leg/right/leg%d.png", nowLegFrame);
			RightLeg->setTexture(str1);

		}

	}
	if (hit == true)
	{
		m_delaytime = DELAY_TIME;
	}

}

void M_Crab::m_bodysollision()
{
	m_bodyhit = true;
}

void M_Crab::m_handsollision()
{
	m_handhit = true;
}

void M_Crab::m_legsollision()
{
	m_leghit = true;
}



Rect M_Crab::m_getBodyRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() + BodyMother->getPositionX() - BodyMother->boundingBox().size.width / 2,
		Mother->getPositionY() + BodyMother->getPositionY() - BodyMother->boundingBox().size.height / 2,
		BodyMother->boundingBox().size.width,
		BodyMother->boundingBox().size.height);
	return mrect;
}
Rect M_Crab::m_getHandRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() + BackMother->getPositionX() - BackMother->boundingBox().size.width / 2,
		Mother->getPositionY() + BackMother->getPositionY() - BackMother->boundingBox().size.height / 2,
		BackMother->boundingBox().size.width,
		BackMother->boundingBox().size.height);
	return mrect;
}
Rect M_Crab::m_getLegRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() + FrontMother->getPositionX() - FrontMother->boundingBox().size.width / 2,
		Mother->getPositionY() + FrontMother->getPositionY() - FrontMother->boundingBox().size.height / 2,
		FrontMother->boundingBox().size.width,
		FrontMother->boundingBox().size.height);
	return mrect;
}


void M_Crab::m_Body_Dmg(int dmg)
{
	M_Body_HP -= dmg;
}
void M_Crab::m_Hand_Dmg(int dmg)
{
	M_Hand_HP -= dmg;
}
void M_Crab::m_Leg_Dmg(int dmg)
{
	M_Leg_HP -= dmg;
}
void M_Crab::removeself()
{
	p->eraseObject(this);
}

Vec2 M_Crab::m_getPosition()
{
	return Mother->getPosition();
}

void M_Crab::m_Pattun(int path)
{

		int patnum;

		patnum = (rand() % 5) + 1;
		//patnum = path;
		//patnum = 4;
		//log("%d", patnum);
		if (patnum == 1)//small hand
		{
			if (HandDead == false)
			{
				
				SmallHand->setOpacity(0);

				M_CrabShildMake * Make = M_CrabShildMake::m_create(SmallHand->getPosition(), MonLayer, &v_shildmake, sp);
				BackMother->addChild(Make);
				v_shildmake.pushBack(Make);

				auto ac = CallFunc::create(CC_CALLBACK_0(M_Crab::m_setOpacity, this));
				auto ac1 = CallFuncN::create(CC_CALLBACK_0(M_Crab::m_removeSmallHand, this));
				auto seq = Sequence::create(DelayTime::create(1.28f), ac, ac1, RemoveSelf::create(), NULL);
				Make->runAction(seq);
			}

		}
		if (patnum == 2)//big hand
		{
			if (HandDead == false)
			{
				
				BigHand->setOpacity(0);

				Crab_EarseQuake * Make = Crab_EarseQuake::m_create(BigHand->getPosition(), MonLayer, &v_earsequake, wp);
				FrontMother->addChild(Make);
				v_earsequake.pushBack(Make);

				auto ac = CallFunc::create(CC_CALLBACK_0(M_Crab::m_setOpacity, this));
				auto ac1 = CallFuncN::create(CC_CALLBACK_0(M_Crab::m_removeBigHand, this));
				auto seq = Sequence::create(DelayTime::create(1.5f), ac, ac1, RemoveSelf::create(), NULL);
				Make->runAction(seq);
			}

		}
		
		if (patnum == 3)//leg
		{
			if (LegDead == false)
			{
				m_pattuntime = 5.5f;
				
				Crab_Smog * Make = Crab_Smog::m_create(Vec2(FrontMother->getPositionX() + 200, FrontMother->getPositionY()), MonLayer, &v_smog, tp);
				Make->setPosition(FrontMother->getPositionX() + 700, FrontMother->getPositionY() + 250);
				this->addChild(Make);
				v_smog.pushBack(Make);

				auto ac1 = CallFuncN::create(CC_CALLBACK_0(M_Crab::m_removeSmog, this));

				auto seq = Sequence::create(DelayTime::create(5.0f), ac1, RemoveSelf::create(), NULL);
				Make->runAction(seq);

				auto ac2 = CallFuncN::create(CC_CALLBACK_0(M_Crab::m_setOpacityLaw_T, this));
				auto ac3 = CallFuncN::create(CC_CALLBACK_0(M_Crab::m_setOpacity_T, this));
				auto seq1 = Sequence::create(DelayTime::create(1.5f), ac2, DelayTime::create(2.5f), ac3, NULL);
				this->runAction(seq1);

			}

		}
		
		if (patnum == 4)//head
		{
			auto ac = CallFunc::create(CC_CALLBACK_0(M_Crab::m_shoot, this));
			auto seq = Sequence::create(ac, DelayTime::create(0.5f), ac, DelayTime::create(0.5f), ac, DelayTime::create(0.5f), ac, DelayTime::create(0.5f), ac, NULL);
			this->runAction(seq);
		}
		
		if (patnum == 5)
		{
			Sprite * Ani = Sprite::create();
			Ani->setPosition(Vec2(700, 360));
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

void M_Crab::m_setOpacity()
{
	Crab->setOpacity(255);
	if (HandDead == false)
	{
		SmallHand->setOpacity(255);
		BigHand->setOpacity(255);
	}
	if (LegDead == false)
	{
		LeftLeg->setOpacity(255);
		RightLeg->setOpacity(255);
	}
}

void M_Crab::m_setOpacityLaw()
{
	if (HandDead == true)
	{
		SmallHand->setOpacity(0);
		BigHand->setOpacity(0);
	}
	if (LegDead == true)
	{
		LeftLeg->setOpacity(0);
		RightLeg->setOpacity(0);
	}
}

void M_Crab::m_setOpacity_T()
{
	Crab->setOpacity(255);
	if (HandDead == false)
	{
		SmallHand->setOpacity(255);
		BigHand->setOpacity(255);
	}
	if (LegDead == false)
	{
		LeftLeg->setOpacity(255);
		RightLeg->setOpacity(255);
	}
	AudioEngine::play2d("sound/effect/crab_up.mp3", false, Volume);
	BodyMother->setPosition(Vec2(0, 0));
	FrontMother->setPosition(Vec2(-80, -180));
	BackMother->setPosition(Vec2(-75, 30));
}

void M_Crab::m_setOpacityLaw_T()
{
	AudioEngine::play2d("sound/effect/crab_hide.mp3", false, Volume);
	Crab->setOpacity(0);
	SmallHand->setOpacity(0);
	BigHand->setOpacity(0);
	LeftLeg->setOpacity(0);
	RightLeg->setOpacity(0);

	BodyMother->setPosition(Vec2(8000, 8000));
	FrontMother->setPosition(Vec2(8000, 8000));
	BackMother->setPosition(Vec2(8000, 8000));
}

void M_Crab::m_shoot()
{
	MonsterMissail * MM = MonsterMissail::m_create(Mother->getPosition(), MonLayer, SubPos, 6, 0);//sdfasfa
	MonLayer->addChild(MM,100);
	mVec->pushBack(MM);
}

void M_Crab::m_removeBigHand()
{
	v_earsequake.eraseObject(v_earsequake.front());
}

void M_Crab::m_removeSmallHand()
{
	
	v_shildmake.eraseObject(v_shildmake.front());
}

void M_Crab::m_removeSmog()
{
	v_smog.eraseObject(v_smog.front());
}

void M_Crab::m_BoomHand()
{
	Sprite * Ani = Sprite::create();
	Ani->setPosition(BigHand->getPositionX() + 100, BigHand->getPositionY()+30);
	FrontMother->addChild(Ani);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 5; i++)
	{
		sprintf(str1, "handboom%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);


	Ani->runAction(seq);
}

void M_Crab::m_BoomLeg()
{
	Sprite * Left = Sprite::create();
	Left->setPosition(Vec2(LeftLeg->getPositionX()+30, LeftLeg->getPositionY()+80));
	BackMother->addChild(Left);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 6; i++)
	{
		sprintf(str1, "leftlegboom%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.15, 1);

	Animate * animate = Animate::create(ani);

	auto * seq = Sequence::create(DelayTime::create(0.45),animate, RemoveSelf::create(), NULL);


	Left->runAction(seq);






	Sprite * Right = Sprite::create();
	Right->setPosition(Vec2(RightLeg->getPositionX(), RightLeg->getPositionY()+50));
	FrontMother->addChild(Right);

	Vector<SpriteFrame *>aniFrames;
	char str[256];
	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "rightlegboom%d.png", i);

		SpriteFrame * frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		aniFrames.pushBack(frame);
	}
	Animation * ani1 = Animation::createWithSpriteFrames(aniFrames, 0.15, 1);

	Animate * animate1 = Animate::create(ani1);

	auto * seq1 = Sequence::create(animate1, RemoveSelf::create(), NULL);


	Right->runAction(seq1);


	auto ac1 = MoveBy::create(1.0f, Vec2(0, -150));
	Mother->runAction(EaseIn::create(ac1,2.0));
}

void M_Crab::setbool()
{
	hitBoom = false;
	hitc = false;
}