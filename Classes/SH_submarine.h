#include "stdafx.h"

class cSubmarine
{
private:
	Node* Base;
	float pointX;
	float pointY;

	int touchIndex;

	bool isMove;

public:
	Sprite* sprSubmarine;
	Sprite* SubmarinePoint;

	void init(Node* base);

	bool touchBegan(Vec2 tp,int index);
	void touchMove(Vec2 tp,int index);
	void touchEnd(Vec2 tp, int index);

	void move();

	void damage();
};