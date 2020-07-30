#pragma once
#include "stdafx.h"

class GameClearLayer : public Node
{
private:
	Node * Par;
	Layer * Table;

	Sprite * TableSpr;
	Sprite * Coin;
	Sprite * Missail;
	Sprite * Score;
	Sprite * Time;
	Sprite * Black;
	Sprite * Complete;

	Sprite * GrayGir[3];
	Sprite * WhiteGir[3];

	LabelBMFont * TimeL;
	LabelBMFont * ScoreL;
	LabelBMFont * TorpedoNumL;
	LabelBMFont * TorpedoScoreL;
	LabelBMFont * CoinL;

	LabelBMFont * Item1NumL;
	LabelBMFont * Item2NumL;

	int n_Score;
	int n_MaxScore;
	float n_timeScore;
	float n_timeScoreMax;
	int n_torpedoNum;
	int n_torpedoScore;
	int n_torpedoScoreMax;
	int n_Coin;
	int n_Item1Num;
	int n_Item1Info;
	int n_Item2Num;
	int n_Item2Info;

	float n_time;
	int nowFrame;
	int girscore;
public:
	void m_create(Node * chi, int torpedonum, int score, int maxscore, float time,  int item1info, int item2info, int item1num, int item2num);
	void m_actioninit();
	
	void m_update(float dt);

	void addtimeScore();
	void addtorpedoScore();
	void setScore();
	void setTime();
	void setTorpedoScore();
	void setCoin();
	void setItem();
	void m_setGir();
	void clearnumsound();
	void tablesound();

	static GameClearLayer * n_create(Node * layer, int torpedonum, int score, int maxscore, float time,  int item1info, int item2info, int item1num, int item2num)
	{
		auto ref = new GameClearLayer();
		ref->m_create(layer,torpedonum,score,maxscore,time,item1info,item2info,item1num,item2num);
		ref->autorelease();

		return ref;
	}
};