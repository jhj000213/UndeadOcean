#include "stdafx.h"

bool isTouchCircle(Point pos, Point center, float radius)
{
	float dx = (pos.x - center.x);
 	float dy = (pos.y - center.y);
 	return (radius >= sqrt((dx*dx) + (dy*dy)));
}


void JoyStick::j_init(Vec2 CPos, Layer * layer)
{
	F_Touch_Pos = CPos;
	JoyStick_under = Sprite::create("joystick_under.png");
	JoyStick_under->setScale(1.5f);
	JoyStick_under->setPosition(F_Touch_Pos);
	layer->addChild(JoyStick_under,10);

	JoyStick_top = Sprite::create("joystick_top.png");
	JoyStick_top->setScale(1.5f);
	JoyStick_top->setPosition(F_Touch_Pos);
	layer->addChild(JoyStick_top,10);
}

Vec2 JoyStick::j_update(Vec2 Pos, float speed)
{
	Vec2 SomePos;
	N_Touch_Pos = Pos;


	JoyStick_top->setPosition(N_Touch_Pos);
	                         
	if (!(isTouchCircle(N_Touch_Pos, JoyStick_under->getPosition(), JoyStick_under->getContentSize().width*1.5 / 2)))
	{
			// 터치 위치값 
		float limitSize = JoyStick_under->getContentSize().width *1.5 / 2;	// 제한 범위의 반지름 


		float dX = N_Touch_Pos.x - JoyStick_under->getPosition().x;
		float dY = N_Touch_Pos.y - JoyStick_under->getPosition().y;

		float distance = sqrt(dX*dX + dY*dY);	// 대각선 길이 구하기 
		float angle = atan2(dY, dX);			// 각도 구하기 

		if (distance > limitSize){
			dX = cos(angle) * limitSize;
			dY = sin(angle) * limitSize;
		}


		if (distance > JoyStick_top->getContentSize().width / 2)
		{
			N_Touch_Pos.x = JoyStick_under->getPosition().x + dX;
			N_Touch_Pos.y = JoyStick_under->getPosition().y + dY;
		}
		JoyStick_top->setPosition(N_Touch_Pos);
		
	}
	else
	{
		JoyStick_top->setPosition(N_Touch_Pos);
	}
		
	//JoyStick_top->setPosition(Pos);

	SomePos.x = (speed * (N_Touch_Pos.x - F_Touch_Pos.x)) / 15.0f;
	SomePos.y = (speed * (N_Touch_Pos.y - F_Touch_Pos.y)) / 15.0f;
	//log("%f %f", SomePos.x, SomePos.y);
	return SomePos;
	
}

void JoyStick::j_setOpacity(int num)
{
	JoyStick_under->setOpacity(num);
	JoyStick_top->setOpacity(num);
}

void JoyStick::j_setPosition(Vec2 Pos)
{
	JoyStick_under->setPosition(Pos);
	JoyStick_top->setPosition(Pos);
}

void JoyStick::j_startMove(Vec2 Pos)
{
	F_Touch_Pos = Pos;
}

