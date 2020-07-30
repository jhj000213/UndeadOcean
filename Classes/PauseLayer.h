#pragma once
#include "stdafx.h"

class PauseLayer : public Node
{
private:
	Node * Par;
	Layer * Table;

	Sprite * TableSpr;
	Sprite * ResumeButton;
	Sprite * ReStart;
	Sprite * MainButton;

	Sprite * SoundButton;

public:
	void m_create(Node * layer);
	void m_resume();
	int m_update(Vec2 touchPos);
	void m_moveupdate(Vec2 touchPos);

	static PauseLayer * n_create(Node * layer)
	{
		auto ref = new PauseLayer();
		ref->m_create(layer);
		ref->autorelease();

		return ref;
	}
};