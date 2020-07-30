#include "stdafx.h"

#define MAX_TIME 0.1f
void MonsterRazer::m_init(Vec2 SPos, int MissailInfo,bool tp)
{

	Mother = Sprite::create();
	Mother->setAnchorPoint(Vec2(1, 0.5));
	Mother->setOpacity(0);
	Mother->setPosition(SPos);
	//m_layer = layer;
	this->addChild(Mother, 100);

	Razer = Sprite::create();
	shootsound = false;
	//Razer->setAnchorPoint(Vec2(1, 0.5));
	Mother->addChild(Razer);


	del = false;
	m_RazerInfo = MissailInfo;
	nowFrame = 0;
	if (m_RazerInfo == 1)
	{
		Razer->setPosition(Vec2(450, 93));
		Mother->setTexture("enemy/middleship/razer/razerhit.png");
		Razer->setTexture("enemy/middleship/razer/razer0.png");
		hit.push_back(13);
		hit.push_back(14);
		hit.push_back(15);
		hit.push_back(16);
		hit.push_back(17);
		hit.push_back(18);

	}
	if (m_RazerInfo == 2)
	{
		Razer->setPosition(Vec2(820, 45));
		Mother->setTexture("enemy/japonica/razer/razerhit.png");
		Razer->setTexture("enemy/japonica/razer/danger0.png");
		hit.push_back(16);
		hit.push_back(17);
		loop = 0;

		
	}
	if (m_RazerInfo == 3)
	{
		Razer->setPosition(Vec2(500, 25));
		Mother->setTexture("enemy/bigrobot/razer/razerhit.png");
		Razer->setTexture("enemy/bigrobot/razer/midshoot0.png");
		hit.push_back(10);
		top = tp;
	}
	if (m_RazerInfo == 4)
	{
		Razer->setPosition(Vec2(467, 246));
		Mother->setTexture("enemy/fishhead/breath/breathhit.png");
		Razer->setTexture("enemy/fishhead/breath/breath0.png");
		hit.push_back(7);
		hit.push_back(8);
		hit.push_back(9);
		hit.push_back(10);
		hit.push_back(11);
		hit.push_back(12);
		//hit.push_back(13);
		//hit.push_back(14);
		//hit.push_back(15);

		top = tp;
	}
}

void MonsterRazer::m_update(float dt)
{

	if (m_RazerInfo == 1)
	{
		m_time -= dt;
		m_delaytime -= dt;
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			for (int num : hit)
			{
				if (num == nowFrame)
					solli = true;
				else
					solli = false;
			}
			if (nowFrame == 13)
			{
				AudioEngine::play2d("sound/effect/dragon_razer.mp3", false, Volume);
			}
			if (nowFrame == 22)//프레임 수
			{
				del = true;
				nowFrame = 0;
				Razer->setOpacity(0);
			}
				
			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;


			char str[256];
			sprintf(str, "enemy/middleship/razer/razer%d.png", nowFrame);
			Razer->setTexture(str);

		}
	}
	else if (m_RazerInfo == 2)
	{
		m_time -= dt;
		m_delaytime -= dt;
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			for (int num : hit)
			{
				if (num == nowFrame)
					solli = true;
				else
					solli = false;
			}

			if (nowFrame == 18)//프레임 수
			{
				nowFrame = 16;
				loop++;

				
			}
			if (nowFrame == 16)
			{
				if (shootsound == false)
				{
					AudioEngine::play2d("sound/effect/japonica_shoot.mp3", false, Volume);
					shootsound = true;
				}
			}

			if (loop == 5)
			{
				del = true;
				Razer->setOpacity(0);
			}

			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;


			char str[256];
			sprintf(str, "enemy/japonica/razer/danger%d.png", nowFrame);
			Razer->setTexture(str);

		}
	}
	else if (m_RazerInfo == 3)
	{
		m_time -= dt;
		m_delaytime -= dt;
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 11)//프레임 수
			{
				nowFrame = 10;
				loop++;
			}
			if (loop == 7)
			{
				Razer->setOpacity(0);
				del = true;
			}
			for (int num : hit)
			{
				if (num == nowFrame)
					solli = true;
				else
					solli = false;
			}



			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;


			char str[256];
			sprintf(str, "enemy/bigrobot/razer/midshoot%d.png", nowFrame);
			Razer->setTexture(str);

		}
	}
	else if (m_RazerInfo == 4)
	{
		m_time -= dt;
		m_delaytime -= dt;
		if (m_time <= 0.0f)
		{
			m_time = MAX_TIME;
			nowFrame++;
			if (nowFrame == 19)//프레임 수
			{
				nowFrame = 0;
				Razer->setOpacity(0);
				del = true;
			}
		
			for (int num : hit)
			{
				if (num == nowFrame)
					solli = true;
				else
					solli = false;
			}

			if (nowFrame == 6)
			{
				AudioEngine::play2d("sound/effect/fishhead_breath.mp3", false, Volume / 2);
			}

			changeFrame = true;
		}
		if (changeFrame == true)
		{
			changeFrame = false;


			char str[256];
			sprintf(str, "enemy/fishhead/breath/breath%d.png", nowFrame);
			Razer->setTexture(str);

		}
	}
}

float MonsterRazer::m_getPositionX()
{
	return 0.0f;
}

void MonsterRazer::m_setPosition(Vec2 Pos)
{
	Mother->setPosition(Pos);
}

Rect MonsterRazer::m_getRect()
{
	if (m_RazerInfo == 3)
	{
		Rect mrect = Rect(
			Mother->getPositionX() - Mother->boundingBox().size.width,
			(Mother->getPositionY() - Mother->boundingBox().size.height / 2)+100, 
			Mother->boundingBox().size.width,
			Mother->boundingBox().size.height);
		return mrect;
	}
	else
	{
		Rect mrect = Rect(
			Mother->getPositionX() - Mother->boundingBox().size.width,
			Mother->getPositionY() - Mother->boundingBox().size.height / 2,
			Mother->boundingBox().size.width,
			Mother->boundingBox().size.height);
		return mrect;
	}
	
	
}

void MonsterRazer::m_boomEffect()
{

}

Vec2 MonsterRazer::m_getPosition()
{
	return Mother->getPosition();
}

bool MonsterRazer::m_sollisionCheck()
{
	return solli&&!del;
}

int MonsterRazer::m_getRazerInfo()
{
	return m_RazerInfo;
}