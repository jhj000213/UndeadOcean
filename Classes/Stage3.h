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
	//!< �� ������ ���� �̱���
	static Scene* createScene();

	//!< �ʱ�ȭ �ϴ� ����
	//!< bool ������ ���� ������ true �� �������� ��ȯ
	//!< false �� ���������� �ȵǾ��� ������ ���� �޽����� ��ȯ�ϱ� ����
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

	//!< ���� ��� ��Ŵ
	CREATE_FUNC(Stage3);
};