#include "stdafx.h"

#define MAX_TIME 0.10f
#define DELAY_TIME 0.45f
#define PAT_DELAY_TIME 4.0f
void M_middleShip::m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<M_MiniOb*> *mv)
{
	M_HP = 2000;

	Mother = Sprite::create("enemy/middleship/midium/midiumhit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	m_HPbar = MonsterHP::m_create(Vec2(120, 300), Mother, 2000);
	Mother->addChild(m_HPbar);

	middleShip = Sprite::create("enemy/middleship/midium/midium0.png");
	middleShip->setPosition(Vec2(290, 145));
	Mother->addChild(middleShip);

	MonLayer = layer;
	p = vec;
	mp = mv;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_patdelaytime = PAT_DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	hitBoom = false;
	moveup = 1;//		1  /  -1
	nowFrame = 0;
	MN = 0;
	UP = 1;
	BubbleTime = 0.0f;

	auto ac = MoveBy::create(3.0f, Vec2(-500, 0));
	Mother->runAction(ac);
}

void M_middleShip::m_update(float dt,int path)
{
	m_HPbar->hp_update(M_HP);

	//log("%f", Mother->getPositionX());
	m_time -= dt;
	m_delaytime -= dt;
	m_patdelaytime -= dt;

	float PosY = Mother->getPositionY();
	if (Mother->getPositionY() + Mother->boundingBox().size.height / 2 >= 700)
		moveup = -1;
	if (Mother->getPositionY() - Mother->boundingBox().size.height / 2 <= 80)
		moveup = 1;
	Mother->setPositionY(PosY + 20 * dt * moveup);

	if (v_MSB.empty() == false)
	{
		for (MiddleShip_Boom * msb : v_MSB)
		{
			msb->m_update(dt);
		}
	}

	if (hitBoom == true && hitc == false)
	{
		hitc = true;
		auto ac = CallFunc::create(CC_CALLBACK_0(M_middleShip::setbool, this));
		auto seq = Sequence::create(DelayTime::create(1.6f), ac, NULL);

		this->runAction(seq);
	}

	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 17)//ÇÁ·¹ÀÓ ¼ö
			nowFrame = 0;
		changeFrame = true;
	}


	BubbleTime -= dt;
	if (BubbleTime <= 0.0f)
	{
		BubbleTime = 3.0f;
		MakeBubble();
	}


	if (m_patdelaytime <= 0.0f)
	{
		m_Pattun(path);//
		m_patdelaytime = PAT_DELAY_TIME;
	}




	if (changeFrame == true)
	{
		changeFrame = false;
		if (m_hit == true && m_delaytime <= 0.0f)
		{
			m_delaytime = DELAY_TIME;
			m_hit = false;

			char str[256];
			sprintf(str, "enemy/middleship/midium/midiumwhite.png");
			//Aghi->setTexture(str);

			Sprite * h = Sprite::create(str);
			h->setPosition(middleShip->getPosition());
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
			sprintf(str, "enemy/middleship/midium/midium%d.png", nowFrame);
			middleShip->setTexture(str);
		}
	}
}

void M_middleShip::m_sollision()
{
	m_hit = true;
}

bool M_middleShip::m_sollisionCheck()
{
	return true;
}

Rect M_middleShip::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_middleShip::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void M_middleShip::m_Pattun(int path)
{
	int patnum;

	//patnum = path;
	//patnum = 2;
	patnum = (rand() % 3) + 1;
	//log("%d", patnum);
	if (patnum == 1)//·ùÅº
	{
		AudioEngine::play2d("sound/effect/middleship_rutan.mp3",false,Volume);
		MiddleShip_Boom * MSB = MiddleShip_Boom::m_create(Mother->getPosition(), MonLayer, p);
		MonLayer->addChild(MSB);
		v_MSB.pushBack(MSB);
	}
	else if (patnum == 2)//Èð»Ñ¸®±â
	{
		/*auto ac1 = CallFunc::create(CC_CALLBACK_0(M_middleShip::m_SprinkleShot, this));
		auto seq = Sequence::create(ac1, DelayTime::create(0.2f), ac1, DelayTime::create(0.2f), ac1, DelayTime::create(0.2f), ac1, DelayTime::create(0.2f), ac1, DelayTime::create(0.2f),
			ac1, DelayTime::create(0.2f), ac1, DelayTime::create(0.2f), ac1, DelayTime::create(0.2f), ac1,NULL);
		this->runAction(seq);*/
		m_SprinkleShot();
	}
	else if (patnum == 3)//Àâ¸÷
	{
		m_hachiAni();
		M_MiniOb * Mob = M_MiniOb::m_create(Vec2(Mother->getPosition().x, Mother->getPosition().y - 150), MonLayer, p,mp,1);
		MonLayer->addChild(Mob);
		mp->pushBack(Mob);
	}

}

void M_middleShip::m_SprinkleShot()
{
	for (int i = 0; i < 5; i++)
	{
		MonsterMissail * Missail = MonsterMissail::m_create(Mother->getPosition(), this, Vec2(0, 0), 3, i);
		MonLayer->addChild(Missail);
		p->pushBack(Missail);
	}


	/*MonsterMissail * Missail = MonsterMissail::m_create(Mother->getPosition(), this, Vec2(0, 0), 3, MN);
	MonLayer->addChild(Missail);
	p->pushBack(Missail);

	if (MN == 4)
	{
		UP = -1;
	}
	if (MN == 0)
		UP = +1;

	MN += UP;*/
}

void M_middleShip::m_hachiAni()
{
	Sprite * Hachi = Sprite::create();
	Hachi->setAnchorPoint(Vec2(0.5, 1));
	Hachi->setPosition(Vec2(260, 20));
	Mother->addChild(Hachi);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 5; i++)
	{
		sprintf(str1, "hechi%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.13f, 1);

	Animate * animate = Animate::create(ani);
	auto ac1 = FadeOut::create(0.5f);

	auto * seq = Sequence::create(animate,ac1,RemoveSelf::create(), NULL);


	Hachi->runAction(seq);
}

void M_middleShip::setbool()
{
	hitBoom = false;
	hitc = false;
}

void M_middleShip::MakeBubble()
{
	Sprite * bub = Sprite::create();
	bub->setPosition(Vec2(0, 0));
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