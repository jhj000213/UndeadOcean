#include "stdafx.h"

class cBullet
{
private:
public:
	Sprite* sprBullet;
	void initenemy(Node* base);

};

class cBulletmanager
{
private:
	vector<cBullet*> vBullet;
	Node* Base;

public:

	void makeBullet(Node* base);
	
	void schedule();

	//패턴들
	void trace(int number,Vec2 subpos);//1번
	void columnDown(int height, int number);//5번
	void columnUp(int height, int number);//6번
	void spray(int height, int number);

	void randomBullet(Vec2 subpos);

	bool checkCollision(Rect boundingBox);
	void passBullet();

	void remove(cBullet* bullet);

};