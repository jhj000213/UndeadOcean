#include "stdafx.h"

#define MAX_TIME 0.10f
#define DELAY_TIME 0.45f
#define PAT_DELAY_TIME 5.0f
void M_BigRobot::m_init(Vec2 Pos, Layer * layer, Vector<MonsterMissail*> *vec, Vector<MonsterRazer*> *mv, Vector<Robot_Missail*> *rv)
{
	M_HP = 2500;

	Mother = Sprite::create("enemy/bigrobot/normal/robothit.png");
	Mother->setAnchorPoint(Vec2(0.5, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	m_HPbar = MonsterHP::m_create(Vec2(120, 500), Mother, 2500);
	Mother->addChild(m_HPbar);

	middleShip = Sprite::create("enemy/bigrobot/normal/robot0.png");
	middleShip->setPosition(Vec2(210, 265));
	Mother->addChild(middleShip);


	



	MonLayer = layer;
	p = vec;
	mp = mv;
	rp = rv;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_patdelaytime = PAT_DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	RazerShoot = false;
	hitBoom = false;
	hitc = false;
	moveup = 1;//		1  /  -1
	nowFrame = 0;
	MN = 0;
	UP = 1;
	pat3p = 1;
	BubbleTime = 0.0f;

	Robot_Razer * Razer = Robot_Razer::m_create(Vec2(250,290), layer, mp, &v_RobotRazer, true);
	Mother->addChild(Razer);
	v_RobotRazer.pushBack(Razer);

	Robot_Razer * Razer1 = Robot_Razer::m_create(Vec2(250,250), layer, mp, &v_RobotRazer, false);
	Mother->addChild(Razer1);
	v_RobotRazer.pushBack(Razer1);

	auto ac = MoveBy::create(3.0f, Vec2(-500, 0));
	Mother->runAction(ac);
}

void M_BigRobot::m_update(float dt,int path)
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

	if (v_RobotRazer.empty() == false)
	{
		for (Robot_Razer * msb : v_RobotRazer)
		{
			msb->m_update(dt,RazerShoot);
		}
		if (RazerShoot == true)
			RazerShoot = false;
	}

	if (hitBoom == true && hitc == false)
	{
		hitc = true;
		auto ac = CallFunc::create(CC_CALLBACK_0(M_BigRobot::setbool, this));
		auto seq = Sequence::create(DelayTime::create(1.6f), ac, NULL);

		this->runAction(seq);
	}

	if (m_time <= 0.0f)
	{
		m_time = MAX_TIME;
		nowFrame++;
		if (nowFrame == 6)//프레임 수
			nowFrame = 0;
		changeFrame = true;
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
			sprintf(str, "enemy/bigrobot/normal/robotwhite.png");
			//Aghi->setTexture(str);

			Sprite * h = Sprite::create(str);
			h->setPosition(middleShip->getPositionX()-30, middleShip->getPositionY());
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
			sprintf(str, "enemy/bigrobot/normal/robot%d.png", nowFrame);
			middleShip->setTexture(str);
		}
	}


	BubbleTime -= dt;
	if (BubbleTime <= 0.0f)
	{
		BubbleTime = 3.5f;
		MakeBubble();
	}
}

void M_BigRobot::m_sollision()
{
	m_hit = true;
}

bool M_BigRobot::m_sollisionCheck()
{
	return true;
}

Rect M_BigRobot::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void M_BigRobot::m_Dmg(int dmg)
{
	M_HP -= dmg;
}

void M_BigRobot::m_Pattun(int path)
{
	int patnum;

	//patnum = path;
	//patnum = 2;
	patnum = (rand() % 3) + 1;
	//log("%d", patnum);
	if (patnum == 1)//미사일
	{
		Robot_Missail * wave = Robot_Missail::m_create(MonLayer ,rp);
		MonLayer->addChild(wave);
		rp->pushBack(wave);

		auto seq = Sequence::create(DelayTime::create(4.0f), RemoveSelf::create(), NULL);
		wave->runAction(seq);
	}
	else if (patnum == 2)//흩뿌리기
	{
		pat3num = 0;
		loo = 0;
		auto ac = CallFunc::create(CC_CALLBACK_0(M_BigRobot::m_SprinkleShot, this));
		auto de = DelayTime::create(0.1f);
		auto seq = Sequence::create(ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, de, ac, NULL);

		this->runAction(seq);
	}
	else if (patnum == 3)//레이저
	{
		RazerShoot = true;
	}

}

void M_BigRobot::m_SprinkleShot()
{


	MonsterMissail * Missail = MonsterMissail::m_create(Mother->getPosition(), this, Vec2(0, 0), 3, pat3num);
	MonLayer->addChild(Missail);
	p->pushBack(Missail);
	pat3num += pat3p;
	loo++;
	if (pat3num == 4)
	{
		pat3p = -1;
	}
	if (pat3num == 0)
	{
		pat3p = 1;
	}
	if (loo == 21)
	{
		pat3num = 0;
		pat3p = 1;
	}

}

M_BigRobot::~M_BigRobot()
{
	v_RobotRazer.eraseObject(v_RobotRazer.front());
	v_RobotRazer.eraseObject(v_RobotRazer.front());
}

Vec2 M_BigRobot::m_getPosition()
{
	return Mother->getPosition();
}

void M_BigRobot::setbool()
{
	hitBoom = false;
	hitc = false;
}

void M_BigRobot::MakeBubble()
{
	Sprite * bub = Sprite::create();
	bub->setPosition(Vec2(-50, 100));
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




	Sprite * bub1 = Sprite::create();
	bub1->setPosition(Vec2(270, 400));
	Mother->addChild(bub1, 1000);

	Vector<SpriteFrame *>aniFrames11;
	char str11[256];
	for (int i = 0; i < 7; i++)
	{
		sprintf(str11, "bub%d.png", i);

		SpriteFrame * frame11 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str11);
		aniFrames11.pushBack(frame11);
	}
	Animation * ani1 = Animation::createWithSpriteFrames(aniFrames11, 0.1f, 1);

	Animate * animate1 = Animate::create(ani1);

	auto * seq1 = Sequence::create(animate1, RemoveSelf::create(), NULL);


	bub1->runAction(seq1);
}