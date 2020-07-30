#include "stdafx.h"

void CPNCamera::init(cocos2d::Layer *pTargetLayer, cocos2d::Size mapSize, cocos2d::Size screenSize)
{
	m_pTargetLayer = pTargetLayer;

	m_mapSize = mapSize;

	m_screenSize = screenSize;
}

void CPNCamera::update(float dx)
{
	cocos2d::Vec2 mapPos;

	
		mapPos.x = dx;
	

	m_pTargetLayer->setPosition(-mapPos);
}