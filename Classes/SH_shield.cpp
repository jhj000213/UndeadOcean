#include "stdafx.h"


void cShield::initShield(Node* base)//쉴드 초기화(스프라이트,제거시간,앵커포인트,자식추가)
{
	sprShield = Sprite::create("sh/stick.png");
	time = 200;
	complete = false;
	isDelete = false;
	isStart = false;

	sprShield->setAnchorPoint(Vec2(0, 0.5f));
	base->addChild(sprShield);
}

void cShield::setBeganPoint(Vec2 point)//시작점받아오기
{
	vBegan = point;
}

void cShield::setEndPoint(Vec2 point)//끝점받아오기
{
	vEnd = point;
}

void cShield::makeShield(bool isEnd)//쉴드만들기
{
	//각도구하기
	float dx = vEnd.x - vBegan.x;
	float dy = vEnd.y - vBegan.y;
	float rad = atan2(dy, dx);
	angle = -((rad * 180) / M_PI);

	//거리구하기 
	float x = pow(vEnd.x - vBegan.x, 2);
	float y = pow(vEnd.y - vBegan.y, 2);
	distance = sqrt(x + y);

	if (distance > 200) distance = 200;

	distance *= 0.003;
	if (vBegan.y > vEnd.y)
	{
		if (isStart == true)
		{
			isStart = false;
			sprShield->setFlipY(!sprShield->isFlipY());
		}
		
		if (80 > angle) angle = 80;
		if (angle > 100) angle = 100;
	}
	else
	{
		if (isStart == false)
		{
			isStart = true;
			sprShield->setFlipY(!sprShield->isFlipY());
		}
		if (-80 < angle)angle = -80;
		if (angle < -100) angle = -100;
	}

	if (isEnd)
	{
		sprShield->setOpacity(255);
		sprShield->setPosition(vBegan);
		sprShield->setScaleX(distance);
		sprShield->setRotation(angle);
	}
	else
	{
		sprShield->setOpacity(190);
		sprShield->setPosition(vBegan);
		sprShield->setScaleX(distance);
		sprShield->setRotation(angle);
	}
}


//////////////////////

void cShieldmanager::makeShield(Node* base)//쉴드매니져 초기화
{
	Base = base;
}

void cShieldmanager::BeganPointManager(Vec2 point, int Index)//벡터에 쉴드밀어넣기 , 쉴드 시작점
{
	touchIndex = Index;

	if (point.x > D_DESIGN_WIDTH/2)
	{
		if (vShield.size() < 3)//AAAA
		{
			auto shield = new cShield;

			shield->initShield(Base);
			shield->setBeganPoint(point);

			vShield.push_back(shield);
		}
	}
}

void cShieldmanager::MovedPointManager(Vec2 point, int Index)//쉴드 움직임
{
	if (point.x > 500 && touchIndex == Index)
	{
		if (!vShield.empty())
		{
			if (!vShield.back()->complete)
			{
				auto shield = vShield.back();
				shield->setEndPoint(point);
				shield->makeShield(false);
			}
		}
	}
}
void cShieldmanager::EndPointManager(Vec2 point, int Index)//쉴드 끝
{
	if (point.x > 500 && touchIndex == Index)
	{
		if (!vShield.empty())
		{
			if (!vShield.back()->complete)
			{
				auto shield = vShield.back();
				shield->setEndPoint(point);
				shield->makeShield(true);
				shield->complete = true;
			}
		}
	}
}

void cShieldmanager::shieldTime(int shieldNum)//데미지 입히는 부분
{

	if (vShield.back()->complete)
	{
		auto shield = vShield.at(shieldNum);

		shield->time -= 50;

		shield->sprShield->runAction(Sequence::create(FadeTo::create(0.1, 100), FadeTo::create(0.2, 225), NULL));
	}
	
}

void cShieldmanager::schedule(float dt)//시간제한을 위한 스케줄
{
	for (int i = 0; i < vShield.size(); i++)
	{
		auto shield = vShield.at(i);

		if (shield->complete)
			vShield.at(i)->time--;

		if (shield->time < 0)
		{
			ShieldRemover(i);
		}
	}
}

void cShieldmanager::ShieldRemover(int eraseShield)
{
	if (!vShield.at(eraseShield)->isDelete)
	{
		auto shield = vShield.at(eraseShield);

		shield->complete = false;
		shield->isDelete = true;

		auto animation = Animation::create();
		char str[100] = { 0, };
		for (int i = 0; i < 11; i++)
		{
			sprintf(str, "sh/shildbreak/shieldbreak%d.png", i);
			animation->addSpriteFrameWithFile(str);
		}
		animation->setDelayPerUnit(0.05f);
		auto animate = Animate::create(animation);

		auto removeSeq = Sequence::create(animate, CallFunc::create(CC_CALLBACK_0(cShieldmanager::remover, this, shield)), NULL);
		shield->sprShield->runAction(removeSeq);

		vShield.erase(vShield.begin() + eraseShield);
	}
}

void cShieldmanager::remover(cShield* shield)
{
	Base->removeChild(shield->sprShield, true);
	
	delete shield;
}