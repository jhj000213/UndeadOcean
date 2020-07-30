#include "stdafx.h"

void PauseLayer::m_create(Node * chi)
{
	Par = chi;
	Table = Layer::create();
	Table->setAnchorPoint(Vec2(0,0));
	Table->setPosition(0,0);
	chi->addChild(Table,9999);

	TableSpr = Sprite::create("pause/table.png");
	TableSpr->setAnchorPoint(Vec2(0, 0));
	Table->addChild(TableSpr, 9999);

	ResumeButton = Sprite::create("pause/resume.png");
	ResumeButton->setPosition(Vec2(1080, 600));
	Table->addChild(ResumeButton, 9999);

	ReStart = Sprite::create("pause/restart.png");
	ReStart->setPosition(Vec2(1080, 500));
	Table->addChild(ReStart, 9999);

	MainButton = Sprite::create("pause/main.png");
	MainButton->setPosition(Vec2(1080, 400));
	Table->addChild(MainButton, 9999);

	SoundButton = Sprite::create("pause/sound.png");
	SoundButton->setPosition(1011 + (Volume*224), 102);
	Table->addChild(SoundButton, 9999);
}

void PauseLayer::m_resume()
{
	Par->removeChild(Table,true);
}

int PauseLayer::m_update(Vec2 touchPos)
{
	if (ResumeButton->boundingBox().containsPoint(touchPos))
	{
		m_resume();
		return 1;
	}
	else if (MainButton->boundingBox().containsPoint(touchPos))
	{

		return 2;
	}
	else if (ReStart->boundingBox().containsPoint(touchPos))
	{

		return 3;
	}
	return 0;
}

void PauseLayer::m_moveupdate(Vec2 touchPos)
{
	if (touchPos.x<1250.0f&&
		touchPos.x>1000.0f&&
		touchPos.y>50.0f&&
		touchPos.y<200.0f)
	{

		if (touchPos.x < 1011.0f)
			touchPos.x = 1011.0f;
		if (touchPos.x > 1235.0f)
			touchPos.x = 1235.0f;

		Volume = ((touchPos.x - 1011.0f)) / 224.0f;
		EffVolume = Volume*0.6f;
		UserDefault::getInstance()->setFloatForKey("Volume", Volume);
		//log("%f vol", Volume);
		for (int i = 0; i < BGM_SOUND_NUM; i++)
		{
			AudioEngine::setVolume(Bgm_Sound[i], Volume);
		}
		//EffectVolume
	}
	SoundButton->setPositionX(1011 + (Volume*224));
	if (SoundButton->getPositionX()<1011.0f)
		SoundButton->setPositionX(1011.0f);

	if (SoundButton->getPositionX()>1235.0f)
		SoundButton->setPositionX(1235.0f);
}