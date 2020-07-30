#pragma once

#include "stdafx.h"

class JoyStick : public Node
{
private:


	Vec2 F_Touch_Pos;
	Vec2 N_Touch_Pos;
	int TouchF;
public:
	Sprite * JoyStick_under;
	Sprite * JoyStick_top;
	void j_init(Vec2 CPos, Layer * layer);
	Vec2 j_update(Vec2 Pos,float speed);
	void j_startMove(Vec2);
	void j_setOpacity(int num);
	void j_setPosition(Vec2 Pos);

	static JoyStick * n_create(Vec2 CPos, Layer * layer)
	{
		auto ref = new JoyStick();
		ref->j_init(CPos, layer);
		ref->autorelease();

		return ref;
	}
};