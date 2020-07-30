#include "stdafx.h"

class cBarricadeType1 //위아래
{
	int state;//1=위만,2아래만,3둘다

public:
	Sprite* sprBarricadeUp;
	Sprite* sprBarricadeDown;
	
	void initBarricade(Node* base);
	bool checkCollision(Rect boundingBox);
	bool passBarricade();

	void remove(Node* base);
};

class cBarricadeType2
{
public:
	Sprite* sprBarricade;

	void initBarricade(Node* base);
	bool checkCollision(Rect boundingBox);
	bool passBarricade();

	void remove(Node* base);
};

class cBarricadeManager
{
private:
	Node* Base;

	vector<cBarricadeType1*> barricade1;
	vector<cBarricadeType2*> barricade2;

public:
	void makeBarricade(Node* base);

	void randomSpawn();

	bool checkCollision(Rect boundingBox);
};