#pragma once

#include "stdafx.h"

class Stage3 : public Layer
{
private:
	EventListenerTouchAllAtOnce *listener;

	Layer * UILayer;

	cSubmarine* player;
	cShieldmanager* shield;
	cBulletmanager* bullet;
	cBarricadeManager* barricade;

	Sprite * PauseButton;
	Vector<PauseLayer*> v_PauseLayer;
	Vector<GameClearLayer*> v_GameClear;

	bool isPlayerMove;
	bool n_pause;
	bool n_GameClear;
	bool n_End;
	float PlayTime;
public:
	//!< 씬 생성에 대한 싱글톤
	static Scene* createScene();

	//!< 초기화 하는 구문
	//!< bool 형으로 만든 이유는 true 면 정상적인 반환
	//!< false 면 정상적으로 안되었기 때문에 오류 메시지를 반환하기 위함
	virtual bool init();

	void spawnBarricade(float dt);
	void spawnBullet(float dt);
	void Update(float dt);
	void GAmeClearAndScene();
	void pauseRecursive(Node * _node, bool _pause);
	//void spawnBullet(float dt);

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);

	//!< 씬을 등록 시킴
	CREATE_FUNC(Stage3);
};