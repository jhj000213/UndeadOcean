#pragma once

#include "cocos2d.h"

class CPNCamera
{
private:
	cocos2d::Layer *m_pTargetLayer;
	cocos2d::Size	m_mapSize;
	bool stopping = false;
	cocos2d::Size	m_screenSize;

public:
	void init(cocos2d::Layer *pTargetLayer, cocos2d::Size mapSize, cocos2d::Size screenSize);

	void update(float dx);
};