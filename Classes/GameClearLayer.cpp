#include "stdafx.h"

void GameClearLayer::m_create(Node * chi,int torpedonum,int score,int maxscore,float time,int item1info,int item2info,int item1num,int item2num)
{
	n_Score = score;
	n_MaxScore = maxscore;

	n_timeScoreMax = 200.0 - time;
	n_timeScore = 200.0 - time;

	n_torpedoNum = torpedonum;
	n_torpedoScore = n_torpedoNum * 10000;
	n_torpedoScoreMax = n_torpedoScore;


	n_Item1Num = item1num;
	n_Item2Num = item2num;

	n_Item1Info = item1info;
	n_Item2Info = item2info;

	Par = chi;
	Table = Layer::create();
	Table->setAnchorPoint(Vec2(0, 0));
	Table->setPosition(0, 0);
	chi->addChild(Table);

	Black = Sprite::create("black.png");
	Black->setOpacity(0);
	Black->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	Table->addChild(Black);

	auto fadet = FadeTo::create(0.5f, 125);
	auto fade = FadeTo::create(0.5f, 0);
	auto seqe = Sequence::create(fadet, DelayTime::create(8.0f), fade, NULL);
	Black->runAction(seqe);



	TableSpr = Sprite::create("gameclear/table.png");
	TableSpr->setPosition(Vec2(D_DESIGN_WIDTH / 2, 1200));
	Table->addChild(TableSpr);

	Vec2 Pos[3] = { Vec2(540,530), Vec2(640,490), Vec2(740,530) };
	for (int i = 0; i < 3; i++)
	{
		GrayGir[i] = Sprite::create("gameclear/graygir.png");
		GrayGir[i]->setPosition(Pos[i]);
		GrayGir[i]->setOpacity(0);
		Table->addChild(GrayGir[i]);

		WhiteGir[i] = Sprite::create("gameclear/whitegir.png");
		WhiteGir[i]->setPosition(Pos[i]);
		WhiteGir[i]->setOpacity(0);
		Table->addChild(WhiteGir[i], 1);
	}

	Coin = Sprite::create("gameclear/coin.png");
	Coin->setOpacity(0);
	Coin->setPosition(Vec2(500,220));
	Table->addChild(Coin);

	Missail = Sprite::create("gameclear/missail.png");
	Missail->setOpacity(0);
	Missail->setPosition(Vec2(500, 325));
	Table->addChild(Missail);

	Score = Sprite::create("gameclear/score.png");
	Score->setOpacity(0);
	Score->setPosition(Vec2(520, 425));
	Table->addChild(Score);

	Time = Sprite::create("gameclear/time.png");
	Time->setOpacity(0);
	Time->setPosition(Vec2(500, 375));
	Table->addChild(Time);

	Complete = Sprite::create("gameclear/msicom0.png");
	Complete->setPosition(Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	Complete->setOpacity(0);
	Table->addChild(Complete);


	
	TimeL = LabelBMFont::create("", "fonts/editfont.fnt");
	TimeL->setPosition(Vec2(700,375));
	TimeL->setOpacity(0);
	Table->addChild(TimeL);

	ScoreL = LabelBMFont::create("", "fonts/editfont.fnt");
	ScoreL->setPosition(Vec2(700,425));
	ScoreL->setOpacity(0);
	Table->addChild(ScoreL);

	TorpedoNumL = LabelBMFont::create("", "fonts/editfont.fnt");
	TorpedoNumL->setPosition(Vec2(550, 325));
	TorpedoNumL->setOpacity(0);
	TorpedoNumL->setScale(0.7f);
	Table->addChild(TorpedoNumL);

	TorpedoScoreL = LabelBMFont::create("", "fonts/editfont.fnt");
	TorpedoScoreL->setPosition(Vec2(700, 325));
	TorpedoScoreL->setOpacity(0);
	Table->addChild(TorpedoScoreL);

	CoinL = LabelBMFont::create("", "fonts/editfont.fnt");
	CoinL->setPosition(Vec2(700, 220));
	CoinL->setOpacity(0);
	Table->addChild(CoinL);

	Item1NumL = LabelBMFont::create("", "fonts/editfont.fnt");
	Item1NumL->setPosition(Vec2(550,150));
	Item1NumL->setOpacity(0);
	Item1NumL->setScale(0.7f);
	Table->addChild(Item1NumL);

	Item2NumL = LabelBMFont::create("", "fonts/editfont.fnt");
	Item2NumL->setPosition(Vec2(700, 150));
	Item2NumL->setOpacity(0);
	Item2NumL->setScale(0.7f);
	Table->addChild(Item2NumL);



	auto ac = CallFunc::create(CC_CALLBACK_0(GameClearLayer::addtimeScore, this));
	auto seq1 = Sequence::create(DelayTime::create(4.5f),CallFunc::create(CC_CALLBACK_0(GameClearLayer::clearnumsound,this)),
		ac, DelayTime::create(0.1f),
		ac, DelayTime::create(0.1f),
		ac, DelayTime::create(0.1f),
		ac, DelayTime::create(0.1f),
		ac, DelayTime::create(0.1f),
		ac, DelayTime::create(0.1f),
		ac, DelayTime::create(0.1f),
		ac, DelayTime::create(0.1f),
		ac, DelayTime::create(0.1f),
		ac, NULL);
	this->runAction(seq1);
	auto ac1 = CallFunc::create(CC_CALLBACK_0(GameClearLayer::addtorpedoScore, this));
	auto seq2 = Sequence::create(DelayTime::create(4.5f),
		ac1, DelayTime::create(0.1f),
		ac1, DelayTime::create(0.1f),
		ac1, DelayTime::create(0.1f),
		ac1, DelayTime::create(0.1f),
		ac1, DelayTime::create(0.1f),
		ac1, DelayTime::create(0.1f),
		ac1, DelayTime::create(0.1f),
		ac1, DelayTime::create(0.1f),
		ac1, DelayTime::create(0.1f),
		ac1, NULL);
	this->runAction(seq2);


	m_actioninit();


	random_device numrand;
	mt19937 Engine(numrand()); // 엔진에 시드를 세팅.
	std::uniform_int_distribution<> dist(30,50);
	auto Num = dist(Engine);
	n_Coin = Num;

	n_time = 0.15f;
	nowFrame = 0;
	girscore = 0;
}

void GameClearLayer::m_actioninit()
{


	auto tablemove = MoveTo::create(1.0f, Vec2(D_DESIGN_WIDTH / 2, D_DESIGN_HEIGHT / 2));
	auto seq1 = Sequence::create(DelayTime::create(0.9f),CallFunc::create(CC_CALLBACK_0(GameClearLayer::tablesound,this)), EaseIn::create(tablemove, 4.0f), NULL);
	TableSpr->runAction(seq1);

	auto fadeo = FadeIn::create(0.5f);
	auto seq2 = Sequence::create(DelayTime::create(1.9f), fadeo, NULL);
	Score->runAction(seq2);

	auto seq3 = Sequence::create(DelayTime::create(2.2f), fadeo, NULL);
	Time->runAction(seq3);

	auto seq4 = Sequence::create(DelayTime::create(2.5f), fadeo, NULL);
	Missail->runAction(seq4);

	auto seq5 = Sequence::create(DelayTime::create(2.8f), fadeo, NULL);
	Coin->runAction(seq5);

	//
	auto call = CallFunc::create(CC_CALLBACK_0(GameClearLayer::m_setGir, this));
	auto seq6 = Sequence::create(DelayTime::create(4.0f), call, NULL);
	this->runAction(seq6);

	setScore();
	setTime();
	setTorpedoScore();
	setCoin();
	setItem();
	
}

void GameClearLayer::m_update(float dt)
{
	
	char Timestr[256];
	sprintf(Timestr, "%.0f", n_timeScore);
	TimeL->setString(Timestr);

	char Torpedostr[256];
	sprintf(Torpedostr, "%d", n_torpedoScore);
	TorpedoScoreL->setString(Torpedostr);

	char TorpedoNumstr[256];
	sprintf(TorpedoNumstr, "x %d", n_torpedoNum);
	TorpedoNumL->setString(TorpedoNumstr);

	char Coinstr[256];
	sprintf(Coinstr, "%d", n_Coin);
	CoinL->setString(Coinstr);

	char Scorestr[256];
	sprintf(Scorestr, "%d", n_Score);
	ScoreL->setString(Scorestr);

	char Item1str[256];
	sprintf(Item1str, "x %d", n_Item1Num);
	Item1NumL->setString(Item1str);

	char Item2str[256];
	sprintf(Item2str, "x %d", n_Item2Num);
	Item2NumL->setString(Item2str);

	n_time -= dt;
	if (n_time <= 0.0f)
	{
		n_time = 0.15f;
		nowFrame++;
		if (nowFrame == 3)
			nowFrame = 2;
		char str[256];
		sprintf(str, "gameclear/msicom%d.png", nowFrame);
		Complete->setTexture(str);
	}
}

void GameClearLayer::addtimeScore()
{
	float score = n_timeScoreMax / 10.0;
	n_timeScore -= score;

	if (n_timeScore < 0)
		n_timeScore = 0;

	n_Score += score;
}

void GameClearLayer::addtorpedoScore()
{
	int score = n_torpedoScoreMax / 10;
	n_torpedoScore -= score;

	if (n_torpedoScore < 0)
		n_torpedoScore = 0;

	n_Score += score;
}

void GameClearLayer::setScore()
{
	auto ac = FadeIn::create(0.4f);
	auto seq = Sequence::create(DelayTime::create(3.5f), ac, NULL);

	ScoreL->runAction(seq);
}

void GameClearLayer::setTime()
{
	auto ac = FadeIn::create(0.4f);
	auto seq = Sequence::create(DelayTime::create(3.7f), ac, NULL);

	TimeL->runAction(seq);
}

void GameClearLayer::setTorpedoScore()
{
	auto ac = FadeIn::create(0.4f);
	auto seq = Sequence::create(DelayTime::create(3.9f), ac, NULL);
	auto ac1 = FadeIn::create(0.4f);
	auto seq1 = Sequence::create(DelayTime::create(3.9f), ac1, NULL);

	TorpedoNumL->runAction(seq);
	TorpedoScoreL->runAction(seq1);
}

void GameClearLayer::setCoin()
{
	auto ac = FadeIn::create(0.4f);
	auto seq = Sequence::create(DelayTime::create(4.1f), ac, NULL);

	CoinL->runAction(seq);
}

void GameClearLayer::setItem()
{
	auto ac = FadeIn::create(0.4f);
	auto seq = Sequence::create(DelayTime::create(4.3f), ac, NULL);
	auto ac1 = FadeIn::create(0.4f);
	auto seq1 = Sequence::create(DelayTime::create(4.3f), ac1, NULL);

	Item1NumL->runAction(seq);

	Item2NumL->runAction(seq1);
}

void GameClearLayer::m_setGir()
{
	girscore = 1;
	if (n_MaxScore / 3 < n_Score)
		girscore = 2;
	if ((n_MaxScore / 3)*2 < n_Score)
		girscore = 3;

	for (int i = 0; i < girscore; i++)
	{
		auto Fad = FadeIn::create(0.45f);
		WhiteGir[i]->runAction(Fad);

		
	}
	for (int i = 0; i < 3; i++)
	{
		auto Fad1 = FadeIn::create(0.45f);
		GrayGir[i]->runAction(Fad1);
	}
}


void GameClearLayer::clearnumsound()
{
	AudioEngine::play2d("sound/effect/clear_num.mp3", false, Volume);
}

void GameClearLayer::tablesound()
{
	AudioEngine::play2d("sound/effect/clear_table.mp3", false, Volume);
}