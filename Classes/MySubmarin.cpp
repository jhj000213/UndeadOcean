#include "stdafx.h"

#define TORPEDO_COOL 1.0f
#define BUBBLE_TIME 2.5f
void MySubmarin::n_init(Vec2 CPos, Layer * layer,Vector<TorpedoBoom*> *bp,int airguninfo)
{
	AirgunInfo = airguninfo;
	if (AirgunInfo == 1)//연사형
	{
		TorpedoDamege = 700;
		MissailDamege = 7;
		GLayer = layer;
		ShootDelayTime = 0.1;
		ShootCoolTime = 0.1;
		TorpedoCoolTime = TORPEDO_COOL;

		Sub = Sprite::create();
		Sub->setPosition(CPos);
		GLayer->addChild(Sub, 2);

		Frame = Sprite::create();
		Frame->setAnchorPoint(Vec2(0.5, 0.52));
		Sub->addChild(Frame);

		//=
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 0; i < 4; i++)
		{
			sprintf(str1, "%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.05f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Frame->runAction(CCRepeatForever::create(seq));
		//=



		Hack = Sprite::create("submarin/submarinhitpoint.png");
		Hack->setOpacity(0);
		//Hack->setPosition(Vec2(-70, 10));
		Sub->addChild(Hack, 5);
		HackWidth = 33.0f;
		HitTime = 1.2f;
		s_Speed = 0.0f;
		s_Moving = false;
		Strong = false;

		p = bp;
	}
	else if (AirgunInfo == 4)//확산
	{
		TorpedoDamege = 700;
		MissailDamege = 7;
		GLayer = layer;
		ShootDelayTime = 0.15;
		ShootCoolTime = 0.15;
		TorpedoCoolTime = TORPEDO_COOL;

		Sub = Sprite::create();
		Sub->setPosition(CPos);
		GLayer->addChild(Sub, 2);

		Frame = Sprite::create();
		Frame->setAnchorPoint(Vec2(0.5, 0.52));
		Sub->addChild(Frame);

		//=
		Vector<SpriteFrame *>aniFrames1;
		char str1[256];
		for (int i = 0; i < 12; i++)
		{
			sprintf(str1, "submarin_devil%d.png", i);

			SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
			aniFrames1.pushBack(frame1);
		}
		Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.1f, 1);

		Animate * animate = Animate::create(ani);

		auto * seq = Sequence::create(animate, NULL);


		Frame->runAction(CCRepeatForever::create(seq));
		//=



		Hack = Sprite::create("submarin/submarinhitpoint.png");
		Hack->setOpacity(0);
		//Hack->setPosition(Vec2(-70, 10));
		Sub->addChild(Hack, 5);
		HackWidth = 33.0f;
		HitTime = 1.2f;
		s_Speed = 0.0f;
		BubbleTime = 0.0f;
		s_Moving = false;
		Strong = false;

		p = bp;
	}
	
}

void MySubmarin::n_update(float dt)
{
	if (s_Speed >= 1.0f)
		s_Speed = 1.0f;

	if (TorpedoCoolTime <= 0.0f)
		TorpedoCoolTime = 0.0f;

	ShootCoolTime += dt;
	TorpedoCoolTime -= dt;
	if (ShootDelayTime <= ShootCoolTime)
	{
		ShootCoolTime = 0.0f;
		if (AirgunInfo == 1)
		{
			AudioEngine::play2d("sound/effect/submarin_missail_shoot.mp3", false, EffVolume);

			s_airShoot(Vec2(0, 7),1);
			s_airShoot(Vec2(0, -7),1);
		}
		else if (AirgunInfo == 4)
		{
			AudioEngine::play2d("sound/effect/submarin_missail_shoot.mp3",false, EffVolume);

			s_airShoot(Vec2(0, 7),1);
			s_airShoot(Vec2(0, -7),1);
			s_airShoot(Vec2(0, 14),2);
			s_airShoot(Vec2(0, -14),3);
		}
	}

	BubbleTime -= dt;
	if (BubbleTime <= 0.0f)
	{
		BubbleTime = BUBBLE_TIME;
		MakeBubble();
	}
}

void MySubmarin::s_setPosition(Vec2 Pos)
{
	Sub->setPosition(Pos);

}

void MySubmarin::s_setPositionX(float Pos)
{
	Sub->setPositionX(Pos);

}

void MySubmarin::s_setPositionY(float Pos)
{
	Sub->setPositionY(Pos);

}

Vec2 MySubmarin::s_getPosition()
{
	return Sub->getPosition();
}

bool MySubmarin::s_ScreenSollisionX(float Pos)
{
	if (Pos - Hack->boundingBox().size.width / 2 < 0)
	{
		Sub->setPositionX(0 + Hack->boundingBox().size.width / 2);
		return true;
	}
	else if (Pos + Hack->boundingBox().size.width / 2 > D_DESIGN_WIDTH)
	{
		Sub->setPositionX(D_DESIGN_WIDTH - Hack->boundingBox().size.width / 2);
		return true;
	}

	return false;
}

bool MySubmarin::s_ScreenSollisionY(float Pos)
{
	if (Pos - Hack->boundingBox().size.height / 2 < 0)
	{
		Sub->setPositionY(0 + Hack->boundingBox().size.height / 2);
		return true;
	}
	else if (Pos + Hack->boundingBox().size.height / 2 > D_DESIGN_HEIGHT)
	{
		Sub->setPositionY(D_DESIGN_HEIGHT - Hack->boundingBox().size.height / 2);
		return true;
	}
	return false;
}

void MySubmarin::s_airShoot(Vec2 Pos,int info)
{


		MyMissail * Missail = MyMissail::m_create(Vec2(Sub->getPosition().x + Pos.x, Sub->getPosition().y + Pos.y), GLayer,info);
		AirGun.pushBack(Missail);
	
	
}

bool MySubmarin::s_Torpedo()
{
	if (TorpedoCoolTime <= 0.0f)
	{
		AudioEngine::play2d("sound/effect/torpedo_shoot.mp3", false, Volume);
		TorpedoCoolTime = TORPEDO_COOL;
		MyTorpedo * Torpedo = MyTorpedo::m_create(Sub->getPosition(), GLayer, &v_Torpedo, p, AirgunInfo);
		//GLayer->addChild(Torpedo);
		v_Torpedo.pushBack(Torpedo);
		return true;
	}
	return false;
}

Rect MySubmarin::s_getRect()
{
	Rect re = Rect(Sub->getPosition().x - HackWidth / 2, Sub->getPositionY() - HackWidth / 2, HackWidth, HackWidth);
	return re;
}

void MySubmarin::s_hitting()
{
	Strong = true;
	auto ac = FadeTo::create(0.0f, 0);
	auto ac1 = FadeTo::create(0.0f, 255);
	auto ac2 = CallFunc::create(CC_CALLBACK_0(MySubmarin::s_setStrong, this));
	auto seq = Sequence::create(ac, DelayTime::create(0.25f), ac1, DelayTime::create(0.25f), ac, DelayTime::create(0.25f),
		ac1, DelayTime::create(0.25f), ac, DelayTime::create(0.25f), ac1, DelayTime::create(0.25f), ac2, NULL);
	Frame->runAction(seq);
}

bool MySubmarin::s_getStrong()
{
	return Strong;
}

void MySubmarin::s_setStrong()
{
	Strong = false;
}

void MySubmarin::MakeBubble()
{
	Sprite * bub = Sprite::create();
	bub->setPosition(Vec2(Sub->getPositionX() + -75, Sub->getPositionY() + -15));
	bub->setScale(0.6f);
	GLayer->addChild(bub,1000 );

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

	auto * seq = Sequence::create(animate,RemoveSelf::create(), NULL);


	bub->runAction(seq);




	Sprite * bub1 = Sprite::create();
	bub1->setPosition(Vec2(Sub->getPositionX() + 75, Sub->getPositionY() + 35));
	bub1->setScale(0.6f);
	GLayer->addChild(bub1, 1000);

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