#include "stdafx.h"

class cShield
{
private:
	Vec2 vBegan;
	Vec2 vEnd;
	bool isStart;

public:
	Sprite* sprShield;
	bool complete;
	bool isDelete;
	int time;

	float angle;
	float distance;

	void initShield(Node* base);
	void setBeganPoint(Vec2 point);
	void setEndPoint(Vec2 point);

	void makeShield(bool isEnd);
};


class cShieldmanager
{
private:
	Node* Base;	
	int touchIndex;

public:
	
	vector<cShield*> vShield;

	void makeShield(Node* base);

	void BeganPointManager(Vec2 point,int Index);
	void MovedPointManager(Vec2 point,int Index);
	void EndPointManager(Vec2 point, int Index);

	void schedule(float dt);

	void shieldTime(int shieldNum);

	void ShieldRemover(int eraseShield);
	void remover(cShield* shield);
};