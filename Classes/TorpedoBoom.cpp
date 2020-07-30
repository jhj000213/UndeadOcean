#include "stdafx.h"

#define MAX_TIME 0.15f
#define DELAY_TIME 0.45f;
void TorpedoBoom::m_init(Vec2 Pos, Vector<TorpedoBoom*> *vec)
{
	Mother = Sprite::create("submarin/animation/boomhit.png");
	Mother->setOpacity(0);
	Mother->setPosition(Pos);
	this->addChild(Mother);

	auto ac = CallFunc::create(CC_CALLBACK_0(TorpedoBoom::removeself, this));
	auto seq = Sequence::create(DelayTime::create(1.5f), ac,RemoveSelf::create(), NULL);
	Mother->runAction(seq);

	p = vec;
	m_time = MAX_TIME;
	m_delaytime = DELAY_TIME;
	m_hit = false;
	changeFrame = false;
	nowFrame = 0;
	BoomNum = 0;

	boomeff();
}

void TorpedoBoom::m_update(float dt)
{

}

void TorpedoBoom::m_sollision()
{
}

bool TorpedoBoom::m_sollisionCheck()
{
	return true;
}

Rect TorpedoBoom::m_getRect()
{
	Rect mrect = Rect(
		Mother->getPositionX() - Mother->boundingBox().size.width / 2,
		Mother->getPositionY() - Mother->boundingBox().size.height / 2,
		Mother->boundingBox().size.width,
		Mother->boundingBox().size.height);
	return mrect;
}

void TorpedoBoom::m_Dmg(int dmg)
{
	
}
void TorpedoBoom::removeself()
{
	p->eraseObject(this);
}

Vec2 TorpedoBoom::m_getPosition()
{
	return Mother->getPosition();
}

void TorpedoBoom::boomeff()
{
	auto ac = CallFunc::create(CC_CALLBACK_0(TorpedoBoom::boomeff_1, this));
	auto de = DelayTime::create(0.15f);
	auto seq = Sequence::create(ac, de, ac, de, ac, de, ac, de, ac, de, ac, NULL);
	this->runAction(seq);
}

void TorpedoBoom::boomeff_1()
{
	AudioEngine::play2d("sound/effect/torpedo_boom.mp3", false, Volume);
	random_device numrand;
	mt19937 Engine(numrand()); // 엔진에 시드를 세팅.
	std::uniform_real_distribution<> dist(0.0f, 359.0f);
	auto Num = dist(Engine);

	Vec2 Pos[6] = { Vec2(340, 310), Vec2(185, 340), Vec2(230, 290), Vec2(290, 210), Vec2(285, 275), Vec2(160, 200) };
	
	Sprite * n_boom = Sprite::create();
	n_boom->setScale(1.0);
	n_boom->setRotation(Num);
	n_boom->setPosition(Pos[BoomNum]);
	Mother->addChild(n_boom,1000);

	Vector<SpriteFrame *>aniFrames1;
	char str1[256];
	for (int i = 1; i < 4; i++)
	{
		sprintf(str1, "boom_%d.png", i);

		SpriteFrame * frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1);
		aniFrames1.pushBack(frame1);
	}
	Animation * ani = Animation::createWithSpriteFrames(aniFrames1, 0.09f, 1);

	Animate * animate = Animate::create(ani);
	auto * seq = Sequence::create(animate, RemoveSelf::create(), NULL);

	n_boom->runAction(seq);

	BoomNum++;
}