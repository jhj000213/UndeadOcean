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

	//���ϵ�
	void trace(int number,Vec2 subpos);//1��
	void columnDown(int height, int number);//5��
	void columnUp(int height, int number);//6��
	void spray(int height, int number);

	void randomBullet(Vec2 subpos);

	bool checkCollision(Rect boundingBox);
	void passBullet();

	void remove(cBullet* bullet);

};